//
//  TcpConnection.h
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#ifndef TcpConnection_h
#define TcpConnection_h

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> pointer;
    
    static pointer create(boost::asio::io_context& io_context);
    boost::asio::ip::tcp::socket& socket();
    
    void start();
    void readMessage();
    void writeMessage(std::string message);
    
private:
    TcpConnection(boost::asio::io_context& io_context);
    
    void pingClients();
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);
    
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::streambuf mIncomingBuffer;
};

#endif /* TcpConnection_h */
