#ifndef wieza_h_
#define wieza_h_
#include "budynek.h"
class Wieza :public Budynek
{
    public :
    Wieza();
    virtual void wyswietl(int x,int y);
    virtual void wyswietl(int x,int y,Kamera &kam);
    virtual void pracuj(int zyznosc,Gracz &ktory);
    virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int=1);
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


#endif // wieza_h_

