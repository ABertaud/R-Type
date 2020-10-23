/*
** SystemManager.cpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/src/Server
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Wed Oct 21 11:41:41 PM 2020 arthurbertaud
** Last update Wed Oct 21 11:41:41 PM 2020 arthurbertaud
*/

#include "SystemManager.hpp"

SystemManager::SystemManager()
{
}

std::vector<std::shared_ptr<ISystem>> &SystemManager::getSystems()
{
    return (_systems);
}

void SystemManager::addSystem(const std::shared_ptr<ISystem> &system)
{
    _systems.push_back(system);
}