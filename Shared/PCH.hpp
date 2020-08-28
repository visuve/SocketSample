#pragma once


#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <ws2tcpip.h>
#undef max
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cerrno>
#endif

// STL
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
