/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include "AEntity.hpp"

namespace Graphic {
class Background : public Graphic::AEntity {
    public:
        Background(bool bonus, const sf::Vector2f &test);
        ~Background();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !BACKGROUND_HPP_ */
