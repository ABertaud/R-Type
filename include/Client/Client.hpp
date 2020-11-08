/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <iostream>

#include "SFMLModule.hpp"
#include "SignalHandler.hpp"
#include "BinaryProtocol.hpp"

class Client
{
    public:
        Client(const std::string& ip, unsigned short port);
        ~Client()=default;
        Client(const Client& other) = default;
        Client& operator=(const Client& other) = default;
        int start(void);
        void stop(void);
    private:
        void sender(const std::string& str);
        void start_receive(void);
        void loop(void);
        // void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
        void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
        void handleServerMessage(const std::string& update);
        void updateMenu(const std::string& update);
        void updateGame(const std::string& update);
        void changeState(void);
    private:
        SignalHandler _sigHandler;
        BinaryProtocol::Codec _binCodec;
        boost::asio::io_service _io_service;
        boost::asio::ip::udp::socket _clientSocket;
        SFMLModule _sfmlModule;
        ClientState _state;
        boost::thread _thread;
        boost::array<uint8_t, 1024> _recvBuff;
        // boost::array<char, 1024> _recvBuff;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        std::string _clientName;
        std::vector<std::shared_ptr<Graphic::AEntity>> _entities;
};

#endif /* !CLIENT_HPP_ */
