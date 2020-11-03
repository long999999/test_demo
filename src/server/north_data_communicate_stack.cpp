/* 
 *  File: north_data_communicate_stack.cpp
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

#include "north_data_communicate_stack.h"

NorthDataCommunicateStack* NorthDataCommunicateStack::m_instance_singleton_ = new NorthDataCommunicateStack;

NorthDataCommunicateStack::NorthDataCommunicateStack()
{   
    open62541_server_ = nullptr;
    mq_fcs_to_212_ = nullptr;
    is_successful_request_fcs_send_item_semaphore_ = false;
    north_chat_subitem_semaphore_ = true;
    north_chat_setrushmethod_semaphore_ = true;
    north_chat_suspend_semaphore_ = true;

    GlogInit("OpcUAServer", "INFO", "./log");
}

NorthDataCommunicateStack::~NorthDataCommunicateStack()
{

}

NorthDataCommunicateStack* NorthDataCommunicateStack::GetInstace()
{
    return m_instance_singleton_;
}

void NorthDataCommunicateStack::Start()
{
    CreateEpoll();
    Run();
}

/**
 * @brief Run epoll to listen fd.
 * 
 */
void NorthDataCommunicateStack::Run()
{
    string client_name;
    int client_fd;

    bool ret = false;

    // Init the fcs and opcua server MQ.
    InitMq();

    // Set epoll param.
    epoll_event_.events = EPOLLIN | EPOLLRDHUP | EPOLLET;

    // Add MQ msg fd.
    epoll_event_.data.fd = mq_fcs_to_212_id_;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, mq_fcs_to_212_id_, &epoll_event_);

    while (1) {
        nfds_ = epoll_wait(epoll_fd_, events, MAX_EVENTS, EPOLL_INTERVAL_TIME);
        if (nfds_ == -1) {
            LOG(ERROR) << "Epoll Wait failed.";
            return;
        }
        // Wait to listen the fd.
        for (n = 0; n < nfds_; ++n) {
            if (events[n].data.fd == mq_fcs_to_212_id_) {
                if (events[n].events & EPOLLIN) {
                    // The fcs to 212 MQ back the data.
                    ReadMqMsg();
                }
            }
        }
    }
}

/**
 * @brief Create the epoll fd.
 * 
 * @return true 
 * @return false 
 */
bool NorthDataCommunicateStack::CreateEpoll()
{
    LOG(INFO) << "CreateEpoll";
    // Create the epoll.
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        LOG(ERROR) << "Epoll Create1 Failed";
        return false;
    }
    return true;
}

bool NorthDataCommunicateStack::DeleteEpoll()
{
    // Close the epoll.
    close(epoll_fd_);
}

/**
 * @brief Init the Mq name.
 * 
 */
void NorthDataCommunicateStack::InitMq()
{
    // Init MQ msg.
    mq_fcs_to_212_name_ = FCS_TO_H212_NAME;

    mq_212_to_fcs_name_ = H212_TO_FCS_NAME;

    StartMqMsg();
}

/**
 * @brief Create the fcs mq and protocol need mq.
 * 
 */
void NorthDataCommunicateStack::StartMqMsg()
{
    // fcs to 212 MQ.
    mq_fcs_to_212_ = new MqAdapter(mq_fcs_to_212_name_);
    mq_fcs_to_212_->CreateMq();
    mq_fcs_to_212_id_ = mq_fcs_to_212_->GetMqId();
    if (!mq_fcs_to_212_->IsOpen()) {
        LOG(ERROR) << "Open " << mq_fcs_to_212_name_ << " Failed.";
        return;
    }

    // 212 to fcs MQ.
    mq_212_to_fcs_ = new MqAdapter(mq_212_to_fcs_name_);
    mq_212_to_fcs_->CreateMq();
    mq_212_to_fcs_id_ = mq_212_to_fcs_->GetMqId();
    if (!mq_212_to_fcs_->IsOpen()) {
        LOG(ERROR) << "Open " << mq_212_to_fcs_name_ << " Failed.";
        return;
    }
}

