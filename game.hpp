#pragma once
#include <SFML/Graphics.hpp>
#include "mainmenu.hpp"
#include "odakurmamenu.hpp"
#include "lobiislemleri.hpp"
#include "odalistelememenu.hpp"

#include "ayarlarmenu.hpp"

#include "Lobiekran.hpp"

#include "Oyunekrani.hpp"




class Game
{
public:
	enum class oyundurumu
	{
		ayarlar,
		anaMenu,
		lobi,
		odakurma,
		odaarama,
		oyunekrani,
		cikis
	};

	Game();

	void ciz();

	void olayokuyucu();

	void calistir();


private:
	odalistelememenu odalistelememenuobjesi;
	Lobiekran lobiekranobjesi;
	lobiislemleri lobi;
	
	sf::Texture arkaplantexture;
	sf::Sprite arkaplanSprite;

	oyundurumu currentdurum;
	sf::RenderWindow pencere;
	MainMenu mainmenu;
	odakurmamenu odakurmamenuobjesi;
	
	ayarlarmenu ayarlarmenuobjesi;

	Oyunekrani oyunekranobjesi;

	sf::View view;
};
