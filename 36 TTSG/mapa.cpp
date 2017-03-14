#include "mapa.h"

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "budynki.h"
#include "gracz.h"
using namespace std;
extern float odleglosc(float x1,float y1,float x2,float y2);

Mapa::Mapa(int n) : szer(n),wys(n),kam(0,0),markery(10)
{
    pola = new Pole[n * n];
}

Mapa::Mapa(int x,int y) :szer(x),wys(y),kam(0,0),markery(10)
{
    pola = new Pole[x * y];
}

Mapa::~Mapa()
{
    delete []pola;
}

Pamiec<Pole>* Mapa::generuj(int x,int y,int rozproszenie,int szansa,int cszansa,Typ teren,Pamiec<Pole> *pam)
{
    bool pierwszy = false; //czy ta funkcja zostala wywolana jako pierwsza
    if(pam == NULL)
    {
    pierwszy = true;
    pam = new Pamiec<Pole>(rozproszenie);
    }

    if(x < 0 || x >= szer) return pam;
    if(y < 0 || y >= wys) return pam;
    if(rozproszenie <= 0)return pam;
    for(int i = 0;i < pam->size();i++)
    if(pam->operator[](i) == &pola[y*szer +x]) return pam;

    *pam += &pola[y * szer + x];

    int nowa_szansa = float(szansa) * float(cszansa) / 100.0;
    cszansa = cszansa - (szansa - nowa_szansa);
    int rzut = rand() % 100;
    if(rozproszenie != 1)
    {
    pam = generuj(x - 1,y,rozproszenie - 1,nowa_szansa,cszansa,teren,pam);
    pam = generuj(x + 1,y,rozproszenie - 1,nowa_szansa,cszansa,teren,pam);
    pam = generuj(x,y - 1,rozproszenie - 1,nowa_szansa,cszansa,teren,pam);
    pam = generuj(x,y + 1,rozproszenie - 1,nowa_szansa,cszansa,teren,pam);
    }
    if(szansa > rzut)
    {
    pola[y * szer + x].typ = teren;
    }
    if(pierwszy)
    {
    delete pam; //najwieksze wejscie w glab
    return NULL;
    }
    return pam;
}

///_x,_y = miejsce gdzie gracz ma kursor,dlugo zajelo mi rozszyfrowanie tego :|,wiec to komentujesz,SZOK!
void Mapa::wyswietl(int _x,int _y,Gracz *kto)
{
    int startx = (kam.zwroc_x() / 50) -1;
    int starty = (kam.zwroc_y() / 50) - 1;
    if(starty < 0)starty = 0;
    if(startx < 0) startx = 0;
    int endx = startx + 18;
    if(endx > szer)endx = szer;
    int endy = starty + 14;
    if(endy > wys)endy = wys;
    for(int y = starty;y < endy;y++)
    for(int x = startx;x < endx;x++)
    {
        int miejscex = kam.przek_x(x * 50);
        int miejscey = kam.przek_y(y * 50);

        bool otoczka[4] = {false,false,false,false};
        if(x == 0 || pola[y *szer +x].przynaleznosc != pola[y * szer + (x-1)].przynaleznosc)otoczka[3] = true;
        if(x == szer - 1 || pola[y * szer+x].przynaleznosc != pola[y * szer + x + 1].przynaleznosc)otoczka[1] = true;
        if(y == 0 ||  pola[y * szer+x].przynaleznosc != pola[(y-1) * szer + x].przynaleznosc)otoczka[0] = true;
        if(y == wys - 1 ||  pola[y * szer+x].przynaleznosc != pola[(y+1)*szer +x].przynaleznosc)otoczka[2] = true;

        if(x == _x && y == _y && (graniczy(_x,_y,kto)
            || pola[y*szer+x].przynaleznosc == kto)) //jesli nalezy do gracza
        pola[y * szer + x].wyswietl(miejscex,miejscey,otoczka,true);
        else pola[y * szer + x].wyswietl(miejscex,miejscey,otoczka,false);
    }

    for(int i = 0;i < markery.size();i++)
    {
    ALLEGRO_COLOR kol = markery[i]->kolor;
   // l_draw_filled_rectangle(545,y1,555,y2,al_map_rgb(255,255,255));
    int x = kam.przek_x(markery[i]->x * 50);
    int y = kam.przek_y(markery[i]->y * 50);
    al_draw_filled_rectangle(x,y,x+50,y+50,kol);
    }
}

