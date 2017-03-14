#include "kopalnia.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Kopalnia::grafika = NULL;
Surowce Kopalnia::koszt = Surowce(0,25,0);
int Kopalnia::il_wym = 1;
Typ *Kopalnia::wymagania = new Typ[il_wym]; // brak :)


Kopalnia::Kopalnia()
{
    if(!Kopalnia::grafika)
    {
        Kopalnia::wymagania[0] = gory;
        grafika = al_load_bitmap("GFX\\kopalnia.bmp");
        al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    }
}

void Kopalnia::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Kopalnia::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Kopalnia::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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

void Kopalnia::pracuj(int zyznosc,Gracz &ktory)
{
   switch(zyznosc)
   {
       case 1:
       {
        Surowce kamien(1,0,0);
        ktory += kamien;
        break;
       }
       case 2:
       {
        Surowce kamien(7,0,0);
        ktory += kamien;
        break;
       }
       case 3:
       {
        Surowce kamien(7,0,0);
        ktory += kamien;
        break;
       }
   }
}


Surowce Kopalnia::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Kopalnia::nazwa()
{
    return "Kopalnia";
}

bool Kopalnia::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(1);
    return true;
}

void Kopalnia::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    stary->usun_budynek(1);
    if(nowy)
    nowy->dodaj_budynek(1);
}
