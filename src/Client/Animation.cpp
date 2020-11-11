/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Animation.cpp
*/

#include "Animation.hpp"

#include <iostream>
Animation::Animation(const sf::Time &frameTime = sf::seconds(0.2)) : _frameTime(frameTime), _currentTime(sf::Time::Zero), _currentState(IDLE), _error(-1)
{
    std::vector<sf::IntRect> idle, action, left, rigth, down, up, shoot;
    _frames.insert(std::make_pair(IDLE, std::make_pair(0, idle)));
    _frames.insert(std::make_pair(ACTION, std::make_pair(0, action)));
    _frames.insert(std::make_pair(LEFT, std::make_pair(0, left)));
    _frames.insert(std::make_pair(RIGHT, std::make_pair(0, rigth)));
    _frames.insert(std::make_pair(DOWN, std::make_pair(0, down)));
    _frames.insert(std::make_pair(UP, std::make_pair(0, up)));
    _frames.insert(std::make_pair(SHOOT, std::make_pair(0, shoot)));

      //  _sprites.insert(std::make_pair(obj, sprite));

}

Animation::~Animation()
{
}

void Animation::addFrame(const StateAnim &state, const sf::IntRect &frame)
{
    for (std::map<StateAnim, std::pair<int, std::vector<sf::IntRect>>>::iterator it = _frames.begin(); it != _frames.end(); it++) {
        if (it->first == state)
            it->second.second.push_back(frame);
    }
}

Animation::StateAnim Animation::getState()const
{
    return _currentState;
}

void Animation::setState(const StateAnim &state)
{
    _currentState = state;
}

sf::IntRect Animation::getFrame(const StateAnim &state)
{
    sf::IntRect error(-1, -1, -1, -1);
    
    for (std::map<StateAnim, std::pair<int, std::vector<sf::IntRect>>>::iterator it = _frames.begin(); it != _frames.end(); it++) {
           if (it->first == state) {
               std::cout << "vec = " << it->second.second.size() << std::endl;
            std::cout << "current = " <<  it->second.first<< std::endl;               
            return it->second.second.at(it->second.first);
        }
    }
    return error;
}

int &Animation::getCurrentFrame(const StateAnim &state)
{
    for (std::map<StateAnim, std::pair<int, std::vector<sf::IntRect>>>::iterator it = _frames.begin(); it != _frames.end(); it++) {
           if (it->first == state)
            return it->second.first;
    }
    return _error;
}

std::vector<sf::IntRect> Animation::getFrames(const StateAnim &state)
{
    std::vector<sf::IntRect> error;

    error.push_back(sf::IntRect(-1, -1, -1, -1));
    for (std::map<StateAnim, std::pair<int, std::vector<sf::IntRect>>>::iterator it = _frames.begin(); it != _frames.end(); it++) {
           if (it->first == state)
            return it->second.second;
    }
    return error;
}

sf::IntRect Animation::update(sf::Time deltaTime, const StateAnim &state)
{
    int currentFrame = getCurrentFrame(state);
    
    // add delta time
    _currentTime += deltaTime;
    _currentState = state;
    // if current time is bigger then the frame time advance one frame
    if (_currentTime >= _frameTime) {
        // reset time, but keep the remainder
        _currentTime = sf::microseconds(_currentTime.asMicroseconds() % _frameTime.asMicroseconds());
        
        // get next Frame index
        std::cout << "current = " << currentFrame <<  " size = " << getFrames(state).size() << std::endl;
        if (currentFrame + 1 < (int)getFrames(state).size()) {
            currentFrame++;
        } else {
            // animation has ended
            if (state == ACTION)
                _currentState = IDLE;
            else
            currentFrame = 0; // reset to start        
        }
            // set the current frame, not reseting the time
        _currentTime = sf::Time::Zero;
    }
    return getFrame(_currentState);
}