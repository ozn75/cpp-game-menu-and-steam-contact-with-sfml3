#include "odakurmamenu.hpp"

odakurmamenu::odakurmamenu() : geritusdurumu(false), odaadi(""), odaaditext(odakurmamfont), lobiarkaplanSprite(lobiarkaplan),
odakurmamenuTus2Sprite(odakurmamenuTus2), sifretext(odakurmamfont)
{
	if (!odakurmamfont.openFromFile("yazitipi.ttf")) // Font dosyasýný uygun bir þekilde yükleyin
	{
		throw std::runtime_error("Font dosyasý yüklenemedi.");
	}
	if (!odakurmatexture.loadFromFile("texturlar/button2.png")) // Oda kurma arka planý için uygun bir resim dosyasý yükleyin
	{
		throw std::runtime_error("Oda kurma arka plan resmi yüklenemedi.");
	}
	if (!lobiarkaplan.loadFromFile("texturlar/loby.png")) // Lobi arka planý için uygun bir resim dosyasý yükleyin
	{
		throw std::runtime_error("Lobi arka plan resmi yüklenemedi.");
	}
	if (!odakurmamenuTus2.loadFromFile("texturlar/button1.png"))
	{
		throw std::runtime_error("Oda kurma menüsü tuþu resmi yüklenemedi.");
	}

	odaaditext.setFont(odakurmamfont); // Oda adý metni için font ayarla
	odaaditext.setCharacterSize(30); // Oda adý metni boyutunu ayarla
	odaaditext.setStyle(sf::Text::Bold); // Oda adýný kalýn yap
	odaaditext.setFillColor(sf::Color::White); // Oda adý metninin rengini ayarla
	odaaditext.setPosition(sf::Vector2f(310, 360)); // Oda adý metninin konumunu ayarla

	sifretext.setFont(odakurmamfont); // Þifre metni için font ayarla
	sifretext.setCharacterSize(30); // Þifre metni boyutunu ayarla
	sifretext.setStyle(sf::Text::Bold); // Þifre metnini kalýn yap
	sifretext.setFillColor(sf::Color::White); // Þifre metninin rengini ayarla
	sifretext.setPosition(sf::Vector2f(310, 560)); // Þifre metninin konumunu ayarla

	lobiarkaplanSprite.setTexture(lobiarkaplan,true); // Lobi arka planýný ayarla
	lobiarkaplanSprite.setPosition(sf::Vector2f(0, 0)); // Lobi arka planýnýn konumunu ayarla
	lobiarkaplanSprite.setScale(sf::Vector2f(1.0f,1.0f)); // Lobi arka planýný ölçeklendir

	odakurmamenuTus2Sprite.setTexture(odakurmamenuTus2, true); // Oda kurma menüsü tuþunu ayarla
	odakurmamenuTus2Sprite.setPosition(sf::Vector2f(0, 0)); // Oda kurma menüsü tuþunun konumunu ayarla
	odakurmamenuTus2Sprite.setScale(sf::Vector2f(1.0f, 1.0f)); // Oda kurma menüsü tuþunu ölçeklendir

	odaadgiris.setSize(sf::Vector2f(400, 50)); // Oda adý giriþ kutusu
	odaadgiris.setFillColor(sf::Color::Black); // Oda adý giriþ kutusunun rengini ayarla
	odaadgiris.setPosition(sf::Vector2f(295, 350)); // Oda adý giriþ kutusunun konumunu ayarla
	odaadgiris.setOutlineThickness(10); // Oda adý giriþ kutusunun kenar kalýnlýðýný ayarla
	odaadgiris.setOutlineColor(sf::Color::Cyan);

	sifregiris.setSize(sf::Vector2f(400, 50)); // Þifre giriþ kutusu
	sifregiris.setFillColor(sf::Color::Black); // Þifre giriþ kutusunun rengini ayarla
	sifregiris.setPosition(sf::Vector2f(295, 550)); // Þifre giriþ kutusunun konumunu ayarla
	sifregiris.setOutlineThickness(10); // Þifre giriþ kutusunun kenar kalýnlýðýný ayarla
	sifregiris.setOutlineColor(sf::Color::Cyan); // Þifre giriþ kutusunun kenar rengini ayarla


	odakurmatextleri(); // Menü metinlerini ayarla
	odatusekleme(); // Oda kurma menüsündeki tuþlarý ekle

}

