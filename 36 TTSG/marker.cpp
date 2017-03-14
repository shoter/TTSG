#include "marker.h"
Marker::Marker(int _x,int _y,ALLEGRO_COLOR k) :x(_x),y(_y),kolor(k)
{}
Marker::Marker() :x(0),y(0),kolor(al_map_rgb(0,0,0))
{}
