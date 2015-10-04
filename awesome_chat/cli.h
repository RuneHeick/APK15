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
    
    static std::string getUserInput();
    static std::string getUserString(const std::string PrintedRequest);
    static int getUserInt(const std::string PrintedRequest);
    
    static void writeDebugMsg(const std::string);
    static void writeLogMsg(const std::string, const std::string);
    static void writeChatMsg(const std::string, const std::string);
    
    static const std::string LOGTYPE_INFO;
    static const std::string LOGTYPE_WARNING;
    static const std::string LOGTYPE_ERROR;
private:
    
};

#endif
