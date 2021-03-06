/* 
 *  File: opcua_server_service.h
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

#ifndef OPCUA_SERVER_SERVICE_H
#define OPCUA_SERVER_SERVICE_H

#include <iostream>
#include <thread>

#include <glog/logging.h>

#include "opcua_server.h"
#include "opcua_server_data_share.h"
#include "north_data_communicate_stack.h"

#include "open62541.h"


using namespace std;

class OpcUaServerService
{
public:
    OpcUaServerService();
    virtual ~OpcUaServerService();

    void ServiceConfig();
    void Start();
    void StartNorthComminute();
    void RunNorthComminute();
    void StartOpcUaServer();
    void GlogInit(string glog_name, string glog_leve, string glog_path);
private:
    OpcUaServer opcua_server_;
};

#endif // OPCUA_SERVER_SERVICE_H