/* 
 *  File: opcua_client.cpp
 *  Copyright (c) 2010-2020, FlexEm Technologies Inc
 *  All rights reserved.
 *  
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted (subject to the limitations in the disclaimer below) provided that
 *  the following conditions are met:
 *  
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *  
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *  
 *  Neither the name of FlexEm Technologies Inc nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without
 *  specific prior written permission.
 *  
 *  NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 *  LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "opcua_client.h"

#ifdef __cplusplus
extern "C" {
#endif

static UA_StatusCode
nodeIter(UA_NodeId childId, UA_Boolean isInverse, UA_NodeId referenceTypeId, void *handle) {
    if(isInverse)
        return UA_STATUSCODE_GOOD;
    UA_NodeId *parent = (UA_NodeId *)handle;
    printf("%d, %d --- %d ---> NodeId %d, %d\n",
           parent->namespaceIndex, parent->identifier.numeric,
           referenceTypeId.identifier.numeric, childId.namespaceIndex,
           childId.identifier.numeric);
    return UA_STATUSCODE_GOOD;
}

static void
handler_TheAnswerChanged(UA_Client *client, UA_UInt32 subId, void *subContext,
                         UA_UInt32 monId, void *monContext, UA_DataValue *value) {
    printf("The Answer has changed!\n");
}

#ifdef __cplusplus
}
#endif

OpcUaClient::OpcUaClient()
{
    client_ = nullptr;
    endpoint_array_ = nullptr;
    endpoint_arraysize_ = 0;
}

OpcUaClient::~OpcUaClient()
{

}

void OpcUaClient::Init()
{
    /* Create a client and init */
    if (client_ == nullptr) {
        client_ = UA_Client_new();
    }
    UA_ClientConfig_setDefault(UA_Client_getConfig(client_));

    InitConnectDescription(connect_description_);
}

