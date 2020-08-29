#include "../PCH.hpp"
#include "WsaInit.hpp"
#include "LogWrap.hpp"

WsaInit::WsaInit() :
	m_status(WSAStartup(MAKEWORD(2, 2), &m_data))
{
	if (!IsInitialized())
	{
		CERR << "WSAStartup failed with error: " << m_status;
	}
}

WsaInit::~WsaInit()
{
	if (IsInitialized())
	{
		m_status = WSACleanup();

		if (m_status != 0)
		{
			CERR << "WSAStartup failed with error: " << m_status << '/' << WSAGetLastError();
		}
	}
}

int WsaInit::Status() const
{
	return m_status;
}

bool WsaInit::IsInitialized() const
{
	return Status() == 0;
}
