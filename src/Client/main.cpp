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

/*#include <SFML/Graphics.hpp>

#include <iostream>
#include <SFML/Window.hpp>

int main()
{
    std::cout << "test1" <<std::endl;
    sf::Window window(sf::VideoMode(800, 600), "My window");
    std::cout << "test2" <<std::endl;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}*/