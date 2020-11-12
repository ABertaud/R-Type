/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Animation.hpp
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        enum StateAnim {
            IDLE,
            ACTION,
            LEFT,
            RIGHT,
            DOWN,
            UP,
            SHOOT
        };
    private:
        sf::Time _frameTime;
        sf::Time _currentTime;
        StateAnim _currentState;
        int _error;
        std::map<StateAnim, std::pair<int, std::vector<sf::IntRect>>> _frames;

        int getCurrentFrame(const StateAnim &);
        std::vector<sf::IntRect> getFrames(const StateAnim &state);
        void setFramePos(int pos, const StateAnim &state);

    public:
        Animation(const sf::Time &frameTime);
        ~Animation();
        void addFrame(const StateAnim &, const sf::IntRect&);
        sf::IntRect getFrame(const StateAnim &);
        sf::IntRect update(sf::Time deltaTime, const StateAnim &state);
        StateAnim getState()const;
        void setState(const StateAnim &);

};

#endif