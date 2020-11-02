/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(boost::asio::io_service& io_service)
: _stopped(false),
_socket(io_service),
_deadline(io_service),
_timer(io_service)
{
    std::cerr << "DEBUG: constructor Client.\n\n";
}

void Client::start(boost::asio::ip::udp::resolver::iterator endpoint_iter)
{
    start_connect(endpoint_iter);//connection sans doute
    _deadline.async_wait(boost::bind(&Client::check_deadline, this));//ca par contre...
}

void Client::start_connect(boost::asio::ip::udp::resolver::iterator endpoint_iter)
{
    if (endpoint_iter != boost::asio::ip::udp::resolver::iterator()) {
        std::cout << "Connecting to " << endpoint_iter->endpoint() << "...\n";
        _deadline.expires_from_now(boost::posix_time::seconds(60));
        _socket.async_connect(endpoint_iter->endpoint(),
            boost::bind(&Client::handle_connect,
            this, _1, endpoint_iter));
    } else {
        stop();
    }
}

void Client::stop()
{
    _stopped = true;
    _socket.close();
    _deadline.cancel();
    _timer.cancel();
}

void Client::handle_connect(const boost::system::error_code& ec, boost::asio::ip::udp::resolver::iterator endpoint_iter)
{
    if (_stopped)
      return;
    if (!_socket.is_open()) {
      std::cout << "Connect timed out\n";
      start_connect(++endpoint_iter);
    } else if (ec) {
      std::cout << "Connect error: " << ec.message() << "\n";
      _socket.close();
      start_connect(++endpoint_iter);
    } else {
      std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
      start_read();
      start_write();
    }
}

void Client::start_read()
{
    _deadline.expires_from_now(boost::posix_time::seconds(30));
/*PB*/    boost::asio::async_read_until(_socket, _inputBuffer, '\n', boost::bind(&Client::handle_read, this, _1));
}

void Client::handle_read(const boost::system::error_code& ec)
{
    if (_stopped)
      return;

    if (!ec) {
      std::string line;
      std::istream is(&_inputBuffer);
      std::getline(is, line);
      if (!line.empty()) {
        std::cout << "Received: " << line << "\n";
      }
      start_read();
    } else {
      std::cout << "Error on receive: " << ec.message() << "\n";
      stop();
    }
}

void Client::start_write()
{
    if (_stopped)
      return;
/*PB*/    boost::asio::async_write(_socket, boost::asio::buffer("\n", 1), boost::bind(&Client::handle_write, this, _1));
}

void Client::handle_write(const boost::system::error_code& ec)
{
    if (_stopped)
      return;

    if (!ec) {
      _timer.expires_from_now(boost::posix_time::seconds(10));
      _timer.async_wait(boost::bind(&Client::start_write, this));
    } else {
      std::cout << "Error on heartbeat: " << ec.message() << "\n";
      stop();
    }
}

void Client::check_deadline()
{
    if (_stopped)
      return;
    if (_deadline.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
      _socket.close();
      _deadline.expires_at(boost::posix_time::pos_infin);
    }
    _deadline.async_wait(boost::bind(&Client::check_deadline, this));
}

Client::~Client()
{
}
