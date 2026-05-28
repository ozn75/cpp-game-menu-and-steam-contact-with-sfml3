#pragma once

#include <SFML/Graphics.hpp>
#include <vector>



class Harita {
public:
	struct kare
	{	
		int kareid;
		sf::RectangleShape sekil;
		sf::Vector2f konum;
		sf::Color renk;
		sf::Vector2f boyut;

	};

	Harita();

	void haritaciz(sf::RenderWindow& win) const;

	void haritaolustur();
	void setharitaboyut(int boyut);

private:
	int haritaboyutu = 0;

	std::vector<kare> haritakareleri;

};