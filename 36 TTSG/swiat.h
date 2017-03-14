#ifndef swiat_h_
#define swiat_h_
#include "mapa.h"
#include "pamiec.h"
#include "textmaster.h"
class Swiat
{
	public:
		Swiat();
		void operator += (Gracz*);
		Pamiec<Gracz> zwroc_graczy();
		bool start();
		void koniec_tury(); //tury wszystkich graczy
		void inicjalizuj_mape(int szx,int szy);
		void wyswietl_min_mape(int x,int y,int w);
		void wyswietl_mape();
		Mapa* zwroc_mape();
		bool wyswietl_mape(bool bot,TextMaster &TM); //bedzie wyswietlalo posuniecia gracza,jesli true to posuneicia bota tez,uzyje do tego smooth move
		void ruch_mapa(bool bot);
		void pracuj(Ekran &gdzie,TextMaster &TM);
		void nastepna_tura(TextMaster &TM);

		Kamera *kamera();



	protected:
    bool rozpoczeta;
    bool ini_map;
    bool ini_players;
    Mapa *map;

    Pamiec<Gracz> gracze;
    int ktory_gracz;
};


#endif // swiat_h_

