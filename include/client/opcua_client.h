/* 
 *  File: opcua_client.h
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

#ifndef OPCUA_CLIENT_H_
#define OPCUA_CLIENT_H_

#include <stdio.h>
#include <unistd.h>

#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

#include <iostream>

#include <glog/logging.h>

#include "opcua_client_description.h"

using namespace std;
using namespace opcua_client_description;


class OpcUaClient
{
public:
    OpcUaClient();
    virtual ~OpcUaClient();

    void Init();
    bool Start();
    bool Connect();
    bool ConnectByAnonymous();
    bool ConnectByCertificated();
    void InitConnectDescription(ConnectDescription & connect_description);

    bool BrowseObjectsNode(UA_BrowseRequest *bReq, UA_BrowseResponse *bResp);
    bool BrowseObjectsNodeByIterator();
    bool CreateSubscription(SubscriptionDescription & subscription_description);
    bool DeleteSubscription(SubscriptionDescription & subscription_description);
    bool GetNodeValue(UA_Int32 & value, NodeAttributeDescription & node_attribute_description);
    bool SetNodeValueByRequest(UA_Int32 value, NodeAttributeDescription & node_attribute_description);
    bool SetNodeValueByHighlevel(UA_Int32 value, NodeAttributeDescription & node_attribute_description);
    bool CallRemoteSeverMethod(MethodCallDescription & method_call_description);
    bool AddNewReferenceType(ReferenceTypeDescription & reference_type_description);
    bool AddNewObjectType(ObjectTypeDescription & object_type_description);
    bool AddNewObject(ObjectDescription & object_description);
    bool AddNewIntegerVariable(UA_Int32 int_value, IntegerVariableDescription & int_var_description);

private:
    UA_Client *client_;
    UA_EndpointDescription *endpoint_array_;
    size_t endpoint_arraysize_;
    string endpoint_url_;
    string username_;
    string password_;
    
    ConnectDescription connect_description_;
};


#endif //OPCUA_CLIENT_H_