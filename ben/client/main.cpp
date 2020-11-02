/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main
*/

#include "Client.hpp"

int main(int ac, char *av[])
{
    try {
        if (ac != 3) {
            std::cerr << "Usage: ./binary <host> <port>\n";
            return 1;
        }
        boost::asio::io_service io_service;
        boost::asio::ip::udp::resolver resolver(io_service);
        Client client(io_service);
        client.start(
            resolver.resolve(
                boost::asio::ip::udp::resolver::query(av[1], av[2])));
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}