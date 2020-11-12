/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include "Entityhpp"

namespace Graphic {
class Pirate : public Graphic::Entity{
    public:
        Pirate(bool bonus, const sf::Vector2f &test);
        ~Pirate();
        entityType getType()const;
    private:
    protected:
};
}
#endif /* !PIRATE_HPP_ */
