/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AEntity.hpp
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"

namespace Graphic {
class AEntity : public Graphic::IEntity {
    public:
        AEntity(const entityType &type, bool bonus, const sf::Vector2f &pos);
        AEntity(const AEntity &other) = default;
        AEntity &operator=(const AEntity &other) = default;
        virtual ~AEntity();
        void setscale(const sf::Vector2f &scale);
        entityType getObject() const;    // return the type of the object
        virtual void update() = 0;   // update the object in your window
    private:
    protected:
        entityType _type;
        sf::Vector2f _pos;           // tmp a revoir le type
        bool _bonus;
        sf::Vector2f _scale;
};
}


#endif