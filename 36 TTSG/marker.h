#ifndef marker_h_
#define marker_h_
#include <allegro5/allegro.h>

struct Marker
{
	public:
    Marker(int x,int y,ALLEGRO_COLOR kolor);
    Marker();
	int x,y;
	ALLEGRO_COLOR kolor;
};


#endif // marker_h_

