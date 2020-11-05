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
#include "SignalHandler.hpp"

class Client
{
    public:
        Client(const std::string &ip, unsigned short port);
        ~Client()=default;
        Client(const Client& other) = default;
        Client& operator=(const Client& other) = default;
        int start(void);
        void stop(void);
    private:
        void sender(const std::string &str);
        void start_receive(void);
        void loop(void);
        // void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
        void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
    private:
        SignalHandler _sigHandler;
        boost::asio::io_service _io_service;
        boost::asio::ip::udp::socket _clientSocket;
        boost::thread _thread;
        boost::array<char, 1024> _recv_buff;
        boost::asio::ip::udp::endpoint _remote_endpoint;
};

#endif /* !CLIENT_HPP_ */
