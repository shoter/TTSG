#include "audio.h"
#include <iostream>
using namespace std;
Audio::Audio()
{

}

//inicjuje dŸwiêk w allegro
void Audio::init()
{
    al_install_audio();
    al_init_acodec_addon();
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(mixer, voice);

}

int Audio::odtworz(ALLEGRO_SAMPLE *dzwiek)
{
    ALLEGRO_SAMPLE_INSTANCE *nowy= al_create_sample_instance(NULL);
    al_set_sample(nowy, dzwiek);
    if(!al_attach_sample_instance_to_mixer(nowy, mixer))
    cout << "Atach sie nie udal" << endl;
    al_play_sample_instance(nowy);
    sample += nowy;
    return(sample.size() -1);
}

bool Audio::dodaj(string sciezka,string nazwa)
{
    for(int i = 0;i < sDzwieki.size();i++)
    if(*sDzwieki[i] == nazwa)
    {
        cout << "Audio::dzwiek " << nazwa << " juz istnieje!" << endl;
        return false;
    }

    //dzwieku nie ma w bazie danych,dodajemy :)
    string *wieczny = new string(nazwa);
    sDzwieki += wieczny;
    ALLEGRO_SAMPLE *samp;
    samp = al_load_sample(sciezka.c_str());
    aDzwieki += samp;

    if(sDzwieki.size() != aDzwieki.size()) cout << "Audio::blad! s != a" << endl; //s != a
    //chociaz up byl bledem,sam jednak blednego dodania nie powodowal,przeciez wszystko sie dodalo :),ale uzytkownik jest ostrzezony o tym fakcie!
    //mam nadzieje ze ci idioci ktorzy beda grali w ta gre chociaz powiedza jesli bledy beda wyskakiwac.
    //jesli ogladasz kod to sorry za up
    //ale i tak nim jestes
    return true;
}

int Audio::odtworz(string ktory)
{
    for(int i= 0;i < sDzwieki.size();i++)
    if(ktory == *sDzwieki[i])
    {

        return odtworz(aDzwieki[i]); //koniec :)
    }
    return -1;
}

int Audio::pracuj()
{
    if(al_get_sample_instance_playing(podklad) == false)
    {
    if(!al_attach_sample_instance_to_mixer(podklad, mixer))
    cout << "Atach sie nie udal" << endl;
    al_play_sample_instance(podklad);
    }
    for(int i =0;i < sample.size();i++)
        if(al_get_sample_instance_playing(sample[i]) == false)
        {
        al_detach_sample_instance(sample[i]);
        sample -= i;
        return i;
        }
        return -1;
}

void Audio::dodaj_podklad(ALLEGRO_SAMPLE *sound)
{
     podklad= al_create_sample_instance(NULL);
    al_set_sample(podklad, sound);
    if(!al_attach_sample_instance_to_mixer(podklad, mixer))
    cout << "Atach sie nie udal" << endl;
    al_play_sample_instance(podklad);
}

void Audio::dodaj_podklad(string ktory)
{
    for(int i= 0;i < sDzwieki.size();i++)
    if(ktory == *sDzwieki[i])
    {

        dodaj_podklad(aDzwieki[i]); //koniec :)
    }
}
