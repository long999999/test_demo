/* 
 *  File: opcua_client_description.h
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

#ifndef OPCUA_CLIENT_DESCRIPTION_H_
#define OPCUA_CLIENT_DESCRIPTION_H_

#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>

#include <string>

#define EN_US_CODE "en-US"
#define DE_DE_CODE "de-DE"

namespace opcua_client_description {

struct ConnectDescription {
    bool anonymous_connect;
    UA_EndpointDescription *endpoint_array; 
    size_t endpoint_arraysize;
    std::string endpoint_url;
    std::string username;
    std::string password;
};

struct SubscriptionDescription {
    UA_CreateSubscriptionRequest subscription_request;
    UA_CreateSubscriptionResponse subscription_response;
    UA_UInt32 sub_id;
    UA_UInt16 namespace_index;
    std::string identifier_string;
    UA_MonitoredItemCreateRequest monitor_item_request;
    UA_MonitoredItemCreateResult monitor_item_response;
    UA_UInt32 publish_request_timeout;
    UA_UInt32 cancel_publish_request_timeout;
};

struct NodeAttributeDescription {
    UA_UInt16 namespace_index;
    std::string identifier_string;
    UA_VariantStorageType write_storageType;
    UA_WriteRequest write_request;
    UA_WriteResponse write_response;
};

struct MethodCallDescription {
    std::string input_msg_string;
    UA_UInt16 object_id_namespace_index;
    UA_UInt32 object_id_identifier_numeric;
    UA_UInt16 method_id_namespace_index;
    UA_UInt32 method_id_identifier_numeric;
};

struct ReferenceTypeDescription {
    UA_NodeId reference_type_id;
    std::string display_name;
    std::string description;
    std::string inverse_name;
    UA_UInt16 requested_new_node_id_namespace_index;
    UA_UInt32 requested_new_node_id_identifier_numeric;
    UA_UInt16 parent_node_id_namespace_index;
    UA_UInt32 parent_node_id_identifier_numeric;
    UA_UInt16 reference_type_id_namespace_index;
    UA_UInt32 reference_type_id_identifier_numeric;
    UA_UInt16 browse_name_id_namespace_index;
    std::string browse_name_id_name;
};

struct ObjectTypeDescription {
    UA_NodeId object_type_id;
    std::string display_name;
    std::string description;
    UA_UInt16 requested_new_node_id_namespace_index;
    UA_UInt32 requested_new_node_id_identifier_numeric;
    UA_UInt16 parent_node_id_namespace_index;
    UA_UInt32 parent_node_id_identifier_numeric;
    UA_UInt16 reference_type_id_namespace_index;
    UA_UInt32 reference_type_id_identifier_numeric;
    UA_UInt16 browse_name_id_namespace_index;
    std::string browse_name_id_name;
};

struct ObjectDescription {
    UA_NodeId object_id;
    std::string display_name;
    std::string description;
    UA_UInt16 requested_new_node_id_namespace_index;
    UA_UInt32 requested_new_node_id_identifier_numeric;
    UA_UInt16 parent_node_id_namespace_index;
    UA_UInt32 parent_node_id_identifier_numeric;
    UA_UInt16 reference_type_id_namespace_index;
    UA_UInt32 reference_type_id_identifier_numeric;
    UA_UInt16 browse_name_id_namespace_index;
    std::string browse_name_id_name;
    UA_UInt32 type_definition_id_identifier_numeric;
    UA_UInt16 type_definition_id_namespace_index;
};

struct IntegerVariableDescription {
    UA_NodeId int_var_id;
    std::string display_name;
    std::string description;
    UA_UInt16 requested_new_node_id_namespace_index;
    UA_UInt32 requested_new_node_id_identifier_numeric;
    UA_UInt16 parent_node_id_namespace_index;
    UA_UInt32 parent_node_id_identifier_numeric;
    UA_UInt16 reference_type_id_namespace_index;
    UA_UInt32 reference_type_id_identifier_numeric;
    UA_UInt16 browse_name_id_namespace_index;
    std::string browse_name_id_name;
    UA_UInt32 type_definition_id_identifier_numeric;
    UA_UInt16 type_definition_id_namespace_index;
};

} // namespace  

#endif // OPCUA_CLIENT_DESCRIPTION_H_