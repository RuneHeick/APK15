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

class Room {
    
public:
    Room(std::string name);
    ~Room();
    std::string getName();
private:
    std::string name_;
};

#endif /* defined(__ac__room__) */
