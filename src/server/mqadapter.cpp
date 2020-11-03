/* 
 *  File: mqadapter.cpp
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

#include <cstring>
#include <cstdio>
#include <glog/logging.h>
#include "mqadapter.h"

MqAdapter::MqAdapter(string name, long msg_num, long msg_size)
    : name_(name), mq_max_msg_num_(msg_num), mq_msg_size_(msg_size)
{
    mq_id_ = -1;
	LOG(INFO) << "name_ : " << name_;
   	LOG(INFO) << "mq_max_msg_num_ : " << mq_max_msg_num_;
   	LOG(INFO) << "mq_msg_size_ : " << mq_msg_size_;
}

MqAdapter::~MqAdapter() {
    DeleteMq();
}

bool MqAdapter::CreateMq() {
    int flag = 0;
    struct mq_attr attr;

    if (name_.empty())
        return false;

    flag =  O_CREAT|O_RDWR | O_NONBLOCK | O_EXCL;
    memset(&attr, 0, sizeof(attr));
    attr.mq_maxmsg = mq_max_msg_num_;
    attr.mq_msgsize = mq_msg_size_;

    mq_id_ = mq_open(name_.c_str(), flag, 0666, &attr);

    if (mq_id_ == (mqd_t)-1) {
        if (errno == EEXIST) {
            flag = O_RDWR | O_NONBLOCK;
            mq_id_ = mq_open(name_.c_str(), flag);
            if (mq_id_ == (mqd_t)-1) {
				LOG(ERROR) << strerror(errno);
                return false;
            } else {
                LOG(INFO) << "Create Mq " << name_ << " successfully.";
                return true;
            }
        }
        LOG(ERROR) << strerror(errno);
        return false;
    }
    LOG(INFO) << "Create Mq " << name_ << " successfully.";
    return true;
}

bool MqAdapter::DeleteMq() {
    mqd_t ret;

    ret = mq_unlink(name_.c_str());
    if (ret == (mqd_t)-1)
        return false;
    else {
        return true;
    }
}

bool MqAdapter::MqSend(char *msg, size_t len, uint32_t msg_prio)
{
    int ret = 0;

    if (!IsOpen()) {
        LOG(ERROR) << "Mq not create.";
        return false;
    }

    ret = mq_send(mq_id_, msg, len, msg_prio);

    if (ret == 0) {
        LOG(INFO) << "Send msg succeesfully. msg len = " << to_string(len) << " , prio =  " << to_string(msg_prio);
        return true;
    } else {
        LOG(ERROR) << strerror(errno);
        return false;
    }
}

long MqAdapter::MqRecv(char *msg, uint32_t &msg_prio) {

    ssize_t size = 0;

    if (!IsOpen()) {
        LOG(ERROR) << "Mq not create.";
        return false;
    }

    size = mq_receive(mq_id_, msg, mq_msg_size_, &msg_prio);
    if (size == -1) {
        LOG(ERROR) << strerror(errno);
    }

    return size;
}

long MqAdapter::GetMqAttr(struct mq_attr &attr)
{
    struct mq_attr at;

    if (mq_id_ == (mqd_t)-1) {
        return -1;
    }

    return mq_getattr(mq_id_, &attr);
}

long MqAdapter::GetCurrMsgNum()
{
    struct mq_attr attr;

    if (!GetMqAttr(attr))
        return attr.mq_curmsgs;
    else
        return -1;
}

long MqAdapter::GetMsgSize()
{
    struct mq_attr attr;

    if (!GetMqAttr(attr))
        return attr.mq_msgsize;
    else
        return -1;
}

long MqAdapter::GetMaxMsgNum()
{
    struct mq_attr attr;

    if (!GetMqAttr(attr))
        return attr.mq_maxmsg;
    else
        return -1;
}

long MqAdapter::GetMqFlags()
{
    struct mq_attr attr;

    if (!GetMqAttr(attr))
        return attr.mq_flags;
    else
        return -1;
}

mqd_t MqAdapter::GetMqId()
{
    return mq_id_;
}

bool MqAdapter::IsOpen()
{
    if (mq_id_ < 0) {
        return false;
    } else {
        return true;
    }
}
