#include "changestate.h"
#include "ekran.h"
#include "state.h"
extern bool  kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2);
ChangeState::ChangeState(int _x,int _y,int _szer,int _wys,int _ilosc) :x(_x),y(_y),szer(_szer),wys(_wys),stany(_ilosc),ilosc(_ilosc),wcisniety(false),wczesniej(false),aktualny(0)
{}

///Pracuje na podanym ekranie z jego uk³adem myszka/klawiatura
///Przyjmuje sie ¿e
///1 klikniecie = 1 zmiana stanu,po zmianie nalezy zwolnic przycisk myszy , co zwolni dostep do ekranu innym funkcjom korzystajacym z myszy
void ChangeState::pracuj(Ekran &gdzie)
{
    bool button =  gdzie.mouseb1(); //buton myszki ofc,nie nawiazuje tu do klasy Button
    int mx = gdzie.mousex();
    int my = gdzie.mousey();
    if(wczesniej && button == false)
    {
        wczesniej = false;
        gdzie.zwolnij_myszke();
        return;
    }
    else if(wczesniej)
    return;
    // wczesniej == false od tego momentu na 100%
    if(!button) return;
    if(!gdzie.prosba_myszka())return;
    //button == true
    if(kolizja(mx,my,1,1,x,y,szer,wys))
    {
        gdzie.rezerwuj_myszke();
        wczesniej = true;
        aktualny++;
        if(aktualny >= ilosc) aktualny = 0;
    }
}

void ChangeState::wyswietl()
{

    stany[aktualny]->wyswietl();
}

void ChangeState::operator +=(State *nowy)
{
    stany += nowy;
}

ChangeState::operator int()
{
    return aktualny;
}
