/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** udpServer.cpp
*/

#include "udpServer.hpp"
#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <sstream>

udpServer::udpServer(boost::asio::io_context& ioContext) : _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT))
{
    _parser.insert(std::make_pair(Client::NONE, &udpServer::parserNoneState));
    _parser.insert(std::make_pair(Client::INLOBBY, &udpServer::parserInLobbyState));
    _parser.insert(std::make_pair(Client::READY, &udpServer::parserReadyState));
    _parser.insert(std::make_pair(Client::INGAME, &udpServer::parserInGameState));
    startReceive();
}

void udpServer::startReceive()
{
    memset(_data, '\0', 4096);
    _socket.async_receive_from(boost::asio::buffer(_data), _remoteEndpoint,
    boost::bind(&udpServer::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

void udpServer::handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (doesClientExist() == false)
        _clients.push_back(std::make_shared<Client>(Client(_remoteEndpoint.address(), _remoteEndpoint.port())));
    if (!error || error == boost::asio::error::message_size) {
        parseData();
        
        startReceive();

    } else
        std::cerr << "error code: " << error.value() << std::endl;
}

void udpServer::parseData()
{
    auto& clt = findClient(_remoteEndpoint.address());

    // std::cout << clt->getState() << std::endl;
    // std::cout << _data << std::endl;
    for (auto it = _parser.begin(); it != _parser.end(); ++it)
        if (it->first == clt->getState())
            (this->*(it->second))(clt);
    startReceive();
}

void udpServer::handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

void udpServer::run()
{
    _socket.get_io_service().run();
}

bool udpServer::doesClientExist()
{
    for (auto& client: _clients) {
        if (client->getEndpoint().address() == _remoteEndpoint.address())
            return (true);
    }
    return (false);
}

std::shared_ptr<Client>& udpServer::findClient(const boost::asio::ip::address& adr)
{
    for (auto& client : _clients) {
        if (client->getEndpoint().address() == adr)
            return (client);
    }
    return (_clients.front());
}



bool udpServer::doesLobbyExist(const std::string& name)
{
    boost::uuids::uuid newUuid;
    std::istringstream iss(name);
    iss >> newUuid;

    for (auto& lobby : _lobbies) {
        if (lobby.getUuid() == newUuid)
            return (true);
    }
    return (false);
}

Lobby& udpServer::findLobby(const std::string& name)
{
    boost::uuids::uuid newUuid;
    std::istringstream iss(name);
    iss >> newUuid;

    for (auto& lobby : _lobbies) {
        if (lobby.getUuid() == newUuid)
            return (lobby);
    }
    return (_lobbies.front());
}

void udpServer::parserNoneState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);
    // auto str = data;
    // std::string buffer = _codec.decodeMessage(str);

    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::size_t second_space = buffer.substr(start + 1, buffer.length()).find(" ");

    
    std::string command = buffer.substr(0, start);
    std::string firstArg = buffer.substr(start + 1, second_space);

    if (std::strcmp(command.c_str(), "Create") == 0) {
        boost::shared_ptr<std::string> message(new std::string("you've create a room"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _lobbies.push_back(Lobby(_buffer));
        _lobbies.back().addClient(clt);
        clt->setState(Client::INLOBBY);
    }
    if (std::strcmp(command.c_str(), "Join") == 0) {
        boost::shared_ptr<std::string> message(new std::string("you want to join a room"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        if (doesLobbyExist(firstArg) == true) {
            findLobby(firstArg).addClient(clt);
            clt->setState(Client::INLOBBY);
        }
    }
}

void udpServer::parserInLobbyState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);

    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::size_t second_space = buffer.substr(start + 1, buffer.length()).find(" ");

    
    std::string command = buffer.substr(0, start);
    std::string firstArg = buffer.substr(start + 1, second_space);

    if (std::strcmp(command.c_str(), "Ready") == 0) {
        boost::shared_ptr<std::string> message(new std::string("ready"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        clt->setState(Client::READY);
    }
    if (std::strcmp(command.c_str(), "Leavelobby") == 0) {
        boost::shared_ptr<std::string> message(new std::string("ready"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        findLobby(firstArg).removeClient(clt->getUuid());
        clt->setState(Client::NONE);
    }
}

void udpServer::parserReadyState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);

    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::size_t second_space = buffer.substr(start + 1, buffer.length()).find(" ");

    
    std::string command = buffer.substr(0, start);
    std::string firstArg = buffer.substr(start + 1, second_space);

    if (std::strcmp(command.c_str(), "Unready") == 0) {
        boost::shared_ptr<std::string> message(new std::string("ready"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        clt->setState(Client::INLOBBY);
    }
    if (std::strcmp(command.c_str(), "Start") == 0) {
        boost::shared_ptr<std::string> message(new std::string("start"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        auto& lobby = findLobby(firstArg);
        if (lobby.isReadyToGo() == true) {
            lobby.startGame();
        }
    }
}

void udpServer::parserInGameState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");

    
    std::string command = buffer.substr(0, start);
    
    if (std::strcmp(command.c_str(), "Leave") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Leave"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        clt->setState(Client::OFF);
        removeClient(clt->getUuid());
        _buffer->addData(clt->getUuid(), "Off");
    }
    if (std::strcmp(command.c_str(), "Up") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Up"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _buffer->addData(clt->getUuid(), "Up");
    }
    if (std::strcmp(command.c_str(), "Down") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Down"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _buffer->addData(clt->getUuid(), "Down");
    }
    if (std::strcmp(command.c_str(), "Right") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Right"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _buffer->addData(clt->getUuid(), "Right");
    }
    if (std::strcmp(command.c_str(), "Left") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Left"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _buffer->addData(clt->getUuid(), "Left");
    }
    if (std::strcmp(command.c_str(), "Shoot") == 0) {
        boost::shared_ptr<std::string> message(new std::string("Shoot"));
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
        boost::bind(&udpServer::handleSend, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        _buffer->addData(clt->getUuid(), "Shoot");
    }
}

void udpServer::removeClient(const boost::uuids::uuid& uuid)
{
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        if ((*clt)->getUuid() == uuid)
            _clients.erase(clt);
    }
}