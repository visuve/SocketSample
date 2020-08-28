#include "PCH.hpp"

int main(int, char**)
{
#if defined(_WIN32) || defined(_WIN64)
	WsaInit guard;

	if (!guard)
	{
		CERR << "Failed to initialize Winsock";
		return 1;
	}
#endif

	constexpr char node[] = "127.0.0.1";
	constexpr char service[] = "http";

	const AddressInfo info = AddressInfo::ClientTcpAddressInfo(nullptr, service);

	if (!info)
	{
		CERR << "Failed to get address info for " << service;
		return 1;
	}

	ClientSocket client;

	if (!client.Connect(info.Get()))
	{
		return -1;
	}

	while (client)
	{
		if (!client.Send("HELLO"))
		{
			return -2;
		}

		COUT << "Sent hello";

		std::string data;

		if (client.Receive(data))
		{
			COUT << "Received: " << data;
		}
	}

	return 0;
}
