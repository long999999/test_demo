/* 
 *  File: opcua_server.cpp
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

#include "opcua_server.h"

#ifdef __cplusplus
extern "C" {
#endif

UA_StatusCode
MyNodeCallBack(UA_Server *server, const UA_NodeId *sessionId,
                     void *sessionContext, const UA_NodeId *methodId,
                     void *methodContext, const UA_NodeId *objectId,
                     void *objectContext, size_t inputSize,
                     const UA_Variant *input, size_t outputSize,
                     UA_Variant *output)
{
    UA_Int32 value = 0;
    for (size_t i = 0; i < inputSize; ++i)
    {
    	UA_Int32 * ptr = (UA_Int32 *)input[i].data;
    	value += (*ptr);
    }

    value += 100;
    
    UA_Variant_setScalarCopy(output, &value, &UA_TYPES[UA_TYPES_INT32]);
    
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
    
    return UA_STATUSCODE_GOOD;
}

#ifdef __cplusplus
}
#endif

OpcUaServer::OpcUaServer()
{
    running_ = true;
}

OpcUaServer::~OpcUaServer()
{
    
}

/**
 * @brief Start server.
 * 
 * @return int 
 */
int OpcUaServer::Start()
{
    UA_Server *server = UA_Server_new();
    // Add the open62541 server to the NorthDataCommunicateStack.
    NorthDataCommunicateStack *chat_stack = chat_stack->GetInstace();
    chat_stack->open62541_server_ = server;
    
    // Set the server by the default setting.
    // UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    // Set the server by custom port.
    UA_StatusCode retval = SetDefaultServerConfigAndPortNumAndCertificate(UA_Server_getConfig(server), 15121, NULL);
    if(retval != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "SetDefaultServerConfigAndPortNumAndCertificate";
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    }
    
    // Import the nodes from xml mode.
    retval = testNS(server);
    if(retval != UA_STATUSCODE_GOOD) {
        LOG(ERROR) << "Set Failed";
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the example nodeset. "
            "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        // Set the method call back.
        UA_Server_setMethodNode_callback(server, UA_NODEID_NUMERIC(2, 7002), &MyNodeCallBack);
    }

    // Init sub item val from fcs config.
    chat_stack->item_mq_msg_.InitFboxLinkServerNode();
    chat_stack->item_mq_msg_.SetPushMethodConfig("HJ212", "interval", 5000);
    chat_stack->item_mq_msg_.SetSubItemConfig("HJ212");
    chat_stack->item_mq_msg_.SetSuspendConfig("HJ212", false);
    // Create the sub item val from fcs.
    chat_stack->StartSubItemFromFcs();

    retval = UA_Server_run(server, &running_);

    UA_Server_delete(server);

    return (int) retval;
}

/**
 * @brief Set the deault server listen port number and the certificate.
 * @param[in] config The deault new server.
 * @param[in] port_number The serve listen port number.
 * @param[in] certificate The server listen port use certificate (deault NULL)
 * @details The config will set the tcp network layer to the given port and adds a single
 * endpoint with the security policy ``SecurityPolicy#None`` to the server. A
 * server certificate may be supplied but is optional.
 * 
 */
UA_StatusCode OpcUaServer::SetDefaultServerConfigAndPortNumAndCertificate(UA_ServerConfig *config, UA_UInt16 port_number,\
        const UA_ByteString *certificate)
{
    return UA_ServerConfig_setMinimal(config, port_number, certificate);
}
