#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Tussprite
{
public:
    Tussprite();
    
    void tussetPosition(float x, float y);
    sf::Sprite gettussprite() const;
    sf::Vector2f gettusposition() const;
    void tusciz(sf::RenderWindow& ekran) const;
    void settusTexture(const sf::Texture& texture);
	bool tustiklandimi(sf::RenderWindow& win) const;

private:
    sf::Texture tustexture;
	sf::Sprite tussprite;
};
