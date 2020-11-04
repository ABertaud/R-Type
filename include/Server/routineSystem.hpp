/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** routineSystem.hpp
*/

#ifndef ROUTINESYSTEM_HPP_
#define ROUTINESYSTEM_HPP_

#include "ASystem.hpp"
#include "Client.hpp"
#include "Position.hpp"
#include "entityType.hpp"
#include "entityDetails.hpp"
#include <boost/asio.hpp>

namespace ECS {
    class routineSystem : public ASystem {
    public:
        routineSystem(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, std::vector<std::shared_ptr<Client>>& clients);
        routineSystem(const routineSystem& other) = default;
        routineSystem& operator=(const routineSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        void sendUpdates(const entityDetails& details, const Position& position);
        void handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred);
        ~routineSystem() = default;
    private:
        std::shared_ptr<boost::asio::ip::udp::socket> _socket;
        std::vector<std::shared_ptr<Client>> _clients;
    };
}

#endif /* !ROUTINESYSTEM_HPP_ */
