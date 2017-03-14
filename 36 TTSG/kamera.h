#ifndef kamera_h_
#define kamera_h_
#define RET_VAR(nazwa,typ,fun) typ fun() { return nazwa ; }


class Kamera
{
    public :
    Kamera(float x=0,float y=0);
    void ustaw(float x2,float y2); //bez smooth move.natychmiastowe przeniesienie
    void smooth(float x2,float y2,float speedx); //z smooth move,przeniesienie z biezacej pozycji do innej
    void smooth(float x1,float y1,float x2,float y2,float speed); //natychmiastowe przeniesienie a potem smooth move do nastepnej pozycji
    void przesun(float x,float y); //przesuwa kamere wedlug podanych wspolrzednych(PRZESUWA!!!NIE USTAWIA!!)
    float przek_x(float x); //przeksztalc X
    float przek_y(float y);  // -''- Y
    void pracuj();
    RET_VAR(x,float,zwroc_x);
    RET_VAR(y,float,zwroc_y);

    protected :
    float x, y; //biezace wspolrzedne kamery


};
#endif
