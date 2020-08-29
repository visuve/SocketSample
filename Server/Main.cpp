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

	constexpr char service[] = "8444";

	const AddressInfo info = AddressInfo(nullptr, service, AddressInfo::ServerHints);

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

		if (!client.Accept(server.Descriptor(), ShutdownSend))
		{
			return -3;
		}
	}

	while (client.IsValid())
	{
		std::string request;

		if (!client.Receive(request))
		{
			CERR << "Failed to receive data from client!";
			return -4;
		}

		COUT << "Received: " << request;

		std::string response;

		if (request == "FOO")
		{
			response = "BAR";
		}		
		else if (request == "BAR")
		{
			response = "FOO";
		}
		else
		{
			response = "FUBAR";
		}

		if (!client.Send(response))
		{
			CERR << "Failed to send response to the client!";
			return -5;
		}

		COUT << "Sent response";
	}

	return 0;
}
