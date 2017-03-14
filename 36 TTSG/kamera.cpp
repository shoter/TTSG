#include "kamera.h"
#include <iostream>
using namespace std;
#include <cmath>
extern float bezwzgledna(float liczba);

Kamera::Kamera(float _x,float _y):x(_x),y(_y)
{}

///ustawia kamere na wybranej pozycji
void Kamera::ustaw(float _x,float _y)
{
    x = _x;
    y = _y;
}

///przesuwa kamere gladkim ruchem od miejsca w ktorym sie znajduje do
///miejsce wskazanego przez wspolrzedne funkcji z dana szybkoscia.
void Kamera::smooth(float x2,float y2,float speed)
{

    float sx,sy;
    float odlx = x2 - x;
    float odly = y2 - y;
    float odl = sqrt(pow(odlx,2) + pow(odly,2));
    float podobienstwo = odl / speed;
    if(podobienstwo == 0)
    {
        sx = 0;sy =0; //pamietaj CHOLERO nie dziel przez ZERO!
    }
    else {
    sx = odlx / podobienstwo;
    sy = odly / podobienstwo;
    }
    if(bezwzgledna(podobienstwo) > 1.0)
    {
    x += sx;
    y += sy;
    }
    else
    {
    x = x2;
    y = y2;
    }

    //cout << x << " += " << sx << "  i   " << y << " += " << sy << endl;
}

///ustawia kamera na wybranej pozycji i potem smooth move do danego miejsca
///dziala jak ustaw + smooth
void Kamera::smooth(float _x1,float _y1,float _x2,float _y2,float speed)
{
    ustaw(_x1,_y1);
    smooth(_x2,_y2,speed);
}

///pracuje nad smooth movem,w innym wypadku nic nie robi
void Kamera::pracuj()
{
}

///przesuwa kamere
void Kamera::przesun(float _x,float _y)
{
    x += _x;
    y += _y;

}

float Kamera::przek_x(float _x)
{
    return _x + -x;
}
float Kamera::przek_y(float _y)
{
    return _y + -y;
}

