#include "PCH.hpp"

int main(int, char**)
{
#if defined(_WIN32) || defined(_WIN64)
	WsaInit guard;

	if (!guard.IsInitialized())
	{
		CERR << "Failed to initialize Winsock";
		return guard.Status();
	}
#endif

	constexpr char service[] = "http";

	const AddressInfo info = AddressInfo::ServerTcpAddressInfo(nullptr, service);

	if (!info)
	{
		CERR << "Failed to get address info for " << service;
		return 1;
	}

	ClientSocket client;

	{
		ServerSocket server;

		if (!server.Bind(info.Get()))
		{
			return -1;
		}

		if (!server.Listen())
		{
			return -2;
		}

		if (!client.Accept(server, ShutdownSend))
		{
			return -3;
		}
	}

	while (client)
	{
		std::string data;

		if (!client.Receive(data))
		{
			CERR << "Failed to receive data from client!";
			return -4;
		}

		COUT << "Received: " << data;

		if (!client.Send("WELCOME"))
		{
			CERR << "Failed to send greeting to client!";
			return -5;
		}

		COUT << "Sent welcome";
	}

	return 0;
}
