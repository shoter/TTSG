#ifndef budynek_h_
#define budynek_h_
#include <string>
#include "pole.h"
#include "surowce.h"
#include "gracz.h"
using namespace std;
class Pole;
class Gracz;
class Mapa;
class Budynek
{
  public :
  Budynek(); //P - pole,p - puste
  ~Budynek();
  virtual void wyswietl(int x,int y);
  virtual void wyswietl(int x,int y,Kamera &kam);
  virtual void pracuj(int zyznosc,Gracz &Gr);
  virtual string zbuduj(Pole &gdzie,Surowce &sur,Gracz &ktory,int mnoznik = 1);
  virtual string zburz();//ustawia ze zniszczony
  virtual bool zburz(Pole *gdzie,Gracz *ktory); //nisczy doszczetnie
  virtual void przejete(Pole *gdzie,Gracz *stary,Gracz *nowy);
  virtual string nazwa();
  static string nazwa(int);
  static Surowce cena(int moznik = 1);

  bool zwroc_zburz();
  protected :
  static ALLEGRO_BITMAP *grafika;
  static Typ *wymagania; //max 4
  static int il_wym;
  static Surowce koszt;
  static string nazwy_budynkow[8]; //wszystko ulozone tak jak na klawie od 1-8,patrz t¹ kartke!
  bool zburzony;

};

#endif
