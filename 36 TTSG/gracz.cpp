#include "gracz.h"
#include <allegro5/allegro_font.h>
#include "budynki.h"
#include "lista.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP* Gracz::gui = NULL;
ALLEGRO_BITMAP* Gracz::bZloto = NULL;
ALLEGRO_BITMAP* Gracz::bDrewno = NULL;
ALLEGRO_BITMAP* Gracz::bKamien = NULL;
ALLEGRO_BITMAP* Gracz::bPoparcie = NULL;
ALLEGRO_BITMAP* Gracz::bZolnierze = NULL;
ALLEGRO_BITMAP* Gracz::bRuch = NULL;

extern Audio audio;

extern ALLEGRO_FONT* font;
Gracz::Gracz(string n,ALLEGRO_COLOR kol, bool b) : nazwa(n),poparcie(50),zolnierze(10),zolnierzemax(10),bot(b),kolor_gracza(kol),x(0),y(0),PA(10),maxPA(10),
ilosc_budynkow{0,0,0,0,0,0,0,0},lis(NULL),cel(NULL)
{
    if(!gui)
    {
        gui = al_load_bitmap("GFX\\gui.bmp");
        bZloto = al_load_bitmap("GFX\\zarlo.bmp");
        al_convert_mask_to_alpha(bZloto,al_map_rgb(255,0,255));

        bDrewno = al_load_bitmap("GFX\\drewno.bmp");
        al_convert_mask_to_alpha(bDrewno,al_map_rgb(255,0,255));

        bKamien = al_load_bitmap("GFX\\kamien.bmp");
        al_convert_mask_to_alpha(bKamien,al_map_rgb(255,0,255));

        bPoparcie = al_load_bitmap("GFX\\poparcie.bmp");
        al_convert_mask_to_alpha(bPoparcie,al_map_rgb(255,0,255));

        bZolnierze = al_load_bitmap("GFX\\zolnierz.bmp");
        al_convert_mask_to_alpha(bZolnierze,al_map_rgb(255,0,255));

        bRuch = al_load_bitmap("GFX\\Ruch.bmp");
        al_convert_mask_to_alpha(bRuch,al_map_rgb(255,0,255));
    }
    surka.dodaj(100,100,100);
    //if(bot)
    //surka.dodaj(1000,1000,5000);
    poprzednia_zyw = surka.zywnosc;
}

void Gracz::wyswietl()
{
    al_draw_bitmap(gui,0,0,NULL);
    int szer= al_get_text_width(font , nazwa.c_str());
    al_draw_textf(font,al_map_rgb(0,0,0),400 - (szer)/2,2,NULL,"%s",nazwa.c_str());
    //zloto
    al_draw_bitmap(bZloto,0,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),35,10,NULL,"%d",surka.zywnosc);
    //drewno
    al_draw_bitmap(bDrewno,100,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),135,10,NULL,"%d",surka.drewno);
    //kamien
    al_draw_bitmap(bKamien,200,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),235,10,NULL,"%d",surka.kamien);
    //PA
    al_draw_bitmap(bRuch,400 + szer / 2 + 20,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),400 + szer / 2 + 55,10,NULL,"%d/%d",PA,maxPA);
    //popracie (po drugiej stronie)
    al_draw_bitmap(bPoparcie,550,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),585,10,NULL,"%d",poparcie);
    //zolnierze
    al_draw_bitmap(bZolnierze,650,0,NULL);
    al_draw_textf(font,al_map_rgb(0,0,0),685,10,NULL,"%d/%d",zolnierze,zolnierzemax);
    for(int i = 0;i < 8;i++)
    al_draw_textf(font,al_map_rgb(255,255,255),0,40 + i *15,NULL,"%d - %s",ilosc_budynkow[i],Budynek::nazwa(i).c_str());

    if(lis)
    lis->wyswietl();
}
// TODO (Damian#2#): TBD

void Gracz::operator +=(Surowce nowe)
{
    surka += nowe;
}

void Gracz::operator -=(Surowce nowe)
{
    surka -= nowe;
}

