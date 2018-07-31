cmake_minimum_required(VERSION 3.5)
project(SeederServer)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Boost 1.67 REQUIRED COMPONENTS system)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(SOURCE_FILES main.cpp
		 TcpServer.cpp
		 TcpConnection.cpp
		 ServerController.cpp
		 Node.cpp)

add_executable(SeederServer ${SOURCE_FILES})
target_link_libraries(SeederServer ${Boost_LIBRARIES})
