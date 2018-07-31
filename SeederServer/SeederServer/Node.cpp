//
//  Node.cpp
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 31/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>
#include "Node.h"

#define INACTIVE_TIME_THRESHOLD 1 // in seconds

Node::Node(std::weak_ptr<TcpConnection> connAddress)
: mConnAddress(connAddress)
, mIsValid(true)
{
    mCreationTime = std::chrono::system_clock::now();
    mLatestAliveTime = mCreationTime;
}

Node::~Node()
{
    mConnAddress.reset();
}

std::weak_ptr<TcpConnection> Node::getConnAddress()
{
    return mConnAddress;
}

void Node::setLatestAliveTime(std::chrono::time_point<std::chrono::system_clock> time)
{
    mLatestAliveTime = time;
}

bool Node::isAlive()
{
    if (!mConnAddress.lock())
    {
        return false;
    }
    
    auto timeNow = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = timeNow - mLatestAliveTime;
    
    return diff.count() < INACTIVE_TIME_THRESHOLD;
}

double Node::getAliveDuration()
{
    std::chrono::duration<double> diff = mLatestAliveTime - mCreationTime;
    return diff.count();
}

bool Node::isValid()
{
    return mIsValid;
}

void Node::setInvalid()
{
    mIsValid = false;
}
