/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** routineSystem.cpp
*/

#include <boost/bind.hpp>
#include <iostream>
#include "ECSEngine.hpp"
#include "routineSystem.hpp"
#include "Zipper.hpp"

ECS::routineSystem::routineSystem(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<Client::playerNumber>>& players) : ECS::ASystem(), _socket(socket)
{
    for (auto it : Zipper::zip(clients, players)) {
        _clients.push_back(it.get<0>());
        _players.push_back(it.get<1>());
    }
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

void ECS::routineSystem::updateGame(const entityDetails& details, const Position& position)
{
    std::string toSend("100 ");
    int ID(0); // L'ID de l'element a mettre a jour
    auto TYPE();//ca c'est le entitytype je crois
    bool STATE(true);// BOOL A 0 SI IL FAUT ENLEVER L'ELEMENT, SINON 1
    int X(0);//posX de l'element
    int Y(1);//posY de l'element

    toSend += std::to_string(ID) + " ";
    toSend += std::to_string(TYPE + "|");
    toSend += std::to_string(STATE + "|");
    toSend += std::to_string(X + ".");
    toSend += std::to_string(Y);
    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>()->getState() == Client::clientState::INGAME && *it.get<1>() != Client::SPEC) {
            _socket->async_send_to(boost::asio::buffer(toSend), it.get<0>()->getEndpoint(),
            boost::bind(&ECS::routineSystem::handleSend, this, toSend,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
}

void ECS::routineSystem::updateMenu(const entityDetails& details, const Position& position)
{
    std::string toSend("200 ");
    std::string player = ("P1/P2/P3/P4");
    std::string state = ("ON/RDY/OFF");
    toSend += std::to_string(player) + " ";//faudra mettre l'enum avec P1/P2/P3/P4          //EN INT
    toSend += std::to_string(state);//faudra mettre l'enum avec si le player est dans la room, si il leave ou si il est dans la room + rdy      // EN INT
    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>()->getState() == Client::clientState::INGAME && *it.get<1>() != Client::SPEC) {
            _socket->async_send_to(boost::asio::buffer(toSend), it.get<0>()->getEndpoint(),
            boost::bind(&ECS::routineSystem::handleSend, this, toSend,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
}

void ECS::routineSystem::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}