#ifndef gracz_h_
#define gracz_h_
#include <allegro5/allegro.h>
#include "ekran.h"
#include "surowce.h"
#include "mapa.h"
#include "marker.h"
#include "textmaster.h"
#include <string>
using namespace std;

#define RET_VAR(nazwa,typ,fun) typ fun() { return nazwa ; }
class Mapa;class Lista;class Pole;
class Gracz
{
    public :
    Gracz(string nazwa="",ALLEGRO_COLOR kol=al_map_rgb(0,50,20),bool bot = false);
    void wyswietl();
    void operator +=(Surowce nowe);
    void operator -=(Surowce nowe);
    bool operator <=(Surowce nowe);
    bool operator <(Surowce nowe);
    bool operator >=(Surowce nowe);
    bool operator >(Surowce nowe);

    void ustaw_poparcie(int);
    void dodaj_poparcie(int);
    void ustaw_PA(int);
    void dodaj_PA(int);
    void dodaj_armie(int);
    void dodaj_maxarmie(int);
    void odejmij_maxPA(int i);
    void dodaj_budynek(int ktory,int i=1);
    void usun_budynek(int i);
    bool jedz(int ile);

    bool ruch_klawiatura(Ekran &gdzie,Mapa &map,TextMaster&);
    void ruch_bota(Mapa &map,TextMaster&);
    void ustaw_kamere(int x,int y);


    bool isbot();bool czybot(); //to samo
    RET_VAR(x,int,retx);
    RET_VAR(y,int,rety); // o rety! :D
    int zwroc_x();
    int zwroc_y();
    int zwroc_PA();
    RET_VAR(poparcie,int,zwroc_poparcie);
    RET_VAR(kolor_gracza,ALLEGRO_COLOR,zwroc_kolor);
    RET_VAR(zolnierze,int,zwroc_armie);
    RET_VAR(zolnierzemax,int,zwroc_maxarmie);
    Surowce& zwroc_surowce();

    Marker* zrob_marker();
    Marker* zwroc_marker();

    protected :
    string nazwa;
    int poparcie;
    int zolnierze,zolnierzemax;
    int PA,maxPA;
    int ilosc_budynkow[8]; //pamietasz jak to na klawiaturze zrobiles?Pamietasz o wiszacej kartce przed toba?Jak tak to zrozumiesz o co chodzi.
    //dla niewtajemiczonych ten tekst nigdy nie bedzie zrozumialy.
    Surowce surka;

    static ALLEGRO_BITMAP *gui;
    static ALLEGRO_BITMAP *bZloto;
    static ALLEGRO_BITMAP *bDrewno;
    static ALLEGRO_BITMAP *bKamien;
    static ALLEGRO_BITMAP *bPoparcie;
    static ALLEGRO_BITMAP *bZolnierze;
    static ALLEGRO_BITMAP *bRuch;

    bool bot;

    ALLEGRO_COLOR kolor_gracza;

    int x,y; //gdzie patrzy gracz,gdzie cos robil

    Marker *mark;

    Lista *lis;

     Pole *cel; //dla bota
     int poprzednia_zyw; //dla bota D:
};

#endif // gracz_h_

