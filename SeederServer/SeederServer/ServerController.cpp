//
//  ServerController.cpp
//  SeederServer
//
//  Created by Yonathan Widya Adipradana on 30/7/18.
//  Copyright © 2018 Yonathan Widya Adipradana. All rights reserved.
//

#include <iostream>

#include "ServerController.h"

#define ONE_HOUR_IN_SECS 3600
#define TWO_HOURS_IN_SECS 7200
#define ONE_DAY_IN_SECS 86400

static ServerController* g_serverController = nullptr;

ServerController* ServerController::getInstance()
{
    if (g_serverController == nullptr)
    {
        g_serverController = new ServerController();
    }
    return g_serverController;
}

void ServerController::pingClients()
{
    for (auto iter = mNodeList.begin(); iter != mNodeList.end(); ++iter)
    {
        if (iter->isValid() && !iter->isAlive())
        {
            iter->setInvalid();
            std::cout << "A node has been removed from the list." << std::endl;
            
            continue;
        }
        
        if (auto tcpConn = iter->getConnAddress().lock())
        {
            tcpConn->writeMessage("Ping");
        }
    }
}

void ServerController::handleMessage(std::string inMessage, std::weak_ptr<TcpConnection> tcpConn)
{
    std::string outMessage;
    
    if (inMessage == "Hello")
    {
        mNodeList.push_back(Node(tcpConn));
        outMessage = "Hello and Welcome! We are adding you to the nodes list.";
    }
    else if (inMessage == "Pong")
    {
        auto timeNow = std::chrono::system_clock::now();
        for (auto iter = mNodeList.begin(); iter != mNodeList.end(); ++iter)
        {
            if (iter->getConnAddress().lock() == tcpConn.lock())
            {
                iter->setLatestAliveTime(timeNow);
                break;
            }
        }
    }
    else if (inMessage == "List all available nodes" ||
             inMessage == "List the nodes that are alive during the last 1 hour" ||
             inMessage == "List the nodes that are alive during the last 2 hours" ||
             inMessage == "List the nodes that are alive during the last 1 day")
    {
        std::string unavailableMessage;
        std::string introMessage;
        double minAliveDuration = 0;
        
        if (inMessage == "List all available nodes")
        {
            unavailableMessage = "No other available nodes in our list.";
            introMessage = "This is the list of all of the available nodes";
        }
        else
        {
            unavailableMessage = "No other nodes has been alive during the last ";
            introMessage = "This is the list of nodes that has been alive during the last ";
            
            if (inMessage == "List the nodes that are alive during the last 1 hour")
            {
                unavailableMessage += "1 hour.";
                introMessage += "1 hour";
                minAliveDuration = ONE_HOUR_IN_SECS;
            }
            else if (inMessage == "List the nodes that are alive during the last 2 hours")
            {
                unavailableMessage += "2 hours.";
                introMessage += "2 hours";
                minAliveDuration = TWO_HOURS_IN_SECS;
            }
            else if (inMessage == "List the nodes that are alive during the last 1 day")
            {
                unavailableMessage += "1 day.";
                introMessage += "1 day";
                minAliveDuration = ONE_DAY_IN_SECS;
            }
        }
        
        if (mNodeList.empty() ||
            (mNodeList.size() == 1 && mNodeList.begin()->getConnAddress().lock() == tcpConn.lock()))
        {
            outMessage = unavailableMessage;
        }
        else
        {
            int nodeCounter = 0;
            std::ostringstream stringStream;
            
            for (auto iter = mNodeList.begin(); iter != mNodeList.end(); ++iter)
            {
                if (iter->getConnAddress().lock() == tcpConn.lock() ||
                    !iter->isValid() ||
                    iter->getAliveDuration() < minAliveDuration)
                {
                    continue;
                }
                
                stringStream << "\n" << ++nodeCounter << ". " << iter->getConnAddress().lock();
            }
            
            if (nodeCounter == 0)
            {
                outMessage = unavailableMessage;
            }
            else
            {
                outMessage = introMessage + stringStream.str();
            }
        }
    }
    else
    {
        outMessage = "Sorry, we don't understand what you were saying. Please try again.";
    }
    
    //std::cout << outMessage << std::endl;
    if (tcpConn.lock())
    {
        tcpConn.lock()->writeMessage(outMessage);
    }
}
