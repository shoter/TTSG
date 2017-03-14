#include "Baraki.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Baraki::grafika = NULL;
Surowce Baraki::koszt = Surowce(25,25,0);
int Baraki::il_wym = 1;
Typ *Baraki::wymagania = new Typ[il_wym]; // brak :)



Baraki::Baraki()
{
if(!Baraki::grafika)
{
    grafika = al_load_bitmap("GFX\\Baraki.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Baraki::wymagania[0] = puste;
}
}

void Baraki::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Baraki::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Baraki::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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

void Baraki::pracuj(int zyznosc,Gracz &ktory)
{
    if(ktory.zwroc_armie() >= ktory.zwroc_maxarmie())return;
    Surowce wymaga(0,0,4);
    if(!(ktory >= wymaga))return;
    ktory -= wymaga;
    ktory.dodaj_armie(1);
}

string Baraki::nazwa()
{
    return "Baraki";
}

Surowce Baraki::cena(int mnoz)
{
    return (koszt * mnoz);
}

bool Baraki::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(3);
    return true;
}

void Baraki::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    stary->usun_budynek(3);
    if(nowy)
    nowy->dodaj_budynek(3);
}
