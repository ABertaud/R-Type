/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ECSEngine.cpp
*/

#include "ECSEngine.hpp"

ECSEngine::ECSEngine(): _storageM(std::unique_ptr<StorageManager>(new StorageManager())), \
_entityM(std::unique_ptr<EntityManager>(new EntityManager())), _systemM(std::unique_ptr<SystemManager>(new SystemManager()))
{
}

void ECSEngine::update(float dt)
{
    auto &systems = _systemM->getSystems();

    for (auto &system : systems)
        system->update(dt, *this);
}

Entity ECSEngine::getNewEntity() const
{
    return (_entityM->createEntity());
}

void ECSEngine::removeEntity(const Entity entity)
{
	auto &storages = _storageM->getStorages();

    for (auto &storage: storages) {
        storage.second->destroyEntity(entity);
    }
	_entityM->destroyEntity(entity);
}

std::shared_ptr<IStorage> &ECSEngine::getStorage(const componentType type)
{
    return (_storageM->getStorage(type));
}

std::vector<Entity> &ECSEngine::getEntites()
{
    return (_entityM->getEntities());
}