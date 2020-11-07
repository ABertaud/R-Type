/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SFMLModule.cpp
*/

#include "SFMLModule.hpp"

SFMLModule::SFMLModule()  : _parser(Parser()), _winpos({1920, 1080}), 
_scale({1, 1}), _key(keyTraducer()), _scene(MENU), _text(TextDrawer()), _menu(MenuDrawer()), _roomName("")
{
    std::map<entityType, std::string> paths = _parser.getPaths();
    loadAllSprite(paths);
    _scene = MENU;
    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    _textures.back()->loadFromFile("../../ressources/sprites/player_background.jpg");
    _background.setTexture(*_textures.back());
}

SFMLModule::~SFMLModule()
{
}

void SFMLModule::loadSprite(const std::string &path, const entityType &obj, sf::IntRect rect)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    (void)rect;
    //sprite.setTextureRect(rect);
    _entities.insert(std::make_pair(obj, sprite));
}

void SFMLModule::loadAllSprite(std::map<entityType, std::string> &paths)
{
    for (std::map<entityType, std::string>::iterator it = paths.begin(); it != paths.end(); it++) {
        loadSprite((*it).second, (*it).first, sf::IntRect(0, 0, 28, 19));
    }
}

void SFMLModule::setState(const MenuDrawer::State &state)
{
    _menu.setState(state);
}

MenuDrawer::State SFMLModule::Menu(const std::string &name, const std::vector<std::shared_ptr<players>>& entities, const ClientState &clientS)
{
    MenuDrawer::State ret;
    
    ret =_menu.handleMenu(_window, _event);
    _menu.draw(_window, name, _event, entities, clientS);
    return ret;
}

std::string SFMLModule::getRoomName()const
{
    return (_menu.getRoomName());
}

void SFMLModule::init()
{
    float x = 1.0f;
    float y = 1.0f;

    if (_window.isOpen())
        _window.close();
    if (_scale.x <= x && _scale.y <= y)
        _window.create(sf::VideoMode(_winpos.x, _winpos.y), "R-Type", sf::Style::Close | sf::Style::Titlebar | sf::Style::Default);
    else
        _window.create(sf::VideoMode(_winpos.x * _scale.x, _winpos.y * _scale.y), "Arcade", sf::Style::Close | sf::Style::Titlebar);
   /* _background.setScale(_scale);
    _menu.setScale(_scale);
    _text.setScale(_scale);
    _menu.setText(_text);
    _pause.setScale(_scale);
    _pause.setText(_text);*/
}

void SFMLModule::stop()
{
    _window.close();
}

Graphic::Command SFMLModule::eventHandler()
{
    Graphic::Command command = Graphic::NOTHING;

    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::KeyPressed)
            command = _key.traduceKey(_event.key.code);
        if (_event.type == sf::Event::Closed) 
            command = Graphic::EXIT;
    }
    if (command == Graphic::MENU)
    {
        _scene = SFMLModule::MENU;
    }
    return (command);
}

void SFMLModule::drawGame(const std::vector<std::shared_ptr<Graphic::AEntity>> &entityArray)
{
    _window.clear();
   // _window.draw(_background);
    for (std::vector<std::shared_ptr<Graphic::AEntity>>::const_iterator it = entityArray.begin(); it != entityArray.end(); it++)
        drawEntity((*it));
    //drawScore(score);
}

void SFMLModule::drawEntity(std::shared_ptr<Graphic::AEntity> entity)
{
   // float x = (((entity->getPos().x * 28.5) + ((_winpos.x - 800) / 2)) * _scale.x);
    //float y = (((entity->getPos().y * 19.3) + ((_winpos.y - 600) / 2)) * _scale.y);
    
    float x = entity->getPos().x;
    float y = entity->getPos().y;

    sf::Vector2f pos(x, y);

    for (std::map<entityType, sf::Sprite>::iterator it = _entities.begin(); it != _entities.end(); it++)
    {
        if (((it)->first) == entity->getObject())
        {
          //  setRect(entity->getHorizon(), (it)->second, (it)->first);
            (it)->second.setPosition(pos);
           // setColor(entity->getId(), (it)->second);
            _window.draw((it)->second);
          //  std::cout << (it)->second.getGlobalBounds().height << std::endl;
        }
    }
}

sf::RectangleShape SFMLModule::createRectangleShape(const sf::Vector2f &size, const sf::Vector2f &pos, const sf::Color &color)
{
    sf::RectangleShape rect(size);

    rect.setPosition(pos);
    rect.setFillColor(color);
    return (rect);
}

const std::string SFMLModule::getPlayerName()
{
    std::string playerName = "";
    sf::Vector2f posConditions(50, 150);
    sf::Vector2f posName(800, 500);
    sf::Vector2f posEnter(50, 800);
    sf::RectangleShape playerZone(createRectangleShape(sf::Vector2f(340, 70), sf::Vector2f(780, 500), sf::Color(255, 255, 255, 50)));
    bool refresh = false;

    displayPlayerScene(posConditions, posName, playerZone, posEnter, playerName);
    while (playerName.find("\n") == std::string::npos)
    {
        refresh = false;
        while (_window.pollEvent(_event))
        {
            if (_event.type == sf::Event::KeyPressed)
                refresh = _key.traduceLetter(_event.key.code, playerName);
            if (_event.type == sf::Event::Closed)
                return ("closssssssse");
            _event.key.code = sf::Keyboard::Escape;
        }
        if (refresh == true)
            displayPlayerScene(posConditions, posName, playerZone, posEnter, playerName);
    }
    playerName = playerName.substr(0, playerName.length() - 1);
    return (playerName);
}

void SFMLModule::displayPlayerScene(const sf::Vector2f &posConditions, const sf::Vector2f &posName, const sf::RectangleShape &rect, const sf::Vector2f &posEnter, const std::string &playerName)
{
    _window.clear();
    _window.draw(_background);
    _window.draw(rect);
    _text.draw(posConditions, "Enter your playername, it has to contain 8 or less alphanumeric characters.", _window);
    _text.draw(posName, playerName, _window, sf::Color::Black);
    _text.draw(posEnter, "Press enter to confirm.", _window);
    _window.display();
}

void SFMLModule::displayWindow()
{
    _window.display();
}