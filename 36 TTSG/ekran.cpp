#include "ekran.h"
#include <iostream>
///konstruktor ekranu
///LT - Logic Time,czas po jakim logika zareaguje
///ST - Sound Time,czas po jakim dzwiek zareaguje
///RB - return button,guzik po ktorym funkcja sie wylaczy,domyslnie : ESCAPE
Ekran::Ekran(float LT,float ST,int RB,string t,Audio *aud) : LogicTime(LT),SoundTime(ST),ReturnButton(RB),audio(aud), //lista konstrukcyjna z argumentow
LogicTimeNow(al_get_time()),LogicTimePrevious(0.0),SoundTimeNow(al_get_time()),SoundTimePrevious(0.0) // lista konstrukcyjna bez uzycia aergumentow
{
    cout << "Inicjalizuje ekran" << endl;
    al_get_keyboard_state(&stan_klawiatury);
    al_get_mouse_state(&stan_myszki);
    tlo = al_load_bitmap(t.c_str());
    uzywana_myszka = false;
    uzywana_klawiatura = false;
    if(!tlo)
    cout << "Blad z inicjalizacja tla! Nie znaleziono : " << t << endl;
    ost_kolko = al_get_mouse_state_axis(&stan_myszki,2);
}

///zwraca true jesli uplynal czas (LogicTime),w przeciwnym wypadku false
bool Ekran::Logika()
{
    if(LogicTimeNow - LogicTimePrevious > LogicTime)
    return true;return false;
}

///Zwraca true jesli uplynal czas(SoundTime), w przeciwnym wypadku false
bool Ekran::Dzwiek()
{
    if(SoundTimeNow - SoundTimePrevious > SoundTime)
    return true;return false;
}

///zwraca true jesli klawisz (ReturnButton) zostanal wcisniety,w przeciwnym wypadku FALSE
bool Ekran::Koniec()
{
    if(al_key_down(&stan_klawiatury,ReturnButton))
    return true;return false;
}

///'resetuje',tak naprawde ustawia timer poprzedniej logiki na terazniejszy,dajac LogicTime czasu do nastepnego Logika()
void Ekran::ResetTimeL()
{LogicTimePrevious = LogicTimeNow;}

///'resetuje',tak naprawde ustawia timer poprzedniego dzwieku na terazniejszy,dajac LogicTime czasu do nastepnego Dzwiek()
void Ekran::ResetTimeD()
{SoundTimePrevious = SoundTimeNow;}

///wykonuje elementarne operacje dla ekranu
void Ekran::Pracuj()
{
    al_get_keyboard_state(&stan_klawiatury);
    al_get_mouse_state(&stan_myszki);


    LogicTimeNow = al_get_time();
    SoundTimeNow = al_get_time();

}

///zwraca os x myszki
int Ekran::mousex()
{
return al_get_mouse_state_axis(&stan_myszki,0);
}

///zwraca os y myszki
int Ekran::mousey()
{
return al_get_mouse_state_axis(&stan_myszki,1);
}

///zwraca stan kolka myszki
int Ekran::mousez()
{
        float zwroc = al_get_mouse_state_axis(&stan_myszki,2);
        ost_kolko = al_get_mouse_state_axis(&stan_myszki,2);
        return zwroc;

}

///zwraca stan kolka myszki(ostatnie poruszenie)
int Ekran::mousezo()
{
        float zwroc = al_get_mouse_state_axis(&stan_myszki,2) - ost_kolko;
        ost_kolko = al_get_mouse_state_axis(&stan_myszki,2);
        return  zwroc;
}

///zwraca button1 myszki
int Ekran::mouseb1()
{
return al_mouse_button_down(&stan_myszki,1);
}

///zwraca button2 myszki
int Ekran::mouseb2()
{
return al_mouse_button_down(&stan_myszki,2);
}

///zwraca klawisz klawiatury
bool Ekran::keyboardb(int klawisz)
{
    return al_key_down(&stan_klawiatury,klawisz);
}

///rysuje na backbuffor oraz potem rysuje na buforze tlo o danym kolorze
void Ekran::DrawClear()
{
    al_flip_display();
    if(tlo)
    al_draw_bitmap(tlo,0,0,NULL);
}

///ekran zwraca true jesli jakis obiekt moze uzyc myszki
bool Ekran::prosba_myszka()
{
    if(uzywana_myszka) return false;
    return true;
}

///jakis program przestaje uzywac myszki
void Ekran::zwolnij_myszke()
{
    uzywana_myszka = false;
}

///rezerwuje myszke
void Ekran::rezerwuj_myszke()
{
    uzywana_myszka = true;
}

///destruktor (usuwa tlo)
Ekran::~Ekran()
{
    al_destroy_bitmap(tlo);
}

///zawraca nam cale dane klawiatury(jako kopie),na wypadek gdyby ktos chcial kopie klawiatury na dany moment
ALLEGRO_KEYBOARD_STATE Ekran::zwroc_klawiature()
{
return stan_klawiatury;
}

///ekran zwraca true jesli obiekt moze uzyc klawiatury
bool Ekran::prosba_klawiatura()
{
    if(uzywana_klawiatura)return false;
    return true;
}

///jakis obiekt przestaje uzywac klawiatury
void Ekran::zwolnij_klawiature()
{
    uzywana_klawiatura = false;
}

///rezerwujemy klawaitura
void Ekran::rezerwuj_klawiature()
{
    uzywana_klawiatura = true;
}

