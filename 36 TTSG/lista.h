#ifndef lista_h_
#define lista_h_
#include <allegro5/allegro.h>
#include <string>
using namespace std;
class Budynek;class Ekran;struct Surowce;

class Lista
{
	public:
		Lista(int ile);
        void dodaj(string,Surowce,int);
		void wyswietl();
		void pracuj(Ekran &gdzie);
		operator int();
		void operator += (int i);
		~Lista();
	protected:
    int ile,ktory,szer,wys;
    int aktywne;
    string *budynki;
    Surowce *surki;
    int *liczba;
    static ALLEGRO_BITMAP *drewno,*kamien,*zywnosc;
};


#endif // lista_h_

