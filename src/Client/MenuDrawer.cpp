/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** MenuDrawer.cpp
*/

#include "MenuDrawer.hpp"
#include <iostream>

MenuDrawer::MenuDrawer() : _state(HOME), _winpos({1920, 1080}), _scale({1, 1}), _text(TextDrawer()), _key(keyTraducer()), _roomName("")
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
    loadSpriteSize("../../ressources/sprites/rectangle.png", WALL, sf::IntRect(0, 0, 28, 19), {2.5, 2.5});
    loadSpriteSize("../../ressources/sprites/spaceship_o.png", P1, sf::IntRect(0, 0, 28, 19), {0.5, 0.5});
    loadSpriteSize("../../ressources/sprites/spaceship_t.png", P2, sf::IntRect(0, 0, 28, 19), {0.45, 0.45});
    loadSpriteSize("../../ressources/sprites/spaceship_tr.png", P3, sf::IntRect(0, 0, 28, 19), {0.3, 0.3});
    loadSpriteSize("../../ressources/sprites/spaceship_f.png", P4, sf::IntRect(0, 0, 28, 19), {0.3, 0.3});
    loadSprite("../../ressources/sprites/New_Button.png", NEW, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Load_Button.png", JOIN, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Settings_Button.png", SETTINGS, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Quit_Button.png", QUIT, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});  
    loadSprite("../../ressources/sprites/ready.png", READY, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});   
    loadSprite("../../ressources/sprites/unready.png", UNREADY, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});    
    loadSprite("../../ressources/sprites/Home_Square_Button.png", HOME, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});    
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
    float y = ((_winpos.y / 3) * _scale.y);
    float x_room = (((_winpos.x / 2) - 250) * _scale.x);
    float y_room = ((_winpos.y / 2) * _scale.y);

    sf::Vector2f pos(x, y);
    sf::Vector2f posRoom(x_room, y_room);

    _posButtons.insert(std::make_pair(NEW, pos));
    pos.y += 130;
    _posButtons.insert(std::make_pair(JOIN, pos));
    pos.y += 130;    
    _posButtons.insert(std::make_pair(SETTINGS, pos));
    pos.y += 130;    
    _posButtons.insert(std::make_pair(QUIT, pos));
    _posButtons.insert(std::make_pair(READY, posRoom));
    _posButtons.insert(std::make_pair(UNREADY, posRoom));

}

void MenuDrawer::loadSpriteSize(const std::string &path, const entityType &obj, sf::IntRect rect, const posVector &scale)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    sprite.setScale(scale.x, scale.y);
    _players.insert(std::make_pair(obj, sprite));
}


void MenuDrawer::loadSprite(const std::string &path, const State &obj, sf::IntRect rect,  const posVector &scale)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    sprite.setScale(scale.x, scale.y);
    _buttons.insert(std::make_pair(obj, sprite));
}

MenuDrawer::State MenuDrawer::clickButton(sf::RenderWindow &window, sf::Event &event)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->second.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
            if (checkHome((it)->first) == true && _state == HOME)
                return (it)->first;
            if (checkRoom((it)->first) == true && _state == ROOM)
                return (it)->first;
        }
    }
    return _state;
}

MenuDrawer::State MenuDrawer::handleMenu(sf::RenderWindow &window, sf::Event &event)
{

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            _state = clickButton(window, event);
        }
    }
    return _state;
}

