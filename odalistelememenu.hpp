#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tussprite.hpp"

class odalistelememenu
{
public:
	odalistelememenu();

	void odalisteleciz(sf::RenderWindow& window);

	void odalisteleolay(sf::RenderWindow& window, sf::Event& event);

	void setgeritusdurmu();
	bool getgeritusdurmu() const;

	void setodalistetus();
	bool getodalistetus() const;

	void setkatiltusdurumu();
	bool getkatiltusdurumu() const;

	void ol_yazýekleme();

	void ol_spriteekle();

	void tiklananoda(sf::RenderWindow& win);

	bool odalisteadlarial(const std::vector<std::string>& odaadi);

	int getodaindex();
private:
	sf::Font listmenuyazýfont;

	std::vector<std::string> odalisteyazilari;
	int seciliodaindex = 0;

	sf::Texture odaisimtextur;
	std::vector<sf::Sprite> odaisimspritelist;

	std::vector<sf::Text> odaisimtext;
    
	bool geritusdurmu = false;
	bool odalisteledurum = false;
	bool katiltusdurumu = false;

	sf::Texture ol_texturtus;
	sf::Texture ol_textur;
	sf::Sprite listmenuarkasprite;


	std::vector<Tussprite> listmenusprite;
	std::vector<sf::Text> listmenuyazýlarý;
};
