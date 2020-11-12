/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Ufo
*/

#ifndef UFO_HPP_
#define UFO_HPP_

#include "Entity.hpp"

namespace Graphic {
class Ufo : public Graphic::Entity {
    public:
        Ufo(bool bonus, const sf::Vector2f &test, const animation &anime);
        ~Ufo();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !UFO_HPP_ */
