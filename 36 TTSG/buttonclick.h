#ifndef buttonclick_h_
#define buttonclick_h_
#include "ekran.h"
#include "button.h"
class ButtonClick : public Button
{
    public :
    ButtonClick(int x,int y,string sIdle,string sActive,string sClicked,ALLEGRO_COLOR maska,int cooldown);
    void wyswietl();
    void operuj(int mousex,int mousey,bool mouseb);
    void pracuj(Ekran &gdzie);
    bool zwroc_click();
    ~ButtonClick();
    protected :
    ALLEGRO_BITMAP *aClicked;
    bool bClicked;
    bool bClikedR;
    int cooldown;
    int max_cooldown;

};
#endif