bool OpcUaClient::Start()
{
    bool ret;
    UA_StatusCode retval;
    Init();

    // Set connect server by anonymous or certificated.
    connect_description_.anonymous_connect = true;
    ret = Connect();
    if (!ret) {
        LOG(ERROR) << "Opcua client connect failed.";
        return false;
    }

    // Browse the object node.
    UA_BrowseRequest bReq;
    UA_BrowseResponse bResp;

    BrowseObjectsNode(&bReq, &bResp);

    // Close browse the object node.
    UA_BrowseRequest_clear(&bReq);
    UA_BrowseResponse_clear(&bResp);

    // Browse the object node by iterator.
    BrowseObjectsNodeByIterator();

    // Create the subscription.
    SubscriptionDescription subscription_description;
    subscription_description.namespace_index = 1;
    subscription_description.identifier_string = "the.answer";
    subscription_description.publish_request_timeout = 1000;
    subscription_description.cancel_publish_request_timeout = 100;
    ret = CreateSubscription(subscription_description);
    if (!ret) {
        LOG(ERROR) << "Create subscription failed.";
        return false;
    }

    /* Read attribute */
    UA_Int32 value = 0;
    NodeAttributeDescription node_attribute_description;
    // node_attribute_description.get_val_variant = nullptr;
    node_attribute_description.namespace_index = 1;
    node_attribute_description.identifier_string = "the.answer";
    
    GetNodeValue(value, node_attribute_description);
    LOG(INFO) << "Get node value: " << value;

    /* Write node attribute */
    value++;
    SetNodeValueByRequest(value, node_attribute_description);

    value++;
    SetNodeValueByHighlevel(value, node_attribute_description);

    /* Call a remote method */
    MethodCallDescription method_call_description;
    method_call_description.input_msg_string = "Hello Server";
    CallRemoteSeverMethod(method_call_description);

    /* Add New ReferenceType */
    ReferenceTypeDescription reference_type_description;
    reference_type_description.display_name = "NewReference";
    reference_type_description.description = "References something that might or might not exist";
    reference_type_description.inverse_name = "IsNewlyReferencedBy";
    reference_type_description.requested_new_node_id_namespace_index = 1;
    reference_type_description.requested_new_node_id_identifier_numeric = 12133;
    reference_type_description.parent_node_id_namespace_index = 0;
    reference_type_description.parent_node_id_identifier_numeric = UA_NS0ID_ORGANIZES;
    reference_type_description.reference_type_id_namespace_index = 0;
    reference_type_description.reference_type_id_identifier_numeric = UA_NS0ID_HASSUBTYPE;
    reference_type_description.browse_name_id_namespace_index = 1;
    reference_type_description.browse_name_id_name = "NewReference";

    AddNewReferenceType(reference_type_description);

    /* Add New ObjectType */
    ObjectTypeDescription object_type_description;
    object_type_description.display_name = "TheNewObjectType";
    object_type_description.description = "Put innovative description here";
    object_type_description.requested_new_node_id_namespace_index = 1;
    object_type_description.requested_new_node_id_identifier_numeric = 12134;
    object_type_description.parent_node_id_namespace_index = 0;
    object_type_description.parent_node_id_identifier_numeric = UA_NS0ID_BASEOBJECTTYPE;
    object_type_description.reference_type_id_namespace_index = 0;
    object_type_description.reference_type_id_identifier_numeric = UA_NS0ID_HASSUBTYPE;
    object_type_description.browse_name_id_namespace_index = 1;
    object_type_description.browse_name_id_name = "NewObjectType";
    
    AddNewObjectType(object_type_description);

    /* Add New Object */
    ObjectDescription object_description;
    object_description.display_name = "TheNewGreatNode";
    object_description.description = "Hier koennte Ihre Webung stehen!";
    object_description.requested_new_node_id_namespace_index = 1;
    object_description.requested_new_node_id_identifier_numeric = 0;
    object_description.parent_node_id_namespace_index = 0;
    object_description.parent_node_id_identifier_numeric = UA_NS0ID_OBJECTSFOLDER;
    object_description.reference_type_id_namespace_index = 0;
    object_description.reference_type_id_identifier_numeric = UA_NS0ID_ORGANIZES;
    object_description.browse_name_id_namespace_index = 1;
    object_description.browse_name_id_name = "TheGreatNode";
    object_description.type_definition_id_namespace_index = 1;
    object_description.type_definition_id_identifier_numeric = 12134;

    AddNewObject(object_description);

    /* Add New Integer Variable */
    IntegerVariableDescription int_var_description;
    int_var_description.display_name = "TheNewVariableNode";
    int_var_description.description = "This integer is just amazing - it has digits and everything.";
    int_var_description.requested_new_node_id_namespace_index = 1;
    int_var_description.requested_new_node_id_identifier_numeric = 0;
    int_var_description.parent_node_id_namespace_index = 0;
    int_var_description.parent_node_id_identifier_numeric = UA_NS0ID_OBJECTSFOLDER;
    int_var_description.reference_type_id_namespace_index = 0;
    int_var_description.reference_type_id_identifier_numeric = UA_NS0ID_ORGANIZES;
    int_var_description.browse_name_id_namespace_index = 0;
    int_var_description.browse_name_id_name = "VariableNode";

    UA_Int32 int_value;
    int_value = 1234;
    AddNewIntegerVariable(int_value, int_var_description);

    while (1) {
        usleep(500); // 500ms
    }
}

bool OpcUaClient::Connect()
{
    bool ret;
    if (connect_description_.anonymous_connect) {
        // Connect the server by anonymous.
        connect_description_.endpoint_url = "opc.tcp://localhost:4840";
        ret = ConnectByAnonymous();
        if (!ret) {
            return false;
        }
    } else {
        // Connect the server by certificated.
        connect_description_.endpoint_url = "opc.tcp://localhost:4840";
        connect_description_.endpoint_array = nullptr;
        connect_description_.endpoint_arraysize = 0;
        connect_description_.username = "user1";
        connect_description_.password = "password";

        ret = ConnectByCertificated();
        if (!ret) {
            return false;
        }   
    }
    return true;
}

/**
 * @brief Connect the server with use anonymous way.
 * 
 * @return true Anonymous Connect successful.
 * @return false Anonymous Connect failed.
 */
