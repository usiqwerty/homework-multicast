#include <cstdlib>
#include <iostream>

#include "config.hpp"
#include "serial.hpp"
#include "udp.hpp"

namespace
{

void print_usage(std::string_view basename)
{
    std::cout << "Usage: " << basename << " <CONFIG_FILE>\n";
}

void print_prompt()
{
    std::cout << "Enter message: ";
}

} // namespace

int main(int argc, char* argv[])
{
    if (argc == 2 && std::string_view(argv[1]) == "-h")
    {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (argc < 2)
    {
        std::cerr << "Not enough arguments!\n";
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    try
    {
        using namespace multicast;
        Config config{argv[1]};
        udp::Socket socket{};
        std::vector<MulticastClient*> clients;

        for ([[maybe_unused]] const auto& entry : config.GetUdpEntries())
        {
            auto socketClient = new udp::SocketMulticastClient {socket, entry.address};
            clients.push_back(socketClient);
        }

        for ([[maybe_unused]] const auto& entry : config.GetSerialEntries())
        {
            auto serialClient = new serial::Device{entry.device};
            clients.push_back(serialClient);
        }

        std::string input{};
        while (print_prompt(), std::getline(std::cin, input))
        {
            input.push_back('\n');
            for (unsigned long i = 0; i < clients.size(); i++)
            {
                clients[i]->send(input);
            }
        }
        for (unsigned long i = 0; i < clients.size(); i++)
        {
            delete clients[i];
        }
        return EXIT_SUCCESS;
    }
    catch (const std::exception& err)
    {
        std::cerr << "Multicast failure: " << err.what() << '\n';
    }
    return EXIT_FAILURE;
}
