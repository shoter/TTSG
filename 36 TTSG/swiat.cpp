#include "swiat.h"
#include "marker.h"
#include <string>
using namespace std;
extern Audio audio;

Swiat::Swiat() :rozpoczeta(false),ini_map(false),ini_players(false),map(NULL),gracze(5),ktory_gracz(0)
{

}

bool Swiat::start()
{

    if(!ini_map)return false;
    if(!ini_players)return false;
    if(gracze.size() < 1)return false;
    ktory_gracz = 0;
    rozpoczeta = true;
    map->oblicz_fog(gracze[ktory_gracz]);
    return true;
}


///inicjalizuje mape swiata z podana szerokoscia i wysokoscia
///w przypadku gdy mapa jest juz zainicjlizowana,stara jest usuwana z pamieci
void Swiat::inicjalizuj_mape(int szx,int szy)
{

    if(rozpoczeta)return;
    if(ini_map)
    {
        delete map;
    }
    map = new Mapa(szx,szy);
    map->generuj();
    ini_map = true;
}

void Swiat::operator +=(Gracz *nowy)
{
    gracze += nowy;
    ini_players = true;
}

Pamiec<Gracz> Swiat::zwroc_graczy()
{
    return gracze;
}

void Swiat::wyswietl_min_mape(int x,int y,int w)
{
    if(!ini_map)return;
    map->wyswietl_miniature(x,y,w);
}

void Swiat::koniec_tury()
{
    if(ktory_gracz < gracze.size())return;
    for(int i = 0;i < gracze.size();i++)
    {
    gracze[i]->dodaj_PA(8);
    }
    map->koniec_tury();
    ktory_gracz = 0;

}

Mapa* Swiat::zwroc_mape()
{
    return map;
}

void Swiat::pracuj(Ekran &gdzie,TextMaster &TM)
{
    if(ktory_gracz >= gracze.size())koniec_tury();
    if(gracze[ktory_gracz]->isbot())
    {
        gracze[ktory_gracz]->ruch_bota(*map,TM);
        ktory_gracz++;
        koniec_tury();
        nastepna_tura(TM);

    }
    else //nie jest botem
    {

        if(gracze[ktory_gracz]->ruch_klawiatura(gdzie,*map,TM))
        {
            Marker *mark = gracze[ktory_gracz]->zwroc_marker();
            if(mark) *map -= mark;
         ktory_gracz++;
         koniec_tury();
         nastepna_tura(TM);
        }
    }
}

void Swiat::ruch_mapa(bool bot)
{
    if(!rozpoczeta) return;
    if(!bot && gracze[ktory_gracz]->isbot()) return;
    Marker *mark = gracze[ktory_gracz]->zwroc_marker();
    if(mark) *map -= mark;
    mark = gracze[ktory_gracz]->zrob_marker();
    *map += mark;
    map->smooth(gracze[ktory_gracz]->zwroc_x() - 350 ,gracze[ktory_gracz]->zwroc_y() - 250,5);
}

bool Swiat::wyswietl_mape(bool bot,TextMaster &TM)
{
    if(!rozpoczeta) return false;
    if(gracze[ktory_gracz]->isbot())
        {
        return true;
        map->wyswietl(gracze[ktory_gracz]->retx(),gracze[ktory_gracz]->rety(),gracze[ktory_gracz]);
        gracze[ktory_gracz]->wyswietl();
        return true;
        }
    al_clear_to_color(al_map_rgb(20,20,20));
    map->wyswietl(gracze[ktory_gracz]->retx(),gracze[ktory_gracz]->rety(),gracze[ktory_gracz]);
    TM.wyswietl(*kamera());
    gracze[ktory_gracz]->wyswietl();
    //po wyswietleniu mazemy markery :)
    return false;
}

Kamera* Swiat::kamera()
{
    return map->zwroc_kamere();
}

void Swiat::nastepna_tura(TextMaster &TM)
{
    if(!gracze[ktory_gracz]->isbot())
    {
    map->oblicz_fog(gracze[ktory_gracz]);
    map->fog_off();
    map->ustaw_kamere(gracze[ktory_gracz]->zwroc_x() - 350,gracze[ktory_gracz]->zwroc_y() - 250 );
    audio.odtworz("turn");
    }
    else
    {
    map->oblicz_fog(gracze[ktory_gracz]);
    }
    TM.clear();

}
