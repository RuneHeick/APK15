//
//  roomHandler.h
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#ifndef __ac__roomHandler__
#define __ac__roomHandler__

#include <stdio.h>
#include <vector>
#include <memory>
#include "room.h"
#include "Network/clientInfo.h"
#include <mutex>

class RoomHandler{
public:
    RoomHandler(std::string defaultRoomName);
    ~RoomHandler();

    std::shared_ptr<Room> getRoom(std::string roomName);
    void addRoom(std::shared_ptr<Room>);
    void deleteRoom(std::string);

    void printAllRooms();
    
private:
    std::vector< std::shared_ptr< Room >> rooms_;
    std::mutex rooms_lock_;
    const std::string m_DefaultRoomName;
};
#endif /* defined(__ac__roomHandler__) */
