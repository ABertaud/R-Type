/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.cpp
*/

#include "Player.hpp"

Graphic::Player::Player(const entityType &type, bool bonus, const sf::Vector2f &test) :
Graphic::AEntity(type, bonus, test)
{
    sf::IntRect rect(0, 0, 33.2, 20);

    _animation.addFrame(Animation::StateAnim::DOWN, rect);
    rect.left += 33.2;
    _animation.addFrame(Animation::StateAnim::DOWN, rect);
    _animation.addFrame(Animation::StateAnim::IDLE, rect);
    rect.left += 33.2;
    _animation.addFrame(Animation::StateAnim::IDLE, rect);
    rect.left += 33.2;
    _animation.addFrame(Animation::StateAnim::UP, rect);
    rect.left += 33.2;
    _animation.addFrame(Animation::StateAnim::UP, rect);

}

Graphic::Player::~Player()
{
}

void Graphic::Player::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Player::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Player::getType() const
{
    return _type;
}