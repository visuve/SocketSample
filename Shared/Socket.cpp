#include "PCH.hpp"
#include "Socket.hpp"
#include "LogWrap.hpp"

Socket::Socket()
{
	CLOG;
}

Socket::~Socket()
{
	Close();
	CLOG;
}

Socket::operator SocketDescriptor() const
{
	return m_socket;
}

bool Socket::Create(const addrinfo* info)
{
	Close();

	m_socket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

	if (!IsValidSocket(m_socket))
	{
		CERR << "Failed to initialize socket!";
		return false;
	}

	COUT << "Initialized";
	return true;
}

bool Socket::Receive(std::string& data, unsigned short limit) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(750)); // TODO: remove

	std::string buffer(limit, '\0');

	const int received = recv(m_socket, &buffer.front(), limit, 0);

	if (received == SocketError)
	{
		CERR << "Failed to receive!";
		return false;
	}

	if (received == 0)
	{
		COUT << "Connection gracefully closed";
		return true;
	}

	if (received < 1)
	{
		COUT << "Nothing to receive: " << received;
		return false;
	}

	COUT << "Received " << received << " byte(s)";

	if (received < limit)
	{
		// Trim excess null
		buffer.resize(received);
	}

	data.append(buffer);
	return true;
}

void Socket::Close() const
{
	if (!IsValidSocket(m_socket))
	{
		// No need to close
		return;
	}

	if (m_closeFlags != SocketError && shutdown(m_socket, m_closeFlags) == SocketError)
	{
		CERR << "Socket shutdown failed with error: " << LastError;
	}
	else
	{
		COUT << "Shutdown";
	}

	if (CloseSocket(m_socket) == SocketError)
	{
		CERR << "Socket closed with error: " << LastError;
		return;
	}

	COUT << "Closed";
}
