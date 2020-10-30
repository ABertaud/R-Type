/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AEntity.hpp
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"

class AEntity : public IEntity {
    public:
        AEntity(const Object &type, bool bonus, const sf::Vector2f &test);
        AEntity(const AEntity &other) = default;
        AEntity &operator=(const AEntity &other) = default;
        ~AEntity() = default;
        Object getObject() const;    // return the type of the object
        virtual void update() = 0;   // update the object in your window
    private:
    protected:
        Object _type;
        sf::Vector2f _pos;           // tmp a revoir le type
        bool _bonus;
};


#endif