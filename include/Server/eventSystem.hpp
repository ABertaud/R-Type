/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** eventSystem.hpp
*/

#ifndef EVENTSYSTEM_HPP_
#define EVENTSYSTEM_HPP_

#include "ASystem.hpp"
#include "Buffer.hpp"
#include "Player.hpp"

namespace ECS {
    class eventSystem : public ASystem {
    public:
        eventSystem(const std::shared_ptr<Buffer>& buffer);
        eventSystem(const eventSystem& other) = default;
        eventSystem& operator=(const eventSystem& other) = default;
        void update(const float dt, ECSEngine& engine);
        void handleEvent(std::vector<std::string>& events, ECS::ECSEngine& engine, const Entity entity, ECS::Player& player);
        ~eventSystem() = default;
    private:
        std::shared_ptr<Buffer> _buffer;
        std::map<std::string, ECS::currentMovement> _moves;
    };
}

#endif /* !EVENTSYSTEM_HPP_ */
