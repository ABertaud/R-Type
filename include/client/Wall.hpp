/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.hpp
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "AEntity.hpp"

class Wall : public AEntity {
    public:
        Wall(const Object &type, bool bonus, const sf::Vector2f &test);
        ~Wall();
        void update();             // update the object in your window
        Object getObject()const;   // return the type of the object
    private:
    protected:
};

#endif