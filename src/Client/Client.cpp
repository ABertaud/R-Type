/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string &ip, unsigned short port)
: _sigHandler(), _io_service(), _clientSocket(_io_service), _sfmlModule(), _state(UNREADY)
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

void Client::changeState()
{
    if (_state == UNREADY)
        _state = READY;
    else
        _state = UNREADY;
}

void Client::loop(void)
{
    MenuDrawer::State state;
    std::string port;
    std::vector<std::shared_ptr<players>> test;

    _sfmlModule.init();
    _clientName = _sfmlModule.getPlayerName();
    test.push_back(std::shared_ptr<players>(new players(P1)));
    test.back()->setState(players::ACTIVE);
    test.push_back(std::shared_ptr<players>(new players(P2)));
    test.back()->setState(players::ACTIVE);
    test.push_back(std::shared_ptr<players>(new players(P3)));
    test.back()->setState(players::ACTIVE);
    test.push_back(std::shared_ptr<players>(new players(P4)));
    test.back()->setState(players::READY);
    while (_sigHandler.isInterrupted() != true) {
        // send message every second/2
      //  std::this_thread::sleep_for (std::chrono::milliseconds(500));
       //sender("Create");
        state = _sfmlModule.Menu(_clientName, test, _state);
        if (state == MenuDrawer::State::QUIT)
            _sfmlModule.stop();
        if (state == MenuDrawer::State::WAITING)
            port = _sfmlModule.getRoomName();
        if (state == MenuDrawer::State::READY || state == MenuDrawer::State::UNREADY) {
            changeState();
            _sfmlModule.setState(MenuDrawer::State::ROOM);
        }
        if (state == MenuDrawer::State::WAITING)
            _sfmlModule.setState(MenuDrawer::State::HOME);
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


void Client::update(const std::string& update)
{
    // if (std::stoi(update, 3) == 100)
    //     updateGame(update);
    // else if (std::stoi(update, 3) == 200)
    //     updateMenu(update);
    // else
    //     std::cerr << "ERROR in server communication" << std::endl;
}

void Client::updateMenu(const std::string& update)
{
    //l'enum avec P1/P2/P3...
    //PLAYER player = update.substr(update.find_first_of(" ") + 1, update.find_last_of(" ") - update.find_first_of(" "));
    //l'enum avec ON/RDY/OFF
    //STATE state = update.substr(update.find_last_of(" ") + 1);
}

void Client::updateGame(const std::string& update)
{
    // int id = std::stoi(update.substr(update.find_first_of(" ") + 1, update.find_last_of(" ") - update.find_first_of(" ")));
    // bool state = std::stoi(update.substr(update.find_last_of(" ") + 1, 1));
    // //entityType type = std::stoi(update.substr(update.find_first_of("|") + 1, update.find_last_of("|") - update.find_first_of("|")));
    // int x = std::stoi(update.substr(update.find_last_of("|") + 1, update.find_first_of(".") - update.find_last_of("|")));
    // int y = std::stoi(update.substr(update.find_first_of(".") + 1));
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
