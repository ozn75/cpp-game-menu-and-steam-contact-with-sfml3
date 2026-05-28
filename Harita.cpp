#include "Harita.hpp"

Harita::Harita() : haritaboyutu(0)
{


}

void Harita::haritaciz(sf::RenderWindow& win) const
{
	for (const auto& k : haritakareleri) {
		win.draw(k.sekil);
	}
}

void Harita::haritaolustur()
{
    for (int satir = 0; satir < haritaboyutu; ++satir)
    {
        for (int sutun = 0; sutun < haritaboyutu; ++sutun)
        {
            kare yenikare;
            yenikare.kareid = satir * haritaboyutu + sutun;
            yenikare.boyut = sf::Vector2f(100.f, 100.f);
            yenikare.sekil.setSize(yenikare.boyut);

            yenikare.konum = sf::Vector2f(sutun * 100.f, satir * 100.f);
            yenikare.sekil.setPosition(yenikare.konum);

			yenikare.sekil.setOutlineThickness(5.f);
			yenikare.sekil.setOutlineColor(sf::Color::Black);

            if ((satir + sutun) % 2 == 0) // satranç görünümü için
                yenikare.renk = sf::Color::Magenta;
            else
                yenikare.renk = sf::Color::Blue;

            yenikare.sekil.setFillColor(yenikare.renk);

            haritakareleri.push_back(yenikare);
        }
    }
}


void Harita::setharitaboyut(int boyut)
{
	haritaboyutu = boyut;
	haritaolustur();
}

