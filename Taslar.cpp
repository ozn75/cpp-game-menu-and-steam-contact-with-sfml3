#include "Taslar.hpp"

Taslar::Taslar() : tassprite(tastexture)
{
	if (!tastexture.loadFromFile("texturlar/sah.png"))
	{
		throw std::runtime_error("Tas texture could not be loaded.");
	}

	tassprite.setTexture(tastexture,true);
	tassprite.setScale(sf::Vector2f(0.5f, 0.5f));
}

void Taslar::settastexture(const sf::Texture& texture1)
{
	tastexture = texture1;
	tassprite.setTexture(tastexture);
}

sf::Sprite Taslar::gettassprite() const
{
	return tassprite;
}

void Taslar::settasposition(float x, float y)
{
	tassprite.setPosition(sf::Vector2f(x, y));
}

