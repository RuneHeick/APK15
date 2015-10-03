//
//  cli.h
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#ifndef ac_cli_h
#define ac_cli_h

#include <string>

class Cli {
    
public:
    Cli();
    ~Cli();
    
    std::string getUserInput();
    
    static void writeDebugMsg(const std::string, const std::string);
    static void writeLogMsg(const std::string);
    static void writeChatMsg(const std::string, const std::string);
    
    static const std::string LOGTYPE_INFO;
    static const std::string LOGTYPE_WARNING;
    static const std::string LOGTYPE_ERROR;
private:
    
};

#endif
