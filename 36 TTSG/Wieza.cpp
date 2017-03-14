#include "Wieza.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Wieza::grafika = NULL;
Surowce Wieza::koszt = Surowce(40,5,0);
int Wieza::il_wym = 1;
Typ *Wieza::wymagania = new Typ[il_wym]; // brak :)



Wieza::Wieza()
{
if(!Wieza::grafika)
{
    grafika = al_load_bitmap("GFX\\Wieza.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Wieza::wymagania[0] = puste;
}
}

void Wieza::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Wieza::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Wieza::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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

    if(ktory.zwroc_PA() < 4)return "Zbyt malo PA(4)";
    ktory.dodaj_PA(-4);

    sur -= pomnozony_koszt;
    gdzie.zbuduj(this);
    return "Zbudowane!"; //ta wiadomosc bedzie wiecznie zielona!
}

void Wieza::pracuj(int zyznosc,Gracz &ktory)
{

}

string Wieza::nazwa()
{
    return "Wieza";
}

Surowce Wieza::cena(int mnoz)
{
    return (koszt * mnoz);
}

bool Wieza::zburz(Pole *gdzie,Gracz *ktory)
{
    if(!zburzony)return false;
    ktory->usun_budynek(5);
    return true;
}

void Wieza::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    if(stary)
    stary->usun_budynek(5);
    if(nowy)
    nowy->dodaj_budynek(5);
}