bool OpcUaClient::ConnectByAnonymous()
{
    LOG(INFO) << "Connect By Anonymous.";
    UA_StatusCode retval;
    retval = UA_Client_connect(client_, connect_description_.endpoint_url.c_str());
    if(retval != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Connect opcua server by anonymous. Errno is: " << retval;
        UA_Client_delete(client_);
        return false;
    }
    return true;
}

/**
 * @brief Connect the server with use endpoints. 
 * 
 * @return true Connect by endpoints successful.
 * @return false Connect by endpoints failed. 
 */
bool OpcUaClient::ConnectByCertificated()
{
    LOG(INFO) << "Connect By Endpoints.";
    UA_StatusCode retval;
    retval = UA_Client_getEndpoints(client_, connect_description_.endpoint_url.c_str(), \
        &connect_description_.endpoint_arraysize, &connect_description_.endpoint_array);
    if(retval != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Connect get endpoints failed. Errno is: " << retval;
        UA_Array_delete(connect_description_.endpoint_array, connect_description_.endpoint_arraysize, \
            &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        UA_Client_delete(client_);
        return false;
    }

    LOG(INFO) << (int)connect_description_.endpoint_arraysize << " endpoints found.";
    for(size_t i = 0; i < connect_description_.endpoint_arraysize; i++) {
        // %.*s can input two param one const char * and one printf length.
        printf("URL of endpoint %i is %.*s\n", (int)i,
               (int)connect_description_.endpoint_array[i].endpointUrl.length,
               connect_description_.endpoint_array[i].endpointUrl.data);
    }
    UA_Array_delete(connect_description_.endpoint_array, connect_description_.endpoint_arraysize, \
        &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

    /* Connect to a server */
    /* anonymous connect would be: retval = UA_Client_connect(client, "opc.tcp://localhost:4840"); */
    LOG(INFO) << "Connect to a server.+++";
    retval = UA_Client_connectUsername(client_, connect_description_.endpoint_url.c_str(), \
        connect_description_.username.c_str(), connect_description_.password.c_str());
    if(retval != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Connect with username and passworld Failed. Errno is: " << retval;
        UA_Client_delete(client_);
        return false;
    }

    return true;
}

/**
 * @brief Init the connect server description.
 * 
 * @param[out] connect_description The connect description.
 */
void OpcUaClient::InitConnectDescription(ConnectDescription & connect_description) 
{
    connect_description.anonymous_connect = true;
    connect_description.endpoint_array = nullptr;
    connect_description.endpoint_arraysize = 0;
    connect_description.endpoint_url.clear();
    connect_description.username.clear();
    connect_description.password.clear();
}

/**
 * @brief Get the objects node from the server.
 * 
 * @return true 
 * @return false 
 */
bool OpcUaClient::BrowseObjectsNode(UA_BrowseRequest *bReq, UA_BrowseResponse *bResp)
{
    LOG(INFO) << "Browsing nodes in objects folder: " ;  
    /* Browse some objects */
    UA_BrowseRequest_init(bReq);
    bReq->requestedMaxReferencesPerNode = 0;

    bReq->nodesToBrowse = UA_BrowseDescription_new();
    bReq->nodesToBrowseSize = 1;
    bReq->nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); /* browse objects folder */
    bReq->nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */

    *bResp = UA_Client_Service_browse(client_, *bReq);
    printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");
    for(size_t i = 0; i < bResp->resultsSize; ++i) {
        for(size_t j = 0; j < bResp->results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp->results[i].references[j]);
            if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC) {
                printf("%-9d %-16d %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                       ref->nodeId.nodeId.identifier.numeric, (int)ref->browseName.name.length,
                       ref->browseName.name.data, (int)ref->displayName.text.length,
                       ref->displayName.text.data);
            } else if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING) {
                printf("%-9d %-16.*s %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                       (int)ref->nodeId.nodeId.identifier.string.length,
                       ref->nodeId.nodeId.identifier.string.data,
                       (int)ref->browseName.name.length, ref->browseName.name.data,
                       (int)ref->displayName.text.length, ref->displayName.text.data);
            }
            /* TODO: distinguish further types */
        }
    }
    
}

