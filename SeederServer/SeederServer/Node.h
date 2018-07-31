//
//  Node.h
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 31/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include "TcpConnection.h"

class Node
{
public:
    Node(std::weak_ptr<TcpConnection> connAddress);
    ~Node();
    
    std::weak_ptr<TcpConnection> getConnAddress();
    void setLatestAliveTime(std::chrono::time_point<std::chrono::system_clock> time);
    bool isAlive();
    double getAliveDuration();
    
    bool isValid();
    void setInvalid();
    
private:
    std::weak_ptr<TcpConnection> mConnAddress;
    std::chrono::time_point<std::chrono::system_clock> mCreationTime;
    std::chrono::time_point<std::chrono::system_clock> mLatestAliveTime;
    bool mIsValid;
};

#endif /* Node_h */
