#pragma once

#include <SFML/Graphics.hpp>



class Taslar {
public:
	Taslar();


	void settastexture(const sf::Texture& texture1);
	sf::Sprite gettassprite() const;
	void settasposition(float x, float y);
	
private:
	
	sf::Texture tastexture;
	sf::Sprite tassprite;



};
