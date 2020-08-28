#pragma once

#include "Types.hpp"

class Socket
{
public:
	Socket();
	virtual ~Socket();

	operator SocketDescriptor() const;
	bool Receive(std::string& data, unsigned short limit = 0x1000) const;

protected:
	bool Create(const addrinfo* info);
	void Close() const;

	SocketDescriptor m_socket = InvalidSocket;
	int m_closeFlags = SocketError;
};
