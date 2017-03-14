#ifndef Zamek_h_
#define Zamek_h_
#include "Budynek.h"
class Zamek :public Budynek
{
    public :
    Zamek();
    virtual void wyswietl(int x,int y);
    virtual void wyswietl(int x,int y,Kamera &kam);
    virtual void pracuj(int zyznosc,Gracz &ktory);
    virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik=1);
    virtual string zburz();//ustawia ze zniszczony
    virtual bool zburz(Pole *gdzie,Gracz *ktory); //nisczy doszczetnie
    virtual void przejete(Pole *gdzie,Gracz *stary,Gracz *nowy);
    static Surowce cena(int moznik = 1);
    virtual string nazwa();


    protected :
    static ALLEGRO_BITMAP *grafika;
    static Typ *wymagania; //max 4
    static int il_wym;
    static Surowce koszt;
};

#endif


