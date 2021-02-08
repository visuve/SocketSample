#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

// STL
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "AddressInfo.hpp"
#include "LogWrap.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "WsaInit.hpp"
#endif
