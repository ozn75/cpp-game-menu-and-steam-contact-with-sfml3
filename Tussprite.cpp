#include "Tussprite.hpp"

Tussprite::Tussprite() : tussprite(tustexture)
{
	if (!tustexture.loadFromFile("texturlar/button2.png"))
	{
		throw std::runtime_error("Tus texture could not be loaded.");
	}
	tussprite.setTexture(tustexture, false);
	tussprite.setTextureRect(sf::IntRect({ 0, 0 }, {1536,1024 })); // Set the texture rectangle to match the button size
	tussprite.setScale(sf::Vector2f(0.20f, 0.10f));

}

void Tussprite::tussetPosition(float x, float y)
{
	tussprite.setPosition(sf::Vector2f(x, y));
}

sf::Sprite Tussprite::gettussprite() const
{
	return tussprite;
}

sf::Vector2f Tussprite::gettusposition() const
{
	return sf::Vector2f(tussprite.getPosition().x, tussprite.getPosition().y);
}

void Tussprite::tusciz(sf::RenderWindow& ekran) const
{
	ekran.draw(tussprite);
}

void Tussprite::settusTexture(const sf::Texture& texture)
{
	tustexture = texture;
	tussprite.setTexture(tustexture, true);
}

bool Tussprite::tustiklandimi(sf::RenderWindow& win) const
{
	// Pixel koordinatlarýný al:
	sf::Vector2i pixelPos = sf::Mouse::getPosition(win);

	// Pixel koordinatlarýný world (view) koordinatlarýna çevir:
	sf::Vector2f worldPos = win.mapPixelToCoords(pixelPos);

	if (tussprite.getGlobalBounds().contains(worldPos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

