//
//  main.cpp
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>
#include <boost/asio.hpp>

#include "TcpServer.h"

#define PORT_NUMBER 3000

int main(int argc, const char * argv[])
{
    std::cout << "Starting Seeder Server..." << std::endl;
    
    try
    {
        boost::asio::io_context io_context;
        TcpServer server(io_context, PORT_NUMBER);
        
        std::cout << "Seeder Server Running on port " << PORT_NUMBER << std::endl;
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout << "Seeder Server Terminated..." << std::endl;
    return 0;
}
