#ifndef Pole_h_
#define Pole_h_
enum Typ{gory='g',pole='P',las='l',puste='p'};


#include "kamera.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "budynek.h"
#include "Gracz.h"

class Budynek;
class Pole
{

    public :

    Pole(Typ t = puste);
    Pole(char);
    operator int() ; //zyznosc

    void wyswietl(int x,int y,bool otoczka[4],bool pasek=false);
    void wyswietl(int x,int y,Kamera &kam,bool otoczka[4]);
    bool zabudowane();
    void zbuduj(Budynek *bud);
    void zniszcz_budynek(); //niszczy jego pamiec!Wczesne zalozenie!Moze wymagac zmiany
    void zmien_przynaleznosc(Gracz *inny);
    void pracuj();
    float zwroc_widocznosc();
    Gracz * zwroc_gracz();
    Budynek * zwroc_budynek();
    void ustaw_widocznosc(float);
    Typ zwroc_typ();
    int zwroc_obrone();

    protected :
    Typ typ;
    static ALLEGRO_BITMAP *bLas[3],*bGora[3],*bPole[3],*bPuste[3],*bHP;
    int zyznosc;
    int obrona; //max = 10
    Budynek *bud;
    Gracz *przynaleznosc; //def : = null
    friend class Mapa; //jest jej przyjacielem bo nim zarzadza.i tyle i pstro
    float widocznosc;

};


#endif