void odakurmamenu::odakurmaciz(sf::RenderWindow& ekran)
{
	ekran.draw(lobiarkaplanSprite); // Lobi arka planýný çiz

	ekran.draw(odakurmamenuTus2Sprite); // Oda kurma arka planýný çiz

	ekran.draw(odaadgiris); // Oda adý giriþ kutusunu çiz

	ekran.draw(sifregiris); // Þifre giriþ kutusunu çiz

	for (int i = 0; i < odakurmamenuTuslar.size(); i++)
	{
		odakurmamenuTuslar[i].tusciz(ekran); // Menü tuþlarýný çiz
	}

	for (int i = 0; i < odakurmamenuitems.size(); i++)
	{
		ekran.draw(odakurmamenuitems[i]); // Menü metinlerini çiz
	}
	
	ekran.draw(odaaditext); // Oda adý metnini çiz
	ekran.draw(sifretext); // Þifre metnini çiz
}

void odakurmamenu::odakurmatextleri()
{
	sf::Text odakurma(odakurmamfont);
	odakurma.setString("Oda Kurma");
	odakurma.setCharacterSize(24);
	odakurma.setFillColor(sf::Color::Black);
	odakurma.setPosition(sf::Vector2f(890, 860));
	odakurmamenuitems.push_back(odakurma);

	sf::Text geriTus(odakurmamfont);
	geriTus.setString("Geri");
	geriTus.setCharacterSize(24);
	geriTus.setFillColor(sf::Color::Black);
	geriTus.setPosition(sf::Vector2f(285, 860));
	odakurmamenuitems.push_back(geriTus);

	sf::Text baslatma(odakurmamfont);
	baslatma.setString("baslat");
	baslatma.setCharacterSize(24);
	baslatma.setFillColor(sf::Color::Black);
	baslatma.setPosition(sf::Vector2f(1215, 860));
	odakurmamenuitems.push_back(baslatma);

	sf::Text odaadgirin(odakurmamfont);
	odaadgirin.setString("Oda Adi Girin:");
	odaadgirin.setStyle(sf::Text::Bold);
	odaadgirin.setCharacterSize(30);
	odaadgirin.setFillColor(sf::Color::Black);
	odaadgirin.setPosition(sf::Vector2f(295, 295));
	odakurmamenuitems.push_back(odaadgirin);

	sf::Text sifregirin(odakurmamfont);
	sifregirin.setString("Sifre Girin:");
	sifregirin.setStyle(sf::Text::Bold);
	sifregirin.setCharacterSize(30);
	sifregirin.setFillColor(sf::Color::Black);
	sifregirin.setPosition(sf::Vector2f(295, 495));
	odakurmamenuitems.push_back(sifregirin);

}

