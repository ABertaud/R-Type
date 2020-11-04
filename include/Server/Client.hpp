/*
** Client.hpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/include/Server
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Sat Oct 31 4:46:09 PM 2020 arthurbertaud
** Last update Tue Nov 2 10:01:01 PM 2020 arthurbertaud
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/asio.hpp>

class Client {
    public:
        enum clientState {
            NONE,
            INLOBBY,
            READY,
            INGAME,
            OFF,
        };
        enum playerNumber {
            P1,
            P2,
            P3,
            P4,
            SPEC,
        };
    public:
        Client(const boost::asio::ip::address& adr, const unsigned short port);
        Client(const Client& other) = default;
        Client& operator=(const Client& other) = default;
        boost::uuids::uuid& getUuid();
        void setState(const clientState state);
        clientState getState() const;
        playerNumber getPlayer() const;
        void setPlayer(const playerNumber player);
        boost::asio::ip::udp::endpoint& getEndpoint();
        ~Client() = default;
    protected:
    private:
        boost::uuids::uuid _uuid;
        boost::asio::ip::udp::endpoint _endpoint;
        clientState _state;
        playerNumber _player;
};

#endif /* !CLIENT_HPP_ */