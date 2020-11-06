/*
** EPITECH PROJECT, 2020
** client
** File description:
** BinaryProtocol
*/

#include "BinaryProtocol.hpp"

bool BinaryProtocol::Packet::operator==(const Packet &other) const
{
    return ((_magicNumber == other._magicNumber)
    && (_message == other._message));

};

BinaryProtocol::Codec::Codec()
{
}

BinaryProtocol::Packet BinaryProtocol::Codec::createPacket(std::string message)
{
    Packet ret;

    ret._magicNumber = MAGIC_NUMBER;
    ret._message = message;
    return (ret);
}

bool BinaryProtocol::Codec::check_packet(const Packet& toCheck)
{
    return (toCheck._magicNumber == MAGIC_NUMBER);
}

std::vector<uint8_t> BinaryProtocol::Codec::serialize(const Packet& input)
{
    std::size_t str_size = input._message.size();
    int index = 0;
    std::vector<uint8_t> outuput;
    unsigned int packet_size = sizeof(input._magicNumber) + 
        (str_size * (sizeof(char) * sizeof(str_size)));

    outuput.resize(packet_size);

    // ecriture de l'id
    memcpy(outuput.data(), &(input._magicNumber), sizeof(input._magicNumber));
    index += sizeof(input._magicNumber);

    // ecriture de la taille de la string
    memcpy(outuput.data() + index, &str_size, sizeof(str_size));
    index += sizeof(str_size);

    // ecriture de la string
    memcpy(outuput.data() + index, input._message.data(), str_size * sizeof(char));
    index += str_size * sizeof(char);

    return (outuput);
}

BinaryProtocol::Packet BinaryProtocol::Codec::unserialize(const std::vector<uint8_t>& input)
{
    Packet output;
    int index = 0;
    std::size_t str_size = 0;

    // récupération de l'id
    memcpy(&(output._magicNumber), input.data(), sizeof(output._magicNumber));
    index += sizeof(output._magicNumber);

    // récupération de la taille du message
    memcpy(&str_size, input.data() + index, sizeof(str_size));
    index += sizeof(str_size);

    // resize a la bonne taille
    output._message.resize(str_size);
    memcpy((char *)output._message.data(), input.data() + index, str_size * sizeof(char));

    return(output);
}

