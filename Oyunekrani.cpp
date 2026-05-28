#include "Oyunekrani.hpp"

Oyunekrani::Oyunekrani()
{

	harita.setharitaboyut(25); // Harita boyutunu 10 olarak ayarlýyoruz
	oyuncugorus.setSize(sf::Vector2f(800.f, 600.f)); // Görüþ alanýný ayarlýyoruz
	oyuncugorus.setCenter(sf::Vector2f(400.f, 300.f)); // Görüþ alanýnýn merkezini ayarlýyoru

    sf::Texture gecici;
    if (!gecici.loadFromFile("texturlar/sah.png"))
    {
        throw std::runtime_error("Geçici taþ texture could not be loaded.");
    }
	
	anatas.settastexture(gecici);
	anatas.settasposition(0.f, 0.f); // Taþý haritanýn ortasýna yerleþtiriyoruz
}

void Oyunekrani::getodabilgilerinial(CSteamID& lobyid)
{
    int n = SteamMatchmaking()->GetNumLobbyMembers(lobyid);

    for (int i = 0; i < n; ++i)
    {
        CSteamID kisii = SteamMatchmaking()->GetLobbyMemberByIndex(lobyid, i);
        const char* kisiadi = SteamFriends()->GetFriendPersonaName(kisii);
        oyuncular yeniOyuncu;
		yeniOyuncu.takimid = (i % 2 == 0) ? 1 : 2; // Ýki takým var, sýrayla atýyoruz
		yeniOyuncu.oyuncuid = i; // Oyuncu ID'si olarak döngü indeksini kullanýyoruz
        yeniOyuncu.kisiid = kisii;
        yeniOyuncu.kisiadi = kisiadi ? kisiadi : "Bilinmiyor";
        oyuncularlistesi.push_back(yeniOyuncu);
	}

}

void Oyunekrani::o_ciz(sf::RenderWindow& win)
{
    win.clear(sf::Color::Black);

	

	harita.haritaciz(win);

    win.draw(anatas.gettassprite());

    win.display();
}

void Oyunekrani::o_olay(sf::RenderWindow& win, sf::Event& olay)
{
    if (olay.is<sf::Event::Closed>())
    {
        win.close();
    }
    
    if (const auto tus = olay.getIf<sf::Event::KeyPressed>())
    {
        if (tus->code == sf::Keyboard::Key::W)
        {
			oyuncugorus.move(sf::Vector2f(0.f,-10.f)); // Yukarý hareket
            
        }
        if (tus->code == sf::Keyboard::Key::S)
        {
            oyuncugorus.move(sf::Vector2f(0.f,+10.f)); // Yukarý hareket

        }
        if (tus->code == sf::Keyboard::Key::A)
        {
            oyuncugorus.move(sf::Vector2f(-10.f,0.f)); // Yukarý hareket

        }
        if (tus->code == sf::Keyboard::Key::D)
        {
            oyuncugorus.move(sf::Vector2f(10.f,0.f)); // Yukarý hareket

        }
    }

    if (const auto mouseclick = olay.getIf<sf::Event::MouseButtonPressed>())
    {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(win);

		sf::Vector2f worldPos = win.mapPixelToCoords(pixelPos);

        if (mouseclick->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f farekonumu = win.mapPixelToCoords(sf::Mouse::getPosition(win));
            std::cout << "Fare týklandý: " << farekonumu.x << ", " << farekonumu.y << std::endl;
			oyuncugorus.setCenter(sf::Vector2f(0,0)); // Fare týklandýðýnda görüþ alanýný fare konumuna ayarlýyoruz
        }
        if (mouseclick->button == sf::Mouse::Button::Right)
        {
            if (anatas.gettassprite().getGlobalBounds().contains(worldPos))
            {
                std::cout << "tasa tiklandi." << std::endl;
            }
            else std::cout << "Sað fare düðmesi týklandý." << std::endl;
		}
	}

    if (const auto scroll = olay.getIf<sf::Event::MouseWheelScrolled>())
    {
        zoomAt(sf::Mouse::getPosition(win), (scroll->delta > 0 ? 0.9f : 1.1f), win, oyuncugorus);
    }


}

void Oyunekrani::oyunekraniruner(sf::RenderWindow& window)
{
	window.setView(oyuncugorus); // Görüþ alanýný ayarlýyoruz
    while (window.isOpen())
    {
        window.setView(oyuncugorus); // Görüþ alanýný ayarlýyoruz
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            o_olay(window, *event);
        }

        o_ciz(window);
    }
}

void Oyunekrani::zoomAt(const sf::Vector2i& pixel, float factor, sf::RenderWindow& win, sf::View& view)
{
    sf::Vector2f before = win.mapPixelToCoords(pixel, view);
    view.zoom(factor);
    sf::Vector2f after = win.mapPixelToCoords(pixel, view);
    view.move(before - after);
}


