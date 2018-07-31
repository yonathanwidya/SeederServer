//
//  TcpServer.cpp
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include "TcpServer.h"

TcpServer::TcpServer(boost::asio::io_context& io_context, int portNum)
: mAcceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portNum))
{
    startAccept();
}

void TcpServer::startAccept()
{
    // creates a socket
    TcpConnection::pointer new_connection = TcpConnection::create(mAcceptor.get_io_service());
    
    // initiates an asynchronous accept operation
    mAcceptor.async_accept(new_connection->socket(),
                           boost::bind(&TcpServer::handleAccept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void TcpServer::handleAccept(TcpConnection::pointer new_connection,
                             const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }
    
    // initiate the next accept operation.
    startAccept();
}
