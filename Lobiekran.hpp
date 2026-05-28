#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tussprite.hpp"
#include <vector>
#include "lobiislemleri.hpp"
#include <steam/steam_api.h>


class Lobiekran {
public:
	Lobiekran();

	void Lobiekranciz(sf::RenderWindow& win);

	void lobiolayokuyucu(sf::Event& event,sf::RenderWindow& window);

	void l_butonlari();

	void l_textleri();

	void setkullanicilistesi(const std::vector<lobiislemleri::kisibilgileri>& liste);
	void l_kullanicilarciz(sf::RenderWindow& pencere);

	void setgeritus_l();
	bool getgeritus_l();

	void setbaslatus();
	bool getbaslatus();

	std::vector<lobiislemleri::kisibilgileri> getkullanicilistesi() const;

private:
	sf::Font l_font;

	sf::Texture l_buttontexture;
	
	sf::Texture l_arkaplantexture;
	sf::Sprite arkaplansprite;

	std::vector<Tussprite> l_tuslar;
	std::vector<sf::Text> l_tustext;

	std::vector<std::string> l_kisiadlari;
	std::vector<sf::Image> l_avatar;
	std::vector<lobiislemleri::kisibilgileri> kullanicilar;

	bool baslatusdurum = false;
	bool geritusdurum = false;
};