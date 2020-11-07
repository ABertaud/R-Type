/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main.cpp
*/

#include "pathHandler.hpp"
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

/*#include "SFMLModule.hpp"
#include <iostream>

int main()
{
    Graphic::Command command;
    MenuDrawer::State state;
    SFMLModule *test = new SFMLModule();
    std::string name;
    bool yo = false;
    test->init();
    name = test->getPlayerName();
    if (name.length() > 8)
        return 5;
    while (yo == false) {
    //    command = test->eventHandler();
        if (command == Graphic::EXIT)
            test->stop();
        state = test->Menu(name);
        if (state == MenuDrawer::State::QUIT)
            test->stop();
        if (state == MenuDrawer::State::JOIN)
            std::cout << "JOIN IS OK" << std::endl;
    }

}*/


/*#include "pathHandler.hpp"
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
}*/
