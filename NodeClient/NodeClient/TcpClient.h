//
//  TcpClient.h
//  Node Client
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#ifndef TcpClient_h
#define TcpClient_h

#include <string>
#include <thread>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

class TcpClient
{
public:
    TcpClient(boost::asio::io_context& io_context, boost::asio::ip::address ipAddress, int portNum);
    
    void readMessage();
    void writeMessage(std::string message);
    
private:
    void startConnect();
    void runMainFlow();
    void takeUserInput();
    
    void handleConnect(const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);
    
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::ip::tcp::endpoint mEndpoint;
    boost::asio::streambuf mIncomingBuffer;
};

#endif /* TcpClient_h */
