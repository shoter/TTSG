#ifndef kopalnia_h_
#define kopalnia_h_
#include "budynek.h"
class Kopalnia :public Budynek
{
	public:
		Kopalnia();
		virtual void wyswietl(int x,int y);
		virtual void wyswietl(int x,int y,Kamera &kam);
		virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik = 1);
		virtual void pracuj(int zyznosc,Gracz &ktory);
        static Surowce cena(int moznik = 1);
        virtual string nazwa();
        virtual bool zburz(Pole *gdzie,Gracz *ktory); //nisczy doszczetnie
        void przejete(Pole *gdzie,Gracz *stary,Gracz *nowy);


	protected:
    static ALLEGRO_BITMAP *grafika;
    static Typ *wymagania; //max 4
    static int il_wym;
    static Surowce koszt;
	private:

};



#endif // kopalnia_h_

