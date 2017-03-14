#ifndef ekran_h_
#define  ekran_h_
#include <allegro5/allegro.h>
#include <string>
#include "audio.h"
using namespace std;

class Ekran
{
    public :
    Ekran(float LogicTime,float SoundTime,int ReturnButton =  ALLEGRO_KEY_ESCAPE,string tlo = "GFX\\tlo.bmp",Audio *audio=NULL);
    //logika i dzwiek
    bool Logika();
    bool Dzwiek();
    void ResetTimeL();
    void ResetTimeD();
    //rysowanie pracowanie
    void DrawClear();
    void Pracuj();
    bool Koniec();
    //stan myszki
    int mousex();
    int mousey();
    int mousez();
    int mousezo();
    int mouseb1();
    int mouseb2();
    //stan klawiatury
    bool keyboardb(int klawisz);
    ALLEGRO_KEYBOARD_STATE zwroc_klawiature();
    //myszka
    bool prosba_myszka();
    void zwolnij_myszke();
    void rezerwuj_myszke();
    //klawiatura
    bool prosba_klawiatura();
    void zwolnij_klawiature();
    void rezerwuj_klawiature();

    ~Ekran();

    protected :
    //timery
    float SoundTimeNow,SoundTimePrevious;
    float LogicTimeNow,LogicTimePrevious;
    float LogicTime,SoundTime;
    //rozne stany
    ALLEGRO_KEYBOARD_STATE stan_klawiatury;
    ALLEGRO_MOUSE_STATE stan_myszki;
    //klawisz wylaczajacy ekran
    int ReturnButton; // <--- do klawiatury
    ALLEGRO_BITMAP *tlo;
    bool uzywana_myszka,uzywana_klawiatura;
    int ost_kolko;bool sprawdzone;
    //dzwiek
    Audio *audio;




};

#endif
