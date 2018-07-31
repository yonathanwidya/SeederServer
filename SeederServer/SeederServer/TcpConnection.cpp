//
//  TcpConnection.cpp
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>
#include <thread>

#include <boost/asio/placeholders.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>

#include "TcpConnection.h"
#include "ServerController.h"

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
: mSocket(io_context)
{
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
    return std::shared_ptr<TcpConnection>(new TcpConnection(io_context));
}

boost::asio::ip::tcp::socket& TcpConnection::socket()
{
    return mSocket;
}

void TcpConnection::start()
{
    readMessage();
    std::thread( [this] { pingClients(); } ).detach();
}

void TcpConnection::readMessage()
{
    boost::asio::async_read_until(mSocket, mIncomingBuffer, "\r",
                                  boost::bind(&TcpConnection::handleRead, shared_from_this(),
                                              boost::asio::placeholders::error));
}

void TcpConnection::writeMessage(std::string message)
{
    std::string messageToSend = message + "\r";
    boost::asio::async_write(mSocket, boost::asio::buffer(messageToSend),
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error));
}

void TcpConnection::pingClients()
{
    while (true)
    {
        ServerController::getInstance()->pingClients();
        usleep(100000);
    }
}

void TcpConnection::handleRead(const boost::system::error_code& error)
{
    if (error && error != boost::asio::error::eof)
    {
        std::cerr << "Error while reading buffer: " << error.message() << std::endl;
        return;
    }
    
    std::string message;
    std::istream is(&mIncomingBuffer);
    std::getline(is, message, '\r');
    
    if (!message.empty())
    {
        //std::cout << message << std::endl;
        ServerController::getInstance()->handleMessage(message, shared_from_this());
    }
    
    // continue to wait and read the next message
    readMessage();
}

void TcpConnection::handleWrite(const boost::system::error_code& error)
{
    if (error)
    {
        std::cerr << "Error while sending message: " << error << std::endl;
        return;
    }
}
