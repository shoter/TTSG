#include "mgracz.h"
#include "colorstate.h"
#include "bitmapstate.h"
#include "ekran.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;
/*
czarny
bialy
czerwony
zielony
niebieski
pomaranczowy
zolty
rozowy
*/
extern bool  kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2);

const int odl1 = 191;
const int odl2 = 32;

extern ALLEGRO_FONT* font;

MGracz::MGracz(int _x,int _y) : x(_x),y(_y),kolor(x + odl1,y,27,28,ilosc_kolorow),typ(x+odl1+odl2,y,27,28,5),nazwa("GRACZ"),uzywana_klawiatura(false),ostatni(-1)
{
    ColorState *nowy = new ColorState(x + odl1,y,27,28,al_map_rgb(0,0,0));
    ColorState *nowy2 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,255,255));
    ColorState *nowy3 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,0,0));
    ColorState *nowy4 = new ColorState(x + odl1,y,27,28,al_map_rgb(0,255,0));
    ColorState *nowy5 = new ColorState(x + odl1,y,27,28,al_map_rgb(0,0,255));
    ColorState *nowy6 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,120,0));
    ColorState *nowy7 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,220,0));
    ColorState *nowy8 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,110,180));

    kolor += nowy;
    kolor += nowy2;
    kolor += nowy3;
    kolor += nowy4;
    kolor += nowy5;
    kolor += nowy6;
    kolor += nowy7;
    kolor += nowy8;

    BitmapState *bs1 = new BitmapState(x + odl1 + odl2,y,al_load_bitmap("GFX\\gracz.bmp"));
    BitmapState *bs2 = new BitmapState(x + odl1 + odl2,y,al_load_bitmap("GFX\\komputer1.bmp"));
    BitmapState *bs3 = new BitmapState(x + odl1 + odl2,y,al_load_bitmap("GFX\\komputer2.bmp"));
    BitmapState *bs4 = new BitmapState(x + odl1 + odl2,y,al_load_bitmap("GFX\\komputer3.bmp"));
    BitmapState *bs5 = new BitmapState(x + odl1 + odl2,y,al_load_bitmap("GFX\\nikt.bmp"));

    typ += bs1;
    typ += bs2;
    typ += bs3;
    typ += bs4;
    typ += bs5;
    //em czy powinienem to zrobic za pomoca nowy[],ale ze mnie...dziwak xD.

}

void MGracz::wyswietl()
{
    kolor.wyswietl();
    typ.wyswietl();
     al_draw_text(font,al_map_rgb(0,0,0),x + 91 - al_get_text_width(font,nazwa.c_str()) / 2,y + 15,NULL,nazwa.c_str() );
///182 - szerokosc miejsca na txt
}


void MGracz::pracuj(Ekran &gdzie)
{

    int mx = gdzie.mousex();
    int my = gdzie.mousey();

    kolor.pracuj(gdzie);
    typ.pracuj(gdzie);
    if(typ == 1) //komputer
    nazwa = "BOT LATWY";
    else if(typ == 2)
    nazwa = "BOT SREDNI";
    else if(typ == 3)
    nazwa = "BOT TRUDNY";
    else if(typ == 4)
    nazwa = "";

    if(kolizja(mx,my,1,1,x,y,182,28) && gdzie.prosba_klawiatura() && typ == 0 && gdzie.mouseb1())
    {
        gdzie.rezerwuj_klawiature();
        uzywana_klawiatura = true;
        cout << "Uzywana = true" << endl;
    }
    if(uzywana_klawiatura)
    {
        bool byl_break = false;

        for(int i = ALLEGRO_KEY_A ; i <=     ALLEGRO_KEY_Z;i++)
        {
            if(gdzie.keyboardb(i) && ostatni != i)
            {
                if(nazwa.size() < 20)
            nazwa += char(i - ALLEGRO_KEY_A) + 'A';
            byl_break = true;
            ostatni = i;
            break;
            al_draw_filled_rectangle(x,y,x + 50,y + 50,al_map_rgb(0,0,0));
            }
            if(gdzie.keyboardb(i) && ostatni)
            {
            byl_break = true;
            break;
            }
        }

        for(int i = ALLEGRO_KEY_0 ; i < ALLEGRO_KEY_9;i++)
        {
            if(gdzie.keyboardb(i) && ostatni != i)
            {
                if(nazwa.size() < 20)
            nazwa += char(i - ALLEGRO_KEY_0) + '0';
            byl_break = true;
            ostatni = i;
            break;
            al_draw_filled_rectangle(x,y,x + 50,y + 50,al_map_rgb(0,0,0));
            }
            if(gdzie.keyboardb(i) && ostatni)
            {
            byl_break = true;
            break;
            }
        }


        if(gdzie.keyboardb(ALLEGRO_KEY_BACKSPACE)  && nazwa.size())
        {
        if(ostatni != ALLEGRO_KEY_BACKSPACE)
        {
        nazwa = nazwa.substr(0,nazwa.size() - 1);
        ostatni = ALLEGRO_KEY_BACKSPACE;
        }
        byl_break = true;
        }

        if(gdzie.keyboardb(ALLEGRO_KEY_SPACE) && nazwa.size() < 20)
        {
        if(ostatni != ALLEGRO_KEY_SPACE)
        {
        nazwa += " ";
        ostatni = ALLEGRO_KEY_SPACE;
        }
        byl_break = true;
        }

        if(byl_break == false)ostatni = -1;


    }
    if(kolizja(mx,my,1,1,x,y,182,28) == false && gdzie.mouseb1() && uzywana_klawiatura)
    {
    uzywana_klawiatura = false;
    gdzie.zwolnij_klawiature();
    cout << "Uzywana = false" << endl;
    }
}

MGracz::operator int()
{
    return typ;
}

MGracz::operator ALLEGRO_COLOR()
{
    ColorState *nowy = new ColorState(x + odl1,y,27,28,al_map_rgb(0,0,0));
    ColorState *nowy2 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,255,255));
    ColorState *nowy3 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,0,0));
    ColorState *nowy4 = new ColorState(x + odl1,y,27,28,al_map_rgb(0,255,0));
    ColorState *nowy5 = new ColorState(x + odl1,y,27,28,al_map_rgb(0,0,255));
    ColorState *nowy6 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,120,0));
    ColorState *nowy7 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,220,0));
    ColorState *nowy8 = new ColorState(x + odl1,y,27,28,al_map_rgb(255,110,180));
    switch(kolor)
    {
        case 0:
        return al_map_rgb(0,0,0);
        case 1:
        return al_map_rgb(255,255,255);
        case 2:
        return al_map_rgb(255,0,0);
        case 3:
        return al_map_rgb(0,255,0);
        case 4:
        return al_map_rgb(0,0,255);
        case 5:
        return al_map_rgb(255,120,0);
        case 6:
        return al_map_rgb(255,220,0);
        case 7:
        return al_map_rgb(255,110,180);
        default :
        return al_map_rgb(255,0,255);
    }
}

MGracz::operator string()
{
    return nazwa;
}



