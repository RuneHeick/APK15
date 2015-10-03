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
    
    void writeDebugMsg(const std::string, const std::string) const;
    void writeLogMsg(const std::string) const;
    void writeChatMsg(const std::string, const std::string) const;
    
    const std::string LOGTYPE_INFO = "INFO";
    const std::string LOGTYPE_WARNING = "WARNING";
    const std::string LOGTYPE_ERROR = "ERROR";
private:
    
};

#endif
