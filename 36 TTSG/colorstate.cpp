#include "colorstate.h"
#include <allegro5/allegro_primitives.h>

ColorState::ColorState(int _x,int _y,int _szer,int _wys,ALLEGRO_COLOR kol) : State(_x,_y,_szer,_wys),kolor(kol)
{}

void ColorState::wyswietl()
{
al_draw_filled_rectangle(x,y,x + szer,y + wys,kolor);
}

int ColorState::zwroc_szer()
{
    return szer;
}

int ColorState::zwroc_wys()
{
    return wys;
}
