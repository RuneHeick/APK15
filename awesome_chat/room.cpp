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

void Room::broadcastMsg(std::string)
{
    
}