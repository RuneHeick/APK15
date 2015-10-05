//
//  messageParser.h
//  ac
//
//  Created by Michael Rahlff on 04/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#ifndef __ac__messageParser__
#define __ac__messageParser__

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "eventJoin.h"
#include "eventMsg.h"
#include "eventWho.h"


class MessageParser{
public:
    MessageParser();
    ~MessageParser();
    
    template<typename T>
    T createEventFromInput(std::string);
    
private:
    EventJoin createJoinEvent();
    EventWho createWhoEvent();
    EventMsg createMsgEvent(std::string);
    
};
#endif /* defined(__ac__messageParser__) */
