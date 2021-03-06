//
//  room.h
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#ifndef __ac__room__
#define __ac__room__

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "Network/clientInfo.h"
#include <mutex>
#include "Events/Events.hpp"

class ClientHandler; // forward declaration

class Room {
	friend class ClientHandler;
public:
    Room(std::string name);
    ~Room(){};
    std::string getName();
    void broadcastMsg(EventMsg msg);
    void addClient(std::shared_ptr<ClientInfo>);
    void removeClient(std::shared_ptr<ClientInfo>);
    bool isEmpty();
private:
    std::string name_;
    std::vector<std::shared_ptr< ClientInfo > > clients_;
};

#endif /* defined(__ac__room__) */
