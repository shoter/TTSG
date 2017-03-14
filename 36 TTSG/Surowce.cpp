#include "surowce.h"
Surowce::Surowce()
{
    kamien = drewno = zywnosc = 0; //<3 kaskadowoœæ
}

Surowce::Surowce(int k,int d,int z)
{
    kamien = k;
    drewno = d;
    zywnosc = z;
}

Surowce Surowce::operator +=(Surowce &inne)
{
    kamien += inne.kamien;
    drewno += inne.drewno;
    zywnosc += inne.zywnosc;
    return *this;
}

Surowce Surowce::operator -=(Surowce &inne)
{
 kamien -= inne.kamien;
 drewno -=  inne.drewno;
 zywnosc -= inne.zywnosc;
 return *this;
}

Surowce Surowce::dodaj(int k,int d,int z)
{
    Surowce sur(k,d,z);
    *this +=  sur;
}
Surowce Surowce::odejmij(int k,int d,int z)
{
    Surowce sur(k,d,z);
    *this -=  sur;
}

bool Surowce::operator >=(Surowce &inne)
{

    if(kamien >= inne.kamien)
    if(drewno >= inne.drewno)
    if(zywnosc >= inne.zywnosc) return true;
    return false;
}

bool Surowce::operator >(Surowce &inne)
{

    if(kamien > inne.kamien)
    if(drewno > inne.drewno)
    if(zywnosc > inne.zywnosc) return true;
    return false;
}

bool Surowce::operator <=(Surowce &inne)
{
    if(inne.kamien >= kamien)
    if(inne.drewno >= drewno)
    if(inne.zywnosc >= zywnosc) return false;
    return true;
}

bool Surowce::operator <(Surowce &inne)
{
    if(inne.kamien > kamien)
    if(inne.drewno > drewno)
    if(inne.zywnosc > zywnosc) return true;
    return false;
}

bool Surowce::operator ==(Surowce &inne)
{
    if(inne.kamien == kamien)
    if(inne.drewno == drewno)
    if(inne.zywnosc == zywnosc)
    return true;return false;
}

Surowce Surowce::operator *=(int i)
{
    kamien *=i;
    drewno *=i;
    zywnosc *=i;
    return *this;
}

Surowce Surowce::operator *(int i)
{
    Surowce zwroc = *this;
    zwroc.kamien *=i;
    zwroc.drewno *=i;
    zwroc.zywnosc *=i;
    return zwroc;
}


