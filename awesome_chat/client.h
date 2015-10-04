
#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdint>
#include <string>

class client {
public:
	client();
	~client();
	void Connect(std::string ip, uint16_t port);
};

#endif /* CLIENT_H_ */
