//
//  messageParser.cpp
//  ac
//
//  Created by Michael Rahlff on 04/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#include "messageParser.h"
#include "cli.h"



MessageParser::MessageParser()
{
    
}
MessageParser::~MessageParser()
{
    
}

/* This function use substr which throws and out-of-range exception
    This exception is handled inside the function*/
template<typename T>
T MessageParser::createEventFromInput(std::string command)
{
    if(command.size() > 0)
    {
        try
        {
            // We first check to see if the command is a basic msg
            if(command.substr(0,1) != "/")
            {
                return createMsgEvent(command);
                
            }else if (command.substr(1,3) == "who")
            {
                return createWhoEvent();
                
            }else if (command.substr(1,4) == "join")
            {
                return createJoinEvent();
                
            }else{
                Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Invalid command!");
            }

        }catch (const std::out_of_range& oor)
        {
            Cli::writeDebugMsg( "Out of range exception");
        }
    }else
    {
        Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Command to short");
    }
}
EventJoin MessageParser::createJoinEvent()
{
    Cli::writeDebugMsg("Join event created");
}
EventWho MessageParser::createWhoEvent()
{
    Cli::writeDebugMsg("Who event created");
}
EventMsg MessageParser::createMsgEvent(std::string)
{
    Cli::writeDebugMsg("Msg event created");
}
