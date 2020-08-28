#include "PCH.hpp"
#include "ClientSocket.hpp"
#include "LogWrap.hpp"

ClientSocket::ClientSocket()
{
	CLOG;
}

ClientSocket::~ClientSocket()
{
	CLOG;
}

bool ClientSocket::Connect(const addrinfo* info)
{
	for (const addrinfo* iter = info; iter != nullptr; iter = iter->ai_next)
	{
		if (!Create(iter))
		{
			CERR << "Failed to create socket!";
			return false;
		}

#if defined(_WIN32) || defined(_WIN64)
		const int result = connect(m_socket, info->ai_addr, static_cast<int>(info->ai_addrlen));
#else
		const int result = connect(m_socket, info->ai_addr, info->ai_addrlen);
#endif

		if (result == SocketError)
		{
			Close();
			continue;
		}

		COUT << "Connected";
		return true;
	}

	CERR << "Failed to connect!";
	return false;
}

bool ClientSocket::Send(const std::string& data) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(250)); // TODO: remove

	if (data.length() >= std::numeric_limits<uint16_t>::max())
	{
		CERR << "Failed to send! Payload too big. Size=" << data.length();
		return false;
	}

#if defined(_WIN32) || defined(_WIN64)
	if (send(m_socket, data.c_str(), static_cast<int>(data.length()), 0) == SocketError)
#else
	if (send(m_socket, data.c_str(), data.length(), 0) == SocketError)
#endif
	{
		CERR << "Failed to send!";
		return false;
	}

	COUT << "Sent " << data.length() << " byte(s)";
	return true;
}

bool ClientSocket::Accept(SocketDescriptor socket, int closeFlags)
{
	Close();

	m_socket = accept(socket, nullptr, nullptr);

	if (!IsValidSocket(m_socket))
	{
		CERR << "Failed to accept socket!";
		return false;
	}

	m_closeFlags = closeFlags;
	COUT << "Accepted";
	return true;
}
