#pragma once
#include <steam/steam_api.h>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


class lobiislemleri
{
public:
	lobiislemleri();

	struct kisibilgileri
	{
		int kisisayisi;
		CSteamID id;
		std::string ad;
		int avatarid;

	};

	bool steamac();
	void steamkapat();
	void odaolustur(const std::string& odaadi, const std::string& sifre);

	void lobilerilistele();

	void odayakatil(int seciliOdaIndex);

	void guncelleme();

	std::vector<kisibilgileri> lobikisileriste(CSteamID& lobbyid);

	std::vector<std::string> getLobiler() const;

	bool getLobilerguncellendi() const;

	void setlobilerguncellendi();

	CSteamID getkatınılanodaid();

	void setlobikisidegisikligi();
	bool getlobikisidegisikligi() const;

	void setlobikatildi();
	bool getlobikatildi() const;

	CSteamID getodaid()const;

private:
	bool lobilerguncellendi = false; // Lobiler güncellendi mi?
	bool lobikisidegisikligi = false;
	bool lobikatildi = false;
	
	CSteamID katınılanodaid;

	std::vector<std::string> li_lobibilgileri; // Oyun lobilerini tutar
	std::vector<CSteamID> li_idlobiler; // Lobilerin Steam ID'leri

	CSteamID katınılanoda;

	// Kullanıcıdan gelen geçici verileri burada tutarız
	std::string odaAdiTemp;
	std::string sifreTemp;

	STEAM_CALLBACK(lobiislemleri, OnLobbyCreated, LobbyCreated_t, m_LobbyCreatedCallback);

	STEAM_CALLBACK(lobiislemleri, OnLobbyMatchList, LobbyMatchList_t, m_CallbackLobbyList);

	STEAM_CALLBACK(lobiislemleri, OnLobbyEnter, LobbyEnter_t, m_CallbackLobbyEnter);

	STEAM_CALLBACK(lobiislemleri,lobidekikisisayisi, LobbyChatUpdate_t, m_lobbychatupdatecallback); //lobiye giren çıkan olunca tetikleniyor

};


