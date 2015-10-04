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

class MessageParser{
public:
    MessageParser();
    ~MessageParser();
    void createEventFromInput(std::string);
private:
    void createJoinEvent();
    void createWhoEvent();
    void createMsgEvent(std::string);
    
};
#endif /* defined(__ac__messageParser__) */
