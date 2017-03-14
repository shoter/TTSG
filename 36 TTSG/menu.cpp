#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "button.h"
#include "ekran.h"
#include "mgracz.h"
#include "buttonclick.h"
#include "swiat.h"
#include "audio.h"
#include <string>
#include <iostream>

using namespace std;
extern ALLEGRO_FONT* font;
extern void Game(Swiat &,Audio *);
Audio audio;

void Menu()
{
    int szx=30,szy=30;
    Swiat SW;
    SW.inicjalizuj_mape(szx,szy);
    Ekran menu(0.025,0.1,ALLEGRO_KEY_ESCAPE,"GFX\\menu.bmp");

    MGracz cos[4] = { MGracz(466,127) , MGracz(466,164) , MGracz(466,199) , MGracz(466,235)};

    ButtonClick plus(650,331,"GFX\\plus.bmp","GFX\\plus.bmp","GFX\\Aplus.bmp",al_map_rgb(255,0,255),5);
    ButtonClick minus(682,331,"GFX\\minus.bmp","GFX\\minus.bmp","GFX\\Aminus.bmp",al_map_rgb(255,0,255),5);
    ButtonClick gen(649,295,"GFX\\gen.bmp","GFX\\gen.bmp","GFX\\Agen.bmp",al_map_rgb(255,0,255),5);
    ButtonClick start(559,492,"GFX\\start.bmp","GFX\\start.bmp","GFX\\Astart.bmp",al_map_rgb(255,0,255),5);


    audio.init();
    audio.dodaj("SFX\\click.wav","klik");
    audio.dodaj("SFX\\build0.wav","build0");
    audio.dodaj("SFX\\build1.wav","build1");

    audio.dodaj("SFX\\attack0.wav","atak0");
    audio.dodaj("SFX\\attack1.wav","atak1");
    audio.dodaj("SFX\\attack2.wav","atak2");
    audio.dodaj("SFX\\attack3.wav","atak3");
    audio.dodaj("SFX\\attack4.wav","atak4");
    audio.dodaj("SFX\\attack5.wav","atak5");

    audio.dodaj("SFX\\cant.wav","cant");
    audio.dodaj("SFX\\destroy.wav","destroy");
    audio.dodaj("SFX\\turn.wav","turn");



    //dlaczego nei w tablicy?Bo menu.bmp jest brzydkie

        bool klik = false;
    while(!menu.Koniec() && !start.zwroc_click())
    {
        if(menu.Logika())
        {
            for(int i =0;i < 4;i++)
        cos[i].pracuj(menu);
         menu.ResetTimeL();
         plus.pracuj(menu);
         minus.pracuj(menu);
         gen.pracuj(menu);
         start.pracuj(menu);
         if(plus.zwroc_click()){szx++;szy++;}
         if(minus.zwroc_click()){szx--;szy--;}
         if(gen.zwroc_click())SW.inicjalizuj_mape(szx,szy);
         if(szx < 15)szx = 15;
         if(szx > 70)szx = 70;
         if(szy < 15)szy = 15;
         if(szy > 70)szy = 70;

        }


        if(menu.Dzwiek())
        {

          //  audio.odtworz("klik");

            menu.ResetTimeD();
        }

        {
            if(menu.mouseb1() && !klik)
            {
            audio.odtworz("klik");
            klik = true;
            }
            if(!menu.mouseb1() && klik) klik = false;

            //dzwiek ale bez danego czasu
        }

        for(int i =0;i < 4;i++)
        cos[i].wyswietl();
        SW.wyswietl_min_mape(470,295,169);
        plus.wyswietl();
        minus.wyswietl();
        gen.wyswietl();
        start.wyswietl();
        al_draw_textf(font,al_map_rgb(0,0,0),560,466,ALLEGRO_ALIGN_CENTRE ,"%d x %d " , szx , szy );
        menu.DrawClear();
        menu.Pracuj();
    }
    if(start.zwroc_click())
    {
        if(cos[0] == 4 && cos[1] == 4 && cos[2] == 4 && cos[3] == 4)
        {
            cout << "Chcesz grac sam?Wylaczam gre!" << endl;
            return;
        }
        Gracz gracze[4];
        for(int i = 0;i < 4;i++)
        if(cos[i] != 4)
        {
        gracze[i] = Gracz(cos[i],cos[i],(cos[i] != 0 ? true : false));
        if(cos[i] >= 3)
        {
        gracze[i].dodaj_maxarmie(50);
        gracze[i].dodaj_armie(50);
        gracze[i].odejmij_maxPA(-20);
        gracze[i].dodaj_PA(20);
        gracze[i].dodaj_poparcie(25);
        gracze[i] += Surowce(1000,1000,1000);
        }
        if(cos[i] == 3)
        {
        gracze[i].dodaj_maxarmie(300);
        gracze[i].dodaj_armie(300);
        gracze[i].odejmij_maxPA(-300);
        gracze[i].dodaj_PA(150);
        gracze[i].dodaj_poparcie(50);
        gracze[i] += Surowce(10000,10000,100000);
        }


        SW += &gracze[i];
        }
        if(cos[0] != 4)
        SW.zwroc_mape()->zaloz_osade(1,1,&gracze[0]);
        if(cos[1] != 4)
        {
        SW.zwroc_mape()->zaloz_osade(szx - 2,1,&gracze[1]);
        gracze[1].ustaw_kamere(szx-2,1);
        }
        if(cos[2] != 4)
        {
        SW.zwroc_mape()->zaloz_osade(1,szy - 2,&gracze[2]);
        gracze[2].ustaw_kamere(1,szy - 2);
        }
        if(cos[3] != 4)
        {
        SW.zwroc_mape()->zaloz_osade(szx - 2,szy - 2,&gracze[3]);
        gracze[3].ustaw_kamere(szx - 2,szy - 2);
        }
        SW.start();
        Game(SW,&audio);
    }

}
