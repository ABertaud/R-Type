/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(std::string configFilePath) :_config()
{
    if (!openFile(configFilePath)) {
        return; //throw error
    }
    if(!linkEntitiesToSprites()) {
        return; //throw error
    }
}

bool Parser::openFile(std::string configFilePath)
{
    _config.open(configFilePath);
    if (!_config) {
        std::cerr << "Error: Incorrect config file\n";
        return false;
    }
    return true;
}

bool Parser::linkEntitiesToSprites()
{
    std::string line(""), code(""), path("");
    
    while (std::getline(_config, line, '\n')) {
        if (line.find("=") != line.npos) {
            code = line.substr(0, line.find("="));
            path = line.substr(line.find("=") + 1);
            if (_key.find(code) == std::end(_key))
                return false;
            _paths.insert(std::pair<Graphic::Object, std::string>(_key.find(code)->second, path));
        }
    }
    return true;
}

std::map<Graphic::Object, std::string> Parser::getPaths() const
{
    return _paths;
}

Parser::~Parser()
{
}

// int main() // MAIN DE TEST DU PARSER
// {
//     Parser *test = new Parser("../../config_file.txt");
//     std::map<Graphic::Object, std::string> map = test->getPaths();
//     for (auto it = map.begin(); it != map.end(); it++)
//         std::cout << it->first << " => " << it->second << std::endl;
//     return 0;
// }