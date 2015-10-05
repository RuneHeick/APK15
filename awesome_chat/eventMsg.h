#include "event.h"
#include <string>

MK_EVENT(EventMsg)
{
public:
    EventMsg(std::string sender, std::string msg);
    ~EventMsg();
    
private:
    std::string sender_;
    std::string msg_;
    
};