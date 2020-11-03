/* 
 *  File: opcua_server_service.cpp
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

#include "opcua_server_service.h"


OpcUaServerService::OpcUaServerService()
{

}

OpcUaServerService::~OpcUaServerService()
{

}

void OpcUaServerService::ServiceConfig()
{
    // GlogInit("OpcUAServer", "INFO", "./log");
}

/**
 * @brief Config server and run not 
 * 
 */
void OpcUaServerService::Start()
{
    // TODO: May be need config a deafult config.
    ServiceConfig();

    StartNorthComminute();

    sleep(5); // 5s.

    StartOpcUaServer();

    while (1) {
        sleep(2);
    }
}

void OpcUaServerService::StartNorthComminute()
{
    ServerDataShare *server_data_share = server_data_share->GetInstace();
    std::thread run_north_comminute(&OpcUaServerService::RunNorthComminute, this);
    server_data_share->thread_handle_map_["run_north_comminute"] = run_north_comminute.native_handle();
    run_north_comminute.detach();
}

void OpcUaServerService::RunNorthComminute()
{
    NorthDataCommunicateStack *chat_stack = chat_stack->GetInstace();
    chat_stack->Start();
}

void OpcUaServerService::StartOpcUaServer()
{
    opcua_server_.Start();
}

void OpcUaServerService::GlogInit(string glog_name, string glog_leve, string glog_path)
{
    // Init glog
    string cglog_name = glog_name;
    google::InitGoogleLogging(cglog_name.c_str());

    // INFO WARNING ERROR FATAL
    if (glog_leve == "INFO") {
        FLAGS_stderrthreshold = google::GLOG_INFO;
    } else if (glog_leve == "WARNING") {
        FLAGS_stderrthreshold = google::GLOG_WARNING;
    } else if (glog_leve == "ERROR") {
        FLAGS_stderrthreshold = google::GLOG_ERROR;
    } else if (glog_leve == "FATAL") {
        FLAGS_stderrthreshold = google::GLOG_FATAL;
    } else {
        FLAGS_stderrthreshold = google::GLOG_INFO;
    }

    FLAGS_log_dir = glog_path;

    FLAGS_logbufsecs = 0;   // Print log in real time.
    FLAGS_max_log_size = 6; // Max log size 6MB.
    FLAGS_colorlogtostderr = true;
}