/**
 * @brief Same thing, this time using the node iterator...
 * 
 * @param parent 
 * @return true 
 * @return false 
 */
bool OpcUaClient::BrowseObjectsNodeByIterator()
{
    UA_NodeId *parent = UA_NodeId_new();
    *parent = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_Client_forEachChildNodeCall(client_, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                   nodeIter, (void *) parent);
    UA_NodeId_delete(parent);
}

/**
 * @brief Create a Subscription object
 * 
 * @param subscription_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::CreateSubscription(SubscriptionDescription & subscription_description)
{
    /* Create a subscription */
    subscription_description.subscription_request = UA_CreateSubscriptionRequest_default();
    subscription_description.subscription_response = UA_Client_Subscriptions_create(client_, \
        subscription_description.subscription_request, NULL, NULL, NULL);

    subscription_description.sub_id = subscription_description.subscription_response.subscriptionId;
    if (subscription_description.subscription_response.responseHeader.serviceResult == UA_STATUSCODE_GOOD) {
        LOG(INFO) << "Create subscription succeeded, id " << subscription_description.sub_id;
    } else {
        LOG(ERROR) << "Create subscription succeeded failed. " << "Errno is: " << subscription_description.sub_id;
        return false;
    }

    subscription_description.monitor_item_request = UA_MonitoredItemCreateRequest_default( \
        UA_NODEID_STRING(subscription_description.namespace_index, \
        (char *)subscription_description.identifier_string.c_str()));
    
    subscription_description.monitor_item_response = UA_Client_MonitoredItems_createDataChange( \
        client_, subscription_description.subscription_response.subscriptionId, \
        UA_TIMESTAMPSTORETURN_BOTH, subscription_description.monitor_item_request, \
        NULL, handler_TheAnswerChanged, NULL);

    if(subscription_description.monitor_item_response.statusCode == UA_STATUSCODE_GOOD) {
        LOG(INFO) << "Monitoring " << subscription_description.identifier_string << " id " << \
            subscription_description.monitor_item_response.monitoredItemId;
    } else {
        LOG(ERROR) << "Set Monitoring failed. " << "Errno is: " << \
            subscription_description.monitor_item_response.statusCode;
    }


    /* The first publish request should return the initial value of the variable */
    UA_StatusCode UA_EXPORT ret = UA_Client_run_iterate(client_, subscription_description.publish_request_timeout);
    if (ret != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "The create subscription first publish request should return the initial value of the variable Failed " << \
            "Errno hex is: " << hex << ret;
        return false;
    }

    return true;
}

/**
 * @brief 
 * 
 * @param subscription_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::DeleteSubscription(SubscriptionDescription & subscription_description)
{
    /* Take another look at the.answer */
    UA_StatusCode UA_EXPORT ret = UA_Client_run_iterate(client_, subscription_description.cancel_publish_request_timeout);
    if (ret != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "The delete subscription publish request should return the initial value of the variable Failed " << \
            "Errno hex is: " << hex << ret;
        return false;
    }
    /* Delete the subscription */
    if(UA_Client_Subscriptions_deleteSingle(client_, subscription_description.sub_id) == UA_STATUSCODE_GOOD) {
        LOG(INFO) << subscription_description.identifier_string << "subscription removed.";
    } else {
        LOG(ERROR) << subscription_description.identifier_string << "subscription removed failed.";
        return false;
    }

    return true;
}

