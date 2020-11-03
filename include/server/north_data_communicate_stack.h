/* 
 *  File: north_data_communicate_stack.h
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

#ifndef NORTH_DATA_COMMUNICATE_STACK_H
#define NORTH_DATA_COMMUNICATE_STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <glog/logging.h>
#include <jsoncpp/json/json.h>

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/regex.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>

#include "open62541.h"
#include "mqadapter.h"
#include "item_mq_msg.h"
#include "opcua_server_data_share.h"
#include "opcua_tool.hpp"
#include "opcua_custom_code.h"
#include "opcua_server_description.h"
#include "opcua_server_variable.h"

using namespace std;
using namespace opcua_server_description;

#define REQUEST_FCS_SEND_ITEM_MQ_MSG_PRIO 1

#define MAX_EVENTS 10
#define EPOLL_INTERVAL_TIME 100
#define PRIO 5

class NorthDataCommunicateStack {
public:
    static NorthDataCommunicateStack* GetInstace();
    void Start();
    void Run();

    bool CreateEpoll();
    bool DeleteEpoll();

    void InitMq();
    void StartMqMsg();
    void ReadMqMsg();
    void SendMqMsg(string send_msg);

    bool AddFdToEpoll(int fd);
    bool RemoveFdFromEpoll(int fd);

    void StartSubItemFromFcs();
    void HandleStartSubItemFromFcs();
    void RunSubItemFromFcs(const boost::system::error_code &ec, boost::asio::deadline_timer *pt);

    void WriteItemValToOpcUaServerNode();

    void ParseNorthMsg(string recv_msg);
    void ParseNorthMsgItemVal(Json::Value recv_item_val_array_msg);

    void GlogInit(string glog_name, string glog_leve, string glog_path);

    ItemMqMsg item_mq_msg_;
    OpcUaTool opcua_tool_;
    OpcUaServerVariable opcua_server_variable_;

    UA_Server *open62541_server_;

private:
    NorthDataCommunicateStack();
    virtual ~NorthDataCommunicateStack();

    NorthDataCommunicateStack(const NorthDataCommunicateStack&);
    NorthDataCommunicateStack& operator = (const NorthDataCommunicateStack&);
    
    static NorthDataCommunicateStack*  m_instance_singleton_;

    // Epoll config param.
    struct epoll_event epoll_event_;
    struct epoll_event events[MAX_EVENTS];
    int nfds_;
    int epoll_fd_;
    int n;

    // TODO: Use the 212 mq to compent the demo logic.

    // Fcs to 212 MQ.
    MqAdapter* mq_fcs_to_212_;
    string mq_fcs_to_212_name_;
    mqd_t mq_fcs_to_212_id_;

    // 212 to fcs MQ.
    MqAdapter* mq_212_to_fcs_;
    string mq_212_to_fcs_name_;
    mqd_t mq_212_to_fcs_id_;

    // Use lock.
    std::mutex mq_send_msg_lock_;
    std::mutex add_epoll_fd_lock_;
    std::mutex remove_epoll_fd_lock_;

    // sub item val from fcs flag.
    bool is_successful_request_fcs_send_item_semaphore_;
    bool north_chat_subitem_semaphore_;
    bool north_chat_setrushmethod_semaphore_;
    bool north_chat_suspend_semaphore_;

};

#endif // NORTH_DATA_COMMUNICATE_STACK_H