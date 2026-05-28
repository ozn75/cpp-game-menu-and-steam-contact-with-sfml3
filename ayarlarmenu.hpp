#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Tussprite.hpp"



class ayarlarmenu
{
public:
    ayarlarmenu();
	void ayarciz(sf::RenderWindow& ekran);

	void ayarolayokuyucu(sf::Event& event, sf::RenderWindow& win);

	void asekilekleyici();
	void aodatextekleyici();

	void setgeritus();
	bool getgeritus();

	void setekranbuton();
	bool getekranbuton();

	void setpencereekranbuton();
	bool getpencereekranbuton();

private:
	sf::Texture ayararkatexture;
	sf::Texture ayarbutontexture;
	sf::Sprite ayararkasprite;

	std::vector<Tussprite> ayarbutonlar;
	std::vector<sf::Text> ayarbutontextleri;

	bool pencereekranbutton = false;
	bool ekranbuton = false;
	bool geritusbutonaktif = false;

	sf::Font font;
};