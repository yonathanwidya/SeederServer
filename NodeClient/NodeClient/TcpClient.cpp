//
//  TcpClient.cpp
//  Node Client
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>
#include <thread>

#include <boost/array.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>

#include "TcpClient.h"

TcpClient::TcpClient(boost::asio::io_context& io_context, boost::asio::ip::address ipAddress, int portNum)
: mSocket(io_context)
, mEndpoint(ipAddress, portNum)
{
    startConnect();
}

void TcpClient::startConnect()
{
    mSocket.async_connect(mEndpoint,
                          boost::bind(&TcpClient::handleConnect, this,
                                      boost::asio::placeholders::error));
}

void TcpClient::readMessage()
{
    boost::asio::async_read_until(mSocket, mIncomingBuffer, "\r",
                                  boost::bind(&TcpClient::handleRead, this,
                                              boost::asio::placeholders::error));
}

void TcpClient::writeMessage(std::string message)
{
    std::string messageToSend = message + "\r";
    boost::asio::async_write(mSocket, boost::asio::buffer(messageToSend),
                             boost::bind(&TcpClient::handleWrite, this,
                                         boost::asio::placeholders::error));
    
    if (message != "Pong")
    {
        std::cout << "Me: " << message << std::endl;
    }
}

void TcpClient::runMainFlow()
{
    std::string userOption =
    "List of available command options:\n"
    "1. Query all available nodes.\n"
    "2. List of nodes which are alive during the last 1 hour.\n"
    "3. List of nodes which are alive during the last 2 hours.\n"
    "4. List of nodes which are alive during the last 1 day.\n"
    "At any point of time, please type the command number that you want to do.\n\n";
    
    std::cout << userOption;
    
    writeMessage("Hello");
    readMessage();
    
    std::thread( [this] { takeUserInput(); } ).detach();
}

void TcpClient::takeUserInput()
{
    while (true)
    {
        int choice;
        std::cin >> choice;
        std::cout << std::endl;
        
        switch (choice)
        {
            case 1:
                writeMessage("List all available nodes");
                break;
            case 2:
                writeMessage("List the nodes that are alive during the last 1 hour");
                break;
            case 3:
                writeMessage("List the nodes that are alive during the last 2 hours");
                break;
            case 4:
                writeMessage("List the nodes that are alive during the last 1 day");
                break;
            default:
                writeMessage(std::to_string(choice));
                break;
        }
    }
}

void TcpClient::handleConnect(const boost::system::error_code& error)
{
    if (error)
    {
        std::cerr << "Error while connecting to server: " << error.message() << std::endl;
        return;
    }
    
    std::cout << "Connected to Seeder Server.\n" << std::endl;
    
    try
    {
        runMainFlow();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TcpClient::handleRead(const boost::system::error_code& error)
{
    if (error && error != boost::asio::error::eof)
    {
        std::cerr << "Error while reading message: " << error << std::endl;
        return;
    }
    
    std::string message;
    std::istream is(&mIncomingBuffer);
    std::getline(is, message, '\r');
    
    if (!message.empty() && message != "Ping")
    {
        std::cout << "Seeder Server: " << message << std::endl;
        std::cout << std::endl;
    }
    else if (message == "Ping")
    {
        writeMessage("Pong");
    }
    
    // continue to wait and read the next messages
    readMessage();
}

void TcpClient::handleWrite(const boost::system::error_code& error)
{
    if (error)
    {
        std::cerr << "Error while writing message: " << error << std::endl;
    }
}
