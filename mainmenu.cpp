#include "mainmenu.hpp"

MainMenu::MainMenu() : anamenucurrentdurum(anamenudurumu::anaMenu)
{
	if (!mtexture.loadFromFile("texturlar/button2.png")) // Arka plan resmi yükleniyor
	{
		throw std::runtime_error("Arka plan resmi yüklenemedi.");
	}

	mfontayarla();
	itemekleme();
	tuslarayarla();
}

void MainMenu::setmenudurum(anamenudurumu durum)
{
	anamenucurrentdurum = durum;
}

void MainMenu::menuciz(sf::RenderWindow& ekran)
{
	for (int i = 0;i<menuitems.size(); i ++)
	{
		tuslar[i].tusciz(ekran);
		ekran.draw(menuitems[i]);
	}

}

void MainMenu::itemekleme()
{	
	sf::Text ayarlar(mfont);
	ayarlar.setPosition(sf::Vector2f(205, 185));
	ayarlar.setString("Ayarlar");
	ayarlar.setCharacterSize(24);
	ayarlar.setFillColor(sf::Color::Black);
	menuitems.push_back(ayarlar);

	sf::Text odaolustur(mfont);
	odaolustur.setPosition(sf::Vector2f(180, 285));
	odaolustur.setString("Oda olustur");
	odaolustur.setCharacterSize(24);
	odaolustur.setFillColor(sf::Color::Black);
	menuitems.push_back(odaolustur);

	sf::Text odagiris(mfont);
	odagiris.setPosition(sf::Vector2f(180, 390));
	odagiris.setString("Odalari listele");
	odagiris.setCharacterSize(24);
	odagiris.setFillColor(sf::Color::Black);
	menuitems.push_back(odagiris);

	sf::Text cikis(mfont);
	cikis.setPosition(sf::Vector2f(220, 490));
	cikis.setString("Cikis");
	cikis.setCharacterSize(24);
	cikis.setFillColor(sf::Color::Black);
	menuitems.push_back(cikis);

}

void MainMenu::mfontayarla()
{
	if (!mfont.openFromFile("yazitipi.ttf")) // Font dosyasýný uygun bir þekilde yükleyin
	{
		throw std::runtime_error("Font dosyasý yüklenemedi.");
	}
}

MainMenu::anamenudurumu MainMenu::getanamenudurum() const
{
	return anamenucurrentdurum;
}

void MainMenu::tuslarayarla()
{
	Tussprite ayarlartus;
	ayarlartus.tussetPosition(120, 155);
	tuslar.push_back(ayarlartus);

	Tussprite odakurulus;
	odakurulus.tussetPosition(120, 255);
	tuslar.push_back(odakurulus);

	Tussprite odagiris;
	odagiris.tussetPosition(120, 360);
	tuslar.push_back(odagiris);

	Tussprite cikis;
	cikis.tussetPosition(120, 460);
	tuslar.push_back(cikis);

	for (int i = 0; i < tuslar.size(); ++i)
	{
		tuslar[i].settusTexture(mtexture);
	}
}

void MainMenu::menuolayokuyucu(sf::Event& event,sf::RenderWindow& win)
{
	if (const auto* mouseclick = event.getIf<sf::Event::MouseButtonPressed>()) 
	{
		if (mouseclick->button == sf::Mouse::Button::Left)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
			sf::Vector2f worldPos = win.mapPixelToCoords(pixelPos);

			//std::cout << "Menude sol tik'a basildi\n";
			if (tuslar[3].tustiklandimi(win))
			{
				std::cout << "cikis secenegine tiklandi\n";
				anamenucurrentdurum = anamenudurumu::cikis;
			}
			if (tuslar[0].tustiklandimi(win))
			{
				std::cout << "ayarlar secenegine tiklandi\n";
				anamenucurrentdurum = anamenudurumu::ayarlar;
			}
			if (tuslar[1].tustiklandimi(win))
			{
				std::cout << "oda kuruluyor secenegine tiklandi\n";
				anamenucurrentdurum = anamenudurumu::odaOlustur;
			}
			if (tuslar[2].tustiklandimi(win))
			{
				std::cout << "odaya giriliyor secenegine tiklandi\n";
				anamenucurrentdurum = anamenudurumu::odaGiris;
			}
		}
			
		if (mouseclick->button == sf::Mouse::Button::Right)
		{
			std::cout << sf::Mouse::getPosition(win).x << ", " << sf::Mouse::getPosition(win).y << std::endl;
		}

	}
}
