/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** udpServer.cpp
*/

#include "udpServer.hpp"
#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <sstream>

udpServer::udpServer(boost::asio::io_context& ioContext) : _socket(std::make_shared<boost::asio::ip::udp::socket>(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT)))
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
    _socket->async_receive_from(boost::asio::buffer(_data), _remoteEndpoint,
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
    auto& clt = findClient(_remoteEndpoint.port());
    bool alreadyDone = false;

    for (auto it = _parser.begin(); it != _parser.end(); ++it)
        if (it->first == clt->getState() && alreadyDone == false) {
            (this->*(it->second))(clt);
            alreadyDone = true;
        }
    startReceive();
}

void udpServer::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

void udpServer::run()
{
    _socket->get_io_service().run();
}

bool udpServer::doesClientExist()
{
    for (auto& client: _clients) {
        if (client->getEndpoint().port() == _remoteEndpoint.port())
            return (true);
    }
    return (false);
}

std::shared_ptr<Client>& udpServer::findClient(const unsigned short port)
{
    for (auto& client : _clients) {
        if (client->getEndpoint().port() == port)
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
        _lobbies.push_back(Lobby());
        _lobbies.back().addClient(clt);
        clt->setState(Client::INLOBBY);
        std::string uuid = "Room " + boost::uuids::to_string(_lobbies.back().getUuid());
        send(uuid);
    }
    else if (std::strcmp(command.c_str(), "Join") == 0) {
        if (doesLobbyExist(firstArg) == true) {
            auto &lobby = findLobby(firstArg);
            if (lobby.isRoomFull() == true) {
                send("Room is full sorry");
            } else {
                lobby.addClient(clt);
                clt->setState(Client::INLOBBY);
              send("You've joined a room");
            }
        }
    } else
        send("Invalid command");
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
        send("Ready");
        clt->setState(Client::READY);
    }
    else if (std::strcmp(command.c_str(), "Leavelobby") == 0) {
        send("Lobby has been left");
        findLobby(firstArg).removeClient(clt->getUuid());
        clt->setState(Client::NONE);
    } else 
        send("Invalid command");
}

void udpServer::parserReadyState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);

    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    
    std::string command = buffer.substr(0, start);

    if (std::strcmp(command.c_str(), "Unready") == 0) {
        send("Unready");
        clt->setState(Client::INLOBBY);
    }
    else if (std::strcmp(command.c_str(), "Start") == 0) {
        auto& lobby = findLobby(clt);
        if (lobby.isReadyToGo() == true) {
            // send("The game will start");
            lobby.startGame(_socket, _buffer);
        } else
            send("All the players aren't ready yet");  
    } else
        send("Invalid command");
}

void udpServer::parserInGameState(std::shared_ptr<Client>& clt)
{
    std::string buffer(_data);
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");

    
    std::string command = buffer.substr(0, start);
    
    if (std::strcmp(command.c_str(), "Leave") == 0) {
        send("You left the game");
        clt->setState(Client::OFF);
        removeClient(clt->getUuid());
        _buffer->addData(clt->getUuid(), "Off");
    }
    else if (std::strcmp(command.c_str(), "Up") == 0) {
        send("You go Up");
        _buffer->addData(clt->getUuid(), "Up");
    }
    else if (std::strcmp(command.c_str(), "Down") == 0) {
        send("You go Down");
        _buffer->addData(clt->getUuid(), "Down");
    }
    else if (std::strcmp(command.c_str(), "Right") == 0) {
        send("You go Right");
        _buffer->addData(clt->getUuid(), "Right");
    }
    else if (std::strcmp(command.c_str(), "Left") == 0) {
         send("You go Left");
        _buffer->addData(clt->getUuid(), "Left");
    }
    else if (std::strcmp(command.c_str(), "Shoot") == 0) {
        send("You Shoot");
        _buffer->addData(clt->getUuid(), "Shoot");
    } else
        send("Invalid command");
}

void udpServer::removeClient(const boost::uuids::uuid& uuid)
{
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        if ((*clt)->getUuid() == uuid)
            _clients.erase(clt);
    }
}

void udpServer::send(const std::string &toSend)
{
    _socket->async_send_to(boost::asio::buffer(toSend), _remoteEndpoint,
    boost::bind(&udpServer::handleSend, this, toSend,
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

Lobby& udpServer::findLobby(const std::shared_ptr<Client>& client)
{
    for (auto& lobby : _lobbies) {
        if (lobby.hasClient(client) == true)
            return (lobby);
    }
    return (_lobbies.front());
}