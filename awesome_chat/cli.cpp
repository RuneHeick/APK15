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

Cli cli;

Cli::Cli()
{
    
}

Cli::~Cli()
{
    
}

std::string Cli::getUserInput()
{
    std::cout << "<< ";
    std::string temp;
    std::getline(std::cin, temp);
    return temp;
}

void Cli::writeDebugMsg(const std::string logtype,const std::string msg) const
{
    std::cout << pt::second_clock::local_time().time_of_day() << " [" <<logtype << "]: " << msg << std::endl;
}

void Cli::writeLogMsg(const std::string msg) const
{
    
}

void Cli::writeChatMsg(const std::string name, const std::string msg) const
{
    std::cout << pt::second_clock::local_time().time_of_day() << " [" << name << "]: " << msg << std::endl;
}
