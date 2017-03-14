#include "text.h"
#include <allegro5/allegro_font.h>

extern ALLEGRO_FONT* font;
Text::Text(int _x,int _y,int x2,int y2,ALLEGRO_COLOR start,ALLEGRO_COLOR end,int czas,string txt):x(_x),y(_y),teraz(start),t(0),maxt(czas),zaw(txt)
{
    float r,g,b,a;
    r = (end.r - start.r) / czas;
    g = (end.g - start.g) / czas;
    b = (end.b - start.b) / czas;
    a = (end.a - start.a) / czas;
    change = al_map_rgba_f(r,g,b,a);
    sx = (x2 - x) / czas;
    sy = (y2 - y) / czas;
}

Text::Text(int _x,int _y,ALLEGRO_COLOR start,ALLEGRO_COLOR end,int czas,string txt):x(_x),y(_y),teraz(start),t(0),maxt(czas),zaw(txt)
{
    sx =0.0;
    sy =0.0;
    float r,g,b,a;
    r = (end.r - start.r) / czas;
    g = (end.g - start.g) / czas;
    b = (end.b - start.b) / czas;
    a = (end.a - start.a) / czas;
    change = al_map_rgba_f(r,g,b,a);
}

void Text::pracuj()
{
    if(t > maxt) return;
    t++;
    teraz.r += change.r;
    teraz.g += change.g;
    teraz.b += change.b;
    teraz.a += change.a;
    x += sx;
    y += sy;
}

void Text::wyswietl()
{
al_draw_text(font,teraz,x,y,ALLEGRO_ALIGN_CENTRE,zaw.c_str());
}
void Text::wyswietl(Kamera &kam)
{
al_draw_text(font,teraz,kam.przek_x(x),kam.przek_y(y),ALLEGRO_ALIGN_CENTRE,zaw.c_str());
}

bool Text::koniec()
{
    if(t >= maxt) return true;return false;
}
