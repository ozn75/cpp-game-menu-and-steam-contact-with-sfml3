#include "game.hpp"



Game::Game() : currentdurum(oyundurumu::anaMenu) , arkaplanSprite(arkaplantexture) , oyunekranobjesi()
{
    lobi.steamac();
    pencere.create(sf::VideoMode({1536,1024}), "CHESS-2", sf::Style::Default);
	pencere.setFramerateLimit(60);
    view.setSize(sf::Vector2f(pencere.getSize()));
    view.setCenter(sf::Vector2f(1536 / 2, 1024 / 2));
	pencere.setView(view);
    

	if (!arkaplantexture.loadFromFile("texturlar/menuarkaplan.png"))
	{
		throw std::runtime_error("Background texture could not be loaded.");
	}
	arkaplanSprite.setTexture(arkaplantexture,true);
	arkaplanSprite.setPosition(sf::Vector2f(0, 0));
	arkaplanSprite.setScale(sf::Vector2f(1.0f, 1.0f)); // Scale the background

}


void Game::ciz()
{
    pencere.clear(sf::Color::Black);

    if (currentdurum == oyundurumu::anaMenu)
    {
		pencere.draw(arkaplanSprite);
    }

    if (oyundurumu::anaMenu == currentdurum)
    {
        mainmenu.menuciz(pencere);
	}

    if (oyundurumu::odakurma == currentdurum)
    {
		odakurmamenuobjesi.odakurmaciz(pencere);
	}

    if (currentdurum == oyundurumu::odaarama)
    {
		odalistelememenuobjesi.odalisteleciz(pencere);
    }

    if (currentdurum == oyundurumu::ayarlar)
    {
		ayarlarmenuobjesi.ayarciz(pencere);
	}

    if (currentdurum == oyundurumu::lobi)
    {
        lobiekranobjesi.Lobiekranciz(pencere);
    }

    pencere.display();
}

void Game::olayokuyucu()
{
    while (std::optional event = pencere.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
			lobi.steamkapat();
            pencere.close();
        }

        // Pencere boyutu deðiþtiðinde View güncelleme
        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            view.setSize(sf::Vector2f(pencere.getSize()));
            view.setCenter(sf::Vector2f(1536/2, 1024/2));
            pencere.setView(view);
        }

        if (oyundurumu::anaMenu == currentdurum)
        {
			mainmenu.menuolayokuyucu(*event,pencere);
            if (mainmenu.getanamenudurum() == MainMenu::anamenudurumu::odaOlustur)
            {
                currentdurum = oyundurumu::odakurma;
            }
            if (mainmenu.getanamenudurum() == MainMenu::anamenudurumu::odaGiris)
            {
                currentdurum = oyundurumu::odaarama;
            }
            else if (mainmenu.getanamenudurum() == MainMenu::anamenudurumu::cikis)
            {
				lobi.steamkapat();
                pencere.close();
			}
            else if (mainmenu.getanamenudurum() == MainMenu::anamenudurumu::ayarlar)
            {
                currentdurum = oyundurumu::ayarlar;
			}
        }
        if (oyundurumu::odakurma == currentdurum)
        {
            odakurmamenuobjesi.odakurmamenuolayokuyucu(*event,pencere);
            if (odakurmamenuobjesi.getgeritusdurumu())
            {
				odakurmamenuobjesi.geritusdurumusýfýla();
                currentdurum = oyundurumu::anaMenu;
				mainmenu.setmenudurum(MainMenu::anamenudurumu::anaMenu);
            }
            if (odakurmamenuobjesi.getodakurmatusbas())
            {
                currentdurum = oyundurumu::lobi;
				odakurmamenuobjesi.setodakurmatusbas();
				lobi.odaolustur(odakurmamenuobjesi.getodaadi(), odakurmamenuobjesi.getsifre());

            }
        }
        if (oyundurumu::odaarama == currentdurum)
        {
			odalistelememenuobjesi.odalisteleolay(pencere,*event);
            if (odalistelememenuobjesi.getgeritusdurmu())
            {
				odalistelememenuobjesi.setgeritusdurmu();
                mainmenu.setmenudurum(MainMenu::anamenudurumu::anaMenu);
                currentdurum = oyundurumu::anaMenu;
            }
            else if (odalistelememenuobjesi.getodalistetus())
            {
                lobi.lobilerilistele();
                if (lobi.getLobilerguncellendi())
                {
                    if (odalistelememenuobjesi.odalisteadlarial(lobi.getLobiler()))
                    {
                        lobi.setlobilerguncellendi();
                        odalistelememenuobjesi.setodalistetus();
                    }
                }
            }
            else if (odalistelememenuobjesi.getkatiltusdurumu())
            {
                currentdurum = oyundurumu::lobi;
                if (odalistelememenuobjesi.getodaindex() >= 0)
                { 
                    lobi.odayakatil(odalistelememenuobjesi.getodaindex());
                }
                else
                    std::cout << "Önce bir oda seçmelisin!\n";

				odalistelememenuobjesi.setkatiltusdurumu();
            }

        }

        if (oyundurumu::ayarlar == currentdurum)
        {
			ayarlarmenuobjesi.ayarolayokuyucu(*event, pencere);
            if (ayarlarmenuobjesi.getgeritus())
            {
				ayarlarmenuobjesi.setgeritus();
				mainmenu.setmenudurum(MainMenu::anamenudurumu::anaMenu);
				currentdurum = oyundurumu::anaMenu;
            }
            else if (ayarlarmenuobjesi.getekranbuton())
            {
				pencere.create(sf::VideoMode::getDesktopMode(), "CHESS-2", sf::State::Fullscreen);
				view.setSize(sf::Vector2f(pencere.getSize()));
				pencere.setView(view);
				ayarlarmenuobjesi.setekranbuton();
            }
            else if (ayarlarmenuobjesi.getpencereekranbuton())
            {
                pencere.create(sf::VideoMode({1536,1024}), "CHESS-2", sf::State::Windowed);
				view.setSize(sf::Vector2f(pencere.getSize()));
                pencere.setView(view);
				ayarlarmenuobjesi.setpencereekranbuton();
            }
        }

        if (oyundurumu::lobi == currentdurum)
        {
            lobiekranobjesi.lobiolayokuyucu(*event, pencere);

            if (lobi.getlobikisidegisikligi() || lobi.getlobikatildi())
            {
                auto lobbyid = lobi.getkatýnýlanodaid();
                auto kisiler = lobi.lobikisileriste(lobbyid);

                lobiekranobjesi.setkullanicilistesi(kisiler); // <-- bunu yazman gerekiyor

                lobi.setlobikatildi();
                lobi.setlobikisidegisikligi();
            }

            if (lobiekranobjesi.getgeritus_l())
            {
                currentdurum = oyundurumu::anaMenu;
                mainmenu.setmenudurum(MainMenu::anamenudurumu::anaMenu);

                lobiekranobjesi.setgeritus_l();
            }

            if (lobiekranobjesi.getbaslatus())
            {
                currentdurum = oyundurumu::oyunekrani;
				auto lobyid = lobi.getkatýnýlanodaid();
				oyunekranobjesi.getodabilgilerinial(lobyid);

                lobiekranobjesi.setbaslatus();
            }




        }
    }
}

void Game::calistir()
{
	lobi.steamac();
    while (pencere.isOpen())
    {   
        if (currentdurum == oyundurumu::oyunekrani)
        {
            lobi.guncelleme();
            oyunekranobjesi.oyunekraniruner(pencere);
    
        }
        else
        {
            olayokuyucu();

            lobi.guncelleme();

            ciz();
        }
    }
    lobi.steamkapat();
}
