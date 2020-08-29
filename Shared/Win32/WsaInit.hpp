#pragma once

class WsaInit
{
public:
	WsaInit();
	~WsaInit();
	int Status() const;
	bool IsInitialized() const;

private:
	WSADATA m_data = { 0 };
	int m_status;
};
