/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.hpp
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
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
        Lobby();
        Lobby(const Lobby& other) = default;
        Lobby& operator=(const Lobby& other) = default;
        boost::uuids::uuid& getUuid();
        void addClient(std::shared_ptr<Client>& client);
        void removeClient(const boost::uuids::uuid& );
        void loadingLobby();
        bool isReadyToGo();
        void startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer);
        bool isRoomFull();
        bool hasClient(const std::shared_ptr<Client>& client);
        ~Lobby() = default;
    protected:
    private:
        void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
        boost::uuids::uuid _uuid;
        std::vector<std::shared_ptr<Client>> _clients;
        std::queue<Client::playerNumber> _available;
        lobbyState _state;
};

#endif /* !LOBBY_HPP_ */