/**
 * @brief Get the node of current value from the opcua server.
 * 
 * @param value 
 * @param node_attribute_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::GetNodeValue(UA_Int32 & value, NodeAttributeDescription & node_attribute_description)
{
    UA_StatusCode retval;
    // TODO: Maybe NodeAttributeDescription need lock?
    // if (node_attribute_description.get_val_variant != nullptr) {
    //     LOG(ERROR) << "Node Attribute Description of get value variant not free then get node val failed";
    //     UA_Variant_delete(node_attribute_description.get_val_variant);
    //     node_attribute_description.get_val_variant = nullptr;
    //     return false;
    // }

    LOG(INFO) << "Reading the value of node " << node_attribute_description.namespace_index << " : " << \
        node_attribute_description.identifier_string;

    UA_Variant *get_val_variant;
    get_val_variant = UA_Variant_new();
    retval = UA_Client_readValueAttribute(client_, \
        UA_NODEID_STRING(node_attribute_description.namespace_index, \
            (char *)node_attribute_description.identifier_string.c_str()), get_val_variant);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(get_val_variant) && \
        get_val_variant->type == &UA_TYPES[UA_TYPES_INT32]) {
            value = *(UA_Int32*)get_val_variant->data;
            UA_Variant_delete(get_val_variant);
            return true;
            // printf("the value is: %i\n", value);
    } else {
        LOG(ERROR) << "Get " << node_attribute_description.namespace_index << " : " << \
            node_attribute_description.identifier_string << " node value failed.";
        UA_Variant_delete(get_val_variant);
        return false;
    }
        
    return true;
}

/**
 * @brief Set node value by use the request to server.
 * 
 * @param value 
 * @param node_attribute_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::SetNodeValueByRequest(UA_Int32 value, NodeAttributeDescription & node_attribute_description)
{
    LOG(INFO) << "Writing a value of node " << node_attribute_description.namespace_index << " : " << \
        node_attribute_description.identifier_string;


    UA_WriteRequest_init(&node_attribute_description.write_request);
    node_attribute_description.write_request.nodesToWrite = UA_WriteValue_new();

    node_attribute_description.write_request.nodesToWriteSize = 1;
    
    node_attribute_description.write_request.nodesToWrite[0].nodeId = \
        UA_NODEID_STRING_ALLOC(node_attribute_description.namespace_index, \
            (char *)node_attribute_description.identifier_string.c_str());

    node_attribute_description.write_request.nodesToWrite[0].attributeId = UA_ATTRIBUTEID_VALUE;
    node_attribute_description.write_request.nodesToWrite[0].value.hasValue = true;
    node_attribute_description.write_request.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_INT32];
    
    if (node_attribute_description.write_storageType != UA_VARIANT_DATA) {
        /* do not free the integer on deletion */
        node_attribute_description.write_request.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA_NODELETE;
    } else {
        node_attribute_description.write_request.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA;
    }

    node_attribute_description.write_request.nodesToWrite[0].value.value.data = &value;
    node_attribute_description.write_response = UA_Client_Service_write(client_, node_attribute_description.write_request);
    if (node_attribute_description.write_response.responseHeader.serviceResult == UA_STATUSCODE_GOOD) {
        LOG(INFO) << "Set the node " << node_attribute_description.namespace_index << " : " << \
            node_attribute_description.identifier_string << "new value is: " << value;
        UA_WriteRequest_clear(&node_attribute_description.write_request);
        UA_WriteResponse_clear(&node_attribute_description.write_response);
        return true;
    } else {
        LOG(ERROR) << "Set the node " << node_attribute_description.namespace_index << " : " << \
            node_attribute_description.identifier_string << " value failed.";
        UA_WriteRequest_clear(&node_attribute_description.write_request);
        UA_WriteResponse_clear(&node_attribute_description.write_response);
        return false;
    }

    return true;
}

