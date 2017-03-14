#include <cmath>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>



bool  kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2)
{
     if(x1 >= x2 && y1 >= y2 && x1 <= x2 + s2 && y1 <= y2 + w2) return true;else
     if(x1 + s1 >= x2 && y1 >= y2 && x1 + s1 <= x2 + s2 && y1 <= y2 + w2)return true;else
     if(x1 >= x2 && y1 + w1 >= y2 && x1 <= x2 + s2 && y1 + w1 <= y2 + w2)return true;else
     if(x1 + s1 >= x2 && y1 + w1 >= y2 && x1 + s1 <= x2 + s2 && y1 + w1 <= y2 + w2)return true;
     return false;
};


float bezwzgledna(float liczba)
{
    if(liczba < 0) return -liczba;
    return liczba;
}
float plus_minus(float liczba)
{
    if(liczba >= 0) return 1.0;
    return -1.0;

}

float odleglosc(float x1,float y1,float x2,float y2)
{
    float zwroc = sqrt(pow((float)x1 -(float)x2,2) + pow((float)y1 - (float)y2,2));
    return zwroc;
}

///http://forum.warsztat.gd/index.php?topic=15082.0
///zabralem stamtad,moj poziom wiedzy nie chce tego ogarnac.kiedys to przestudiuje
///przepraszam cie autorze tego algorytmu!
float DegLength(float fAlfa, float fBeta) {
	float fLen = fabs(fAlfa - fBeta);

	fAlfa -= 2 * ALLEGRO_PI;
	if(fAlfa < -ALLEGRO_PI)  fAlfa += 4 * ALLEGRO_PI;
	if(fabs(fAlfa - fBeta) < fLen) fLen = fabs(fAlfa - fBeta);

	return ALLEGRO_PI - fLen;
}

float DegLength360(float fAlfa, float fBeta) {
	float fLen = fabs(fAlfa - fBeta);

	fAlfa -= 360;
	if(fAlfa < -180) { fAlfa += 720; }
	if(fabs(fAlfa - fBeta) < fLen) { fLen = fabs(fAlfa - fBeta); }

	return fLen;
}

float Flinia(float x,float y,float dlug,float kat,ALLEGRO_COLOR kolor=al_map_rgb(0,0,0))
{
    float x2 = cos(kat) * dlug + x;
    float y2 = sin(kat) * dlug + y;
    al_draw_line(x,y,x2,y2,kolor,3);
}

float azymut(float kat)
{
    return kat - ALLEGRO_PI / 2;
}


