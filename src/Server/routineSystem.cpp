/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** routineSystem.cpp
*/

#include "routineSystem.hpp"
#include "ECSEngine.hpp"
#include <boost/bind.hpp>
#include <iostream>

ECS::routineSystem::routineSystem(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, std::vector<std::shared_ptr<Client>>& clients) : ECS::ASystem(), _socket(socket)
{
    for (auto& clt : clients)
        _clients.push_back(clt);   
}

void ECS::routineSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::ENTITY_DETAILS), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), entities);

    for (auto& ent: entities) {
        sendUpdates(engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS), engine.getComponent<ECS::Position>(ent, ECS::POSITION));
    }
}

void ECS::routineSystem::sendUpdates(const entityDetails& details, const Position& position)
{
    std::string toSend("");
    toSend += std::to_string(details._type) + " ";
    toSend += std::to_string(details._state) + " ";
    toSend += std::to_string(position._x) + "." + std::to_string(position._y);
    for (auto& clt : _clients) {
        _socket->async_send_to(boost::asio::buffer(toSend), clt->getEndpoint(),
        boost::bind(&ECS::routineSystem::handleSend, this, toSend,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
}

void ECS::routineSystem::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

// ECS::routineSystem::~routineSystem()
// {
// }