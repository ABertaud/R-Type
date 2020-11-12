/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#include "Client.hpp"
#include <memory>

Client::Client(const std::string &ip, unsigned short port)
: _builder(),_sigHandler(), _binCodec(), _ioService(), _clientSocket(_ioService), _sfmlModule(), _state(NONE)
{
    boost::system::error_code err;

    _clientSocket.open(boost::asio::ip::udp::v4(), err);
    if (err)
        std::cerr << "Error while opening socket" << std::endl;
    _remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
    std::fill(_recvBuff.begin(), _recvBuff.end(), -1);
    _serverResponse.insert(std::make_pair(100, &Client::handleUpdateGame));
    _serverResponse.insert(std::make_pair(110, &Client::handleUpdateMenu));
    _serverResponse.insert(std::make_pair(111, &Client::handleFine));
    _serverResponse.insert(std::make_pair(222, &Client::handleInvalidCommand));
    _serverResponse.insert(std::make_pair(333, &Client::handleGhostRoom));
    _serverResponse.insert(std::make_pair(444, &Client::handleFullRoom));
    _serverResponse.insert(std::make_pair(555, &Client::handleTooFast));
}

void Client::start(void)
{
    std::cout << "Welcome to the client !" << std::endl;
    startReceive();
    _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
    _sfmlModule.init();
    _clientName = _sfmlModule.getPlayerName();
    if (_clientName.size() > 8) {
        _sfmlModule.stop();
        return;
    }
    loop();
}

void Client::stop(void)
{
    _thread.detach();
    _ioService.stop();
    _clientSocket.close();
    std::cout << "Bye bye !" << std::endl;
}

void Client::setState(const ClientState& state)
{
    _state = state;
}

void Client::loop(void)
{
    MenuDrawer::State stateMenu = MenuDrawer::State::UNREADY;
    static timeType start = std::chrono::system_clock::now();
    timeType end;
    std::chrono::seconds time;

    _players.push_back(std::shared_ptr<players>(new players(P1)));
    _players.back()->setState(players::READY);
    _players.push_back(std::shared_ptr<players>(new players(P2)));
    _players.back()->setState(players::ACTIVE);
    _players.push_back(std::shared_ptr<players>(new players(P3)));
    _players.back()->setState(players::READY);
    _players.push_back(std::shared_ptr<players>(new players(P4)));
    _players.back()->setState(players::READY);
    while (_sigHandler.isInterrupted() != true) {
        end = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (_state == INLOBBY || _state == READY)
            stateMenu = _sfmlModule.Menu(_clientName, _players, _state);
        else if (_state == INGAME)
            _sfmlModule.drawGame(_entities);
        if (checkGameState(stateMenu, time, end, start) == -1)
            break;
    };
}

int Client::checkGameState(const MenuDrawer::State& state, const std::chrono::seconds &time, const timeType &end, timeType &start)
{
    if (state == MenuDrawer::State::QUIT) {
        _sfmlModule.stop();
        return (-1);
    }
    if (state == MenuDrawer::State::WAITING)
        send(_sfmlModule.getRoomName());
    if (state == MenuDrawer::State::READY || state == MenuDrawer::State::UNREADY) {
        if (time >= std::chrono::seconds(1)) {
            send("210");
            start = std::chrono::system_clock::now();
        }
        _sfmlModule.setState(MenuDrawer::State::ROOM);
    }
    return (0);
}

