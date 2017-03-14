#ifndef Gospoda_h_
#define Gospoda_h_
#include "Budynek.h"
class Gospoda :public Budynek
{
    public :
    Gospoda();
    virtual void wyswietl(int x,int y);
    virtual void wyswietl(int x,int y,Kamera &kam);
    virtual void pracuj(int zyznosc,Gracz &ktory);
    virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik = 1);
    static Surowce cena(int moznik = 1);
    virtual string nazwa();
    virtual bool zburz(Pole *gdzie,Gracz *ktory); //nisczy doszczetnie
    void przejete(Pole *gdzie,Gracz *stary,Gracz *nowy);


    protected :
    static ALLEGRO_BITMAP *grafika;
    static Typ *wymagania; //max 4
    static int il_wym;
    static Surowce koszt;
};

#endif


