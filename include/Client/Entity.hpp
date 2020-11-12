/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IEntity.hpp"
#include "Animation.hpp"

namespace Graphic {
class Entity : public Graphic::IEntity {
    public:
        Entity(const entityType &type, bool bonus, const sf::Vector2f &pos);
        Entity(const Entity &other) = default;
        Entity &operator=(const Entity &other) = default;
        virtual ~Entity();
        Animation &getAnimation();
        sf::Vector2f getPos()const;
        void setscale(const sf::Vector2f &scale);
        int getId(void) const;
        entityType getType() const;
        virtual void update(const sf::Vector2f& pos);
        virtual void update(int x, int y);
    protected:
        int _id;
        entityType _type;
        sf::Vector2f _pos;
        bool _bonus;
        sf::Vector2f _scale;
        Animation _animation;    
};
}


#endif