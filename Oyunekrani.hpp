#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lobiislemleri.hpp"
#include <steam/steam_api.h>
#include "Harita.hpp"
#include "Taslar.hpp"


class Oyunekrani {
public:

	struct oyuncular
	{
		int takimid;
		int oyuncuid;
		CSteamID kisiid;
		std::string kisiadi;
	};

	Oyunekrani();

	void getodabilgilerinial(CSteamID& lobyid);

	void o_ciz(sf::RenderWindow& win);

	void o_olay(sf::RenderWindow& win,sf::Event& olay);

	void oyunekraniruner(sf::RenderWindow& window);

	void zoomAt(const sf::Vector2i& pixel, float factor, sf::RenderWindow& win, sf::View& view);

private:

	Taslar anatas;

	sf::View oyuncugorus;

	Harita harita;

	lobiislemleri lobiobjesi;

	std::vector<oyuncular> oyuncularlistesi;


};
