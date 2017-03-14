#ifndef textmaster_h_
#define textmaster_h_
#include "text.h"
#include "pamiec.h"
#include "kamera.h"
class TextMaster
{
    public :
    TextMaster(int prawdziwa = 32);
    void wyswietl(Kamera &kam);
    void pracuj();
    void operator +=(Text *nowy);
    void operator -=(int i);
    Text* operator [](int i);
    void dobra_wiadomosc(int x,int y,string wiad);
    void zla_wiadomosc(int x,int y,string wiad);
    void neutralna_wiadomosc(int x,int y,string wiad);
    int size();
    void clear();

    protected :
    Pamiec<Text> napisy;
    Pamiec<Text> czekaj;
    int cooldown;
    static int max_cooldown;

};

#endif // textmaster_h_

