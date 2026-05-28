#include "ayarlarmenu.hpp"

ayarlarmenu::ayarlarmenu() : ayararkasprite(ayararkatexture)
{
	if (!font.openFromFile("yazitipi.ttf"))
	{
		throw std::runtime_error("Yazý tipi yüklenemedi.");
	}

	if (!ayararkatexture.loadFromFile("texturlar/loby.png"))
	{
		throw std::runtime_error("Ayarlar resmi yüklenemedi.");
	}

	if (!ayarbutontexture.loadFromFile("texturlar/button2.png"))
	{
		throw std::runtime_error("Ayar buton resmi yüklenemedi.");
	}
	ayararkasprite.setTexture(ayararkatexture,true);
	ayararkasprite.setPosition(sf::Vector2f(0, 0));
	ayararkasprite.setScale(sf::Vector2f(1.0f, 1.0f)); // Ölçeklendirme ay

	asekilekleyici();
	aodatextekleyici();

}

void ayarlarmenu::ayarciz(sf::RenderWindow& ekran)
{
	ekran.draw(ayararkasprite);

	for (const auto& buton : ayarbutonlar)
	{
		buton.tusciz(ekran);
	}
	for (const auto& text : ayarbutontextleri)
	{
		ekran.draw(text);
	}
}

void ayarlarmenu::ayarolayokuyucu(sf::Event& event, sf::RenderWindow& win)
{
	if (const auto* mouseclick = event.getIf<sf::Event::MouseButtonPressed>())
	{
		sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
		if (mouseclick->button == sf::Mouse::Button::Left)
		{
			if (ayarbutonlar[0].tustiklandimi(win))
			{
				geritusbutonaktif = true;
			}
			else if (ayarbutonlar[1].tustiklandimi(win))
			{
				ekranbuton = true;
			}
			else if (ayarbutonlar[2].tustiklandimi(win))
			{
				pencereekranbutton = true;
			}

		}
	}
}

void ayarlarmenu::asekilekleyici()
{
	Tussprite geritusbutton;
	geritusbutton.tussetPosition(100, 900);
	ayarbutonlar.push_back(geritusbutton);

	Tussprite ekransizebuton;
	ekransizebuton.tussetPosition(400, 500);
	ayarbutonlar.push_back(ekransizebuton);

	Tussprite pencerelibuton;
	pencerelibuton.tussetPosition(400, 700);
	ayarbutonlar.push_back(pencerelibuton);

	for (int i = 0; i < ayarbutonlar.size(); ++i)
	{
		ayarbutonlar[i].settusTexture(ayarbutontexture);
	}
}

void ayarlarmenu::aodatextekleyici()
{
	sf::Text geritustext(font);
	geritustext.setString("Geri");
	geritustext.setCharacterSize(24);
	geritustext.setFillColor(sf::Color::White);
	geritustext.setPosition(sf::Vector2f(ayarbutonlar[0].gettusposition().x + 80, ayarbutonlar[0].gettusposition().y + 40));
	ayarbutontextleri.push_back(geritustext);

	sf::Text tamekrantext(font);
	tamekrantext.setString("Tam Ekran");
	tamekrantext.setCharacterSize(24);
	tamekrantext.setFillColor(sf::Color::White);
	tamekrantext.setPosition(sf::Vector2f(ayarbutonlar[1].gettusposition().x + 80,ayarbutonlar[1].gettusposition().y + 40));
	ayarbutontextleri.push_back(tamekrantext);


	sf::Text pencerelibutontext(font);
	pencerelibutontext.setString("Pencere Modu");
	pencerelibutontext.setCharacterSize(24);
	pencerelibutontext.setFillColor(sf::Color::White);
	pencerelibutontext.setPosition(sf::Vector2f(ayarbutonlar[2].gettusposition().x + 80, ayarbutonlar[2].gettusposition().y + 40));
	ayarbutontextleri.push_back(pencerelibutontext);
}

void ayarlarmenu::setgeritus()
{
	geritusbutonaktif = false;
}

bool ayarlarmenu::getgeritus()
{
	return geritusbutonaktif;
}

void ayarlarmenu::setekranbuton()
{
	ekranbuton = false;
}

bool ayarlarmenu::getekranbuton()
{
	return ekranbuton;
}

void ayarlarmenu::setpencereekranbuton()
{
	pencereekranbutton = false;
}

bool ayarlarmenu::getpencereekranbuton()
{
	return pencereekranbutton;
}
