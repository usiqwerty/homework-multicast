#pragma once

#include "multicast_client.h"
#include <string_view>

#include <netinet/in.h>

namespace multicast
{
namespace udp
{

class Socket
{
public:
    Socket();
    Socket(const Socket&) = delete;
    Socket(Socket&&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) = delete;
    ~Socket() noexcept;
    int Handler() const noexcept;

private:
    int fd_;
};

bool send(const Socket& socket, const sockaddr_in& address,
    std::string_view message);

class SocketMulticastClient : public MulticastClient
{
public:
    SocketMulticastClient(const Socket& socket, const sockaddr_in& address);
    bool send(std::string_view message) override;

private:
    const Socket& _socket;
    const sockaddr_in& _address;
};
} // namespace udp
} // namespace multicast
