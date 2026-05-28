#include "odalistelememenu.hpp"

odalistelememenu::odalistelememenu() : listmenuarkasprite(ol_textur)
{
	if (!listmenuyazýfont.openFromFile("yazitipi.ttf"))
	{
		std::cerr << "Oda listeleme menüsü yazý tipi yüklenemedi!" << std::endl;
	}

	if (!ol_texturtus.loadFromFile("texturlar/button2.png"))
	{
		std::cerr << "Oda listeleme menüsü tuþ resmi yüklenemedi!" << std::endl;
	}

	// Oda listeleme menüsü için gerekli baþlangýç ayarlarý
	if (!ol_textur.loadFromFile("texturlar/loby.png"))
	{
		std::cerr<< "Oda listeleme menüsü arka plan resmi yüklenemedi!" << std::endl;
	}

	if (!odaisimtextur.loadFromFile("texturlar/button1.png"))
	{
		std::cerr << "Oda isim arka plan resmi yüklenemedi!" << std::endl;
	}

	listmenuarkasprite.setTexture(ol_textur,true);
	listmenuarkasprite.setPosition(sf::Vector2f(0, 0)); // Arka planý pencerenin sol üst köþesine yerleþtir
	listmenuarkasprite.setScale(sf::Vector2f(1.0f, 1.0f)); // Gerekirse ölçeklendirme yapabilirsiniz
	ol_spriteekle();
	ol_yazýekleme();


}

void odalistelememenu::odalisteleciz(sf::RenderWindow& window)
{
	window.draw(listmenuarkasprite);

	for (int i = 0; i < listmenusprite.size(); ++i)
	{
		listmenusprite[i].tusciz(window);
	}

	for (int i = 0; i < listmenuyazýlarý.size(); ++i)
	{
		window.draw(listmenuyazýlarý[i]);
	}

	for (int i = 0; i < odaisimspritelist.size(); ++i)
	{
		window.draw(odaisimspritelist[i]);
	}

	for (int i = 0; i < odaisimtext.size(); ++i)
	{
		window.draw(odaisimtext[i]);
	}

}
void odalistelememenu::ol_yazýekleme()
{
	sf::Text geritustext(listmenuyazýfont);
	geritustext.setString("Geri");
	geritustext.setCharacterSize(24);
	geritustext.setFillColor(sf::Color::Black);
	geritustext.setPosition(sf::Vector2f(215, 640));
	listmenuyazýlarý.push_back(geritustext);

	sf::Text odalisteletext(listmenuyazýfont);
	odalisteletext.setString("Oda Listele");
	odalisteletext.setCharacterSize(24);
	odalisteletext.setFillColor(sf::Color::Black);
	odalisteletext.setPosition(sf::Vector2f(215, 820));
	listmenuyazýlarý.push_back(odalisteletext);

	sf::Text katiltext(listmenuyazýfont);
	katiltext.setString("Katil");
	katiltext.setCharacterSize(24);
	katiltext.setFillColor(sf::Color::Black);
	katiltext.setPosition(sf::Vector2f(200, 140));
	listmenuyazýlarý.push_back(katiltext);

}

void odalistelememenu::ol_spriteekle()
{
	Tussprite geritussprite;
	geritussprite.tussetPosition(100, 600);
	listmenusprite.push_back(geritussprite);

	Tussprite odalisteletussprite;
	odalisteletussprite.tussetPosition(100, 800);
	listmenusprite.push_back(odalisteletussprite);

	Tussprite katil;
	katil.tussetPosition(100, 100);
	listmenusprite.push_back(katil);

	for (int i = 0; i < listmenusprite.size(); ++i)
	{
		listmenusprite[i].settusTexture(ol_texturtus);
	}

}

