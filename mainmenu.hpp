//mainmenu.hpp
#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tussprite.hpp"

class MainMenu
{
public:
	enum class anamenudurumu
	{
		anaMenu,
		ayarlar,
		loby,
		odaOlustur,
		odaGiris,
		cikis
	};

	MainMenu();

	void setmenudurum(anamenudurumu durum);
	void menuciz(sf::RenderWindow& ekran);
	void menuolayokuyucu(sf::Event& event, sf::RenderWindow& win);
	void itemekleme();
	void mfontayarla();
	anamenudurumu getanamenudurum() const;

	void tuslarayarla();

private:
	std::vector<sf::Text> menuitems;
	sf::Font mfont;
	anamenudurumu anamenucurrentdurum = anamenudurumu::anaMenu;

	sf::Texture mtexture;

	std::vector<Tussprite> tuslar;
};