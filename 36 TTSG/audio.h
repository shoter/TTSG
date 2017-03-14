#ifndef audio_h_
#define audio_h_
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "pamiec.h"
#include <string>
using namespace std;

class Audio
{
    public:
    Audio();
    void init();
    int odtworz(ALLEGRO_SAMPLE *sound);
    bool dodaj(string sciezka,string nazwa);
    int odtworz(string);
    void dodaj_podklad(ALLEGRO_SAMPLE *sound);
    void dodaj_podklad(string);
    int pracuj(); //int melduje jaka muzyka zostala usunieta
    protected :
    ALLEGRO_VOICE *voice;
    ALLEGRO_MIXER *mixer;
    Pamiec<ALLEGRO_SAMPLE_INSTANCE> sample;
    Pamiec<ALLEGRO_SAMPLE> aDzwieki; //taka biblioteka dzwiekow
    Pamiec<string> sDzwieki; //odpowiedniki biblioteki w stringu
    ALLEGRO_SAMPLE_INSTANCE *podklad;

};

#endif
