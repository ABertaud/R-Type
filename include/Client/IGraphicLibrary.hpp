/*
** IGraphicLibrary.hpp for OOP_arcade_2019 in /home/arthurbertaud/Second_year/OOP/OOP_arcade_2019/core/include
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Mon Mar 9 11:16:44 AM 2020 arthurbertaud
** Last update Sun Apr 4 6:44:49 PM 2020 arthurbertaud
*/

#ifndef IGRAPHICLIBRARY_HPP_
#define IGRAPHICLIBRARY_HPP_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "entityType.hpp"
#include "AEntity.hpp"


namespace Graphic
{
enum Command
{
    NOTHING,
    //handled by core
    MENU,
    EXIT,
    //handled by game
    RIGHT,
    LEFT,
    UP,
    DOWN,
    SHOOT,
};
class IGraphicLibrary
{

public:
    virtual ~IGraphicLibrary() = default;
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual Command eventHandler(const std::vector<std::shared_ptr<Graphic::AEntity>> &entityArray) = 0;
    virtual void drawGame(const std::vector<std::shared_ptr<Graphic::AEntity>> &) = 0;
    /* data */
    virtual const std::string getPlayerName() = 0;
    virtual void displayWindow() = 0;

protected:
private:
}; // namespace Arcade
} // namespace Arcade

#endif /* !IGRAPHICLIBRARY_HPP_ */