void odakurmamenu::odakurmamenuolayokuyucu(sf::Event& event,sf::RenderWindow& win)
{	
	if (textgirisdurumodaadi || textgirisdurumusifre)
	{
		if (const auto textEntered = event.getIf<sf::Event::TextEntered>())
		{
			if (textgirisdurumodaadi)
			{
				if (textEntered->unicode == 8) { // Backspace (silme)
					if (!odaadi.empty())
					{
						odaadi.pop_back();
					}
				}
				else if (textEntered->unicode >= 32 && textEntered->unicode <= 126) {
					// Yazýlabilir karakterse (örneðin harf veya sayý)
					char girilenHarf = static_cast<char>(textEntered->unicode);
					if (odaadi.length() < 15)
					{
						odaadi += girilenHarf;
					}
				}

				// sf::Text nesnesine string’i aktar
				odaaditext.setString(odaadi);
			}
			if (textgirisdurumusifre)
			{
				if (textEntered->unicode == 8) { // Backspace (silme)
					if (!sifre.empty())
					{
						sifre.pop_back();
					}
				}
				else if (textEntered->unicode >= 32 && textEntered->unicode <= 126) {
					// Yazýlabilir karakterse (örneðin harf veya sayý)
					char girilenHarf = static_cast<char>(textEntered->unicode);
					if (sifre.length() < 15)
					{
						sifre += girilenHarf;
					}
				}
				// sf::Text nesnesine string’i aktar
				sifretext.setString(sifre);
			}
			
		}
	}
	
	if (const auto* mouseclick = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseclick->button == sf::Mouse::Button::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(win);
			sf::Vector2f worldMousePosition = win.mapPixelToCoords(mousePosition);
			if (odakurmamenuTuslar[0].tustiklandimi(win)) // Geri tuþu
			{
				geritusdurumu = true;
			}
			else if (odakurmamenuTuslar[1].tustiklandimi(win)) // Oda kurma tuþu
			{
				odakurmatusbas = true;
			}
			if (odaadgiris.getGlobalBounds().contains(worldMousePosition)) {
				textgirisdurumodaadi = true;
				textgirisdurumusifre = false;
				odaadgiris.setOutlineColor(sf::Color::Red);
				sifregiris.setOutlineColor(sf::Color::Cyan);
			}
			else if (sifregiris.getGlobalBounds().contains(worldMousePosition)) {
				textgirisdurumusifre = true;
				textgirisdurumodaadi = false;
				sifregiris.setOutlineColor(sf::Color::Red);
				odaadgiris.setOutlineColor(sf::Color::Cyan);
			}
			else if (!sifregiris.getGlobalBounds().contains(worldMousePosition) && !odaadgiris.getGlobalBounds().contains(worldMousePosition))
			{
				
				textgirisdurumodaadi = false;
				textgirisdurumusifre = false;
				odaadgiris.setOutlineColor(sf::Color::Cyan);
				sifregiris.setOutlineColor(sf::Color::Cyan);
			}
		}

		if (mouseclick->button == sf::Mouse::Button::Right)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(win);
			sf::Vector2f worldMousePosition = win.mapPixelToCoords(mousePosition);
			std::cout << "Mouse Right Clicked at: (" << worldMousePosition.x << ", " << worldMousePosition.y << ")\n";
			std::cout << "mouse position: " << mousePosition.x << ", " << mousePosition.y << "\n";
		}

	}
}

void odakurmamenu::odakurmasetfont(sf::Font& font)
{
	odakurmamfont = font;
}

void odakurmamenu::odatusekleme()
{
	Tussprite geriTus;
	geriTus.tussetPosition(160, 820); // Geri tuþunun konumunu ayarla
	odakurmamenuTuslar.push_back(geriTus);

	Tussprite odakur;
	odakur.tussetPosition(800, 820); // Oda kurma tuþunun konumunu ayarla
	odakurmamenuTuslar.push_back(odakur);

	Tussprite baslatus;
	baslatus.tussetPosition(1100, 820);
	odakurmamenuTuslar.push_back(baslatus);

	for (int i = 0; i < odakurmamenuTuslar.size(); i++)
	{
		odakurmamenuTuslar[i].settusTexture(odakurmatexture); // Tuþlarýn dokusunu ayarla
	}
}

bool odakurmamenu::getgeritusdurumu()
{
	return geritusdurumu;
}

void odakurmamenu::geritusdurumusýfýla()
{
	geritusdurumu = false; // Geri tuþu durumu sýfýrla
}

bool odakurmamenu::getodakurmatusbas()
{
	return odakurmatusbas;
}

void odakurmamenu::setodakurmatusbas()
{
	odakurmatusbas = false;
}

std::string odakurmamenu::getodaadi()
{
	return odaadi;
}

std::string odakurmamenu::getsifre()
{
	return sifre;
}
