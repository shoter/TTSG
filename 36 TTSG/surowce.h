#ifndef surowce_h_
#define surowce_h_

struct Surowce
{
    Surowce();
    Surowce(int k,int d,int z);
    Surowce operator +=(Surowce &inne);
    Surowce dodaj(int k,int d,int z);
    Surowce operator -=(Surowce &inne)
    ;
    Surowce odejmij(int k,int d,int z);
    Surowce operator *(int);
    Surowce operator *=(int);

    bool operator >=(Surowce &inne);
    bool operator >(Surowce &inne);
    bool operator <=(Surowce &inne);
    bool operator <(Surowce &inne);
    bool operator == (Surowce &inne);
    int kamien,drewno,zywnosc;
};

#endif // surowce_h_