/**
 * @brief Set the node value by the highlevel way.
 * 
 * @param value 
 * @param node_attribute_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::SetNodeValueByHighlevel(UA_Int32 value, NodeAttributeDescription & node_attribute_description)
{
    UA_StatusCode ret;
    UA_Variant *myVariant = UA_Variant_new();
    ret = UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT32]);
    if (ret != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Set Node Value By Highlevel use function UA_Variant_setScalarCopy failed.";
        UA_Variant_delete(myVariant);
        return false;
    }
    ret = UA_Client_writeValueAttribute(client_, \
        UA_NODEID_STRING(node_attribute_description.namespace_index, \
            (char *)node_attribute_description.identifier_string.c_str()), myVariant);
    if (ret != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Set Node Value By Highlevel use function UA_Client_writeValueAttribute failed.";
        UA_Variant_delete(myVariant);
        return false;
    }
    UA_Variant_delete(myVariant);
    return true;
}

/**
 * @brief Call the remote server method functino return back the run result.
 * 
 * @param method_call_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::CallRemoteSeverMethod(MethodCallDescription & method_call_description)
{
    UA_StatusCode retval;

    method_call_description.object_id_namespace_index = 0;
    method_call_description.object_id_identifier_numeric = UA_NS0ID_OBJECTSFOLDER;
    method_call_description.method_id_namespace_index = 1;
    method_call_description.method_id_identifier_numeric = 62541;

    /* Call a remote method */
    UA_Variant input;
    UA_String argString = UA_STRING((char *)method_call_description.input_msg_string.c_str());
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &argString, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    retval = UA_Client_call(client_, \
        UA_NODEID_NUMERIC(method_call_description.object_id_namespace_index, \
            method_call_description.object_id_identifier_numeric), \
        UA_NODEID_NUMERIC(method_call_description.method_id_namespace_index, \
            method_call_description.method_id_identifier_numeric), \
        1, &input, &outputSize, &output);

    if(retval == UA_STATUSCODE_GOOD) {
        LOG(INFO) << "Method call was successful, and " << (unsigned long)outputSize << " returned values available.";
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    } else {
        LOG(ERROR) << "Method call was unsuccessful, and " << retval << " returned values available.";
        UA_Variant_clear(&input);
        return false;
    }
    UA_Variant_clear(&input);

    return true;
}

/**
 * @brief Add new reference type to the server.
 * 
 * @param reference_type_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::AddNewReferenceType(ReferenceTypeDescription & reference_type_description)
{
    /* New ReferenceType */
    UA_StatusCode retval;
    UA_ReferenceTypeAttributes ref_attr = UA_ReferenceTypeAttributes_default;
    ref_attr.displayName = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)reference_type_description.display_name.c_str());
    ref_attr.description = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)reference_type_description.description.c_str());
    ref_attr.inverseName = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)reference_type_description.inverse_name.c_str());
    retval = UA_Client_addReferenceTypeNode(client_, \
        UA_NODEID_NUMERIC(reference_type_description.requested_new_node_id_namespace_index, \
            reference_type_description.requested_new_node_id_identifier_numeric), \
        UA_NODEID_NUMERIC(reference_type_description.parent_node_id_namespace_index, \
            UA_NS0ID_ORGANIZES),
        UA_NODEID_NUMERIC(reference_type_description.reference_type_id_namespace_index, \
            UA_NS0ID_HASSUBTYPE),
        UA_QUALIFIEDNAME(reference_type_description.browse_name_id_namespace_index, \
            (char *)reference_type_description.browse_name_id_name.c_str()),
        ref_attr, &reference_type_description.reference_type_id);

    if(retval == UA_STATUSCODE_GOOD ) {
        LOG(INFO) << "Created " << reference_type_description.browse_name_id_name \
            << " with numeric NodeID " << reference_type_description.reference_type_id.identifier.numeric;
        return true;
    } else {
        LOG(ERROR) << "Created " << reference_type_description.browse_name_id_name << "failed."; 
        return false;
    }
    return true;
}

/**
 * @brief Add new object type to the server.
 * 
 * @param object_type_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::AddNewObjectType(ObjectTypeDescription & object_type_description)
{
    /* Add New ObjectType */
    UA_StatusCode retval;
    UA_ObjectTypeAttributes objt_attr = UA_ObjectTypeAttributes_default;
    objt_attr.displayName = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)object_type_description.display_name.c_str());
    objt_attr.description = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)object_type_description.description.c_str());
    retval = UA_Client_addObjectTypeNode(client_,
    UA_NODEID_NUMERIC(object_type_description.requested_new_node_id_namespace_index, \
        object_type_description.requested_new_node_id_identifier_numeric), \
    UA_NODEID_NUMERIC(object_type_description.parent_node_id_namespace_index, \
        UA_NS0ID_BASEOBJECTTYPE), \
    UA_NODEID_NUMERIC(object_type_description.reference_type_id_namespace_index, \
        UA_NS0ID_HASSUBTYPE), \
    UA_QUALIFIEDNAME(object_type_description.browse_name_id_namespace_index, \
        (char *)object_type_description.browse_name_id_name.c_str()), \
    objt_attr, &object_type_description.object_type_id);

    if(retval == UA_STATUSCODE_GOOD) {
        LOG(INFO) << "Created " << object_type_description.browse_name_id_name << \
            " with numeric NodeID " << object_type_description.object_type_id.identifier.numeric;
        return true;
    } else {
        LOG(ERROR) << "Created " << object_type_description.browse_name_id_name << " failed.";
        return false;
    }
    
    return true;
}

