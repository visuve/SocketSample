#include "PCH.hpp"

std::atomic<bool> keepRunning = true;

void SignalHandler(int signal)
{
	COUT << "Received signal " << signal;
	keepRunning = false;
}

std::string GetResponse(const std::string& request)
{
	std::stringstream response;

	if (request == "give_time")
	{
		const auto now = std::chrono::system_clock::now();
		const auto sinceEpoch = now.time_since_epoch();
		const auto secondsSinceEpoch =
			std::chrono::duration_cast<std::chrono::seconds>(sinceEpoch);

		response << secondsSinceEpoch.count();
	}

	if (request == "give_weather")
	{
		response << -7.0; // celcius
		response << " ";
		response << 4.0; // meters per second
		response << " ";
		response << "NW";
		response << " ";
		response << -8.0; // celcius
		response << " ";
		response << 93; // percent
		response << " ";
		response << 0.1; // millimeters
		response << " ";
		response << 14000; // meters
		response << " ";
		response << "Cloudy";
		response << " ";
		response << 1024.6; // hPa
		response << " ";
		response << 440; // millimeters
	}

	return response.str();
}

int main(int, char**)
{
	if (std::signal(SIGINT, SignalHandler) == SIG_ERR)
	{
		CERR << "Cannot attach CTRL+C interrupt handler!";
	}

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

	while (keepRunning && client.IsValid())
	{
		std::string request;

		if (!client.Receive(request))
		{
			CERR << "Failed to receive data from client!";
			return -4;
		}

		COUT << "Received: " << request;

		std::string response = GetResponse(request);

		if (!client.Send(response))
		{
			CERR << "Failed to send response to the client!";
			return -5;
		}

		COUT << "Sent response";
	}

	return 0;
}
