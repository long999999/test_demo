/* 
 *  File: mqadapter.h
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

//
// Created by Win10 on 2019/11/18.
//

#ifndef MQADAPTER_H_
#define MQADAPTER_H_
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <cstdint>
#include <cerrno>
#include <cstdio>
#include <iostream>

using namespace std;

#define TCP_TO_FCS_NAME         "/tcp_to_fcs"
#define FCS_TO_TCP_NAME         "/fcs_to_tcp"
#define MQTT_TO_FCS_NAME        "/mqtt_to_fcs"
#define FCS_TO_MQTT_NAME        "/fcs_to_mqtt"
#define H212_TO_FCS_NAME        "/h212_to_fcs"
#define FCS_TO_H212_NAME        "/fcs_to_h212"

class MqAdapter {
public:
    MqAdapter(string name, long msg_num = 20, long msg_size = 4096);
    ~MqAdapter();

    bool CreateMq();
    bool DeleteMq();
    bool MqSend(char msg[], size_t len, uint32_t msg_prio);
    long MqRecv(char *msg, uint32_t &msg_prio);
    long GetMqAttr(struct mq_attr &addr);
    long GetCurrMsgNum();
    long GetMsgSize();
    long GetMaxMsgNum();
    long GetMqFlags();
    mqd_t GetMqId();
    bool IsOpen();

private:
    string name_;
    mqd_t mq_id_;
    long mq_max_msg_num_;
    long mq_msg_size_;
};


#endif //MQADAPTER_H_
