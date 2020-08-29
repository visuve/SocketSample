#pragma once

#include "Types.hpp"

class AddressInfo
{
public:
	static const addrinfo ServerHints;
	static const addrinfo ClientHints;

	AddressInfo(const char* node, const char* service, const addrinfo& hints);
	~AddressInfo();

	bool Initialized() const;
	operator bool() const;
	addrinfo* Get() const;
private:
	addrinfo* m_addressInfo = nullptr;
	const int m_status;
};
