//
//  TcpServer.h
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#ifndef TcpServer_h
#define TcpServer_h

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "TcpConnection.h"

class TcpServer
{
public:
    TcpServer(boost::asio::io_context& io_context, int portNum);
    
private:
    void startAccept();
    void handleAccept(TcpConnection::pointer new_connection,
                       const boost::system::error_code& error);
    
    boost::asio::ip::tcp::acceptor mAcceptor;
};

#endif /* TcpServer_h */
