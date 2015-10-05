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
T MessageParser::createEventFromInput(std::string user, std::string command)
{
    if(command.size() > 0)
    {
        try
        {
            // We first check to see if the command is a basic msg
            if(command.substr(0,1) != "/")
            {
                T temp = createMsgEvent(user, command);
                return temp;
                
            }else if (command.substr(1,3) == "who")
            {
                
                T temp = createWhoEvent(user);
                return temp;
                
            }else if (command.substr(1,4) == "join")
            {
                // 6'th place is the first char of the target room name.
                // ETC /join myRoom
                T temp = createJoinEvent(user, command.substr(6));
                return temp;
                
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

EventJoin MessageParser::createJoinEvent(std::string usr, std::string room)
{
    Cli::writeDebugMsg(usr + " created a Join event created. Target room = " + room);
    EventJoin e_join(usr, room);
    return e_join;
}

EventWho MessageParser::createWhoEvent(std::string usr)
{
    Cli::writeDebugMsg(usr + " created a Who event.");
    EventWho e_who(usr);
    return e_who;
}

EventMsg MessageParser::createMsgEvent(std::string usr, std::string msg)
{
    Cli::writeDebugMsg(usr + " created a Msg event. Msg = " + msg);
    EventMsg e_msg(usr, msg);
    return e_msg;
}
