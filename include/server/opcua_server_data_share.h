/* 
 *  File: opcua_server_data_share.h
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

#ifndef OPCUA_SERVER_DATA_SHARE_H
#define OPCUA_SERVER_DATA_SHARE_H

#include <iostream>
#include <mutex>
#include <map>

#include <boost/any.hpp>

using namespace std;

static std::mutex fbox_minor_item_link_server_node_namespace_index_lock_;
static std::mutex fbox_minor_item_link_server_node_identifier_lock_;


class ServerDataShare {
public:
    static ServerDataShare* GetInstace();
    void demo_data_link_map_init();

    // The opcua server node value datatype which can read and write.
    // The first param mean server node namespace id and identifier.
    // The second param mean server node of datatype.
    map<string, string> server_node_value_type_map_; 
    // The fbox minor item link the opcua server node identifier map.
    // The first param mean fbox minor item id.
    // The second param mean server node namespace id and identifier.
    map<string, string> fbox_minor_item_link_server_node_identifier_map_;
    // The fbox minor item link fcs back item val map.
    // The first param mean fbox minor item id.
    // The second param mean fcs back item val.
    map<string, string> minor_item_data_val_;

    map<std::string, pthread_t> thread_handle_map_;
     
private:
    ServerDataShare();
    virtual ~ServerDataShare();
    
    ServerDataShare(const ServerDataShare&);
    ServerDataShare& operator = (const ServerDataShare&);

    static ServerDataShare*  m_instance_singleton_;
};

#endif // OPCUA_SERVER_DATA_SHARE_H