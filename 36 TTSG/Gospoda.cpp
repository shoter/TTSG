#include "Gospoda.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Gospoda::grafika = NULL;
Surowce Gospoda::koszt = Surowce(10,50,0);
int Gospoda::il_wym = 1;
Typ *Gospoda::wymagania = new Typ[il_wym]; // brak :)



Gospoda::Gospoda()
{
if(!Gospoda::grafika)
{
    grafika = al_load_bitmap("GFX\\Gospoda.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Gospoda::wymagania[0] = puste;
}
}

void Gospoda::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Gospoda::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Gospoda::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
{
    Surowce pomnozony_koszt = koszt * mnoznik;
    if(gdzie.zwroc_gracz() != &ktory) return "To nie twoja ziemia!";
    if(gdzie.zabudowane()) return "Na tym polu jest cos zbudowane!"; //Na polu juz stoi budynek.nothing to do
    if(!(sur >= pomnozony_koszt))return "Za malo surowcow!";
    if(ktory.zwroc_poparcie() < 1)return "Zbyt niskie poparcie!";

    bool spelnione = false;
    for(int i =0;i < il_wym;i++)
    if(wymagania[i] == gdzie.zwroc_typ())spelnione = true;
    if(!spelnione) return "Zly typ terenu";

    if(ktory.zwroc_PA() < 8)return "Zbyt malo PA(8)";
    ktory.dodaj_PA(-8);

    sur -= pomnozony_koszt;
    gdzie.zbuduj(this);
    return "Zbudowane!"; //ta wiadomosc bedzie wiecznie zielona!
}

void Gospoda::pracuj(int zyznosc,Gracz &ktory)
{
   ktory.dodaj_poparcie(1);
}

Surowce Gospoda::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Gospoda::nazwa()
{
    return "Gospoda";
}

bool Gospoda::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(6);
    ktory->dodaj_poparcie(-10);
    return true;
}

void Gospoda::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    {
    stary->usun_budynek(6);
    stary->dodaj_poparcie(-5);
    }
    if(nowy)
    {
    nowy->dodaj_budynek(6);
    nowy->dodaj_poparcie(5);
    }
}