/**
 * @brief Read the mq reply msg.
 * 
 */
void NorthDataCommunicateStack::ReadMqMsg()
{
    char buf[4096] = "";
    uint32_t prio = 0;
    uint32_t &p = prio;
    ssize_t len = 0;
    string recv_msg = "";

    memset(buf, 0, sizeof(buf));
    len =  mq_fcs_to_212_->MqRecv(buf, p);
    if (len > 0) {
        LOG(INFO) << "received msg = " << buf;

        recv_msg = buf;
        JSONCPP_STRING errs; 
        Json::Value root;
        Json::CharReaderBuilder readerBuilder;  
        int res;

        std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
        res = jsonReader->parse(recv_msg.c_str(), recv_msg.c_str() + recv_msg.length(), &root, &errs);
        if (!res || !errs.empty()) {
	        std::cout << "parseJson err. " << errs << std::endl;
	        return;
        }
        
        // Parse the mq msg.
        // Update fcs opcua server mode value.
        ParseNorthMsg(recv_msg);
    }
}

/**
 * @brief Send mq msg.
 * 
 * @param send_msg 
 */
void NorthDataCommunicateStack::SendMqMsg(string send_msg)
{
    mq_send_msg_lock_.lock();
    mq_fcs_to_212_->MqSend((char *)send_msg.c_str(), send_msg.size(), PRIO);
    mq_send_msg_lock_.unlock();
}

/**
 * @brief Add the fd to epoll to listen.
 * 
 * @param fd 
 * @return true 
 * @return false 
 */
bool NorthDataCommunicateStack::AddFdToEpoll(int fd)
{
    add_epoll_fd_lock_.lock();
    epoll_event_.data.fd = fd;
    int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &epoll_event_);
    if (ret < 0) {
        LOG(INFO) << "epoll_ctl failed.";
        add_epoll_fd_lock_.unlock();
        return false;
    }
    add_epoll_fd_lock_.unlock();
    return true;
}

/**
 * @brief Remove the fd from the epoll listen union.
 * 
 * @param fd 
 * @return true 
 * @return false 
 */
bool NorthDataCommunicateStack::RemoveFdFromEpoll(int fd)
{
    remove_epoll_fd_lock_.lock();
    int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &epoll_event_);
    if (ret < 0) {
        LOG(ERROR) << "epoll ctl remove " << fd << "failed.";
        remove_epoll_fd_lock_.unlock();
        return false;
    }
    remove_epoll_fd_lock_.unlock();
    return true;
}

/**
 * @brief Create the cycle request fcs push back item val thread.
 * 
 */
void NorthDataCommunicateStack::StartSubItemFromFcs()
{
    // Create the sub item from fcs thread to cycle to request the fcs push item val.
    std::thread start_sub_item_from_fcs(&NorthDataCommunicateStack::HandleStartSubItemFromFcs, this);
    // Save the thread handle.
    ServerDataShare *server_data_share = server_data_share->GetInstace();
    server_data_share->thread_handle_map_["start_sub_item_from_fcs"] = start_sub_item_from_fcs.native_handle();
    // Deatach thread.
    start_sub_item_from_fcs.detach();
}

void NorthDataCommunicateStack::HandleStartSubItemFromFcs()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    // Synchronization to run.
    t.async_wait(boost::bind(&NorthDataCommunicateStack::RunSubItemFromFcs,\
        this, boost::asio::placeholders::error, &t));
    // Wait to timing task finish.
    io.run();
}

/**
 * @brief Cycle send the request get item val data to fcs, then wait to the fcs reply the successful msg.
 * 
 * @param ec 
 * @param pt 
 */
