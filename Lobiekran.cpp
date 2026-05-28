#include "Lobiekran.hpp"



Lobiekran::Lobiekran() : arkaplansprite(l_arkaplantexture)
{
	if (!l_font.openFromFile("yazitipi.ttf"))
	{
		std::cout << "yazi tipi yuklenmedi" << std::endl;
	}
	if (!l_arkaplantexture.loadFromFile("texturlar/lobi.png"))
	{
		std::cerr << "texture yuklenmedi" << std::endl;
	}
	if (!l_buttontexture.loadFromFile("texturlar/button2.png"))
	{
		std::cerr << "buton texture yuklenmedi" << std::endl;
	}

	arkaplansprite.setTexture(l_arkaplantexture);
	arkaplansprite.setTextureRect(sf::IntRect({ 0,0 }, { 1536,1024 }));

	l_butonlari();
	l_textleri();

}

void Lobiekran::Lobiekranciz(sf::RenderWindow& win)
{
	win.draw(arkaplansprite);

	for (int i = 0; i < l_tuslar.size(); i++)
	{
		l_tuslar[i].tusciz(win);
	}
	for (int i = 0; i < l_tustext.size(); i++)
	{
		win.draw(l_tustext[i]);
	}

	l_kullanicilarciz(win);  // KULLANICILARI BURADA ÇİZ
}

void Lobiekran::lobiolayokuyucu(sf::Event& event, sf::RenderWindow& window)
{
	if (const auto* mouseclick = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseclick->button == sf::Mouse::Button::Left)
		{
			if (l_tuslar[0].tustiklandimi(window))
			{
				geritusdurum = true;
			}

			if (l_tuslar[1].tustiklandimi(window))
			{
				baslatusdurum = true;
			}
		}
	}
}

void Lobiekran::l_butonlari()
{
	Tussprite geributon;
	geributon.tussetPosition(100, 800);
	l_tuslar.push_back(geributon);

	Tussprite baslabuton;
	baslabuton.tussetPosition(1100,800);
	l_tuslar.push_back(baslabuton);

	for (int i = 0; i < l_tuslar.size(); i++)
	{
		l_tuslar[i].settusTexture(l_buttontexture);
	}
}

void Lobiekran::l_textleri()
{
	sf::Text geritext(l_font);
	geritext.setCharacterSize(24);
	geritext.setString("geri");
	geritext.setFillColor(sf::Color::Black);
	geritext.setPosition(sf::Vector2f(l_tuslar[0].gettusposition().x + 80, l_tuslar[0].gettusposition().y + 30));
	l_tustext.push_back(geritext);

	sf::Text baslatext(l_font);
	baslatext.setCharacterSize(24);
	baslatext.setString("basla");
	baslatext.setFillColor(sf::Color::Black);
	baslatext.setPosition(sf::Vector2f(l_tuslar[1].gettusposition().x + 80, l_tuslar[1].gettusposition().y + 30));
	l_tustext.push_back(baslatext);

}

void Lobiekran::setkullanicilistesi(const std::vector<lobiislemleri::kisibilgileri>& liste)
{
	kullanicilar = liste;
}

void Lobiekran::l_kullanicilarciz(sf::RenderWindow& pencere)
{
	float x = 600.f;
	float y = 300.f;

	for (const auto& kisi : kullanicilar)
	{
		uint32 width = 0, height = 0;
		std::vector<uint8_t> buffer(4 * width * height);
		if (SteamUtils()->GetImageSize(kisi.avatarid, &width, &height))
		{
			std::vector<uint8_t> buffer(4 * width * height);
			if (SteamUtils()->GetImageRGBA(kisi.avatarid, buffer.data(), buffer.size()))
			{
				sf::Texture textur;
				textur.resize(sf::Vector2u(width,height));
				textur.update(buffer.data());
				
				sf::Sprite avartarsprite(textur);
				avartarsprite.setScale(sf::Vector2f(2.f, 2.f));
				avartarsprite.setPosition(sf::Vector2f(x-65,y));

				pencere.draw(avartarsprite);
			}
		}

		sf::RectangleShape alan;
		alan.setSize({ 300, 70 });
		alan.setPosition({ x, y });
		alan.setFillColor(sf::Color::Black);
		pencere.draw(alan);

		sf::Text adyazi(l_font);
		adyazi.setCharacterSize(24);
		adyazi.setFillColor(sf::Color::White);
		adyazi.setString(kisi.ad);
		adyazi.setPosition(sf::Vector2f(x + 10, y + 15));
		pencere.draw(adyazi);

		y += 80; // bir sonraki satıra geç
	}
}

void Lobiekran::setgeritus_l()
{
	geritusdurum = false;
}

bool Lobiekran::getgeritus_l()
{
	return geritusdurum;
}

void Lobiekran::setbaslatus()
{
	baslatusdurum = false;
}

bool Lobiekran::getbaslatus()
{
	return baslatusdurum;
}

std::vector<lobiislemleri::kisibilgileri> Lobiekran::getkullanicilistesi() const
{
	return kullanicilar;
}
