#ifndef mapa_h_
#define mapa_h_
#include "pole.h"
#include "pamiec.h"
#include "marker.h"
#include "textmaster.h"
#define RET_VAR(nazwa,typ,fun) typ fun() { return nazwa ; }
class Gracz;
class Pole;
class Mapa
{
	public:
		Mapa(int n);
		Mapa(int szerx,int szery);
		~Mapa();
		void wyswietl(int x = -1,int y=-1,Gracz *ktory = NULL);

		void przesun_kamere(int x,int y);
		void porusz_myszka(float deadzone,float speed);
		void smooth(float x,float y,float sp); //dla kamery
		void ustaw_kamere(int x,int y);

		void generuj();
		void wyswietl_miniature(int x,int y,int w);
		void koniec_tury();

		void operator +=(Marker *nowy);
		void operator -=(Marker *ktory);
		Pole& operator[](int i);
		void clear();

		void ustanow_teren(int x,int y,Gracz *wlasciciel,TextMaster &TM);
		bool atak(int x,int y,Gracz *wlasciciel,TextMaster &TM);
		bool atak(int i,Gracz *wlasciciel,TextMaster &TM);
		bool graniczy(int x,int y,Gracz *wlasciciel);
		bool graniczy(int i,Gracz *wlasciciel);
		bool otacza(int x,int y,Gracz *wlasciciel);

		void ustaw_widok(int x,int y,float);
		void oblicz_fog(Gracz * );
		void odkryj_wokol(int x,int y);
		void fog_off();

		Gracz *wlasnosc(int x,int y);
		Gracz *wlasnosc(int i);
		void zaloz_osade(int x,int y,Gracz*);

		RET_VAR(szer,int,zwroc_szer);
		RET_VAR(wys,int,zwroc_wys);
		Kamera *zwroc_kamere();
		int index_pola(Pole*); //CZASOCHLONNA OPERACJA!!!

protected:
	Pole *pola;
	int szer,wys;
	Kamera kam;
    Pamiec<Marker> markery;

	private:
	Pamiec<Pole>* generuj(int x,int y,int rozproszenie,int szansa,int cszansa,Typ teren,Pamiec<Pole> *pam=NULL);
	void generuj(Typ teren,float wspolczynnik);

};


#endif