void Mapa::przesun_kamere(int x,int y)
{
    kam.przesun(x,y);
}

void Mapa::generuj()
{
    float ile = 1.0;
    if(szer < 25) ile -= 0.2;
    if(szer > 50) ile += 0.5;
    generuj(las,ile);
    generuj(gory,ile * 3 / 4);
    generuj(pole,ile);
    generuj(las,ile / 9);
}

void Mapa::generuj(Typ teren,float wspolczynnik)
{
    vector<int> pozx;
    vector<int> pozy;
    int ile = sqrt(szer * wys) * wspolczynnik;
    float odl = sqrt(ile);
    cout << ile << " - " << odl << endl;
    for(int i =0;i < ile;)
    {
        int x = rand() % szer;
        int y =  rand() % wys;
        for(int I = 0;I < pozx.size();I++)
        {
            if(pozx[I] == x || pozy[I] == y)continue;
            if(odleglosc(pozx[I],pozy[I],x,y) > odl) continue;
        }

        generuj(x,y,5 +rand() % 5,100,99 - rand() % 10,teren);
        pozx.push_back(x);
        pozy.push_back(y);
        i++;
    }
}

void Mapa::wyswietl_miniature(int wspx,int wspy,int wielkosc)
{
    int max = szer;
    if(max < wys)max = wys;
    float bok = wielkosc / float(max);

    for(int x = 0;x < szer;x++)
    for(int y = 0;y < wys;y++)
    {
        float miejscex = float(wspx) + (float(x) * bok);
        float miejscey = float(wspy) + (float(y) * bok);
        ALLEGRO_COLOR kol = al_map_rgb(255,255,255);
        Pole *wybrane = &pola[y * szer + x];
        if(wybrane->typ == pole)kol = al_map_rgb(255,255,0);
        else if (wybrane->typ == las) kol = al_map_rgb(0,255,0);
        else if(wybrane->typ == gory) kol = al_map_rgb(0,0,0);
        al_draw_filled_rectangle(miejscex,miejscey,miejscex + bok,miejscey + bok,kol);

    }
}

void Mapa::koniec_tury()
{
    for(int i =0; i < szer * wys;i++)
    {
        pola[i].pracuj();
    }
}

void Mapa::smooth(float x,float y,float speeed)
{
    kam.smooth(x,y,speeed);
}

void Mapa::clear()
{
    markery.clear();
}

void Mapa::operator +=(Marker *nowy)
{
    markery += nowy;
}

void Mapa::operator -=(Marker *co)
{
    markery -= co;
}

void Mapa::ustanow_teren(int x,int y,Gracz *wlascicel,TextMaster &TM)
{


if(x < 0 || x>= szer) return;
if(y < 0 || y>= wys) return;

pola[y*szer+x].widocznosc = 1.0;
odkryj_wokol(x,y);

if(pola[y*szer+x].zwroc_gracz()==wlascicel)
{
TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,"To twoje pole!!");
return;
}
if(pola[y*szer+x].przynaleznosc)pola[y*szer+x].przynaleznosc->dodaj_poparcie(-1);
pola[y * szer + x].zmien_przynaleznosc(wlascicel);
pola[y * szer + x].obrona = 1;
TM.neutralna_wiadomosc(x * 50 + 25,y * 50 + 25,"Zajete!");

int _x = x +1,_y = y;
if(otacza(_x,_y,wlascicel) && pola[_y * szer + _x].przynaleznosc != wlascicel)
{
TM.neutralna_wiadomosc(_x * 50 + 25,_y * 50 + 25,"Zajete!");
pola[_y * szer + _x].obrona = pola[_y * szer + _x].obrona/2;
if(pola[_y*szer+_x].bud)pola[_y*szer+_x].bud->przejete(&pola[_y*szer+_x],pola[_y*szer+_x].przynaleznosc,wlascicel);
if(pola[_y*szer+_x].przynaleznosc)pola[_y*szer+_x].przynaleznosc->dodaj_poparcie(-2);
pola[_y * szer + _x].zmien_przynaleznosc(wlascicel);
}

_x = x-1;
if(otacza(_x,_y,wlascicel) && pola[_y * szer + _x].przynaleznosc != wlascicel)
{
TM.neutralna_wiadomosc(_x * 50 + 25,_y * 50 + 25,"Zajete!");
pola[_y * szer + _x].obrona = pola[_y * szer + _x].obrona/2;
if(pola[_y*szer+_x].bud)pola[_y*szer+_x].bud->przejete(&pola[_y*szer+_x],pola[_y*szer+_x].przynaleznosc,wlascicel);
if(pola[_y*szer+_x].przynaleznosc)pola[_y*szer+_x].przynaleznosc->dodaj_poparcie(-2);
pola[_y * szer + _x].zmien_przynaleznosc(wlascicel);
}

