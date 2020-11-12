/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AEntity.hpp
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"
#include "Animation.hpp"

namespace Graphic {
class AEntity : public Graphic::IEntity {
    public:
        AEntity(const entityType &type, bool bonus, const sf::Vector2f &pos);
        AEntity(const AEntity &other) = default;
        AEntity &operator=(const AEntity &other) = default;
        virtual ~AEntity();
        Animation &getAnimation();
        sf::Vector2f getPos()const;
        void setscale(const sf::Vector2f &scale);
        int getId(void) const;
        entityType getType() const;
        virtual void update(const sf::Vector2f& pos) = 0;
        virtual void update(int x, int y) = 0;
    private:
    protected:
        int _id;
        entityType _type;
        sf::Vector2f _pos;           // tmp a revoir le type
        bool _bonus;
        sf::Vector2f _scale;
        Animation _animation;
        
};
}


#endif