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
#include "Client.hpp"
#include "buffer.hpp"

class Lobby {
    public:
        Lobby(const std::shared_ptr<buffer>& buffer);
        Lobby(const Lobby& other) = default;
        Lobby& operator=(const Lobby& other) = default;
        boost::uuids::uuid& getUuid();
        void addClient(std::shared_ptr<Client>& client);
        void removeClient(const boost::uuids::uuid& );
        void loadingLobby();
        bool isReadyToGo();
        void startGame();
        ~Lobby() = default;
    protected:
    private:
        boost::uuids::uuid _uuid;
        std::vector<std::shared_ptr<Client>> _clients;
        std::shared_ptr<buffer> _buffer;
};

#endif /* !LOBBY_HPP_ */
