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

	constexpr char server[] = "localhost";
	constexpr char port[] = "8444";

	const AddressInfo info = AddressInfo(server, port, AddressInfo::ClientHints);

	if (!info)
	{
		CERR << "Failed to get address info for " << server;
		return 1;
	}

	Socket client;

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
