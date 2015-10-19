#include "NetSocket.h"

void Simple_Server::Lisen(uint port)
{
	acceptorPtr = std::shared_ptr<bip::tcp::acceptor>(new bip::tcp::acceptor(io_service, bip::tcp::endpoint(bip::tcp::v4(), port)));
}

Simple_Server::~Simple_Server()
{
	if(acceptorPtr)
	{
		acceptorPtr->close();
	}
}

Simple_Socket Simple_Server::Accept()
{
	if(acceptorPtr)
	{
		std::shared_ptr<bip::tcp::socket> socPtr = std::shared_ptr<bip::tcp::socket>(new bip::tcp::socket(io_service));
		acceptorPtr->accept(*socPtr);

		return Simple_Socket(socPtr);
	}
	return std::shared_ptr<bip::tcp::socket>();
}

Simple_Socket& Simple_Socket::operator=(Simple_Socket other)
{
	socket = other.socket;
	ioService = other.ioService;
	return *this;
}

Simple_Socket::Simple_Socket(const Simple_Socket& other)
{
	socket = other.socket;
	ioService = other.ioService;
}

void Simple_Socket::connect(const std::string& ip, uint port)
{
	try
	{
		ioService = std::shared_ptr<boost::asio::io_service>( new boost::asio::io_service());
		bip::tcp::resolver resolver(*ioService);
		bip::tcp::resolver::query query(ip, boost::lexical_cast<std::string>(port));

		bip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		bip::tcp::resolver::iterator end;

		socket = std::shared_ptr<bip::tcp::socket>(new bip::tcp::socket(*ioService));

		boost::asio::connect(*socket, endpoint_iterator);
	}
	catch(...)
	{
		throw boost::system::system_error(boost::asio::error::host_not_found);
	}
}

std::shared_ptr<RawPacket> Simple_Socket::read()
{
	try
	{
		uint8_t lenbuffer[2];
		std::size_t len = socket->receive(boost::asio::buffer(lenbuffer,2));
		if(len == 2)
		{
			std::size_t packetSize = (lenbuffer[0]<<8)+lenbuffer[1];
			std::shared_ptr<RawPacket> packet(new RawPacket(packetSize));
			std::size_t recivedPlen = 0;
			while(recivedPlen < packetSize)
			{
				recivedPlen += socket->receive(boost::asio::buffer(&packet->Packet()[recivedPlen],packetSize-recivedPlen));
			}

			return packet;
		}
	}
	catch(boost::system::system_error & e)
	{
		if(e.code() == boost::asio::error::eof)
		{
			return std::shared_ptr<RawPacket>(new RawPacket(0));
		}
		else
		{
			throw;
		}
	}

	return std::shared_ptr<RawPacket>(new RawPacket(0));
}

void Simple_Socket::write(const std::shared_ptr<RawPacket>& data)
{
		uint16_t size = data->Size();
		uint8_t lenbuffer[2] = {static_cast<uint8_t>((size<<8)), static_cast<uint8_t>(size)};
		socket->send(boost::asio::buffer(lenbuffer,2));
		socket->send(boost::asio::buffer(data->Packet(),size));
}

void Simple_Socket::disconnect()
{
	if(socket)
	{
		socket = std::shared_ptr<bip::tcp::socket>();
	}
}
