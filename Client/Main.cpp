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

	size_t sentMessageCount = 0;

	while (client.IsValid())
	{
		if (!client.Send(sentMessageCount % 2 ? "FOO" : "BAR"))
		{
			return -2;
		}

		++sentMessageCount;
		COUT << "Sent request";

		std::string data;

		if (client.Receive(data))
		{
			COUT << "Received: " << data;
		}
	}

	return 0;
}