_y = y + 1;_x = x;
if(otacza(_x,_y,wlascicel) && pola[_y * szer + _x].przynaleznosc != wlascicel)
{
TM.neutralna_wiadomosc(_x * 50 + 25,_y * 50 + 25,"Zajete!");
pola[_y * szer + _x].obrona = pola[_y * szer + _x].obrona/2;
if(pola[_y*szer+_x].bud)pola[_y*szer+_x].bud->przejete(&pola[_y*szer+_x],pola[_y*szer+_x].przynaleznosc,wlascicel);
if(pola[_y*szer+_x].przynaleznosc)pola[_y*szer+_x].przynaleznosc->dodaj_poparcie(-2);
pola[_y * szer + _x].zmien_przynaleznosc(wlascicel);
}

_y = y -1;
if(otacza(_x,_y,wlascicel) && pola[_y * szer + _x].przynaleznosc != wlascicel)
{
TM.neutralna_wiadomosc(_x * 50 + 25,_y * 50 + 25,"Zajete!");
pola[_y * szer + _x].obrona = pola[_y * szer + _x].obrona/2;
if(pola[_y*szer+_x].bud)pola[_y*szer+_x].bud->przejete(&pola[_y*szer+_x],pola[_y*szer+_x].przynaleznosc,wlascicel);
if(pola[_y*szer+_x].przynaleznosc)pola[_y*szer+_x].przynaleznosc->dodaj_poparcie(-2);
pola[_y * szer + _x].zmien_przynaleznosc(wlascicel);
}

}

Kamera* Mapa::zwroc_kamere()
{
    return &kam;
}

Pole& Mapa::operator[](int i)
{
    return pola[i];
}

///czy dane terytorium graniczy z innym terytorium danego gracza
bool Mapa::graniczy(int x,int y,Gracz *wlasciciel)
{
    if(pola[y * szer + (x-1)].zwroc_gracz() == wlasciciel && x > 0) return true;
    if(pola[y * szer + (x+1)].zwroc_gracz() == wlasciciel && x < (szer - 1)) return true;
    if(pola[(y - 1) * szer + x].zwroc_gracz() == wlasciciel && y > 0) return true;
    if(pola[(y + 1) * szer + x].zwroc_gracz() == wlasciciel && x <( wys-1)) return true;
    return false;
}

///true - odejmuje 2 PA
///false - nic nie odejmuje
bool Mapa::atak(int x,int y,Gracz *wlasciciel,TextMaster &TM)
{
    if(wlasciciel->zwroc_armie() <= 0)
    {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,"Za malo wojska!");
    return false;
    }
    Pole *ktore = &pola[y * szer + x];//najlepiej miec to pod reka :)
    if(wlasciciel != ktore->przynaleznosc)
    {
    wlasciciel->dodaj_armie(-1);
    ktore->obrona --;
    if(ktore->obrona < 0)
    {
    if(ktore->bud)ktore->bud->przejete(ktore,ktore->przynaleznosc,wlasciciel);
    ustanow_teren(x,y,wlasciciel,TM);
    }
    else if(!(rand() % 20) && ktore->bud && !(ktore->bud->zwroc_zburz()) ) //kazdy atak to 20% szansy na zniszczenie budynku
    {
        string zwroc =  ktore->bud->zburz();
        TM.dobra_wiadomosc(x*50+25,y*50+25,zwroc);
    }
    return true;
    }
    else if(ktore->obrona != 10)
    {
        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,"++");
        wlasciciel->dodaj_armie(-1);
        ktore->obrona++;
        return true;
    }
    return false;
}

bool Mapa::atak(int i,Gracz *wlasciciel,TextMaster &TM)
{
    int x = i % szer;
    int y = (i - x ) / szer;
    atak(x,y,wlasciciel,TM);

}

void Mapa::ustaw_widok(int x,int y,float co)
{
    if(x < 0 || x>= szer) return;
    if(y < 0 || y>= wys) return;
    pola[y*szer+x].widocznosc = co;
}

