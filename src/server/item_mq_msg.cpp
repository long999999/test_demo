/* 
 *  File: item_mq_msg.cpp
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

#include "item_mq_msg.h"

ItemMqMsg::ItemMqMsg()
{
    
}

ItemMqMsg::~ItemMqMsg()
{

}

/**
 * @brief Map the fbox monitor item with opcua server node. 
 * 
 */
void ItemMqMsg::InitFboxLinkServerNode()
{
    // Init the fcs node link opc ua serve node.
    ServerDataShare *server_data_share = server_data_share->GetInstace();
    server_data_share->fbox_minor_item_link_server_node_identifier_map_["0x80000000"] = "2:6005";
    server_data_share->fbox_minor_item_link_server_node_identifier_map_["0x80000001"] = "2:6006";
    server_data_share->fbox_minor_item_link_server_node_identifier_map_["0x80000002"] = "2:6007";
    server_data_share->fbox_minor_item_link_server_node_identifier_map_["0x80000003"] = "2:6008";
    server_data_share->fbox_minor_item_link_server_node_identifier_map_["0x80000004"] = "2:6009";
    
    server_data_share->server_node_value_type_map_["2:6005"] = "Double";
    server_data_share->server_node_value_type_map_["2:6006"] = "Double";
    server_data_share->server_node_value_type_map_["2:6007"] = "Double";
    server_data_share->server_node_value_type_map_["2:6008"] = "Double";
    server_data_share->server_node_value_type_map_["2:6009"] = "Double";

    // Create the sub monito mq msg.
    CreateSendToFcsMqItemJsonMsg();
}

/**
 * @brief Crete send fcs sub monitor mq msg.
 * 
 */
void ItemMqMsg::CreateSendToFcsMqItemJsonMsg()
{
    ServerDataShare *server_data_share = server_data_share->GetInstace();

    int i = 0;
    for (auto iter = server_data_share->fbox_minor_item_link_server_node_identifier_map_.begin();\
        iter != server_data_share->fbox_minor_item_link_server_node_identifier_map_.end(); ++iter, ++i) {
        item_address_[i] = iter->first;
    }
}

/**
 * @brief Set the fcs push method way.
 * 
 * @param[in] protocol 
 * @param[in] push_mode The fcs push item val mode(change or )
 * @param[in] push_interval The push_interval unit is ms. 
 */
void ItemMqMsg::SetPushMethodConfig(string protocol, string push_mode, uint32_t push_interval)
{
    Json::Value data;
    Json::Value mq_msg;
    Json::StreamWriterBuilder builder;
    // builder["commentStyle"] = "None";
    builder["indentation"] = "";
    builder.settings_["precision"] = 16;
    builder.settings_["emitUTF8"] = true;

    data["protocol"] = protocol;
    data["flexem_push_mode"] = push_mode;
    if (push_interval < 500) {
        data["flexem_push_interval"] = 500;
    } else {
        data["flexem_push_interval"] = Json::Value(push_interval);
    }

    data["flexem_push_alarm"] = false;
    data["server_index"] = 1;
    mq_msg["function"] = "SetPushMethod";
    mq_msg["data"] = data;

    // Rewrite json to string by fast json api.
    send_to_fcs_mq_push_method_msg_ = Json::writeString(builder, mq_msg);
}

/**
 * @brief Get the fcs push method mq msg.
 * 
 * @param send_mq_msg 
 */
void ItemMqMsg::GetPushMethodMsg(string & send_mq_msg)
{
    send_mq_msg = send_to_fcs_mq_push_method_msg_;
}

/**
 * @brief Set the suspend way.
 * 
 * @param protocol 
 * @param pause 
 */
void ItemMqMsg::SetSuspendConfig(string protocol, bool pause)
{
    Json::Value data;
    Json::Value mq_msg;
    Json::StreamWriterBuilder builder;
    // builder["commentStyle"] = "None";
    builder["indentation"] = "";
    builder.settings_["precision"] = 16;
    builder.settings_["emitUTF8"] = true;

    data["protocol"] = protocol;
    data["flexem_pause"] = pause;
    data["server_index"] = 1;
    mq_msg["function"] = "Suspend";
    mq_msg["data"] = data;

    send_to_fcs_mq_suspend_msg_ = Json::writeString(builder, mq_msg);
}

/**
 * @brief Get the suspend mq msg.
 * 
 * @param send_mq_msg 
 */
void ItemMqMsg::GetSuspendMsg(string & send_mq_msg)
{
    send_mq_msg = send_to_fcs_mq_suspend_msg_;
}

/**
 * @brief Set the fcs subitem way.
 * 
 * @param protocol 
 */
void ItemMqMsg::SetSubItemConfig(string protocol)
{
    Json::Value data;
    Json::Value mq_msg;
    Json::StreamWriterBuilder builder;
    // builder["commentStyle"] = "None";
    builder["indentation"] = "";
    builder.settings_["precision"] = 16;
    builder.settings_["emitUTF8"] = true; 

    data["protocol"] = protocol;
    data["items"] = item_address_;
    data["server_index"] = 1;
    data["items_alarm"] = Json::nullValue;
    mq_msg["data"] = data;
    mq_msg["function"] = "SubItem";

    // Rewrite json to string by fast json api.
    send_to_fcs_mq_sub_item_msg_ = Json::writeString(builder, mq_msg);
}

/**
 * @brief Get the send to fcs sub item information mq msg.
 * 
 * @param send_mq_msg 
 */
void ItemMqMsg::GetSubItemMqMsg(string & send_mq_msg)
{
    send_mq_msg = send_to_fcs_mq_sub_item_msg_;
}