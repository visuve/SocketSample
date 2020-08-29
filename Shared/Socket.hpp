#pragma once

#include "Types.hpp"

class Socket
{
public:
	Socket();
	virtual ~Socket();

	SocketDescriptor Descriptor() const;
	bool IsValid() const;
	bool Receive(std::string& data, unsigned short limit = 0x1000) const;

protected:
	bool Create(const addrinfo* info);
	void Close();

	SocketDescriptor m_socket = InvalidSocket;
	int m_closeFlags = SocketError;
};
