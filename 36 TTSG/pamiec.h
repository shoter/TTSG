#ifndef pamiec_h_
#define pamiec_h_
template <class typ>
class Pamiec
{
    public:
    Pamiec(int prawdziwa = 32,bool us = true);
    ~Pamiec();
    typ* operator[](int i);
    void operator += (typ*);
    void operator -=(int i);
    void operator -=(typ*);
    int size();
    int capacity();
    int rozmiar();
    int prawdziwy_rozmiar(); //2 wersje jezykowe,wow
    void clear();

    protected :
    int ilosc,prawdziwa_ilosc;
    typ **pam;
    bool usuwanie; //pamieci

};

template <class typ>
Pamiec<typ>::Pamiec(int prawdziwa,bool us) :ilosc(0),prawdziwa_ilosc(prawdziwa),usuwanie(us)
{
    pam = new typ*[prawdziwa_ilosc];
}

template <class typ>
Pamiec<typ>::~Pamiec()
{
    delete []pam;
}

template <class typ>
typ * Pamiec<typ>::operator [](int i)
{
    if(i < 0 || i >= ilosc) return 0;
    return pam[i];
}

template <class typ>
void Pamiec<typ>::operator +=(typ* nowy)
{
    if(ilosc == prawdziwa_ilosc)
    {
        prawdziwa_ilosc *= 2;
        typ **temp = new typ*[ilosc];
        for(int i =0;i < ilosc;i++)
        temp[i] = pam[i];
        delete [] pam;
        pam = new typ*[prawdziwa_ilosc];
        for(int i = 0;i < ilosc;i++)
        pam[i] = temp[i];
        delete []temp;
    }
    pam[ilosc] = nowy;
    ilosc++;
}

template <class typ>
void Pamiec<typ>::operator -=(int co)
{
    typ *temp = pam[co];
    for(int i = co;i < ilosc - 1;i++)
    pam[i] = pam[i+1];
    if(usuwanie)
    delete temp;
    ilosc--;
}

///funkcja ta poszukuje obiektu z tym samym adresem,jesli go znajdzie to go usuwa
template <class typ>
void Pamiec<typ>::operator-=(typ *co)
{
    for(int i = 0;i < ilosc;i++)
    if(pam[i] == co)
    {
    *this-=i;
    break;
    }
}
template <class typ>
int Pamiec<typ>::size()
{ return ilosc; }

template <class typ>
int Pamiec<typ>::rozmiar()
{ return ilosc; }

template <class typ>
int Pamiec<typ>::capacity()
{ return prawdziwa_ilosc; }

template <class typ>
int Pamiec<typ>::prawdziwy_rozmiar()
{ return prawdziwa_ilosc; }

template <class typ>
void Pamiec<typ>::clear()
{
    for(int i = 0;i < ilosc;i++)
    delete pam[i];
    ilosc=0;
}

#endif // pamiec_h_

