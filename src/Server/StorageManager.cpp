/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** StorageManager.cpp
*/

#include "StorageManager.hpp"

StorageManager::StorageManager()
{
}

std::unordered_map<componentType, std::shared_ptr<IStorage>> &StorageManager::getStorages()
{
    return (_storages);
}

std::shared_ptr<IStorage> &StorageManager::getStorage(const componentType type)
{
    return (_storages[type]);
}