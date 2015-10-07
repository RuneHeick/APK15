//
//  roomHandler.cpp
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#include <string>
#include "roomHandler.h"
#include "cli.h"
#include "Network/clientInfo.h"

RoomHandler::RoomHandler(std::string defaultRoomName)
{
    getRoom(defaultRoomName);
}


RoomHandler::~RoomHandler()
{
    
}


std::shared_ptr<Room> RoomHandler::getRoom(std::string roomName)
{
    // Find the room and return it
    for (auto it = rooms_.begin(); it != rooms_.end(); it++)
    {
        if(roomName == (*it)->getName())
        {
            return *it;
        }
    }
    // ... or create a new room, save it in vector and return it
    std::shared_ptr<Room> roomPtr(new Room(roomName));
    addRoom(roomPtr);
    return roomPtr;
}

std::shared_ptr<Room> RoomHandler::createNewRoom(std::string roomName)
{
    std::shared_ptr<Room> roomPtr(new Room(roomName));
    return roomPtr;
}


void RoomHandler::addRoom(std::shared_ptr<Room> room)
{
    rooms_.push_back(room);
}


void RoomHandler::deleteRoom(std::string name_)
{
    for (auto it = rooms_.begin(); it != rooms_.end(); ) {
        
        if (name_ == (*it)->getName())
        {
            rooms_.erase(it);
        }else
        {
            it++;
        }
    }
}


void RoomHandler::printAllRooms()
{
    for (auto it = rooms_.begin(); it != rooms_.end(); it++)
    {
        Cli::writeDebugMsg((*it)->getName());
    }
}
