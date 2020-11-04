/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** gameLoop.hpp
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "ECSEngine.hpp"
#include "Client.hpp"
#include "Buffer.hpp"
#include "Lobby.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>

class gameLoop
{
public:
    gameLoop();
    gameLoop(const gameLoop& other) = default;
    gameLoop& operator=(const gameLoop& other) = default;
    void run(std::vector<std::shared_ptr<Client>>& clients, Lobby::lobbyState &lobbyState);
    void prepareGame(std::vector<std::shared_ptr<Client>>& clients, const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer);
    ~gameLoop() = default;
private:
    void createPlayers(std::vector<std::shared_ptr<Client>>& clients);
    void update(const float dt);
    void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
    void registerComponents();
    void registerSystems(std::vector<std::shared_ptr<Client>>&, const std::shared_ptr<boost::asio::ip::udp::socket>&, const std::shared_ptr<Buffer>&);
    ECS::ECSEngine _engine;
    std::shared_ptr<Buffer> _buffer;
};


#endif /* !GAMELOOP_HPP_ */
