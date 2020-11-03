
cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt)

if(BUILD_OPCUA_CLIENT)
    add_executable(client client.cpp ${CLIENT_SRC})
    target_link_libraries(client opcua_client)

endif(BUILD_OPCUA_CLIENT)

if(BUILD_OPCUA_SERVER)
    add_executable(server server.cpp ${SERVER_SRC})
    target_link_libraries(server opcua_server)

endif(BUILD_OPCUA_SERVER)

