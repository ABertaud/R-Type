/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** MenuDrawer.hpp
*/

#ifndef MenuDrawer_HPP_
#define MenuDrawer_HPP_

#include <memory>
#include <map>
#include "TextDrawer.hpp"
#include "Vector.hpp"
#include "keyTraducer.hpp"
#include <utility>

class MenuDrawer {
public:
    enum State
    {
        HOME = 1,
        NEW = 2,
        JOIN = 3,
        SETTINGS = 4,
        QUIT = 5,
        NORMAL = 6,
        BIG = 7,
        ROOM = 8,
    };
public:
    MenuDrawer();
    ~MenuDrawer();
    State draw(sf::RenderWindow &window, const std::string &playerName, sf::Event &event);
    State handleMenu(sf::RenderWindow &window, sf::Event &event);
    void setScale(const sf::Vector2f &);

protected:
private:
    State _state;
    posVector _winpos;
    sf::Vector2f _scale;
    TextDrawer _text;
    keyTraducer _key;
    sf::Sprite _background;
    sf::Texture _back;
    std::map<State, sf::Sprite> _buttons;
    std::map<State, sf::Vector2f> _posButtons;
    std::vector<std::shared_ptr<sf::Texture>> _textures;

    void setButton();
    void loadSprite(const std::string &path, const State &obj, sf::IntRect);
    void drawHome(sf::RenderWindow &window, const std::string &playerName);
    bool checkHome(const State &);
    State clickButton(sf::RenderWindow &window, sf::Event &event);
    sf::Vector2f getPosButton(const State &obj);
    void initPosButton();
    void displayJoinScene(const sf::Vector2f &posConditions, const sf::Vector2f &posName, const sf::RectangleShape &rect, \
    const sf::Vector2f &posEnter, const std::string &port, sf::RenderWindow &window,  const sf::Sprite &back);
    const std::string JoinId(sf::RenderWindow &window, sf::Event &event);
    sf::RectangleShape createRectangleShape(const sf::Vector2f &size, const sf::Vector2f &pos, const sf::Color &color);
};

#endif /* !MenuDrawer_HPP_ */
