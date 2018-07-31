//
//  main.cpp
//  Node Client
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>

#include <boost/array.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "TcpClient.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT_NUMBER 3000

int main(int argc, const char * argv[])
{
    std::cout << "Starting Node Client..." << std::endl;
    
    try
    {
        boost::asio::io_context io_context;
        TcpClient client(io_context, boost::asio::ip::address::from_string(IP_ADDRESS), PORT_NUMBER);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