void NorthDataCommunicateStack::RunSubItemFromFcs(const boost::system::error_code &ec, boost::asio::deadline_timer *pt)
{
    // Not successful request fcs send item wait next to request.

    if (!is_successful_request_fcs_send_item_semaphore_) {
    // Send Mq msg to request the fcs send item val.

        // Send the SubItem mq msg to fcs.
        if (north_chat_subitem_semaphore_) {
            string tmp_item_string;
            item_mq_msg_.GetSubItemMqMsg(tmp_item_string);
            LOG(INFO) << "GetSubItemMqMsg " << tmp_item_string;
            mq_212_to_fcs_->MqSend((char *)tmp_item_string.c_str(), tmp_item_string.size(), REQUEST_FCS_SEND_ITEM_MQ_MSG_PRIO);
        }

        // Send the SetPushMethod mq msg to fcs.
        if (north_chat_setrushmethod_semaphore_) {
            string tmp_item_string;
            item_mq_msg_.GetPushMethodMsg(tmp_item_string);
            LOG(INFO) << "GetPushMethodMsg " << tmp_item_string;
            mq_212_to_fcs_->MqSend((char *)tmp_item_string.c_str(), tmp_item_string.size(), REQUEST_FCS_SEND_ITEM_MQ_MSG_PRIO);
        }

        // Send the Suspend mq msg to fcs.
        if (north_chat_suspend_semaphore_) {
            string tmp_item_string;
            item_mq_msg_.GetSuspendMsg(tmp_item_string);
            LOG(INFO) << "GetSuspendMsg " << tmp_item_string;
            mq_212_to_fcs_->MqSend((char *)tmp_item_string.c_str(), tmp_item_string.size(), REQUEST_FCS_SEND_ITEM_MQ_MSG_PRIO);
        }

        // Successful request fcs send item then set the flag.
        if (!north_chat_subitem_semaphore_ && !north_chat_suspend_semaphore_ && !north_chat_setrushmethod_semaphore_) {
            LOG(INFO) << "Is successful request fcs send item.";
            is_successful_request_fcs_send_item_semaphore_ = true;
            return;
        }

        // Not successful request fcs send item wait next to request.
        pt->expires_at(pt->expires_at() + boost::posix_time::seconds(5));
        pt->async_wait(boost::bind(&NorthDataCommunicateStack::RunSubItemFromFcs,\
            this, boost::asio::placeholders::error, pt));
    }
}

void NorthDataCommunicateStack::WriteItemValToOpcUaServerNode()
{
    ServerDataShare *server_data_share = server_data_share->GetInstace();
    WriteVariableDescription write_Val_description;
    write_Val_description.server = open62541_server_;
    string tmp_namespace_id;
    string tmp_val;
    UA_UInt16 namespace_index;
    UA_UInt32 identifier;
    // Get the item id map val.
    for (auto iter = server_data_share->minor_item_data_val_.begin();\
        iter != server_data_share->minor_item_data_val_.end(); ++iter) {
            // TODO: The OpcUa Server of node have many data type.
            // Get the item id link Node data type.
            tmp_namespace_id.clear();
            tmp_val.clear();
            tmp_namespace_id = server_data_share->fbox_minor_item_link_server_node_identifier_map_[iter->first];
            tmp_val = iter->second;
            if (server_data_share->server_node_value_type_map_[tmp_namespace_id] == "Double") {
                UA_Double write_val = opcua_tool_.StringToNum<UA_Double>(tmp_val);
                string tmp_namespace_index;
                string tmp_identifier;
                // Get the Node namespace id and identifier.
                opcua_tool_.GetNamespaceIdAndIdentifier(tmp_namespace_id, tmp_namespace_index, tmp_identifier);
                // Transfer the Namespace id and identifier to the number.
                opcua_tool_.TransferNamespaceIdAndIdentifier(tmp_namespace_index, tmp_identifier,\
                    namespace_index, identifier);
                write_Val_description.namespace_index = namespace_index;
                write_Val_description.identifier = identifier;
                opcua_server_variable_.WriteVariableValue(write_Val_description, write_val);
            }
        }
}

/**
 * @brief Parse the fcs back the north msg.
 * 
 * @param recv_msg 
 */
