#include "button.h"
extern bool  kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2);

//konstruktor
Button::Button(int _x,int _y,string id,string ac,ALLEGRO_COLOR maska) :x(_x),y(_y)
{
    idle = al_load_bitmap(id.c_str());
    active = al_load_bitmap(ac.c_str());
    stan = false;

    al_convert_mask_to_alpha(idle,maska);
    al_convert_mask_to_alpha(active,maska);
}

//wyswietla guzik
void Button::wyswietl()
{
    if(stan)
        al_draw_bitmap(active,x,y,NULL);
    else
        al_draw_bitmap(idle,x,y,NULL);
}

//sprawdza kolizje i uaktualnia stan
//potrzebuje wspolrzednych myszki do tego celu
void Button::operuj(int mousex,int mousey)
{
    stan = false;
    if(kolizja(mousex + 1,mousey + 1,1,1,x,y,al_get_bitmap_width(active),al_get_bitmap_height(active)))
    stan = true;
}

//zwraca stan
bool Button::zwroc_stan()
{return stan;}


//zwraca stan :D
Button::operator bool()
{return stan;}

Button::~Button()
{
al_destroy_bitmap(idle);
al_destroy_bitmap(active);
}
