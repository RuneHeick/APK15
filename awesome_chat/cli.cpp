//
//  cli.cpp
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "cli.h"
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>


//namespace greg = boost::gregorian;
namespace pt = boost::posix_time;

const std::string Cli::LOGTYPE_INFO = "INFO";
const std::string Cli::LOGTYPE_WARNING = "WARNING";
const std::string Cli::LOGTYPE_ERROR = "ERROR";

Cli::Cli()
{
    
}

Cli::~Cli()
{
    
}


std::string Cli::getUserString(const std::string requestPrint)
{
	Cli::writeDebugMsg(Cli::LOGTYPE_INFO, requestPrint);
    std::cout << "<< ";
    std::string temp;
    std::getline(std::cin, temp);
    return temp;
}

/* Request an integer from the user.
 * If conversion of the input fails an error message is printed.
 * The exceptions of std::stoi() is rethrown.
 */
int Cli::getUserInt(const std::string requestPrint)
{
	std::string str = getUserString(requestPrint);
	int value;
	try {
		value = std::stoi(str);
	} catch(std::out_of_range& e) {
		Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Input value out of range.");
		throw;
	} catch(std::invalid_argument& e) {
		Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Invalid input - unable to convert to an integer.");
		throw;
	}

	return value;
}

void Cli::writeDebugMsg(const std::string logtype,const std::string msg)
{
    std::cout << pt::second_clock::local_time().time_of_day() << " [" <<logtype << "]: " << msg << std::endl;
}

void Cli::writeLogMsg(const std::string msg)
{
    
}

void Cli::writeChatMsg(const std::string name, const std::string msg)
{
    std::cout << pt::second_clock::local_time().time_of_day() << " [" << name << "]: " << msg << std::endl;
}
