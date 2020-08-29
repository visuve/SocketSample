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

	const AddressInfo info = AddressInfo(nullptr, service, AddressInfo::ClientHints);

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
