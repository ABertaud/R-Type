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
        std::map<Graphic::Object, std::string> getPaths() const;
        ~Parser();

    protected:
        std::ifstream _config;
        std::map<Graphic::Object, std::string> _paths;
        const std::map<std::string, Graphic::Object> _key {
        {"background", Graphic::BACKGROUND},//background
        {"planete", Graphic::WALL},//indestructible obstacles
        {"meteorite", Graphic::OBSTACLE},//destructible obstacles
        {"player", Graphic::PLAYER},//player spaceship
        {"player_shoot", Graphic::PLAYER_SHOOT},//player bullets
        {"alien", Graphic::ALIEN},
        {"alien_shoot", Graphic::ALIEN_SHOOT},
        {"ufo", Graphic::UFO},//hunter monster
        {"ufo_shoot", Graphic::UFO_SHOOT},//hunter monster bullets
        {"spaceship", Graphic::SPACESHIP},
        {"spaceship_shoot", Graphic::SPACESHIP_SHOOT},
        {"pirate", Graphic::PIRATE},
        {"pirate_shoot", Graphic::PIRATE_SHOOT},
    };
};

#endif /* !PARSER_HPP_ */
