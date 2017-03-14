#include "Zamek.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP *Zamek::grafika = NULL;
Surowce Zamek::koszt = Surowce(100,100,0);
int Zamek::il_wym = 1;
Typ *Zamek::wymagania = new Typ[il_wym]; // brak :)



Zamek::Zamek()
{
if(!Zamek::grafika)
{
    grafika = al_load_bitmap("GFX\\Zamek.bmp");
    al_convert_mask_to_alpha(grafika,al_map_rgb(255,0,255));
    Zamek::wymagania[0] = puste;
}
}

void Zamek::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Zamek::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Zamek::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
{
    Surowce pomnozony_koszt = koszt * mnoznik;
    if(gdzie.zwroc_gracz() != &ktory) return "To nie twoja ziemia!";
    if(gdzie.zabudowane()) return "Na tym polu jest cos zbudowane!"; //Na polu juz stoi budynek.nothing to do
    if(!(sur >= pomnozony_koszt))return "Za malo surowcow!";
    if(ktory.zwroc_poparcie() < 20)return "Zbyt niskie poparcie!";


    bool spelnione = false;
    for(int i =0;i < il_wym;i++)
    if(wymagania[i] == gdzie.zwroc_typ())spelnione = true;
    if(!spelnione) return "Zly typ terenu";

    if(ktory.zwroc_PA() < 10)return "Zbyt malo PA(10)";
    ktory.dodaj_PA(-10);

    sur -= pomnozony_koszt;
    gdzie.zbuduj(this);
    ktory.odejmij_maxPA(-1);
    ktory.dodaj_maxarmie(1);
    return "Zbudowane!"; //ta wiadomosc bedzie wiecznie zielona!
}

void Zamek::pracuj(int zyznosc,Gracz &ktory)
{
   ktory.dodaj_PA(1);
}

string Zamek::zburz()
{

    string teksty[5] = {"BOOM!","Zamek padl","Zniszczono zamek!","delete zamek","!!!"};
    zburzony = true;
    return teksty[rand() % 5];
}

bool Zamek::zburz(Pole *gdzie,Gracz *ktory)
{
    if(zburzony)
    {
    ktory->odejmij_maxPA(1);
    ktory->dodaj_maxarmie(-1);
    ktory->usun_budynek(4);
    }
    return zburzony;
}

void Zamek::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{

    if(nowy)
    {
    nowy->odejmij_maxPA(-1);
    nowy->dodaj_maxarmie(1);
    nowy->dodaj_budynek(4);
    }
    if(stary)
    {
    stary->odejmij_maxPA(1);
    stary->dodaj_maxarmie(-1);
    stary->usun_budynek(4);
    }
}

Surowce Zamek::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Zamek::nazwa()
{
    return "Zamek";
}

