#include "tartak.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Tartak::grafika = NULL;
Surowce Tartak::koszt = Surowce(25,5,0);
int Tartak::il_wym = 1;
Typ *Tartak::wymagania = new Typ[il_wym]; // brak :)



Tartak::Tartak()
{
if(!Tartak::grafika)
{
    grafika = al_load_bitmap("GFX\\tartak.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Tartak::wymagania[0] = las;
}
}

void Tartak::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Tartak::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Tartak::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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

void Tartak::pracuj(int zyznosc,Gracz &ktory)
{
   switch(zyznosc)
   {
       case 1:
       {
        Surowce drewno(0,1,0);
        ktory += drewno;
        break;
       }
       case 2:
       {
        Surowce drewno(0,3,0);
        ktory += drewno;
        break;
       }
       case 3:
       {
        Surowce drewno(0,7,0);
        ktory += drewno;
        break;
       }
   }
}

Surowce Tartak::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Tartak::nazwa()
{
    return "Tartak";
}

void Tartak::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    stary->usun_budynek(2);
    if(nowy)
    nowy->dodaj_budynek(2);
}

bool Tartak::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(2);
    return true;
}

