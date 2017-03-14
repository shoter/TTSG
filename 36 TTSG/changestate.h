#ifndef changestate_h_
#define changestate_h_
#include "pamiec.h"
class State;class Ekran;
///Klasa sluzy do tego aby zmieniac stan danego przycisku poprzez klikniecie na niego,sluzy np do zmiany kolorow :)
///Klasa nie ma zadnego powiazania z Button
class ChangeState
{
	public:
		ChangeState(int x,int y,int szer,int wys,int ilosc);
        void operator +=(State *stan);
        void pracuj(Ekran &gdzie);
        void wyswietl();
        operator int();
	protected:
	int x,y;
	int szer,wys;
	Pamiec<State> stany;
    int ilosc,aktualny;
    bool wcisniety;
    bool wczesniej; //stan wcisniety wczesniej

};


#endif // changestate_h_

