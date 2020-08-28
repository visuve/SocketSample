#pragma once

constexpr int SocketError = -1;

#if defined(_WIN32) || defined(_WIN64)
using SocketDescriptor = SOCKET;
constexpr SocketDescriptor InvalidSocket = INVALID_SOCKET;
constexpr auto CloseSocket = closesocket;
constexpr bool IsValidSocket(const SocketDescriptor sd) { return sd != INVALID_SOCKET; }
#define LastError WSAGetLastError()
#define ShutdownSend SD_SEND
#else
#include <unistd.h>
#include <netdb.h>
using SocketDescriptor = int;
constexpr SocketDescriptor InvalidSocket = -1;
constexpr auto CloseSocket = close;
constexpr bool IsValidSocket(const SocketDescriptor sd) { return sd > 0; }
#define LastError errno
#define ShutdownSend SHUT_WR
#endif