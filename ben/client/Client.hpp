/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/bind.hpp>
#include <boost/asio/write.hpp>//PB
#include <boost/asio/read_until.hpp>//PB
#include <iostream>

class Client {
    public:
        Client(boost::asio::io_service&);
        void start(boost::asio::ip::udp::resolver::iterator);
        void stop();
        ~Client();

    private:
        void start_connect(boost::asio::ip::udp::resolver::iterator);
        void handle_connect(const boost::system::error_code&, boost::asio::ip::udp::resolver::iterator);
        void check_deadline();
        void start_read();
        void handle_read(const boost::system::error_code&);
        void start_write();
        void handle_write(const boost::system::error_code&);

        boost::asio::deadline_timer _deadline;
        boost::asio::ip::udp::socket _socket;
        boost::asio::deadline_timer _timer;
        boost::asio::streambuf _inputBuffer;
        bool _stopped;


};

#endif /* !CLIENT_HPP_ */
