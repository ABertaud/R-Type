/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main.cpp
*/

#include "pathHandler.hpp"
#include "Error.hpp"
#include <iostream>

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try {
        pathHandler hdl(pathType::REGULAR_FILE);
        if (ac > 2)
            throw ErrorNbArgs();
        else if (ac == 2)
            hdl.setPath(av[1]);
        if (hdl.isFileValid() == false)
            throw ErrorConfigPath();
        //Client clt();
        //clt.run();
    } catch (Error const &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
    return (0);    
}