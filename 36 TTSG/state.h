#ifndef state_h_
#define state_h_

class State
{
    public :
    State(int x,int y,int szer,int wys);
    virtual void wyswietl()=0;
    virtual int zwroc_szer()=0;
    virtual int zwroc_wys()=0;
    protected :
    int x,y,szer,wys;

};

#endif // state_h_

