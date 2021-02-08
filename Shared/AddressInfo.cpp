#include "PCH.hpp"
#include "AddressInfo.hpp"

const addrinfo AddressInfo::ServerHints =
{
	AI_PASSIVE, // ai_flags
	AF_INET, // ai_family
	SOCK_STREAM, // ai_socktype
	IPPROTO_TCP, // ai_protocol
	0, // ai_addrlen
	nullptr, // ai_canonname
	nullptr, // ai_addr
	nullptr, // ai_next
};

const addrinfo AddressInfo::ClientHints =
{
	0, // ai_flags
	AF_INET, // ai_family
	SOCK_STREAM, // ai_socktype
	IPPROTO_TCP, // ai_protocol
	0, // ai_addrlen
	nullptr, // ai_canonname
	nullptr, // ai_addr
	nullptr, // ai_next
};

AddressInfo::AddressInfo(const char* node, const char* service, const addrinfo& hints) :
	m_status(getaddrinfo(node, service, &hints, &m_addressInfo))
{
	if (m_status != 0)
	{
		printf("Getaddrinfo failed with error: %d / %d\n", m_status, LastError);
	}
}

AddressInfo::~AddressInfo()
{
	if (Initialized())
	{
		freeaddrinfo(m_addressInfo);
	}
}

bool AddressInfo::Initialized() const
{
	return m_status == 0 && m_addressInfo != nullptr;
}

AddressInfo::operator bool() const
{
	return Initialized();
}

addrinfo* AddressInfo::Get() const
{
	return m_addressInfo;
}
