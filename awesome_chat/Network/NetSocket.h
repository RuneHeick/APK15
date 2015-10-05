/*
 * NetSocket.h
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#ifndef NETSOCKET_H_
#define NETSOCKET_H_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "../RawPacket.h"
#include <memory>

namespace bip = boost::asio::ip;

class Simple_Socket
{
public:
	Simple_Socket(){};
	Simple_Socket(std::shared_ptr<bip::tcp::socket> soc):socket(soc){};

	Simple_Socket& operator=(Simple_Socket other);
	Simple_Socket(const Simple_Socket& other);

	void connect(const std::string& ip, uint port);
	void disconnect();
	std::shared_ptr<RawPacket> read();
	void write(const std::shared_ptr<RawPacket>& data);
	bool IsOpen() {if(socket) return socket->is_open(); else return false;}

private:
	std::shared_ptr<bip::tcp::socket> socket;
};

class Simple_Server
{
public:
	void Lisen(uint port);

	Simple_Socket Accept();

private:
	std::shared_ptr<bip::tcp::acceptor> acceptorPtr;
	boost::asio::io_service io_service;
};



#endif /* NETSOCKET_H_ */
