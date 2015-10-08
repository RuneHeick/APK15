//
//  room.cpp
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#include "room.h"

Room::Room(std::string name)
{
    name_ = name;
}

Room::~Room()
{
    
}

std::string Room::getName()
{
    return name_;
}


void Room::broadcastMsg(EventMsg msg)
{
    EventVariant temp = msg;
    std::lock_guard<std::mutex> lock(clients_lock_); // todo dette skal gøres mere konsistent. - Formentlig fjernes?
    for (auto it = clients_.begin(); it != clients_.end(); it++) {
        (*it)->Send(temp);
    }
}

bool Room::isEmpty() {
	return clients_.empty();
}

void Room::addClient(std::shared_ptr<ClientInfo> client)
{
    clients_.push_back(client);
}

void Room::removeClient(std::shared_ptr<ClientInfo> client)
{
    for (auto it = clients_.begin(); it != clients_.end(); ) {
        
        if ((*it) == client) {
            clients_.erase(it);
            return;
        }else
        {
            // We only increase the iterator if we DONT delete anything
            it++;
        }
    }
}

