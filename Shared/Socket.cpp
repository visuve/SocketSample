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

bool Socket::Create(const addrinfo* info)
{
	Close();

	m_socket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

	if (!IsValid())
	{
		CERR << "Failed to initialize socket!";
		return false;
	}

	COUT << "Initialized";
	return true;
}

bool Socket::IsValid() const
{
#if defined(_WIN32) || defined(_WIN64)
	return m_socket != INVALID_SOCKET;
#else
	return m_socket > 0;
#endif
}

SocketDescriptor Socket::Descriptor() const
{
	return m_socket;
}

bool Socket::Send(const std::string& data) const
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

bool Socket::Bind(const addrinfo* info)
{
	if (!Create(info))
	{
		CERR << "Failed to create socket!";
		return false;
	}

#if defined(_WIN32) || defined(_WIN64)
	const int result = bind(m_socket, info->ai_addr, static_cast<int>(info->ai_addrlen));
#else
	const int result = bind(m_socket, info->ai_addr, info->ai_addrlen);
#endif

	if (result == SocketError)
	{
		CERR << "Failed to bind socket!";
		return false;
	}

	COUT << "Bound";
	return true;
}

bool Socket::Listen() const
{
	if (listen(m_socket, SOMAXCONN) == SocketError)
	{
		CERR << "Failed to listen socket!";
		return false;
	}

	COUT << "Listening...";
	return true;
}

bool Socket::Accept(SocketDescriptor socket, int closeFlags)
{
	Close();

	m_socket = accept(socket, nullptr, nullptr);

	if (!IsValid())
	{
		CERR << "Failed to accept socket!";
		return false;
	}

	m_closeFlags = closeFlags;
	COUT << "Accepted";
	return true;
}

bool Socket::Connect(const addrinfo* info)
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

void Socket::Close()
{
	if (!IsValid())
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
		m_socket = InvalidSocket;
		return;
	}

	m_socket = InvalidSocket;
	COUT << "Closed";
}