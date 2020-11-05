/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string &ip, unsigned short port)
: _sigHandler(), _io_service(), _clientSocket(_io_service)
{
    boost::system::error_code err;

    _clientSocket.open(boost::asio::ip::udp::v4(), err);
    if (err)
        std::cerr << "Error while opening socket" << std::endl;
    _remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
    std::fill(_recv_buff.begin(), _recv_buff.end(), '\0');
}

int Client::start(void)
{
    std::cout << "Welcome to the client !" << std::endl;
    start_receive();
    _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));
    loop();
    return (0);
}

void Client::stop(void)
{
    _thread.detach();
    _io_service.stop();
    _clientSocket.close();
    std::cout << "Bye bye !" << std::endl;
}

void Client::loop(void)
{
    while (_sigHandler.isInterrupted() != true)
    {
        // send message every second/2
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        sender("Create");
    };
}

void Client::start_receive(void)
{
    _clientSocket.async_receive(boost::asio::buffer(_recv_buff), boost::bind(&Client::read_handler, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

// void Client::write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred)
// {
//     std::cout << "Bytes transferred while writing = " << bytes_transferred << std::endl;
//     if (ec)
//         std::cerr << "ERROR while writing " << bytes_transferred << " bytes on socket" << std::endl;
// }

void Client::read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    if (ec) {
        std::cerr << "ERROR while reading " << bytes_transferred << " bytes on socket" << std::endl;
        return;
    }
    std::cout << "Data : '" << std::string(_recv_buff.begin(), _recv_buff.begin()+bytes_transferred) << "' received" << std::endl;
    start_receive();
}

void Client::sender(const std::string &str)
{
    boost::system::error_code err;

    _clientSocket.send_to(boost::asio::buffer(str), _remote_endpoint, 0, err);
    if (err) {
        std::cerr << "ERROR while sending data" << std::endl;
        return;
    }
}
