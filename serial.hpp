#pragma once

#include "multicast_client.h"


#include <string_view>

namespace multicast
{
namespace serial
{

class Device : public MulticastClient
{
public:
    explicit Device(std::string_view path);
    Device(const Device&) = delete;
    Device(Device&&) = delete;
    Device& operator=(const Device&) = delete;
    Device& operator=(Device&&) = delete;
    ~Device() noexcept override;
    int Handler() const noexcept;

    bool send(std::string_view message) override;
private:
    int fd_;
};

bool send(const Device& device, std::string_view message);

} // namespace serial
} // namespace multicast
