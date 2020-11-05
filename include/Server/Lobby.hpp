/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.hpp
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_


#include <memory>
#include <queue>
#include "Client.hpp"
#include "Buffer.hpp"

class Lobby {
    public:
        enum lobbyState {
            FREE,
            INGAME,
        };
        Lobby(const std::string &name);
        Lobby(const Lobby& other) = default;
        Lobby& operator=(const Lobby& other) = default;
        void addClient(std::shared_ptr<Client>& client);
        void removeClient(const std::shared_ptr<Client>& client);
        void loadingLobby();
        bool isReadyToGo();
        void startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer);
        bool isRoomFull();
        std::string getName() const;
        bool hasClient(const std::shared_ptr<Client>& client);
        Client::playerNumber getPlayerNumber(const std::shared_ptr<Client>& client);
        Lobby::lobbyState getState() const;
        ~Lobby() = default;
    protected:
    private:
        void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
        std::string _name;
        std::vector<std::shared_ptr<Client::playerNumber>> _players;
        std::vector<std::shared_ptr<Client>> _clients;
        std::queue<Client::playerNumber> _available;
        lobbyState _state;
};

#endif /* !LOBBY_HPP_ */
