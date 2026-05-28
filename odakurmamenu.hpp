#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Tussprite.hpp"


class odakurmamenu
{
public:
	odakurmamenu();
	void odakurmaciz(sf::RenderWindow& ekran);
	void odakurmatextleri();

	void odakurmamenuolayokuyucu(sf::Event& event, sf::RenderWindow& win);
	void odakurmasetfont(sf::Font& font);
	void odatusekleme();
	bool getgeritusdurumu();
	void geritusdurumusýfýla();

	bool getodakurmatusbas();
	void setodakurmatusbas();

	std::string getodaadi();
	std::string getsifre();

private:

	std::vector<sf::Text> odakurmamenuitems;
	sf::Font odakurmamfont;
	sf::Texture odakurmatexture;
	std::vector<Tussprite> odakurmamenuTuslar;

	sf::Texture lobiarkaplan;
	sf::Sprite lobiarkaplanSprite;

	sf::Texture odakurmamenuTus2;
	sf::Sprite odakurmamenuTus2Sprite;

	sf::RectangleShape odaadgiris;

	sf::RectangleShape sifregiris;

	std::string sifre = "";
	sf::Text sifretext;

	std::string odaadi = "";
	sf::Text odaaditext;

	bool textgirisdurumusifre = false; // Þifre için text giriþ durumu
	bool textgirisdurumodaadi = false; // Oda adý için text giriþ durumu
	bool geritusdurumu = false; // Geri tuþunun durumu
	bool odakurmatusbas = false; // Oda kurma tuþuna basýldý mý?
};