/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** entityType.hpp
*/

#ifndef ENTITYTYPE_HPP_
#define ENTITYTYPE_HPP_

enum entityType
{
    P1,
    P2,
    P3,
    P4,
    BACKGROUND,
    WALL,
    OBSTACLE,
    PLAYER_SHOOT,
    ALIEN,
    ALIEN_SHOOT,
    UFO,
    UFO_SHOOT,
    SPACESHIP,
    SPACESHIP_SHOOT,
    PIRATE,
    PIRATE_SHOOT,
};

enum entityState
{
   BASIC,
   SPECIAL,
   BONUS,
};

#endif /* !ENTITYTYPE_HPP_ */
