#ifndef Baraki_h_
#define Baraki_h_
#include "Budynek.h"
class Baraki :public Budynek
{
    public :
    Baraki();
    virtual void wyswietl(int x,int y);
    virtual void wyswietl(int x,int y,Kamera &kam);
    virtual void pracuj(int zyznosc,Gracz &ktory);
    virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik=1);
    virtual string nazwa();
    static Surowce cena(int moznik = 1);
    virtual bool zburz(Pole *gdzie,Gracz *ktory); //nisczy doszczetnie
    void przejete(Pole *gdzie,Gracz *stary,Gracz *nowy);


    protected :
    static ALLEGRO_BITMAP *grafika;
    static Typ *wymagania; //max 4
    static int il_wym;
    static Surowce koszt;
};

#endif