bool Gracz::operator <(Surowce nowe)
{
    if(surka < nowe) return true;return false;
}

bool Gracz::operator <=(Surowce nowe)
{
    if(surka <= nowe)return true;return false;
}

bool Gracz::operator >(Surowce nowe)
{
    if(surka > nowe) return true;return false;
}

bool Gracz::operator >=(Surowce nowe)
{

    if(surka >= nowe)return true;return false;
}

bool Gracz::isbot()
{
    return bot;
}
bool Gracz::czybot()
{
    return bot;
}

///funkcja powoduje dla gracz ruch klawiatura
///gdzie -> stad pobierze jaki klawisze sa wcisniete
///map - operacje na mapie
bool Gracz::ruch_klawiatura(Ekran &gdzie,Mapa &map,TextMaster&TM)
{
    static int ostatni = 0;
    int wymus = 0;
    if(!gdzie.keyboardb(ostatni))ostatni = 0;

    string tekst = (rand() % 2? "0" : "0");
    tekst = "build" + tekst;


    //wiem obrzydzilem w tej fukcji kod na maxa,wiesz co?Nie czytaj dalej :|
    if(gdzie.keyboardb(ALLEGRO_KEY_TAB) && ostatni != ALLEGRO_KEY_TAB)
    {
        ostatni = ALLEGRO_KEY_TAB;
        if(lis)
        {
            wymus = *lis;
            delete lis;
            lis = NULL;
        }
        else
        {
            int ile = 5;
            if(map[x + y * map.zwroc_szer()].zwroc_typ() == gory ||map[x + y * map.zwroc_szer()].zwroc_typ() == las || map[x + y * map.zwroc_szer()].zwroc_typ() == pole)
            ile = 1;
            lis = new Lista(ile);
            if(map[x + y * map.zwroc_szer()].zwroc_typ() == pole)
            lis->dodaj("Farma(6 PA)",Farma::cena(ilosc_budynkow[0]+1),1);
            else if (map[x + y * map.zwroc_szer()].zwroc_typ() == gory)
            lis->dodaj("Kopalnia(6 PA)",Kopalnia::cena(ilosc_budynkow[1]+1),2);
            else if(map[x + y * map.zwroc_szer()].zwroc_typ() == las)
            lis->dodaj("Tartak(6 PA)",Tartak::cena(ilosc_budynkow[2]+1),3);
            else
            {
            lis->dodaj("Koszary(6 PA)",Baraki::cena(ilosc_budynkow[3]+1),4);
            lis->dodaj("Zamek(10 PA)",Zamek::cena(ilosc_budynkow[4]+1),5);
            lis->dodaj("Wieza(4 PA)",Wieza::cena(ilosc_budynkow[5]+1),6);
            lis->dodaj("Gospoda(8 PA)",Gospoda::cena(ilosc_budynkow[6]+1),7);
            lis->dodaj("Kosciol(8 PA)",Kosciol::cena(ilosc_budynkow[7]+1),8);
            }
        }
    }
     if(gdzie.keyboardb(ALLEGRO_KEY_Q) && ostatni != ALLEGRO_KEY_Q)
    {
        ostatni = ALLEGRO_KEY_Q;
        if(lis)
        {
            delete lis;
            lis = NULL;
        }
    }
    if(lis)
    {
         if(gdzie.keyboardb(ALLEGRO_KEY_UP) && ostatni != ALLEGRO_KEY_UP) {*lis += (-1);ostatni = ALLEGRO_KEY_UP;}
        else if(gdzie.keyboardb(ALLEGRO_KEY_DOWN)&& ostatni != ALLEGRO_KEY_DOWN)   {*lis += (1);ostatni = ALLEGRO_KEY_DOWN;}
        return false;
    }

    if (gdzie.keyboardb(ALLEGRO_KEY_A) && ostatni != ALLEGRO_KEY_A)
    {
    if(map.graniczy(x,y,this) || map.wlasnosc(x,y) == this)
       {
           if(PA >= 2){
            if(map.atak(x,y,this,TM))
            {
            PA-=2;
            string tmp = "atak";
            tmp +=  char('0' + rand() % 6);
            audio.odtworz(tmp);
            }}

           else{
           TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,"Za malo PA!");
           audio.odtworz("cant");
           }
       }
       else
       {
       TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,"Nie graniczy!");
       audio.odtworz("cant");
        }
       ostatni = ALLEGRO_KEY_A;
    }

    //TARTAK
    //TARTAK
    else if((gdzie.keyboardb(ALLEGRO_KEY_3) && ostatni != ALLEGRO_KEY_3) || wymus == 3)
    {
     Tartak *nowy = new Tartak();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[2]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[2]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz(tekst);
     }

     else
     {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_3;
    }
    //KOPALNIA
    //KOPALNIA
    else if((gdzie.keyboardb(ALLEGRO_KEY_2) && ostatni != ALLEGRO_KEY_2) || wymus == 2)
    {
     Kopalnia *nowy = new Kopalnia();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[1]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[1]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz(tekst);
     }
     else
     {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
      ostatni = ALLEGRO_KEY_2;

    }

    //FARMA
    //FARMA
     else if((gdzie.keyboardb(ALLEGRO_KEY_1) && ostatni != ALLEGRO_KEY_1) || wymus == 1)
    {
     Farma *nowy = new Farma();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[0]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[0]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz(tekst);
     }

     else
      {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_1;
    }
    //KOSZARY
    //KOSZARY
    else if((gdzie.keyboardb(ALLEGRO_KEY_4) && ostatni != ALLEGRO_KEY_4) || wymus == 4)
    {
     Baraki *nowy = new Baraki();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[3]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[3]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz(tekst);
     }
     else
      {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_4;
    }
     //ZAMEK
     //ZAMEK
     else if((gdzie.keyboardb(ALLEGRO_KEY_5) && ostatni != ALLEGRO_KEY_5) || wymus == 5)
    {
     Zamek *nowy = new Zamek();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[4]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[4]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz("build1");
     }

     else
      {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_5;
    }
    //WIEZA
    //WIEZA
    else if((gdzie.keyboardb(ALLEGRO_KEY_6) && ostatni != ALLEGRO_KEY_6) || wymus == 6)
    {
     Wieza *nowy = new Wieza();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[5]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[5]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     audio.odtworz(tekst);
     }

     else
     {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_6;
    }
    //GOSPODA
    //GOSPODA
     else if((gdzie.keyboardb(ALLEGRO_KEY_7) && ostatni != ALLEGRO_KEY_7) || wymus == 7)
    {
     Gospoda *nowy = new Gospoda();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[6]+1);
     if(zwroc == "Zbudowane!")
     {
        ilosc_budynkow[6]++;
        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
        audio.odtworz(tekst);
     }

     else
      {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_7;
    }
    //KOSCIOL
    //KOSCIOL
     else if((gdzie.keyboardb(ALLEGRO_KEY_8) && ostatni != ALLEGRO_KEY_8) || wymus == 8)
    {
     Kosciol *nowy = new Kosciol();
     string zwroc;
     zwroc = nowy->zbuduj(map[y * map.zwroc_szer() + x],surka,*this,ilosc_budynkow[7]+1);
     if(zwroc == "Zbudowane!")
     {
        ilosc_budynkow[7]++;
        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
        audio.odtworz(tekst);
     }

     else
      {
    TM.zla_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
    delete nowy;
     }
    ostatni = ALLEGRO_KEY_8;
    }

    else if((gdzie.keyboardb(ALLEGRO_KEY_W) && ostatni != ALLEGRO_KEY_W)) //zburz
    {
    if(map[y*map.zwroc_szer() + x].zwroc_gracz() != this)
    TM.zla_wiadomosc(x*50+25,y*50 + 25,"To nie twoje pole");
    else if(!map[y*map.zwroc_szer() + x].zabudowane())
    TM.zla_wiadomosc(x*50+25,y*50 + 25,"Tu nie ma budynku");
    else
    {
        string zwroc =  map[y*map.zwroc_szer() + x].zwroc_budynek()->zburz();
        map[y*map.zwroc_szer() + x].zniszcz_budynek();
        TM.dobra_wiadomosc(x*50+25,y*50+25,zwroc);
        audio.odtworz("destroy");
    }
    ostatni = ALLEGRO_KEY_W;
    }


     else if(gdzie.keyboardb(ALLEGRO_KEY_ENTER) && ostatni != ALLEGRO_KEY_ENTER)
    {
        ostatni = ALLEGRO_KEY_ENTER;
        return true;
    }


    if(gdzie.keyboardb(ALLEGRO_KEY_UP) && ostatni != ALLEGRO_KEY_UP) {y--;ostatni = ALLEGRO_KEY_UP;}
    else if(gdzie.keyboardb(ALLEGRO_KEY_LEFT)&& ostatni != ALLEGRO_KEY_LEFT) {x--;ostatni = ALLEGRO_KEY_LEFT;}
    else if(gdzie.keyboardb(ALLEGRO_KEY_DOWN)&& ostatni != ALLEGRO_KEY_DOWN)   {y++;ostatni = ALLEGRO_KEY_DOWN;}
    else if(gdzie.keyboardb(ALLEGRO_KEY_RIGHT)&& ostatni != ALLEGRO_KEY_RIGHT)  {x++;ostatni = ALLEGRO_KEY_RIGHT;}


    if(x < 0)x = 0;
    if(x >= map.zwroc_szer()) x = map.zwroc_szer() - 1;
    if(y < 0)y = 0;
    if(y >= map.zwroc_wys()) y = map.zwroc_wys() - 1;
    if(wymus) ostatni = ALLEGRO_KEY_TAB; //ehh...
    return false;
}

