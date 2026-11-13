#ifndef MULTICAST_MULTICAST_CLIENT_H
#define MULTICAST_MULTICAST_CLIENT_H
#include <string_view>

class MulticastClient
{
public:
    virtual bool send(std::string_view message) = 0;
    virtual ~MulticastClient() = default;
};

#endif // MULTICAST_MULTICAST_CLIENT_H
