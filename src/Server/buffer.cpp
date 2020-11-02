/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** buffer.cpp
*/

#include "buffer.hpp"
#include <boost/uuid/uuid_generators.hpp>

buffer::buffer()
{
}

bool buffer::isDataAvailable(boost::uuids::uuid& uuid) const
{
    if (_sBuffer.find(uuid) != _sBuffer.end())
        return (true);
    return (false);
}

std::vector<std::string>& buffer::getData(boost::uuids::uuid& uuid)
{
    return (_sBuffer[uuid]);
}

void buffer::addData(boost::uuids::uuid& uuid, const std::string& data)
{
    std::vector<std::string> &buff = _sBuffer[uuid];
    buff.push_back(data);
}