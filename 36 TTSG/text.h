#ifndef text_h_
#define text_h_
#include <allegro5/allegro.h>
#include <string>
#include "kamera.h"
using namespace std;
class Text
{
    public :
    Text(int x,int y,int x2,int y2,ALLEGRO_COLOR start,ALLEGRO_COLOR end,int czasm,string txt);
    Text(int x,int y,ALLEGRO_COLOR start,ALLEGRO_COLOR end,int czas,string txt);
    void wyswietl();
    void wyswietl(Kamera&);
    void pracuj();
    bool koniec();
    protected :
    float x,y;
    string zaw; //zawartosc
    ALLEGRO_COLOR teraz;
    ALLEGRO_COLOR change;
    int t,maxt;
    float sx,sy;
};

#endif // text_h_

