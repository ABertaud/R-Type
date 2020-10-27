/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** EntityManager.cpp
*/

#include "EntityManager.hpp"
#include <algorithm>
#include <iostream>
#include "Error.hpp"

EntityManager::EntityManager() : _nbEntities(0)
{
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
		_entities.push(entity);
	}
}

Entity EntityManager::createEntity()
{
	if (_nbEntities == MAX_ENTITIES)
		throw ErrorEntitiesNumber();
	Entity id = _entities.front();
	_entities.pop();
	_nbEntities++;
	_ids.push_back(id);
	return (id);
}

void EntityManager::destroyEntity(const Entity entity)
{
	std::vector<Entity>::iterator it = std::find(_ids.begin(), _ids.end(), entity);
	if (it != _ids.end())
    	_ids.erase(it);
	else {
		std::cerr << "invalid remove" << std::endl;
		return;
	}
	_entities.push(entity);
	_nbEntities--;
}

std::vector<Entity> &EntityManager::getEntities()
{
	return (_ids);
}