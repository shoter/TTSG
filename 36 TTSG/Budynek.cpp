#include "budynek.h"
#include "mapa.h"
ALLEGRO_BITMAP *Budynek::grafika = NULL;
Surowce Budynek::koszt = Surowce(0,0,0);
int Budynek::il_wym = 0;
Typ *Budynek::wymagania = new Typ[il_wym]; // brak :)
string Budynek::nazwy_budynkow[8] =
{"Farma","Kopalnia","Tartak","Baraki","Zamek","Wieza","Gospoda","Kosciol"};


Budynek::Budynek() : zburzony(false)
{


}

void Budynek::wyswietl(int x,int y)
{
    al_draw_bitmap(grafika,x,y,NULL);
}

void Budynek::wyswietl(int x,int y,Kamera &kam)
{
    wyswietl(kam.przek_x(x),kam.przek_y(y));
}

string Budynek::zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik)
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
    sur -= pomnozony_koszt;
    gdzie.zbuduj(this);
    return "Zbudowane!"; //ta wiadomosc bedzie wiecznie zielona!
}

string Budynek::zburz()
{
    zburzony = true;
    return "Budynek znisczony!";

}

Budynek::~Budynek()
{
    //nic do zrobienia
}

void Budynek::pracuj(int zyznosc,Gracz &ktory)
{
    return; //NTBD
}

string Budynek::nazwa()
{
    return "Budynek";
}

bool Budynek::zburz(Pole *gdzie,Gracz *ktory)
{
    return zburzony;
}

bool Budynek::zwroc_zburz()
{
    return zburzony;
}

void Budynek::przejete(Pole *gdzie,Gracz *stary,Gracz *nowy)
{
    //NTBD
}

Surowce Budynek::cena(int mnoz)
{
    return (koszt * mnoz);
}

string Budynek::nazwa(int co)
{
    if(co < 0 || co >= 8) return "";
    return nazwy_budynkow[co];
}
