#include "Farma.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Farma::grafika = NULL;
Surowce Farma::koszt = Surowce(25,10,0);
int Farma::il_wym = 1;
Typ *Farma::wymagania = new Typ[il_wym]; // brak :)



Farma::Farma()
{
if(!Farma::grafika)
{
    grafika = al_load_bitmap("GFX\\Farma.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Farma::wymagania[0] = pole;
}
}

void Farma::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Farma::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Farma::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
{
    Surowce pomnozony_koszt = koszt * mnoznik;
    if(gdzie.zwroc_gracz() != &ktory) return "To nie twoja ziemia!";
    if(gdzie.zabudowane()) return "Na tym polu jest cos zbudowane!"; //Na polu juz stoi budynek.nothing to do
    if(!(sur >= pomnozony_koszt))return "Za malo surowcow!";
    if(ktory.zwroc_poparcie() < 10)return "Zbyt niskie poparcie!";


    bool spelnione = false;
    for(int i =0;i < il_wym;i++)
    if(wymagania[i] == gdzie.zwroc_typ())spelnione = true;
    if(!spelnione) return "Zly typ terenu";

    if(ktory.zwroc_PA() < 6)return "Zbyt malo PA(6)";
    ktory.dodaj_PA(-6);

    sur -= pomnozony_koszt;
    gdzie.zbuduj(this);
    return "Zbudowane!"; //ta wiadomosc bedzie wiecznie zielona!
}

void Farma::pracuj(int zyznosc,Gracz &ktory)
{
     switch(zyznosc)
   {
       case 1:
       {
        Surowce drewno(0,0,3);
        ktory += drewno;
        break;
       }
       case 2:
       {
        Surowce drewno(0,0,6);
        ktory += drewno;
        break;
       }
       case 3:
       {
        Surowce drewno(0,0,11);
        ktory += drewno;
        break;
       }
   }
}

string Farma::nazwa()
{
    return "Farma";
}

bool Farma::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(0);
    return true;
}

Surowce Farma::cena(int mnoz)
{
    return (koszt * mnoz);
}

void Farma::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    stary->usun_budynek(0);
    if(nowy)
    nowy->dodaj_budynek(0);
}


