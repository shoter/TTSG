#include "lista.h"
#include "surowce.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
extern ALLEGRO_FONT* font;
ALLEGRO_BITMAP * Lista::drewno = NULL;
ALLEGRO_BITMAP * Lista::kamien = NULL;
ALLEGRO_BITMAP * Lista::zywnosc = NULL;


Lista::Lista(int _ile) :ile(_ile),ktory(0),aktywne(0)
{
    budynki = new string[_ile];
    surki = new Surowce[_ile];
    liczba = new int[_ile];
    if(drewno == NULL)
    {
        zywnosc = al_load_bitmap("GFX\\zarlo.bmp");
        al_convert_mask_to_alpha(zywnosc,al_map_rgb(255,0,255));

        drewno = al_load_bitmap("GFX\\drewno.bmp");
        al_convert_mask_to_alpha(drewno,al_map_rgb(255,0,255));

        kamien = al_load_bitmap("GFX\\kamien.bmp");
        al_convert_mask_to_alpha(kamien,al_map_rgb(255,0,255));
    }
    szer = 350;
    wys = 30 * ile;
}

void Lista::dodaj(string bud,Surowce surka,int licz)
{
    if(ktory == ile)return;
    budynki[ktory] = bud;
    liczba[ktory] = licz;
    surki[ktory ++] = surka;
}

void Lista::wyswietl()
{
    al_draw_filled_rectangle(400 - szer / 2,300 - wys / 2,400 + szer / 2 , 300 + wys / 2,al_map_rgb(190,150,50));
    for(int i = 0;i < ktory;i++)
    {
        if(aktywne == i)
        al_draw_filled_rectangle(400 - szer / 2,300 - wys / 2 + i * 30,400 + szer / 2 , 300 - wys / 2 + (i + 1) * 30,al_map_rgb(160,130,40));
        char drew[10],kam[10],zyw[10];
        itoa(surki[i].drewno,drew,10);
        itoa(surki[i].kamien,kam,10);
        itoa(surki[i].zywnosc,zyw,10);
        int dlugosc = 116;//ikony surek
         dlugosc += al_get_text_width(font,budynki[i].c_str());
         dlugosc += al_get_text_width(font,zyw);
         dlugosc += al_get_text_width(font,kam);
         dlugosc += al_get_text_width(font,drew);
        int start = 400 - szer / 2 + 10;

        al_draw_text(font,al_map_rgb(0,0,0),start,300 - wys / 2 + i * 30 + 11,NULL,budynki[i].c_str() );
        start += 15 + al_get_text_width(font,budynki[i].c_str());

        al_draw_text(font,al_map_rgb(0,0,0),start + 30,300 - wys / 2 + i * 30 + 11,NULL,zyw );
        al_draw_bitmap(zywnosc,start,300 - wys / 2 + i * 30,NULL);
        start += 34 + al_get_text_width(font,zyw);

        al_draw_text(font,al_map_rgb(0,0,0),start+30,300 - wys / 2 + i * 30 + 11,NULL,drew );
        al_draw_bitmap(drewno,start,300 - wys / 2 + i * 30,NULL);
        start += 34 + al_get_text_width(font,drew);

        al_draw_text(font,al_map_rgb(0,0,0),start+34,300 - wys / 2 + i * 30 + 11,NULL,kam );
        al_draw_bitmap(kamien,start ,300 - wys / 2 + i * 30,NULL);
        start += 34 + al_get_text_width(font,kam);
    }
}

Lista::~Lista()
{
    delete []budynki;
    delete []surki;
}

Lista::operator int()
{
    return liczba[aktywne];
}

void Lista::operator += (int i)
{
    aktywne += i;
    if(aktywne < 0)aktywne = ktory-1;
    if(aktywne >= ktory) aktywne = 0;
}
