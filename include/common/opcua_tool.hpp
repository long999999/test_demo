#ifndef OPCUA_TOOL_H
#define OPCUA_TOOL_H

#include <iostream>
#include <sstream>    

#include <glog/logging.h>

#include <boost/regex.hpp>

#include "open62541.h"

using namespace std;


class OpcUaTool
{
public:
    OpcUaTool() {};
    virtual ~OpcUaTool() {};
    template <class Type> Type StringToNum(const string& str) {
        istringstream iss(str);
        Type num;
        iss >> num;
        return num;
    }
    /**
     * @brief Get the Namespace Id And Identifier.
     * 
     * @param[out] namespace_id Node of namespace id.
     * @param[out] identifier Node of identifier.
     */
    void GetNamespaceIdAndIdentifier(string regex_str, string & namespace_id, string & identifier) {
        /**
         * example1:
         * 2:the.answer
         * what[0]:2:the.answer
         * what[1]:2
         * what[2]:the.answer
         * example2:
         * 2:6022
         * what[0]:2:6022
         * what[1]:2
         * what[2]:6022
         */

        boost::regex expression("(.*?):(.*)");
        boost::smatch what;

        if ( !boost::regex_search(regex_str, what, expression) ) {
            LOG(ERROR) << "Get NamespaceId And Identifier RegexNorthMsgId failed.";
            return;
        }

        // Get namespace id string.
        if (!what[1].matched) {
            LOG(ERROR) << "GetNamespaceIdAndIdentifier boost::regex_search namespace id failed.";
            return;
        }
        namespace_id = what[1];

        // Get identifier.
        if (!what[2].matched) {
            LOG(ERROR) << "GetNamespaceIdAndIdentifier boost::regex_search identifier failed.";
            return;
        }
        identifier = what[2];
    }

    void TransferNamespaceIdAndIdentifier(string str_namespace_id, string str_identifier,\
        UA_UInt16 & namespace_index, UA_UInt32 & identifier) {
        namespace_index = StringToNum<UA_UInt16>(str_namespace_id);
        identifier = StringToNum<UA_UInt32>(str_identifier);
    }
};

#endif // OPCUA_TOOL_H