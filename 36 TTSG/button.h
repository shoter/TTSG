#ifndef button_h_
#define button_h_
#include <string>
#include <allegro5/allegro.h>
using namespace std;

class Button
{
    public :
    Button(int x,int y,string sIdle,string sActive,ALLEGRO_COLOR maska);
    void wyswietl();
    void operuj(int mousex,int mousey);
    bool zwroc_stan();
    operator bool();
    ~Button();
    protected :
    ALLEGRO_BITMAP *idle,*active;
    int x,y;
    bool stan;


};
#endif
