#include "NetSocket.h"


void Server::Lisen(uint port)
{
	acceptorPtr = boost::shared_ptr<bip::tcp::acceptor>(new bip::tcp::acceptor(io_service, bip::tcp::endpoint(bip::tcp::v4(), port)));
}

Client Server::Accept()
{
	if(acceptorPtr)
	{
		boost::shared_ptr<bip::tcp::socket> socPtr = boost::shared_ptr<bip::tcp::socket>(new bip::tcp::socket(io_service));
		acceptorPtr->accept(*socPtr);

		return Client(socPtr);
	}
	return boost::shared_ptr<bip::tcp::socket>();
}

void Client::connect(std::string ip, uint port)
{

	boost::asio::io_service io_service;
	bip::tcp::resolver resolver(io_service);
	bip::tcp::resolver::query query(ip, boost::lexical_cast<std::string>(port));

	bip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	bip::tcp::resolver::iterator end;


	socket = boost::shared_ptr<bip::tcp::socket>(new bip::tcp::socket(io_service));
	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endpoint_iterator != end)
	{
	  socket->close();
	  socket->connect(*endpoint_iterator++, error);
	}

	if (error)
	  throw boost::system::system_error(error);

	isOpen = true;

}

boost::shared_ptr<RawPacket> Client::read()
{
	  try
	  {
		  uint8_t lenbuffer[2];
		  size_t len = socket->receive(boost::asio::buffer(lenbuffer,2));
		  if(len == 2)
		  {
			  size_t packetSize = (lenbuffer[0]<<8)+lenbuffer[1];
			  boost::shared_ptr<RawPacket> packet(new RawPacket(packetSize));
			  size_t recivedPlen = 0;
			  while(recivedPlen < packetSize)
			  {
				  recivedPlen += socket->receive(boost::asio::buffer(&packet->Packet()[recivedPlen],packetSize-recivedPlen));
			  }


			  return packet;
		  }
	  }
	  catch(boost::system::system_error & e)
	  {
		  isOpen = false;
		  if(e.code() == boost::asio::error::eof)
		  {
			  return boost::shared_ptr<RawPacket>(new RawPacket(0));
		  }
		  else
		  {
			  //Close
			  throw;
		  }
	  }

	  return boost::shared_ptr<RawPacket>(new RawPacket(0));

}

void Client::write(boost::shared_ptr<RawPacket> data)
{

	try
	{
		uint8_t lenbuffer[2] = {static_cast<uint8_t>((data->Size()<<8)), static_cast<uint8_t>(data->Size())};
		socket->send(boost::asio::buffer(lenbuffer,2));
		socket->send(boost::asio::buffer(data->Packet(),data->Size()));
	}
	catch(boost::system::system_error & e)
	{
	  isOpen = false;
	  if(e.code() != boost::asio::error::eof)
	  {
		  throw;
	  }
	}
}

void Client::disconnect()
{
	if(isOpen)
	{
		isOpen = false;
		socket->close();
	}
}
