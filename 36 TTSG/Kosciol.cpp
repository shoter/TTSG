#include "Kosciol.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Kosciol::grafika = NULL;
Surowce Kosciol::koszt = Surowce(100,50,0);
int Kosciol::il_wym = 1;
Typ *Kosciol::wymagania = new Typ[il_wym]; // brak :)



Kosciol::Kosciol()
{
if(!Kosciol::grafika)
{
    grafika = al_load_bitmap("GFX\\Kosciol.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Kosciol::wymagania[0] = puste;
}
}

void Kosciol::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Kosciol::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Kosciol::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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

void Kosciol::pracuj(int zyznosc,Gracz &ktory)
{
   ktory.dodaj_poparcie(2);
}

Surowce Kosciol::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Kosciol::nazwa()
{
    return "Kosciol";
}

bool Kosciol::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(7);
    ktory->dodaj_poparcie(-20);
    return true;
}

void Kosciol::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    {
    stary->usun_budynek(7);
    stary->dodaj_poparcie(-10);
    }
    if(nowy)
    {
    nowy->dodaj_budynek(7);
    nowy->dodaj_poparcie(10);
    }
}
