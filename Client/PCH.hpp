#pragma	once

#if defined(_WIN32) || defined(_WIN64)
#define	WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#endif

// STL
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "AddressInfo.hpp"
#include "Socket.hpp"
#include "LogWrap.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "WsaInit.hpp"
#endif