/**
 * @brief Add new object to the server.
 * 
 * @param object_description 
 * @return true 
 * @return false 
 */
bool OpcUaClient::AddNewObject(ObjectDescription & object_description)
{
    /* Add New Object */
    UA_StatusCode retval;
    UA_ObjectAttributes obj_attr = UA_ObjectAttributes_default;
    obj_attr.displayName = UA_LOCALIZEDTEXT(EN_US_CODE, \
        (char *)object_description.display_name.c_str());
    obj_attr.description = UA_LOCALIZEDTEXT(DE_DE_CODE, \
        (char *)object_description.description.c_str());
    retval = UA_Client_addObjectNode(client_, \
        UA_NODEID_NUMERIC(object_description.requested_new_node_id_namespace_index, \
            object_description.requested_new_node_id_identifier_numeric), \
        UA_NODEID_NUMERIC(object_description.parent_node_id_namespace_index, \
            UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(object_description.reference_type_id_namespace_index, \
            UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(object_description.browse_name_id_namespace_index, \
            (char *)object_description.browse_name_id_name.c_str()),
        UA_NODEID_NUMERIC(object_description.type_definition_id_namespace_index, \
            object_description.type_definition_id_identifier_numeric), \
        obj_attr, &object_description.object_id);

    if(retval == UA_STATUSCODE_GOOD ) {
        LOG(INFO) << "Created " << object_description.browse_name_id_name << \
            " with numeric NodeID " << object_description.object_id.identifier.numeric;
        return true;
    } else {
        LOG(ERROR) << "Created " << object_description.browse_name_id_name << " failed.";
        return false;
    }
    
    return true;
}

bool OpcUaClient::AddNewIntegerVariable(UA_Int32 int_value, IntegerVariableDescription & int_var_description)
{
    /* Add New Integer Variable */
    UA_StatusCode retval;
    UA_VariableAttributes var_attr = UA_VariableAttributes_default;
    var_attr.displayName = UA_LOCALIZEDTEXT(EN_US_CODE, (char *)int_var_description.display_name.c_str());
    var_attr.description =
        UA_LOCALIZEDTEXT(EN_US_CODE, (char *)int_var_description.description.c_str());

    /* This does not copy the value */
    UA_Variant_setScalar(&var_attr.value, &int_value, &UA_TYPES[UA_TYPES_INT32]);
    var_attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    retval = UA_Client_addVariableNode(client_, \
        // Assign new/random NodeID 
        UA_NODEID_NUMERIC(int_var_description.requested_new_node_id_namespace_index, \
            int_var_description.requested_new_node_id_identifier_numeric), \
        UA_NODEID_NUMERIC(int_var_description.parent_node_id_namespace_index, UA_NS0ID_OBJECTSFOLDER), \
        UA_NODEID_NUMERIC(int_var_description.reference_type_id_namespace_index, UA_NS0ID_ORGANIZES), \
        UA_QUALIFIEDNAME(int_var_description.browse_name_id_namespace_index, \
            (char *)int_var_description.browse_name_id_name.c_str()), \
        // no variable type
        UA_NODEID_NULL, \
        var_attr, &int_var_description.int_var_id);
    if(retval == UA_STATUSCODE_GOOD ) {
        LOG(INFO) << "Created " << int_var_description.browse_name_id_name << \
            " with numeric NodeID " << int_var_description.int_var_id.identifier.numeric;
        return true;
    } else {
        LOG(ERROR) << "Created" << int_var_description.browse_name_id_name << " failed.";
        return false;
    }
    return true;
}
