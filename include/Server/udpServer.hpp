/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** udpServer.hpp
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "INetwork.hpp"
#include "buffer.hpp"
#include "Lobby.hpp"
#include <map>

#define BUFFER_SIZE 4096
#define PORT 1666

class udpServer : public INetwork {
public:
    udpServer(boost::asio::io_context& );
    void run();
    udpServer(const udpServer& other) = default;
    udpServer& operator=(const udpServer& other) = default;
    ~udpServer() = default;
    typedef void(udpServer::*parsingFunction)(std::shared_ptr<Client>&);
private:
    std::shared_ptr<Client>& findClient(const boost::asio::ip::address& adr);
    bool doesClientExist();
    void startReceive();
    void parseData();
    void acceptConnection();
    Lobby& findLobby(const std::string& name);
    bool doesLobbyExist(const std::string& name);
    void parserNoneState(std::shared_ptr<Client>&);
    void parserInLobbyState(std::shared_ptr<Client>& clt);
    void parserReadyState(std::shared_ptr<Client>& clt);
    void parserInGameState(std::shared_ptr<Client>& clt);
    void removeClient(const boost::uuids::uuid& uuid);
    void handleReceive(const boost::system::error_code& error, std::size_t);
    void handleSend(boost::shared_ptr<std::string>, const boost::system::error_code&, std::size_t);
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    char _data[BUFFER_SIZE];
    std::vector<std::shared_ptr<Client>> _clients;
    std::vector<Lobby> _lobbies;
    std::shared_ptr<buffer> _buffer;
    std::map<Client::clientState, parsingFunction> _parser;
};

#endif /* !UDPSERVER_HPP_ */
