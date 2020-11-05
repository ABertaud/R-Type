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

}


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
}*/

/*#include <SFML/Graphics.hpp>

#include <iostream>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window;
    
    window.create(sf::VideoMode(800, 600), "SFML works!");
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(200.0f, 80.0f));
    button.setPosition(300.0f, 260.0f);
    sf::Texture texture;
    if (!texture.loadFromFile("./logo.png"))
    {
        std::cout << "nop" << std::endl;    // erreur...
        return 1;
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(300, 260));
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                        std::cout << "Button pressed" << std::endl;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}*/
