#ifndef mgracz_h_
#define mgracz_h_
#define ilosc_kolorow 8
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "ChangeState.h"
#include <string>
class Ekran;
using namespace std;
class MGracz
{
	public:
		MGracz(int x,int y);
		ALLEGRO_COLOR zwroc_kolor();
		void pracuj(Ekran &gdzie);
		void wyswietl();
		operator ALLEGRO_COLOR();
		operator int();
		operator string();
	protected:
	int x,y;
    ChangeState kolor,typ;
	private:
	static ALLEGRO_COLOR kolory[ilosc_kolorow];
	string nazwa;
	bool uzywana_klawiatura;
	int ostatni;
};


#endif // mgracz_h_

