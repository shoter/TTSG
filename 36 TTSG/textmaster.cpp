#include "textmaster.h"
#include <iostream>
int TextMaster::max_cooldown =  8;
using namespace std;
TextMaster::TextMaster(int prawdziwa) :napisy(prawdziwa),czekaj(prawdziwa * 2,false)
{}

void TextMaster::wyswietl(Kamera &kam)
{
    for(int i =0;i < napisy.size();i++)
    napisy[i]->wyswietl(kam);
}

void TextMaster::pracuj()
{
    cooldown ++;
    if(czekaj.size() > 15 || (cooldown > max_cooldown && czekaj.size()))
    {
        Text *temp = czekaj[0];
        napisy += temp;
        czekaj -= 0;
        if(cooldown > max_cooldown)cooldown = 0;
    }


    //cout << napisy.size() << " | " << napisy.prawdziwy_rozmiar() << "   |||     " << czekaj.size() << " | " << czekaj.prawdziwy_rozmiar()<< endl;
    for(int i = 0;i < napisy.size();i++)
    {
        if(napisy[i]->koniec())
        {
            *this -= i;
            continue;
        }
        napisy[i]->pracuj();
    }
}

void TextMaster::operator+=(Text *nowy)
{
    czekaj += nowy;
}

void TextMaster::operator -=(int i)
{
    napisy -= i;
}

Text* TextMaster::operator [](int i)
{
    return napisy[i];
}

int TextMaster::size()
{
    return napisy.size();
}

void TextMaster::dobra_wiadomosc(int x,int y,string wiad)
{
     Text *nowy = new Text(x,y,x,y - 50,al_map_rgba(0,255,0,255),al_map_rgba(0,255,0,35),300,wiad);
     *this += nowy;
}

void TextMaster::zla_wiadomosc(int x,int y,string wiad)
{
     Text *nowy = new Text(x,y,x,y - 50,al_map_rgba(255,0,0,255),al_map_rgba(255,0,0,35),300,wiad);
     *this += nowy;
}

void TextMaster::neutralna_wiadomosc(int x,int y,string wiad)
{
     Text *nowy = new Text(x,y,x,y - 50,al_map_rgba(0,0,0,255),al_map_rgba(0,0,0,35),300,wiad);
     *this += nowy;
}

void TextMaster::clear()
{
    napisy.clear();
    czekaj.clear();
}
