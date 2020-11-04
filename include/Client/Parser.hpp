/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "IEntity.hpp"

class Parser {
    public:    
        Parser(std::string configFilePath = "ressources/config_file.txt");
        bool openFile(std::string configFilePath);
        bool linkEntitiesToSprites();
        std::map<entityType, std::string> getPaths() const;
        ~Parser();

    protected:
        std::ifstream _config;
        std::map<entityType, std::string> _paths;
        const std::map<std::string, entityType> _key {
        {"player1", entityType::P1},//player spaceship
        {"player2", entityType::P2},//player spaceship
        {"player3", entityType::P3},//player spaceship
        {"player4", entityType::P4},//player spaceship
        {"background", entityType::BACKGROUND},//background
        {"planete", entityType::WALL},//indestructible obstacles
        {"meteorite", entityType::OBSTACLE},//destructible obstacles
        {"player_shoot", entityType::PLAYER_SHOOT},//player bullets
        {"alien", entityType::ALIEN},
        {"alien_shoot", entityType::ALIEN_SHOOT},
        {"ufo", entityType::UFO},//hunter monster
        {"ufo_shoot", entityType::UFO_SHOOT},//hunter monster bullets
        {"spaceship", entityType::SPACESHIP},
        {"spaceship_shoot", entityType::SPACESHIP_SHOOT},
        {"pirate", entityType::PIRATE},
        {"pirate_shoot", entityType::PIRATE_SHOOT},
    };
};

#endif /* !PARSER_HPP_ */