void NorthDataCommunicateStack::ParseNorthMsg(string recv_msg)
{
    JSONCPP_STRING errs; 
    Json::Value root;
    Json::Value json_obj;
    Json::Value json_data_items_array;
    Json::CharReaderBuilder readerBuilder;
    int res = 0;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(recv_msg.c_str(), recv_msg.c_str() + recv_msg.length(), &root, &errs);
    if (!res || !errs.empty()) {
        LOG(ERROR) << "Json parseJson err: " << errs;
        return;
    }

    string tmp_id;
    string tmp_data;
    string tmp_function;
    unsigned int error_no;

    // The tmp_id is the sign the client parse.
    tmp_id = root["data"]["server_index"].asString();
    tmp_function = root["function"].asString();
    error_no = root["data"]["flexem_error_code"].asUInt();

    // Judge the function.
    if (tmp_function == NORCHART_SUSPENDREPLY_FUNCTION) {
        // Fcs back suspend reply function.
        if (north_chat_suspend_semaphore_ && (error_no == 200)) {
            north_chat_suspend_semaphore_ = false;
        }
    } else if (tmp_function == NORCHART_SETPUSHMETHODREPLY_FUNCTION) {
        // Fcs back setpushmethod reply function.
        if (north_chat_setrushmethod_semaphore_ && (error_no == 200)) {
            north_chat_setrushmethod_semaphore_ = false;
        }
    } else if (tmp_function == NORCHART_SUBITEMREPLY_FUNCTINO) {
        // Fcs back subitem function.
        if (north_chat_subitem_semaphore_ && (error_no == 200)) {
            north_chat_subitem_semaphore_ = false;
        }
    } else if ((tmp_function == NORCHART_PUSHMONITORDATA_FUNCTINO) && \
        (open62541_server_ != nullptr) && is_successful_request_fcs_send_item_semaphore_) {
        json_obj = root["data"];
        json_data_items_array = json_obj["items"];
        // Get the item id and fcs back source val.
        ParseNorthMsgItemVal(json_data_items_array);
        // Write the val to the server node.
        WriteItemValToOpcUaServerNode();
    }
}

void NorthDataCommunicateStack::ParseNorthMsgItemVal(Json::Value recv_item_val_array_msg)
{
    Json::Value::Members members;
    Json::Value data;
    string json_key_name;
    bool ret;

    ServerDataShare *server_data_share = server_data_share->GetInstace();
    // FIXME: The minor_item_data_val need lock.
    server_data_share->minor_item_data_val_.clear();

    unsigned int i;
    for (i = 0; i < recv_item_val_array_msg.size(); ++i) {
        data = recv_item_val_array_msg[i];

        members = data.getMemberNames();
        for (auto iter = members.begin(); iter != members.end(); ++iter) {
            // Get the minor data id.
            json_key_name = *iter;

            switch(data[*iter].type()) {
                // Json member object type of value is string.
                case Json::stringValue:
                    // Push the item id and val to the map.
                    server_data_share->minor_item_data_val_[*iter] = data[json_key_name].asString(); 
                    break;
                // Json member object type of value is bool.
                case Json::booleanValue:
                    ret = data[json_key_name].asBool();
                    if (ret) {
                        server_data_share->minor_item_data_val_[*iter] = "1";
                    } else {
                        server_data_share->minor_item_data_val_[*iter] = "0";
                    }
                    break;
                // Json member object type of value is null.
                case Json::nullValue:
                    server_data_share->minor_item_data_val_[*iter] = "0";
                    break;
                // Json array object type of value is float of double.
                case Json::realValue:
                    server_data_share->minor_item_data_val_[*iter] = data[json_key_name].asString();
                    break;
                default:
                    // Push the item name and val to the map.
                    server_data_share->minor_item_data_val_[*iter] = data[json_key_name].asString();
            }
        }
    }
}


void NorthDataCommunicateStack::GlogInit(string glog_name, string glog_leve, string glog_path)
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