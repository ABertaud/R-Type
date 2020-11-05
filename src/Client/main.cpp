/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main.cpp
*/

#include "pathHandler.hpp"
#include "Error.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "./client <host> <port>" << std::endl;
        return (1);
    }
    try
    {
        Client cli(av[1], std::atoi(av[2]));

        cli.start();
        cli.stop();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}