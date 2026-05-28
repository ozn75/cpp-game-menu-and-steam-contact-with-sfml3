#include "lobiislemleri.hpp"

lobiislemleri::lobiislemleri() : m_LobbyCreatedCallback(this, &lobiislemleri::OnLobbyCreated),
m_CallbackLobbyList(this, &lobiislemleri::OnLobbyMatchList), m_CallbackLobbyEnter(this, &lobiislemleri::OnLobbyEnter),
m_lobbychatupdatecallback(this,&lobiislemleri::lobidekikisisayisi)
{

}

bool lobiislemleri::steamac()
{
	if (SteamAPI_Init())
	{
		std::cout << "Steam API baþarýyla baþlatýldý." << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Steam API baþlatýlamadý!" << std::endl;
		return false;
	}
}

void lobiislemleri::steamkapat()
{
	SteamAPI_Shutdown();
	std::cout << "Steam API baþarýyla kapatýldý." << std::endl;
}


void lobiislemleri::odaolustur(const std::string& odaadi, const std::string& sifre)
{
	// Kullanýcýdan gelen deðerleri geçici olarak saklýyoruz
	odaAdiTemp = odaadi;
	sifreTemp = sifre;

	// Steam sunucusuna yeni lobi oluþturma isteði gönderiyoruz
	SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 2); // 2 kiþi max
}

void lobiislemleri::lobilerilistele()
{
	SteamMatchmaking()->RequestLobbyList();
	std::cout << "Steam'den lobi listesi istendi...\n";
}



void lobiislemleri::odayakatil(int seciliOdaIndex)
{
	if (seciliOdaIndex < 0 || seciliOdaIndex >= li_idlobiler.size())
	{
		std::cout << "[HATA] Geçersiz oda seçimi.\n";
		return;
	}

	CSteamID lobbyID = li_idlobiler[seciliOdaIndex];

	katýnýlanodaid = lobbyID;

	std::cout << "[Steam] Katýlma iþlemi baþlatýldý! LobbyID: " << lobbyID.ConvertToUint64() << std::endl;
	SteamMatchmaking()->JoinLobby(lobbyID);
}

void lobiislemleri::guncelleme()
{
	SteamAPI_RunCallbacks(); // Steam'in olay sistemini iþle
}

std::vector<lobiislemleri::kisibilgileri> lobiislemleri::lobikisileriste(CSteamID& lobbyid)
{
	std::vector<kisibilgileri> bilgiler;
	int count = SteamMatchmaking()->GetNumLobbyMembers(lobbyid);
	std::cout << "kisi sayisi: " << count << std::endl;
	for (int i = 0; i < count; i++)
	{
		CSteamID memberID = SteamMatchmaking()->GetLobbyMemberByIndex(lobbyid, i); // id sini

		const char* name = SteamFriends()->GetFriendPersonaName(memberID);  // adýný

		int imageID = SteamFriends()->GetSmallFriendAvatar(memberID);    // avatarini

		kisibilgileri kisi;
		kisi.kisisayisi = count;
		kisi.id = memberID;
		kisi.ad = name ? name : "[bilinmiyor]";
		kisi.avatarid = imageID;

		bilgiler.push_back(kisi);
	}
	return bilgiler;
}

std::vector<std::string> lobiislemleri::getLobiler() const
{
	return li_lobibilgileri;
}

bool lobiislemleri::getLobilerguncellendi() const
{
	return lobilerguncellendi;
}

void lobiislemleri::setlobilerguncellendi()
{
	lobilerguncellendi = false;
}

CSteamID lobiislemleri::getkatýnýlanodaid()
{
	return katýnýlanoda;
}

void lobiislemleri::setlobikisidegisikligi()
{
	lobikisidegisikligi = false;
}

bool lobiislemleri::getlobikisidegisikligi() const
{
	return lobikisidegisikligi;
}

void lobiislemleri::setlobikatildi()
{
	lobikatildi = false;
}

bool lobiislemleri::getlobikatildi() const
{
	return lobikatildi;
}

CSteamID lobiislemleri::getodaid() const
{
	return katýnýlanodaid;
}


void lobiislemleri::OnLobbyCreated(LobbyCreated_t* pCallback)
{
	if (pCallback->m_eResult == k_EResultOK)
	{
		CSteamID lobbyID = pCallback->m_ulSteamIDLobby;

		katýnýlanoda = lobbyID;

		// Steam’e lobi bilgilerini yaz
		SteamMatchmaking()->SetLobbyData(lobbyID, "name", odaAdiTemp.c_str());
		SteamMatchmaking()->SetLobbyData(lobbyID, "sifre", sifreTemp.c_str());

		std::cout << "[Steam] Lobi baþarýyla oluþturuldu!\n";
		std::cout << "[Steam] Lobi ID: " << lobbyID.ConvertToUint64() << std::endl;
		std::cout << "[Steam] Oda Adý: " << odaAdiTemp << " | Þifre: " << sifreTemp << std::endl;
		lobikatildi = true;
	}
	else
	{
		std::cerr << "[Steam] Lobi oluþturulamadý! Hata kodu: " << pCallback->m_eResult << std::endl;
	}
}

void lobiislemleri::OnLobbyMatchList(LobbyMatchList_t* pCallback)
{
	li_lobibilgileri.clear(); // Eski lobileri temizle!
	li_idlobiler.clear(); // Bunu mutlaka ekle!

	int toplamLobiSayisi = pCallback->m_nLobbiesMatching;
	std::cout << "[Steam] Toplam bulunan lobi sayisi: " << toplamLobiSayisi << "\n";

	// Lobileri ekranda göstermek için bir döngü kullanalým
	for (int i = 0; i < toplamLobiSayisi; ++i)
	{
		CSteamID lobbyID = SteamMatchmaking()->GetLobbyByIndex(i);
		std::string lobbyIsmi = SteamMatchmaking()->GetLobbyData(lobbyID, "name");

		if (!lobbyIsmi.empty())
		{
			li_lobibilgileri.push_back(lobbyIsmi);
			li_idlobiler.push_back(lobbyID);
		}

		std::cout << "[Steam] Bulunan Lobi (" << i << "): " << lobbyIsmi << "\n";

		// Bu lobileri GUI'ye aktarmak için kendi fonksiyonunu yazmalýsýn
		// Örnek: odalistelememenuobjesi.LobiEkle(lobbyIsmi);
	}
	if (li_lobibilgileri.size() > 0)
	{
		lobilerguncellendi = true; // Lobiler güncellendi
	}
}

void lobiislemleri::OnLobbyEnter(LobbyEnter_t* pCallback)
{
	if (pCallback->m_EChatRoomEnterResponse == k_EChatRoomEnterResponseSuccess)
	{
		CSteamID lobbyid = pCallback->m_ulSteamIDLobby;

		katýnýlanoda = lobbyid;
		lobikatildi = true;

		std::cout << "[Steam] Odaya baþarýyla katýldýn!\n";
		// Burada GUI’yi oyun ekranýna geçirebilirsin
	}
	else
	{
		std::cout << "[Steam] Katýlma baþarýsýz. Kod: " << pCallback->m_EChatRoomEnterResponse << std::endl;
	}
}


void lobiislemleri::lobidekikisisayisi(LobbyChatUpdate_t* callback)
{
	if (callback->m_rgfChatMemberStateChange)
	{
		lobikisidegisikligi = true;
		std::cout << "lobide kisi degisikligi oldu" << std::endl;
	}
}
