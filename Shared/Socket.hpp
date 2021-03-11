#pragma once

#include "Types.hpp"

class Socket
{
public:
	Socket();
	~Socket();

	// Common
	bool Create(const addrinfo* info);
	bool IsValid() const;
	SocketDescriptor Descriptor() const;
	bool Send(const std::string& data) const;
	bool Receive(std::string& data, unsigned short limit = 0x1000) const;

	// Server
	bool Bind(const addrinfo* info);
	bool Listen() const;
	bool Accept(SocketDescriptor socket, int closeFlags);

	// Client
	bool Connect(const addrinfo* info);
	
	void Close();

	SocketDescriptor m_socket = InvalidSocket;
	int m_closeFlags = SocketError;
};