void Client::startReceive(void)
{
    _clientSocket.async_receive(boost::asio::buffer(_recvBuff), boost::bind(&Client::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

// void Client::write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred)
// {
//     std::cout << "Bytes transferred while writing = " << bytes_transferred << std::endl;
//     if (ec)
//         std::cerr << "ERROR while writing " << bytes_transferred << " bytes on socket" << std::endl;
// }

void Client::handleReceive(const boost::system::error_code& ec, std::size_t bytesTransferred)
{
    BinaryProtocol::Packet p;

    if (ec) {
        std::cerr << "ERROR while reading " << bytesTransferred << " bytes on socket" << std::endl;
        return;
    }
    p = _binCodec.unserialize(_recvBuff);
    if (_binCodec.check_packet(p) != true) {
        std::cerr << "ERROR: packet not valid" << std::endl;
        startReceive();
        return;
    }
    handleServerMessage(p._message);
    startReceive();
}

void Client::handleServerMessage(std::string& update)
{
    int code = std::atoi(update.c_str());

    for (auto it = _serverResponse.begin(); it != _serverResponse.end(); ++it)
        if (it->first == code)
            (this->*(it->second))(update);
}

void Client::handleUpdateMenu(std::string& update)
{
    entityType bufE(static_cast<entityType>(std::atoi(update.substr(update.find_first_of(" ") + 1, update.find_last_of(" ") - update.find_first_of(" ")).c_str())));
    players::State bufC(static_cast<players::State>(std::atoi(update.substr(update.find_last_of(" ") + 1).c_str())));
    players player(bufE);
    player.setState(bufC);
    if (_state == NONE || INGAME)
        _state = INLOBBY;
}


void Client::handleUpdateGame(std::string& update)
{
    int id = std::atoi(update.substr(update.find_first_of(" ") + 1, update.find_last_of(" ") - update.find_first_of(" ")).c_str());
    bool state = std::atoi(update.substr(update.find_last_of(" ") + 1, 1).c_str());
    entityType type = static_cast<entityType>(std::atoi(update.substr(update.find_first_of("|") + 1, update.find_last_of("|") - update.find_first_of("|")).c_str()));
    int x = std::atoi(update.substr(update.find_last_of("|") + 1, update.find_first_of(".") - update.find_last_of("|")).c_str());
    int y = std::atoi(update.substr(update.find_first_of(".") + 1).c_str());

    if (state == true) {
        int found(0);
        for (auto it = _entities.begin(); it != _entities.end(); ++it)
            if (it->get()->getId() == id) {
                it->get()->update(x, y);
                found++;
            }
        if (found == 0) {
            createEntity(id, type, false, sf::Vector2f{x, y});
        }
    } else {
        for (auto it = _entities.begin(); it != _entities.end(); ++it)
            if (it->get()->getId() == id)
                _entities.erase(it);
    }
}

void Client::handleFine(std::string& update)
{
    (void)update;
    std::cout << "code received" << std::endl;
}

void Client::handleInvalidCommand(std::string& update)
{
    (void)update;
    std::cout << "code received" << std::endl;
}

void Client::handleGhostRoom(std::string& update)
{
    (void)update;
    std::cout << "code received" << std::endl;
}

void Client::handleFullRoom(std::string& update)
{
    (void)update;
    std::cout << "code received" << std::endl;
}

void Client::handleTooFast(std::string& update)
{
    (void)update;
    std::cout << "code received" << std::endl;
}

void Client::send(const std::string &str)
{
    boost::system::error_code err;
    std::size_t bytes = 0;

    bytes = _clientSocket.send_to(boost::asio::buffer(_binCodec.serialize(_binCodec.createPacket(str))), _remoteEndpoint, 0, err);
    if (err) {
        std::cerr << "ERROR while sending " << bytes << " bytes of data" << std::endl;
        return;
    }
}

void Client::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos)
{
    //_entities.push_back(std::make_shared<Graphic::AEntity>(_builder.createEntity(entityType, entityType, bonus, entityPos)));
}

void Client::updateEntity(int entityId, const sf::Vector2f& entityPos) const
{
    for (size_t index = 0; index != _entities.size(); index++) {
        if ((_entities[index].get()->getId() == entityId)) {
            _entities.at(index).get()->update(entityPos.x, entityPos.y);
        }
    }
}

void Client::destroyEntity(int entityId)
{
    for (size_t index = 0; index != _entities.size(); index++) {
        if ((_entities[index].get()->getId() == entityId))
            _entities.erase(_entities.begin() + index);
    }
}