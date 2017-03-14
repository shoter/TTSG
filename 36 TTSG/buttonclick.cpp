#include "buttonclick.h"
extern bool  kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2);
//konstruktor
//wywoluje konstruktor po odziedziczonym obiekcie
ButtonClick::ButtonClick(int _x,int _y,string id,string ac,string click,ALLEGRO_COLOR maska,int cd) :
Button(_x,_y,id,ac,maska),bClikedR(false)
{
    aClicked = al_load_bitmap(click.c_str());
    al_convert_mask_to_alpha(aClicked,maska);
    cooldown = 0;
    max_cooldown = cd;
}

//wyswietla przycisk
void ButtonClick::wyswietl()
{
    if(stan)
    {
        if(bClicked)
        al_draw_bitmap(aClicked,x,y,NULL);
        else
        al_draw_bitmap(active,x,y,NULL);
    }
    else
    al_draw_bitmap(idle,x,y,NULL);
}

//operuje na buttonie
//mozemy najechac na button i takze na niego kliknac
//uzywa cooldowna
void ButtonClick::operuj(int mousex,int mousey,bool mouseb)
{
    cooldown ++;
    bClicked = false;
    bClikedR = false;
    stan = false;
    if(kolizja(mousex + 1,mousey + 1,1,1,x,y,al_get_bitmap_width(active),al_get_bitmap_height(active)))
    {
        stan = true;
        if(mouseb)
        {
            bClicked = true;
            if(cooldown < max_cooldown)return;
            bClikedR = true;
            cooldown = 0;
        }

    }
}

//zwraca bClicked
bool ButtonClick::zwroc_click()
{return bClikedR;}

ButtonClick::~ButtonClick()
{
    al_destroy_bitmap(aClicked);
}


void ButtonClick::pracuj(Ekran &gdzie)
{
    int mx = gdzie.mousex();
    int my = gdzie.mousey();
    bool mb = gdzie.mouseb1();
    operuj(mx,my,mb);
}