void odalistelememenu::tiklananoda(sf::RenderWindow& win)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(win);
	sf::Vector2f worldMousePosition = win.mapPixelToCoords(mousePosition);

	// Sonra yalnýzca týklanana kýrmýzý uygula
	for (int i = 0; i < odaisimspritelist.size(); ++i)
	{
		if (odaisimspritelist[i].getGlobalBounds().contains(worldMousePosition))
		{
			if (odaisimtext[i].getFillColor() == sf::Color::Red)
			{
				// Eðer zaten kýrmýzýysa, týklanan oda rengini eski haline getir
				odaisimtext[i].setFillColor(sf::Color::White);
				std::cout << "Týklanan oda: " << odaisimtext[i].getString().toAnsiString() << " tekrar týklandý, renk beyaza döndürüldü." << std::endl;
				return; // Týklanan oda zaten kýrmýzý, bu yüzden döngüyü sonlandýr
			}
			
			else if (odaisimtext[i].getFillColor() == sf::Color::White)
			{
				// Eðer beyazsa, týklanan oda rengini kýrmýzý yap
				odaisimtext[i].setFillColor(sf::Color::Red);
				seciliodaindex = i; // Týklanan oda indeksini güncelle
				std::cout << "Týklanan oda: " << odaisimtext[i].getString().toAnsiString() << " týklandý, renk kýrmýzýya döndürüldü." << std::endl;
			}
		}
		else if (!odaisimspritelist[i].getGlobalBounds().contains(worldMousePosition))
		{
			odaisimtext[i].setFillColor(sf::Color::White); // Týklanmayan odalarýn rengini beyaz yap
		}
	}
}

bool odalistelememenu::odalisteadlarial(const std::vector<std::string>& odaadi)
{
	//liste adlarý alýnýyor
	odalisteyazilari.clear();
	for (const auto& oda : odaadi)
	{
		odalisteyazilari.push_back(oda);
	}

	// Eski GUI elemanlarýný temizle
	odaisimtext.clear();
	odaisimspritelist.clear();

	// Baþlangýç pozisyonlarý
	int yPozisyonyazi = 120;
	int ypozisyonsprite = 100;

	// Her bir lobi için sprite ve text oluþtur
	for (int i = 0; i < odalisteyazilari.size(); i++)
	{
		// Arka plan sprite
		sf::Sprite odaisimsprite(odaisimtextur);
		odaisimsprite.setTexture(odaisimtextur);
		odaisimsprite.setScale(sf::Vector2f(0.60f, 0.10f));
		odaisimsprite.setPosition(sf::Vector2f(400.f, static_cast<float>(ypozisyonsprite)));
		odaisimspritelist.push_back(odaisimsprite);

		// Lobi ismi yazýsý
		sf::Text lobiText(listmenuyazýfont);
		lobiText.setCharacterSize(30);
		lobiText.setStyle(sf::Text::Bold);
		lobiText.setFillColor(sf::Color::White);
		lobiText.setString(odalisteyazilari[i]);

		// Yazýnýn konumu sprite'ýn ortasýna göre ayarlanýyor
		float textX = odaisimsprite.getPosition().x + 160.f; // sola boþluk
		float textY = odaisimsprite.getPosition().y + 30.f; // yukarýdan ortala
		lobiText.setPosition(sf::Vector2f(textX, textY));

		odaisimtext.push_back(lobiText);

		// Sonraki sprite/text için pozisyonu güncelle
		ypozisyonsprite += 90;
		yPozisyonyazi += 90;
	}

	for (int i = 0; i < odaisimspritelist.size(); ++i)
	{
		odaisimspritelist[i].setTexture(odaisimtextur);
	}

	if (odalisteyazilari.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int odalistelememenu::getodaindex()
{
	return seciliodaindex;
}

void odalistelememenu::odalisteleolay(sf::RenderWindow& window, sf::Event& event)
{
	if (const auto* mouseclick = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseclick->button == sf::Mouse::Button::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);
			if (listmenusprite[0].tustiklandimi(window))
			{
				geritusdurmu = true;
			}

			else if (listmenusprite[1].tustiklandimi(window)) // oda listeleme tuþu
			{
				odalisteledurum = true;
			}
			else if (listmenusprite[2].tustiklandimi(window)) // katil tuþu
			{
				katiltusdurumu = true;
			}
			tiklananoda(window);

		}

		if (mouseclick->button == sf::Mouse::Button::Right)
		{
			std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
		}

	}

}

void odalistelememenu::setgeritusdurmu()
{
	geritusdurmu = false;
}

bool odalistelememenu::getgeritusdurmu() const
{
	return geritusdurmu;
}

void odalistelememenu::setodalistetus()
{
	odalisteledurum = false;
}

bool odalistelememenu::getodalistetus() const
{
	return odalisteledurum;
}

void odalistelememenu::setkatiltusdurumu()
{
	katiltusdurumu = false;
}

bool odalistelememenu::getkatiltusdurumu() const
{
	return katiltusdurumu;
}