bool MenuDrawer::checkRoom(const State &state)
{
    if (state == READY)
        return true;
    if (state == UNREADY)
        return true;
    if (state == HOME)
        return true;
    return false;
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

    window.clear();
    window.draw(_background);
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if (checkHome((it)->first) == true) {
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
    window.display();
}

std::string MenuDrawer::getRoomName()const
{
    return (_roomName);
}

void MenuDrawer::draw(sf::RenderWindow &window, const std::string &playerName, sf::Event &event, const std::vector<std::shared_ptr<players>>&entities, const ClientState &clientS)
{
    if (_state == HOME)
        drawHome(window, playerName);
    if (_state == SETTINGS) {
        window.clear();
        window.draw(_background);
        window.display();
    }
    if (_state == NEW) {
        _roomName = enterScene(window, event);
    }
        
    if (_state == JOIN || _state == WAITING) {
        _roomName = enterScene(window, event);
    }
    if (_state == ROOM || _state == READY || _state == UNREADY)
        drawRoom(window, playerName, event, entities, clientS);   // window()
}

std::string MenuDrawer::getPlayerName(const entityType &type)
{
    if (type == P1)
        return std::string("player 1");
    if (type == P2)
        return std::string("player 2");
    if (type == P3)
        return std::string("player 3");
    if (type == P4)
        return std::string("player 4");
    return std::string("");    
}

void MenuDrawer::drawPlayerRoom(const std::shared_ptr<players> &player, sf::RenderWindow &window)
{
    float x = _winpos.x / 4;
    float y = _winpos.y / 6;
    float x_icon = x + 33;
    float y_icon = y + 35;
    float x_text = x + 150;
    float y_text = y + 25;
    std::string name;
    sf::Vector2f pos(x, y);
    sf::Vector2f posIcon(x_icon, y_icon);
    sf::Vector2f posText(x_text, y_text);
    
    for (std::map<entityType, sf::Sprite>::iterator it = _players.begin(); it != _players.end(); it++) {
        if ((it)->first == player->getObject() && player->getState() != players::OFF) {
            drawRect(pos, window);
            name = getPlayerName((it)->first);
            (it)->second.setPosition(posIcon);
            window.draw((it)->second);
            _text.drawSize(posText, name, window, 45);
            if (player->getState() == players::READY)
                drawIconStat(READY, window, pos);
            else
                drawIconStat(UNREADY, window, pos);
        }
        posText.y += 120;
        pos.y += 120;
        posIcon.y += 120;
    }
}

void MenuDrawer::drawRect(const sf::Vector2f &pos, sf::RenderWindow &window)
{
    for (std::map<entityType, sf::Sprite>::iterator it = _players.begin(); it != _players.end(); it++) {
        if ((it)->first == WALL) {
            //setRect(entity->getHorizon(), (it)->second, (it)->first);
            (it)->second.setPosition(pos);
            //setColor(entity->getId(), (it)->second);
            window.draw((it)->second); 
        }
    }
}

void MenuDrawer::drawIconStat(const State &state, sf::RenderWindow &window, sf::Vector2f pos)
{
    sf::Texture texture;
    sf::Sprite go;

    pos.x *= 2.3;
    pos.y += 30;
    go.setPosition(pos);
    go.setScale(sf::Vector2f(0.3f, 0.3f));
    if (state == State::READY)
        texture.loadFromFile("../../ressources/sprites/V_Button.png");
    else
        texture.loadFromFile("../../ressources/sprites/X_Button.png");
    texture.setSmooth(true);
    go.setTexture(texture);
    window.draw(go);    
}

void MenuDrawer::drawState(const State &state, sf::RenderWindow &window, sf::Vector2f pos)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->first == state) {
            //setRect(entity->getHorizon(), (it)->second, (it)->first);
            (it)->second.setPosition(pos);
            //setColor(entity->getId(), (it)->second);
            window.draw((it)->second);
          //  std::cout << (it)->second.getGlobalBounds().height << std::endl;
        }
    }
}

void MenuDrawer::setState(const State &state)
{
    _state = state;
}

void MenuDrawer::drawButton(const State &state, const sf::Vector2f &pos, sf::RenderWindow &window)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->first == state) {
            (it)->second.setPosition(pos);
            window.draw((it)->second);
        }
    }
}

void MenuDrawer::drawRoom(sf::RenderWindow &window, const std::string &playerName, sf::Event &event, const std::vector<std::shared_ptr<players>>&players, const ClientState &clientS)
{
    float x = _winpos.x / 2 + 350;
    float y = _winpos.y / 6;
    sf::Vector2f pos(x, y);
    sf::Vector2f posBack(_winpos.x - 200, _winpos.y - 250);

    window.clear();
    window.draw(_background);
    drawButton(HOME, posBack, window);
    for (auto it = players.begin(); it != players.end(); it++) {
       drawPlayerRoom((*it), window);
    }
    if (clientS == ClientState::READY) 
        drawState(READY, window, pos);
    else
        drawState(UNREADY, window, pos);
    window.display();
}

const std::string MenuDrawer::enterScene(sf::RenderWindow &window, sf::Event &event)
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

    window.clear();
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
    _state = ROOM;
    return (port);
}

sf::RectangleShape MenuDrawer::createRectangleShape(const sf::Vector2f &size, const sf::Vector2f &pos, const sf::Color &color)
{
    sf::RectangleShape rect(size);

    rect.setPosition(pos);
    rect.setFillColor(color);
    return (rect);
}

void MenuDrawer::displayJoinScene(const sf::Vector2f &posConditions, const sf::Vector2f &posName, \
const sf::RectangleShape &rect, const sf::Vector2f &posEnter, const std::string &port, sf::RenderWindow &window, const sf::Sprite &back)
{
    window.clear();
    window.draw(_background);
    window.draw(rect);
    _text.draw(posConditions, "Enter the name of the room.", window);
    _text.draw(posName, port, window, sf::Color::Black);
    _text.draw(posEnter, "Press enter to confirm.", window);
    window.draw(back);
    window.display();
}