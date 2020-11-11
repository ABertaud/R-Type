/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** IEntity.hpp
*/


#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "entityType.hpp"

namespace Graphic {

class IEntity {
    public:
        virtual ~IEntity() = default;
        virtual void update() = 0;   // update the object in your window
        virtual entityType getType()const = 0;   // return the type of the object
    protected:
    private:
};
}
#endif