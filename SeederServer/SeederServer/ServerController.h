//
//  ServerController.h
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#ifndef ServerController_h
#define ServerController_h

#include <string>

#include "Node.h"
#include "TcpConnection.h"

class ServerController
{
public:
    static ServerController* getInstance();
    
    void handleMessage(std::string inMessage, std::weak_ptr<TcpConnection> tcpConn);
    void pingClients();
    
private:
    std::vector<Node> mNodeList;
};

#endif /* ServerController_h */
