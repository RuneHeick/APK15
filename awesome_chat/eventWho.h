#include "event.h"
#include <string>

MK_EVENT(EventWho)
{
public:
    EventWho(std::string usr);
    ~EventWho();
    
private:
    std::string user;
    
};