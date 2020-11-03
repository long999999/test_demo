#
# For x64 compile, please use command
# cmake ..
# For arm cross compile, please use command
# cmake -DPLATFORM=arm ..
# make -j8
#

cmake_minimum_required(VERSION 3.5)

project(freeopc_demo)

option(BUILD_OPCUA_CLIENT "Build OpcUa client" OFF)
option(BUILD_OPCUA_SERVER "Build OpcUa server" ON)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        ""
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

if(PLATFORM MATCHES "arm")
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)

    set(CMAKE_C_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-g++)

    set(GNU_CXX_FLAGS "-mfpu=vfp -std=c++11 -fPIC -g -W -O2 -DBOOST_ASIO_DISABLE_STD_FUTURE")
    set(GNU_C_FLAGS "-mfpu=vfp -fPIC -g -W -O2 -std=c99")
    set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")

else()
    set(GNU_CXX_FLAGS "-DCOM_X64 -g -W -std=c++11")
    set(GNU_C_FLAGS "-DCOM_X64 -g -W -std=c99")
    set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")
    
endif()

# Client library
if(BUILD_OPCUA_CLIENT)
    message(STATUS "Build OpcUa client")

    include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/open62541/include)
    link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/open62541/lib)

    include_directories(${CMAKE_CURRENT_LIST_DIR}/include/client)
    aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/client CLIENT_SRC)
    
    add_library(opcua_client ${CLIENT_SRC})


endif(BUILD_OPCUA_CLIENT)

# Server library
if(BUILD_OPCUA_SERVER)

    message(STATUS "Build OpcUa Server")

    if(PLATFORM MATCHES "arm")

        # include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/open62541/include)
        # link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/open62541/lib)

        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/glog/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/glog/lib)

        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/jsoncpp/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/jsoncpp/lib)

        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/boost/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/boost/lib)

        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/common)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/server)

        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/server SERVER_SRC)

        add_library(opcua_server ${SERVER_SRC})
        target_link_libraries(opcua_server glog pthread rt boost_system boost_regex
            ${CMAKE_CURRENT_LIST_DIR}/libs/arm/open62541/lib/libopen62541.a
            ${CMAKE_CURRENT_LIST_DIR}/libs/arm/jsoncpp/lib/libjsoncpp.a)

    else()

        set(GNU_CXX_FLAGS "-DCOM_X64 -g -W -std=c++11")
        set(GNU_C_FLAGS "-DCOM_X64 -g -W -std=c99")
        set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
        set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")
    
        # include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/open62541/include)
        # link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/open62541/lib)

        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/common)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/server)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/server SERVER_SRC)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/csou SERVER_SRC)

        add_library(opcua_server ${SERVER_SRC})
        target_link_libraries(opcua_server open62541 glog pthread rt jsoncpp boost_system boost_regex)
        # target_link_libraries(opcua_server glog pthread rt jsoncpp boost_system boost_regex)

    endif()

endif(BUILD_OPCUA_SERVER)
