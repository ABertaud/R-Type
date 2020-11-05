/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** MenuDrawer.cpp
*/

#include "MenuDrawer.hpp"
#include <iostream>

MenuDrawer::MenuDrawer() : _state(HOME), _winpos({1920, 1080}), _scale({1, 1}), _text(TextDrawer()), _key(keyTraducer())
{
    setButton();
    initPosButton();
    _back.loadFromFile("../../ressources/sprites/background_rtype.jpg");
    _back.setSmooth(true);
    _background.setTexture(_back);
}

MenuDrawer::~MenuDrawer()
{
}

void MenuDrawer::setButton()
{
    loadSprite("../../ressources/sprites/New_Button.png", NEW, sf::IntRect(0, 0, 28, 19));
    loadSprite("../../ressources/sprites/Load_Button.png", JOIN, sf::IntRect(0, 0, 28, 19));
    loadSprite("../../ressources/sprites/Settings_Button.png", SETTINGS, sf::IntRect(0, 0, 28, 19));
    loadSprite("../../ressources/sprites/Quit_Button.png", QUIT, sf::IntRect(0, 0, 28, 19));
}

void MenuDrawer::setScale(const sf::Vector2f &scale)
{
    _scale = scale;
}

sf::Vector2f MenuDrawer::getPosButton(const State &obj)
{
    sf::Vector2f error(-1, -1);

    for (std::map<State, sf::Vector2f>::iterator it = _posButtons.begin(); it != _posButtons.end(); it++) {
        if ((it)->first == obj)
            return (it)->second;
    }
    return error;
}

void MenuDrawer::initPosButton()
{
    float x = (((_winpos.x / 2) - 150) * _scale.x);
    float y = (((_winpos.y / 2) - 130) * _scale.y);

    sf::Vector2f pos(x, y);

    _posButtons.insert(std::make_pair(NEW, pos));
    pos.y += 130;
    _posButtons.insert(std::make_pair(JOIN, pos));
    pos.y += 130;    
    _posButtons.insert(std::make_pair(SETTINGS, pos));
    pos.y += 130;    
    _posButtons.insert(std::make_pair(QUIT, pos));
}

void MenuDrawer::loadSprite(const std::string &path, const State &obj, sf::IntRect)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    sprite.setScale(0.5f, 0.5f);
    _buttons.insert(std::make_pair(obj, sprite));
}

MenuDrawer::State MenuDrawer::clickButton(sf::RenderWindow &window, sf::Event &event)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->second.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
            std::cout << "Button yop" << std::endl;
            return (it)->first;
        }
    }
    return _state;
}

MenuDrawer::State MenuDrawer::handleMenu(sf::RenderWindow &window, sf::Event &event)
{

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) 
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            _state = clickButton(window, event);
        }
    }
    return _state;
}

bool MenuDrawer::checkHome(const State &state)
{
    if (state == NEW)
        return true;
    if (state == SETTINGS)
        return true;
    if (state == JOIN)
        return true;
    if (state == QUIT)
        return true;
    return false;
}

void MenuDrawer::drawHome(sf::RenderWindow &window, const std::string &playerName)
{
    sf::Vector2f pos;
    std::string wel = "Welcome Capitain " + playerName + " !";

    window.draw(_background);
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++)
    {
        if (checkHome((it)->first) == true)
        {
            //setRect(entity->getHorizon(), (it)->second, (it)->first);
            pos = getPosButton((it)->first);
            (it)->second.setPosition(pos);
            //setColor(entity->getId(), (it)->second);
            window.draw((it)->second);
          //  std::cout << (it)->second.getGlobalBounds().height << std::endl;
        }
    }
    pos = getPosButton(NEW);
    pos.x -= 80;
    pos.y -= 150;
    _text.draw(pos, wel, window);
}

MenuDrawer::State MenuDrawer::draw(sf::RenderWindow &window, const std::string &playerName, sf::Event &event)
{
    std::string port;

    if (_state == HOME) {
        drawHome(window, playerName);
        window.display();
    }
    if (_state == JOIN) {
        port = JoinId(window, event);
        _state = HOME;
    }
    return _state;
   // window()
}

const std::string MenuDrawer::JoinId(sf::RenderWindow &window, sf::Event &event)
{
    std::string port = "";
    sf::Vector2f posConditions(50, 150);
    sf::Vector2f posName(800, 500);
    sf::Vector2f posEnter(50, 800);
    sf::Vector2f posBack(_winpos.x - 200, _winpos.y - 250);
    sf::RectangleShape zone(createRectangleShape(sf::Vector2f(340, 70), sf::Vector2f(780, 500), sf::Color(255, 255, 255, 50)));
    bool refresh = false;
    sf::Texture texture;
    sf::Sprite back;
    
    back.setPosition(posBack);
    back.setScale(sf::Vector2f(0.5f, 0.5f));
    texture.loadFromFile("../../ressources/sprites/Home_Square_Button.png");
    texture.setSmooth(true);
    back.setTexture(texture);
    displayJoinScene(posConditions, posName, zone, posEnter, port, window, back);
    while (port.find("\n") == std::string::npos)
    {
        refresh = false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                refresh = _key.traduceLetter(event.key.code, port);
            if (event.type == sf::Event::Closed)
                return ("closssssssse");
            if (event.type == sf::Event::MouseButtonPressed) {
                if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    _state = HOME;
                    return ("");
                }
            }
            event.key.code = sf::Keyboard::Escape;
        }
        if (refresh == true) {
            displayJoinScene(posConditions, posName, zone, posEnter, port, window, back);
            window.draw(back);
        }
    }
    port = port.substr(0, port.length() - 1);
    return (port);
}

sf::RectangleShape MenuDrawer::createRectangleShape(const sf::Vector2f &size, const sf::Vector2f &pos, const sf::Color &color)
{
    sf::RectangleShape rect(size);

    rect.setPosition(pos);
    rect.setFillColor(color);
    return (rect);
}

void MenuDrawer::displayJoinScene(const sf::Vector2f &posConditions, const sf::Vector2f &posName, const sf::RectangleShape &rect, const sf::Vector2f &posEnter, const std::string &port, sf::RenderWindow &window, const sf::Sprite &back)
{
    window.clear();
    window.draw(_background);
    window.draw(rect);
    _text.draw(posConditions, "Enter Id of the game.", window);
    _text.draw(posName, port, window, sf::Color::Black);
    _text.draw(posEnter, "Press enter to confirm.", window);
    window.draw(back);
    window.display();
}