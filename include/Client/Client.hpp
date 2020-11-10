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
#include <map>

#include "SFMLModule.hpp"
#include "SignalHandler.hpp"
#include "BinaryProtocol.hpp"

#include <chrono>

using timeType = std::chrono::time_point<std::chrono::system_clock>;
class Client
{
    public:
        Client(const std::string& ip, unsigned short port);
        ~Client()=default;
        Client(const Client& other) = default;
        Client& operator=(const Client& other) = default;
        int start(void);
        void stop(void);
        typedef void(Client::*hsmFunction)(std::string&);
    private:
        void sender(const std::string& str);
        void start_receive(void);
        void loop(void);
        int check_game_state(const MenuDrawer::State& state, std::chrono::seconds *time, timeType *end, timeType *start);
        // void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
        void read_handler(const boost::system::error_code& ec, std::size_t bytesTransferred);
        void handleServerMessage(std::string& update);
        void handleUpdateMenu(std::string& update);
        void handleUpdateGame(std::string& update);
        void handleFine(std::string& update);
        void handleInvalidCommand(std::string& update);
        void handleGhostRoom(std::string& update);
        void handleFullRoom(std::string& update);
        void handleTooFast(std::string& update);
        void changeState(void);
    private:
        SignalHandler _sigHandler;
        BinaryProtocol::Codec _binCodec;
        boost::asio::io_service _ioService;
        boost::asio::ip::udp::socket _clientSocket;
        SFMLModule _sfmlModule;
        ClientState _state;
        boost::thread _thread;
        boost::array<uint8_t, 1024> _recvBuff;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::string _clientName;
        std::vector<std::shared_ptr<Graphic::AEntity>> _entities;
        std::vector<std::shared_ptr<players>> _players;
        std::map<int, hsmFunction> _serverResponse;
};

#endif /* !CLIENT_HPP_ */
