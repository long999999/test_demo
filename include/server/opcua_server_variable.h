/* 
 *  File: opcua_server_variable.h
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

#ifndef OPCUA_SERVER_VARIABLE_H
#define OPCUA_SERVER_VARIABLE_H

#include <signal.h>
#include <stdlib.h>

#include <iostream>

#include <boost/any.hpp>
#include <glog/logging.h>

#include "opcua_server_description.h"
#include "open62541.h"

using namespace std;
using namespace opcua_server_description;

class OpcUaServerVariable
{
public:
    OpcUaServerVariable();
    virtual ~OpcUaServerVariable();
    
    int Start();
    void AddMatrixVariable();
    void WriteVariable();
    void WriteWrongVariable();

    /**
     * @brief Add the server node variable.
     * 
     * @tparam T 
     * @param variable_description 
     * @param add_val 
     */
    template <typename T>
    void AddVariable(const AddVariableDescription & variable_description, T & add_val) {
        /* Define the attribute of the variable node */
        UA_VariableAttributes attr = UA_VariableAttributes_default;
        T my_add_val = add_val;
        // Get the add val of type.
        boost::any d_type(my_add_val);
        if (typeid(UA_UInt16) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_UINT16]);
            attr.dataType = UA_TYPES[UA_TYPES_UINT16].typeId;
        } else if (typeid(UA_Int16) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_INT16]);
            attr.dataType = UA_TYPES[UA_TYPES_UINT16].typeId;
        } else if (typeid(UA_Int32) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_INT32]);
            attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
        } else if (typeid(UA_UInt32) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_UINT32]);
            attr.dataType = UA_TYPES[UA_TYPES_UINT32].typeId;
        } else if (typeid(UA_Int64) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_INT64]);
            attr.dataType = UA_TYPES[UA_TYPES_INT64].typeId;
        } else if (typeid(UA_UInt64) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_UINT64]);
            attr.dataType = UA_TYPES[UA_TYPES_UINT64].typeId;
        } else if (typeid(UA_Float) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_FLOAT]);
            attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
        } else if (typeid(UA_Double) == d_type.type()) {
            UA_Variant_setScalar(&attr.value, &my_add_val, &UA_TYPES[UA_TYPES_DOUBLE]);
            attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
        } else {
            LOG(ERROR) << "OpcUa Server Add Variable Value Unknow Data type.";
            return;
        }

        attr.description = UA_LOCALIZEDTEXT("en-US", (char *)variable_description.description.c_str());
        attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)variable_description.display_name.c_str());
        attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

        /* Add the variable node to the information model */
        // TODO: 1.Add the variable by the name of string.
        //       2.Add the variable by numeric.
        UA_NodeId my_node_id = UA_NODEID_STRING(variable_description.namespace_index, \
            (char *)variable_description.identifier_string.c_str());
        UA_QualifiedName my_name = UA_QUALIFIEDNAME(variable_description.qualified_name_namespace_index, \
            (char *)variable_description.qualified_name_string.c_str());
        UA_NodeId parent_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
        UA_NodeId parent_reference_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
        UA_StatusCode retval = UA_Server_addVariableNode(variable_description.server, my_node_id, parent_node_id,\
                                  parent_reference_node_id, my_name,\
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),\
                                  attr, NULL, NULL);
        if (retval != UA_STATUSCODE_GOOD) {
            LOG(ERROR) << "Add Variable Node Failed. Error: " << hex << retval;
        }
    }

    /**
     * @brief Write the value by the input data type.
     * 
     * @tparam T 
     * @param write_val 
     */
    template <typename T> 
    void WriteVariableValue(const WriteVariableDescription & variable_description, T & write_val) {
        // Get the node object by the node of namespace_index and only identifier.
        UA_NodeId my_value_nodeid = UA_NODEID_NUMERIC(variable_description.namespace_index,\
            variable_description.identifier);
        // Write the value by the Write UA_Variant Api.
        T my_write_val = write_val;
        UA_Variant my_variant;
        UA_Variant_init(&my_variant);
        // Get the write data type.
        // FIXME: Can't know the Construction failure maybe failed.
        boost::any d_type(my_write_val);
        // TODO: Add the base data type write value as follows.
        if (typeid(UA_UInt16) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_UINT16]);
        } else if (typeid(UA_Int16) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_INT16]);
        } else if (typeid(UA_Int32) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_INT32]);
        } else if (typeid(UA_UInt32) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_UINT32]);
        } else if (typeid(UA_Int64) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_INT64]);
        } else if (typeid(UA_UInt64) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_UINT64]);
        } else if (typeid(UA_Float) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_FLOAT]);
        } else if (typeid(UA_Double) == d_type.type()) {
            UA_Variant_setScalar(&my_variant, &my_write_val, &UA_TYPES[UA_TYPES_DOUBLE]);
        } else {
            LOG(ERROR) << "OpcUa Server Write Variable Value Unknow Data type.";
            return;
        }
        
        UA_StatusCode retval = UA_Server_writeValue(variable_description.server, my_value_nodeid, my_variant);
        if (retval != UA_STATUSCODE_GOOD) {
            LOG(ERROR) << "Write Variable Value Failed. Error: " << hex << retval;
        }
    }

};

#endif