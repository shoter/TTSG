#ifndef colorstate_h_
#define colorstate_h_
#include <allegro5/allegro.h>
#include "state.h"
class ColorState : public State
{
    public :
    ColorState(int x,int y,int szer,int wys,ALLEGRO_COLOR kolor);
    virtual void wyswietl();
    virtual int zwroc_szer();
    virtual int zwroc_wys();

    protected :
    ALLEGRO_COLOR kolor;

};

#endif // colorstate_h_

