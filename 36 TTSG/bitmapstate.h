#ifndef bitmapstate_h_
#define bitmapstate_h_
#include "state.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


class BitmapState :public State
{
	public:
		BitmapState(int x,int y,int szer,int wys,ALLEGRO_BITMAP*);
		BitmapState(int x,int y,ALLEGRO_BITMAP*);
		~BitmapState();
		virtual int zwroc_szer();
		virtual int zwroc_wys();
		virtual void wyswietl();
	protected:
    ALLEGRO_BITMAP *grafika;
	private:
};


#endif // bitmapstate_h_

