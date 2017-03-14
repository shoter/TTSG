#include "bitmapstate.h"

BitmapState::BitmapState(int x,int y,int szer,int wys,ALLEGRO_BITMAP *bitmapa) : State(x,y,szer,wys),grafika(bitmapa)
{}

BitmapState::BitmapState(int x,int y,ALLEGRO_BITMAP *bitmapa) : State(x,y,0,0),grafika(bitmapa)
{
szer = al_get_bitmap_width(bitmapa);
wys = al_get_bitmap_height(bitmapa);
}

void BitmapState::wyswietl()
{
    al_draw_bitmap(grafika,x,y,NULL);
}

int BitmapState::zwroc_szer()
{
    return szer;
}

int BitmapState::zwroc_wys()
{
    return wys;
}

BitmapState::~BitmapState()
{
    al_destroy_bitmap(grafika);
}
