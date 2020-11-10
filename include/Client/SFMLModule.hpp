/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SFMLModule.hpp
*/

#ifndef SFMLMODULE_HPP_
#define SFMLMODULE_HPP_

#include <SFML/Graphics.hpp>
#include "Parser.hpp"
#include "IGraphicLibrary.hpp"
#include "Vector.hpp"
#include "MenuDrawer.hpp"

class SFMLModule : public Graphic::IGraphicLibrary {

public:
    enum Scene
    {
        PAUSE = 12,
        MENU = 6,
        GAME = 5
    };
public:
        SFMLModule();
        ~SFMLModule();
        void init();
        void stop();
        Graphic::Command eventHandler();
        void drawGame(const std::vector<std::shared_ptr<Graphic::AEntity>>&);
        MenuDrawer::State Menu(const std::string &name, const std::vector<std::shared_ptr<players>>&, const ClientState &);
        const std::string getPlayerName();
        void displayWindow();
        std::string getRoomName()const;
        void setState(const MenuDrawer::State &);
    protected:
    private:
       Parser _parser;
       posVector _winpos;
       sf::Vector2f _scale;
       keyTraducer _key;
       Scene _scene;
       TextDrawer _text;
       MenuDrawer _menu;
       std::string _roomName;
       sf::RenderWindow _window;
       std::map<entityType, sf::Sprite> _entities;
       std::vector<std::shared_ptr<sf::Texture>> _textures;
       sf::Event _event;
       sf::Sprite _background;
       
       void loadSprite(const std::string &path, const entityType &obj, sf::IntRect);
       void loadAllSprite(std::map<entityType, std::string> &paths);
       void drawEntity(std::shared_ptr<Graphic::AEntity>);
       void displayPlayerScene(const sf::Vector2f &posConditions, const sf::Vector2f &posName, const sf::RectangleShape &rect, const sf::Vector2f &, const std::string &playerName);
       sf::RectangleShape createRectangleShape(const sf::Vector2f &size, const sf::Vector2f &pos, const sf::Color &color);
};


#endif /* !SFMLMODULE_HPP_ */
