#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include "pole.h"
#include "ekran.h"
#include "mapa.h"
#include "pamiec.h"
#include "gracz.h"
#include "wieza.h"
#include "swiat.h"
#include "textmaster.h"
#include "lista.h"
using namespace std;
extern ALLEGRO_FONT* font;

void  Game(Swiat &SW,Audio *aud)
{
Ekran gra(0.025,0.5);


TextMaster TM(16);

int music = -1;
aud->dodaj("SFX\\theme.wav","theme");
aud->dodaj_podklad("theme");


while(!gra.Koniec())
    {


        if(gra.Logika())
        {
         gra.ResetTimeL();



        SW.pracuj(gra,TM);
        SW.ruch_mapa(false);
        TM.pracuj();

        }



        if(SW.wyswietl_mape(false,TM) == true)
        {
            gra.Pracuj();
            al_flip_display();
            //al_rest(0.1);
        }
        else
        {
        gra.Pracuj();
        al_flip_display();
        }
        gra.DrawClear();
    }

}
/*
jak tego nie wykorzystam pozniej,to usun to.
        if(gra.keyboardb(ALLEGRO_KEY_UP))y-=15;
         if(gra.keyboardb(ALLEGRO_KEY_DOWN))y+=15;
         if(gra.keyboardb(ALLEGRO_KEY_LEFT))x-=15;
         if(gra.keyboardb(ALLEGRO_KEY_RIGHT))x+=15;*/
