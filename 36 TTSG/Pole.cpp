#include "pole.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "audio.h"
ALLEGRO_BITMAP *Pole::bLas[3] = {NULL,NULL,NULL};
ALLEGRO_BITMAP *Pole::bGora[3] = {NULL,NULL,NULL};
ALLEGRO_BITMAP *Pole::bPole[3] = {NULL,NULL,NULL};
ALLEGRO_BITMAP *Pole::bPuste[3] = {NULL,NULL,NULL};
ALLEGRO_BITMAP *Pole::bHP =  NULL;



Pole::Pole(Typ t) :typ(t),zyznosc(1 + rand() % 3),bud(NULL),przynaleznosc(NULL),widocznosc(1.0)
{
    if(!bGora[0])
    {
    bGora[0] = al_load_bitmap("GFX\\gora1.bmp");
    al_convert_mask_to_alpha(bGora[0],al_map_rgb(255,0,255));
    bGora[1] = al_load_bitmap("GFX\\gora2.bmp");
    al_convert_mask_to_alpha(bGora[1],al_map_rgb(255,0,255));
    bGora[2] = al_load_bitmap("GFX\\gora3.bmp");
    al_convert_mask_to_alpha(bGora[2],al_map_rgb(255,0,255));

    bLas[0] =  al_load_bitmap("GFX\\las1.bmp");
    al_convert_mask_to_alpha(bLas[0],al_map_rgb(255,0,255));
    bLas[1] =  al_load_bitmap("GFX\\las2.bmp");
    al_convert_mask_to_alpha(bLas[1],al_map_rgb(255,0,255));
    bLas[2] =  al_load_bitmap("GFX\\las3.bmp");
    al_convert_mask_to_alpha(bLas[2],al_map_rgb(255,0,255));

    bPole[0] = al_load_bitmap("GFX\\pole1.bmp");
    al_convert_mask_to_alpha(bPole[0],al_map_rgb(255,0,255));
    bPole[1] = al_load_bitmap("GFX\\pole2.bmp");
    al_convert_mask_to_alpha(bPole[1],al_map_rgb(255,0,255));
    bPole[2] = al_load_bitmap("GFX\\pole3.bmp");
    al_convert_mask_to_alpha(bPole[2],al_map_rgb(255,0,255));

    bPuste[0] = al_load_bitmap("GFX\\puste1.bmp");
    al_convert_mask_to_alpha(bPuste[0],al_map_rgb(255,0,255));
    bPuste[1] = al_load_bitmap("GFX\\puste2.bmp");
    al_convert_mask_to_alpha(bPuste[1],al_map_rgb(255,0,255));
    bPuste[2] = al_load_bitmap("GFX\\puste3.bmp");
    al_convert_mask_to_alpha(bPuste[2],al_map_rgb(255,0,255));
    bHP =  al_load_bitmap("GFX\\HP.bmp");
    }
    obrona =  rand() % 5;
}

void Pole::wyswietl(int x,int y,bool otoczka[4],bool pasek)
{
    //TYP TERENU
    switch(typ)
    {
        case gory:
        al_draw_bitmap(bGora[zyznosc - 1],x,y,NULL);break;
        case pole :
        al_draw_bitmap(bPole[zyznosc-1],x,y,NULL);break;
        case las :
        al_draw_bitmap(bLas[zyznosc-1],x,y,NULL);break;
        case puste :
        al_draw_bitmap(bPuste
                       [0],x,y,NULL);break;
        break;
    }
    // BUDYNEK
    if(bud != NULL && ! bud->zwroc_zburz())
    bud->wyswietl(x,y);
    //CZYJ TEREN
    if(przynaleznosc)
    {
    ALLEGRO_COLOR kol = przynaleznosc->zwroc_kolor();
    kol.a = 0.2
    ;
    al_draw_filled_rectangle(x,y,x+50,y+50,kol);
    kol.a = 0.5;
    if(otoczka[0])
    al_draw_line(x,y + 1,x + 50,y + 1,kol,2);
    if(otoczka[1])
    al_draw_line(x+ 49,y,x + 49,y + 50,kol,2);
    if(otoczka[2])
    al_draw_line(x,y + 49,x + 50,y + 49,kol,2);
    if(otoczka[3])
    al_draw_line(x+ 1,y,x + 1,y + 50,kol,2);


    //al_draw_rectangle(x,y,x+50,y+50,kol,1);

    }

    //HP
    if(pasek)
    {
    int prawy = float(10.0 - obrona) / 10.0 * 25.0;
    al_draw_bitmap_region(bHP,prawy,0,50 - prawy * 2,8,x + prawy,y + 50 - 8,NULL);
    }

    ALLEGRO_COLOR kol = al_map_rgba(0,0,0,0);
    kol.a = (1.0 - widocznosc);
    al_draw_filled_rectangle(x,y,x+50,y+50,kol);


}

void Pole::wyswietl(int x,int y,Kamera &kam,bool otoczka[4])
{
    wyswietl(kam.przek_x(x),kam.przek_y(y),otoczka);
}

bool Pole::zabudowane()
{
    if(bud)return true;return false;
}

void Pole::zbuduj(Budynek *co)
{
    bud = co;
}

void Pole::zniszcz_budynek()
{
    if(bud)if(bud->zburz(this,przynaleznosc))
    {
    delete bud;
    bud = NULL;
    }
}

void Pole::pracuj()
{

    if(!przynaleznosc) return;

    //pole cos zjada(ze niby mieszkancy cos jedza)
    if(przynaleznosc->jedz(1) == false) //LUD NIE MA JEDZENIA.ZABIC PANA!!! D:
    przynaleznosc->dodaj_poparcie(-1); //zabic go!

    if(bud)if(bud->zburz(this,przynaleznosc)) //nisczenie budynku jesli zostal znisczony
    {
    delete bud;
    bud = NULL; //ustawienie wskaznika zerowego,tak dla bezpieczenstwa
    }

    if(bud)bud->pracuj(zyznosc,*przynaleznosc);
    switch(typ)
    {
        case gory:
        {
        Surowce temp(1,0,0);
        *przynaleznosc += temp;
        break;
        }
        case las:
        {
        Surowce temp(0,1,0);
        *przynaleznosc += temp;
        break;
        }
        case pole:
        {
        Surowce temp(0,0,2);
        *przynaleznosc += temp;
        break;
        }
    }
    if(przynaleznosc->zwroc_poparcie() < 10)
    if(!(rand() % (10 * (przynaleznosc->zwroc_poparcie() + 1)) )) przynaleznosc = NULL; //jesli poparcie mniejsze niz 10 to obszar sie buntuje :)
}

void Pole::zmien_przynaleznosc(Gracz *zmiana)
{
    przynaleznosc = zmiana;
}

Gracz* Pole::zwroc_gracz()
{
    return przynaleznosc;
}

Typ Pole::zwroc_typ()
{
    return typ;
}

void Pole::ustaw_widocznosc(float co)
{
    widocznosc = co;
}

Budynek * Pole::zwroc_budynek()
{
    return bud;
}

Pole::operator int()
{
    return zyznosc;
}

float Pole::zwroc_widocznosc()
{
    return widocznosc;
}

int Pole::zwroc_obrone()
{
    return obrona;
}
