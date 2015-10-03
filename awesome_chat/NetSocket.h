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
#include "RawPacket.h"
#include <boost/asio/buffer.hpp">

namespace bip = boost::asio::ip;

class Client
{
public:
	Client(){};
	Client(boost::shared_ptr<bip::tcp::socket> soc):socket(soc)
	{};
	void connect(std::string ip, uint port);
	void disconnect();
	boost::shared_ptr<RawPacket> read();
	void write(boost::shared_ptr<RawPacket> data);
	bool IsOpen() {return isOpen;}

private:
	boost::shared_ptr<bip::tcp::socket> socket;
	bool isOpen = false;
};

class Server
{
public:
	void Lisen(uint port);

	Client Accept();

private:
	boost::shared_ptr<bip::tcp::acceptor> acceptorPtr;
	boost::asio::io_service io_service;
};



#endif /* NETSOCKET_H_ */
