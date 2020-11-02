/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** buffer.hpp
*/


#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>

class buffer
{
public:
    buffer();
    buffer(const buffer& other) = default;
    buffer& operator=(const buffer& other) = default;
    void addData(boost::uuids::uuid& uuid, const std::string& data);
    std::vector<std::string>& getData(boost::uuids::uuid& uuid);
    bool isDataAvailable(boost::uuids::uuid& uuid) const;
    ~buffer() = default;
private:
    std::map<boost::uuids::uuid, std::vector<std::string>> _sBuffer;
};

#endif /* !BUFFER_HPP_ */
