#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

// STL
#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <sstream>
#include <string>

#include "AddressInfo.hpp"
#include "Socket.hpp"
#include "LogWrap.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "WsaInit.hpp"
#endif
