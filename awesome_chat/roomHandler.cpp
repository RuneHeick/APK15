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

RoomHandler::RoomHandler(std::string defaultRoomName) : m_DefaultRoomName(defaultRoomName)
{
    getRoom(m_DefaultRoomName);
}


RoomHandler::~RoomHandler()
{
    
}


std::shared_ptr<Room> RoomHandler::getRoom(std::string roomName)
{
    
    std::lock_guard<std::mutex> lock(rooms_lock_);
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


void RoomHandler::addRoom(std::shared_ptr<Room> room)
{
    std::lock_guard<std::mutex> lock(rooms_lock_);
    rooms_.push_back(room);
}


void RoomHandler::deleteRoom(std::string name_)
{
	if( !name_.compare(m_DefaultRoomName) ) { // Don't delete the default room.
		std::lock_guard<std::mutex> lock(rooms_lock_);
		for (auto it = rooms_.begin(); it != rooms_.end(); ) {

			if (name_ == (*it)->getName()) {
				rooms_.erase(it); // makes iterator invalid.
				return;
			} else  {
				it++;
			}
		}
	}
}


void RoomHandler::printAllRooms()
{
    std::lock_guard<std::mutex> lock(rooms_lock_);
    for (auto it = rooms_.begin(); it != rooms_.end(); it++)
    {
        Cli::writeDebugMsg((*it)->getName());
    }
}
