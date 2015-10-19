//
//  messageParser.cpp
//  ac
//
//  Created by Michael Rahlff on 04/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#include "messageParser.h"
#include <system_error>
#include <boost/tokenizer.hpp>


MessageParser::MessageParser()
{
    
}
MessageParser::~MessageParser()
{
    
}

// This function use substr which throws and out-of-range exception This exception is handled inside the function
EventVariant MessageParser::createEventFromInput(std::string user, std::string command)
{
	if(command.size() > 0)
	{
		try
		{
			// We first check to see if the command is a basic msg
			if(command.substr(0,1) != "/")
			{
				EventVariant temp = createMsgEvent(user, command);
				return temp;

			}else if (command.substr(1,3) == "who")
			{

				EventVariant temp = createWhoEvent();
				return temp;

			}else if (command.substr(1,4) == "join")
			{
				boost::char_separator<char> sep(" ");
				boost::tokenizer<boost::char_separator<char> > tokens(command, sep);
				auto itr = tokens.begin();

				if( std::distance(itr, tokens.end()) == 3)
				{
					itr++;
					std::string username = *itr;
					itr++;
					std::string room = *itr;

					EventVariant temp = createJoinEvent(username, room);
					return temp;
				}
				else
				{
					Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Join usage : /join <Name> <Room>");
					throw std::system_error(EINVAL, std::generic_category());
				}

			}else{
				Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Invalid command!");
                throw std::system_error(EINVAL, std::generic_category());
			}

		}catch (const std::out_of_range& oor)
		{
			Cli::writeDebugMsg( "Out of range exception");
            throw;
		}
	}else
	{
		Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Command to short");
        throw std::system_error(EINVAL, std::generic_category());
	}

}

EventJoin MessageParser::createJoinEvent(std::string usr, std::string room)
{
    Cli::writeDebugMsg(usr + " created a Join event. Target room = " + room);
    EventJoin e_join(usr, room);
    return e_join;
}

EventWho MessageParser::createWhoEvent()
{
    Cli::writeDebugMsg(" created a Who event.");
    EventWho e_who;
    return e_who;
}

EventMsg MessageParser::createMsgEvent(std::string usr, std::string msg)
{
    Cli::writeDebugMsg(usr + " created a Msg event. Msg = " + msg);
    EventMsg e_msg(usr, msg);
    return e_msg;
}

