/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ParallaxShader.hpp
*/

#include <SFML/Graphics.hpp>
#include <string>

class ParallaxShader {
    private:
        float _offset;
        sf::Clock _clock; 
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Shader _parallaxShader;
    public:
        ParallaxShader(const std::string &);
        ~ParallaxShader();
        void parallaxShaderDraw(sf::RenderWindow &window);
};