void Mapa::odkryj_wokol(int x,int y)
{
    ustaw_widok(x,y,1);
    if(x >= 1)    ustaw_widok(x - 1,y,1);
    if(x < szer-1)    ustaw_widok(x+1,y,1);
    if(y >= 1)    ustaw_widok(x,y-1,1);
    if(y < wys-1)    ustaw_widok(x,y +1,1);
    if(x >= 1 && y >= 1) ustaw_widok(x-1,y - 1,1);
    if(x < szer-1 && y > 1)ustaw_widok(x+1,y-1,1);
    if(x >= 1 && y < szer-1)ustaw_widok(x-1,y+1,1);
    if(x < szer-1 && y < szer-1)ustaw_widok(x+1,y+1,1 );
}

void Mapa::oblicz_fog(Gracz *kto)
{
    for(int i = 0;i < wys*szer;i++)
    pola[i].widocznosc = 0.05;
    for(int y = 0;y < wys;y++)
    for(int x = 0;x < szer;x++)
    {
        if(pola[y * szer + x].przynaleznosc == kto)
        {
            ustaw_widok(x,y,1.0);
            odkryj_wokol(x,y);
            if(pola[y*szer+x].bud)
            if(pola[y*szer+x].bud->nazwa() == "Wieza")
            {
                odkryj_wokol(x-2,y);
                odkryj_wokol(x+2,y);
                odkryj_wokol(x,y-2);
                odkryj_wokol(x,y+2);
                odkryj_wokol(x-1,y-1);
                odkryj_wokol(x+1,y-1);
                odkryj_wokol(x - 1,y + 1);
                odkryj_wokol(x + 1,y + 1);
            }
        }
    }
}

void Mapa::fog_off()
{
    for(int i = 0;i < wys*szer;i++)
    pola[i].widocznosc = 1.0;
}

void Mapa::ustaw_kamere(int x,int y)
{
    kam.ustaw(x,y);
}

Gracz* Mapa::wlasnosc(int x,int y)
{
    return pola[y*szer+x].przynaleznosc;
}

Gracz* Mapa::wlasnosc(int i)
{
    return pola[i].przynaleznosc;
}
void Mapa::zaloz_osade(int x,int y,Gracz *kto)
{
    Surowce surka(9999,9999,9999);
    pola[y * szer + x].typ = puste;
    pola[y * szer + x].przynaleznosc = kto;
    Baraki *kosz = new Baraki();
    Baraki *nowy = new Baraki();
    nowy->zbuduj(pola[y * szer + x],surka,*kto);
    kto->dodaj_budynek(3,1);


    pola[y * szer + x-1].typ = pole;
    pola[y * szer + x-1].zyznosc = 1;
    if(kto->isbot()) pola[y * szer + x-1].zyznosc = 3;
    pola[y * szer + x-1].przynaleznosc = kto;


    pola[y * szer + x+1].typ = gory;
    pola[y * szer + x+1].zyznosc = 1;
    if(kto->isbot()) pola[y * szer + x+1].zyznosc = 3;
    pola[y * szer + x+1].przynaleznosc = kto;


    y--;
    pola[y * szer + x].typ = las;
    pola[y * szer + x].zyznosc = 1;
    if(kto->isbot()) pola[y * szer + x].zyznosc = 3;
    pola[y * szer + x].przynaleznosc = kto;

    if(kto->isbot())
    {
        y+=2;
    kto->dodaj_budynek(5,1);

    Zamek *zam = new Zamek();
    pola[y*szer+x].bud = zam;
    pola[y * szer + x].typ = puste;
    pola[y * szer + x].zyznosc = 1;
    pola[y * szer + x].przynaleznosc = kto;
    }
}

///czy dane terytorium jest otoczne
bool Mapa::otacza(int x,int y,Gracz *wlasciciel)
{
    if(pola[y * szer + (x-1)].zwroc_gracz() == wlasciciel && x > 0)
    if(pola[y * szer + (x+1)].zwroc_gracz() == wlasciciel && x < (szer - 1))
    if(pola[(y - 1) * szer + x].zwroc_gracz() == wlasciciel && y > 0)
    if(pola[(y + 1) * szer + x].zwroc_gracz() == wlasciciel && x <( wys-1)) return true;
    return false;
}

int Mapa::index_pola(Pole *ktore)
{
    for(int i = 0;i < szer*wys;i++)
    if(&pola[i] == ktore)return i;
    return -1;
}

bool Mapa::graniczy(int i,Gracz *wlasciciel)
{
    int x = i % szer;
    int y = i / szer;
    graniczy(x,y,wlasciciel);
}
