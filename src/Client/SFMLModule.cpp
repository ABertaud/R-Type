/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SFMLModule.cpp
*/

#include "SFMLModule.hpp"

SFMLModule::SFMLModule(const std::string& path)  : _parser(path), _winpos({1116, 797}), 
_scale({1, 1}), _key(keyTraducer()), _scene(MENU), _text(TextDrawer()), 
_menu(MenuDrawer(_scale)), _roomName(""),  _parallaxShader("../../ressources/sprites/Game/BackgroundGame.png", _scale),
_audio()
{
    std::map<entityType, std::string> paths = _parser.getPaths();
    
    loadAllSprite(paths);
    _scene = MENU;
    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    _textures.back()->loadFromFile("../../ressources/sprites/player_background.png");
    _background.setTexture(*_textures.back());
    _audio.addSound("../../ressources/sounds/gameLoop.ogg", true, Audio::GAME);    
    _audio.addSound("../../ressources/sounds/shoot.wav", false, Audio::SHOOT);
   // _audio.addSound("../../ressources/sounds/bomb.wav", false, Audio::BOMB);    
    _audio.addSound("../../ressources/sounds/startGame.ogg", false, Audio::STARTGAME);    
    _audio.addSound("../../ressources/sounds/playerName.wav", false, Audio::PLAYERNAME);       
}

SFMLModule::~SFMLModule()
{
}

void SFMLModule::loadSprite(const std::string& path, const entityType& obj)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    //sprite.setTextureRect(rect);
    _sprites.insert(std::make_pair(obj, sprite));
}

Audio &SFMLModule::getAudio()
{
    return _audio;
}

void SFMLModule::loadAllSprite(std::map<entityType, std::string>& paths)
{
    for (std::map<entityType, std::string>::iterator it = paths.begin(); it != paths.end(); it++) {
        loadSprite((*it).second, (*it).first);
    }
   /* loadSprite("../../ressources/sprites/Game/player1.png", P1);
    loadSprite("../../ressources/sprites/Game/shoot.png", PLAYER_SHOOT);
    loadSprite("../../ressources/sprites/Game/pirate.png", PIRATE);*/
}

void SFMLModule::setState(const MenuDrawer::State& state)
{
    _menu.setState(state);
}

MenuDrawer::State SFMLModule::Menu(const std::string& name, const std::vector<std::shared_ptr<Players>>& entities, const ClientState& clientS, sf::Clock &frameClock)
{
    MenuDrawer::State ret;
    sf::Time frameTime = frameClock.restart();

    _menu.handleMenu(_window, _event);
    _menu.draw(_window, name, _event, entities, clientS, frameTime);
    ret = _menu.getState();
    return ret;
}

MenuDrawer &SFMLModule::getMenuDrawer()
{
    return _menu;
}

std::string SFMLModule::getRoomName()const
{
    return (_menu.getRoomName());
}

void SFMLModule::init(const sf::Vector2f& scale)
{
    float x = 1.0f;
    float y = 1.0f;
    
    if (_window.isOpen())
        _window.close();
    _scale = scale;
    if (_scale.x <= x && _scale.y <= y)
        _window.create(sf::VideoMode(_winpos.x, _winpos.y), "R-Type", sf::Style::Close | sf::Style::Titlebar | sf::Style::Default);
    else 
        _window.create(sf::VideoMode(_winpos.x * _scale.x, _winpos.y * _scale.y), "R-Type", sf::Style::Close | sf::Style::Titlebar | sf::Style::Default);
    _menu.setScale(_scale);
    _menu.reSize();
    _background.setScale(_scale.x, _scale.y);
    _parallaxShader.setScale(_scale);
    _window.setVerticalSyncEnabled(true);
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
        if (_event.type == sf::Event::KeyPressed) {
            command = _key.traduceKey(_event.key.code);
            //_event.key.code = sf::Keyboard::O;
        }
        if (_event.type == sf::Event::Closed) 
            command = Graphic::EXIT;
    }
    return (command);
}

Graphic::Command SFMLModule::game(const std::vector<std::shared_ptr<Graphic::Entity>>& entityArray)
{
    Graphic::Command ret;

    ret = eventHandler();
    drawGame(entityArray);
    return ret;
}

void SFMLModule::drawGame(const std::vector<std::shared_ptr<Graphic::Entity>>& entityArray)
{
    _window.clear();
    _parallaxShader.parallaxShaderDraw(_window);
   // _window.draw(_background);
    for (std::vector<std::shared_ptr<Graphic::Entity>>::const_iterator it = entityArray.begin(); it != entityArray.end(); it++) 
        drawEntity((*it));
    //drawScore(score);
    //sprite.setTextureRect(rect)
    _window.display();
}

void SFMLModule::drawEntity(std::shared_ptr<Graphic::Entity> entity)
{
   // float x = (((entity->getPos().x * 28.5) + ((_winpos.x - 800) / 2)) * _scale.x);
    //float y = (((entity->getPos().y * 19.3) + ((_winpos.y - 600) / 2)) * _scale.y);
    
    float x = entity->getPos().x;
    float y = entity->getPos().y;
    sf::IntRect rect;
    sf::IntRect error(-1, -1, -1, -1);
    sf::Vector2f pos(x, y);
    animationState anime;

    for (std::map<entityType, sf::Sprite>::iterator it = _sprites.begin(); it != _sprites.end(); it++) {
        if (((it)->first) == entity->getType()) {
          //  setRect(entity->getHorizon(), (it)->second, (it)->first);
            (it)->second.setPosition(pos);
            anime = entity->getCurrentAnimation();
            rect = entity->getRectAnime(anime);
    //        if (rect != error)
           (it)->second.setTextureRect(rect);
     //      if (entity->getType() == BOMB)
       //         _audio.playSound(Audio::BOMB);
           // setColor(entity->getId(), (it)->second);
            _window.draw((it)->second);
        }
    }
}

sf::RectangleShape SFMLModule::createRectangleShape(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color)
{
    sf::RectangleShape rect(size);

    rect.setPosition(pos);
    rect.setFillColor(color);
    return (rect);
}

const std::string SFMLModule::getPlayerName()
{
    std::string playerName = "";
    sf::Vector2f posConditions(50, _winpos.y /4 - 100);
    sf::Vector2f posName(_winpos.x /3 + 60, _winpos.y /2);
    sf::Vector2f posEnter(50, _winpos.y - 100);
    sf::RectangleShape playerZone(createRectangleShape(sf::Vector2f(340, 70), sf::Vector2f(_winpos.x /3, _winpos.y /2), sf::Color(255, 255, 255, 50)));
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

void SFMLModule::displayPlayerScene(const sf::Vector2f& posConditions, const sf::Vector2f& posName, const sf::RectangleShape& rect, const sf::Vector2f& posEnter, const std::string& playerName)
{
    _window.clear();
    _window.draw(_background);
    _window.draw(rect);
    _text.draw(posConditions, "Enter your playername.", _window);
    _text.draw(posName, playerName, _window, sf::Color::White);
    _text.draw(posEnter, "Press enter to confirm.", _window);
    _window.display();
}

void SFMLModule::displayWindow()
{
    _window.display();
}