int Gracz::zwroc_x()
{
    return (x*50) - 25;
}

int Gracz::zwroc_y()
{
    return (y * 50) - 25;
}

Marker* Gracz::zrob_marker()
{
mark = new Marker(x,y,kolor_gracza);
mark->kolor.a = 0.4;
return mark;
}

Marker* Gracz::zwroc_marker()
{
    return mark;
}

void Gracz::ustaw_poparcie(int i)
{
    poparcie = i;
}

void Gracz::dodaj_poparcie(int i)
{
    poparcie += i;
    if(poparcie > 100)poparcie = 100;
    if(poparcie <= 0)poparcie = 0;
}

void Gracz::ustaw_PA(int i)
{
    PA = i;
}

void Gracz::dodaj_PA(int i)
{
    PA += i;
    if(PA > maxPA) PA = maxPA;
    if(PA < 0) PA = 0;
}

void Gracz::dodaj_armie(int i)
{
    zolnierze += i;
    if(zolnierze > zolnierzemax) zolnierze = zolnierzemax;
    if(zolnierze < 0) zolnierze = 0;
}

void Gracz::odejmij_maxPA(int i)
{
    if(maxPA - i < 1)return;
    maxPA-=i;
}

int Gracz::zwroc_PA()
{
    return PA;
}

Surowce& Gracz::zwroc_surowce()
{
return surka;
}

void Gracz::dodaj_maxarmie(int co)
{
    zolnierzemax+=co;
    if(zolnierzemax < 1) zolnierzemax = 1;
}

void Gracz::dodaj_budynek(int ktory,int i)
{
    if(ktory < 0 || ktory >= 8)return;
    ilosc_budynkow[ktory]+=i;
}

void Gracz::usun_budynek(int i)
{
    ilosc_budynkow[i] -= 1;
    if(ilosc_budynkow[i] < 0)
    cout << "Wykryto niepoprawnosc dla ilosci budynkow,index budynku = " << i << endl;
}

bool Gracz::jedz(int ile)
{
    if(surka.zywnosc - ile < 0) return false;
    surka.zywnosc -= ile;
    return true;
}

void Gracz::ustaw_kamere(int _x,int _y)
{
    x = _x;
    y = _y;
}
