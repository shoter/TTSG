#include "gracz.h"
#include "budynki.h"
#include <iostream>
using namespace std;
#define DEBUG 1

char mozna_otoczyc(Gracz *kto,Pole *ktore,Mapa &gdzie);
///n - nie,g - gora,d - dol,l - lewo,p - prawo

void Gracz::ruch_bota(Mapa &map,TextMaster&TM)
{
dodaj_PA(2); //bot ma buffa 2 do PA zeby zamki mogl stawiac
Pamiec<Pole> wrog(20); //moze byc puste
Pamiec<Pole> nieuzyte[3];//podzielone ze wzgledu na zyznosc(przejete bez budynkow)
Pamiec<Pole> nic; //ziemia pusta(NIE GORY,NIE LASY,NIE POLA)
Pamiec<Pole> obok[3]; //podzielone ze wzgledu na zyznosc(do zajecia)
Pamiec<Pole> granica; //jesli pole graniczy z polem ktorego wlasciciel != NULL i != this
Pamiec<Pole> graniczace; //bez wzgledu na to czy wrog czy nie,uzywane do otaczania
bool Nlas=false,Npole=false,Ngora=false; //czy jest nieuzty las , pole , gora
bool glod = false;
if(surka.zywnosc <= 10) glod = true;
if(poprzednia_zyw - surka.zywnosc > 0) glod = true;

///jak widac pola z budynkami nas nie interesuja,sa juz zagospodarowane , co chciec wiecej?
///schemat dzialania bota
/*
1.sprawdzenie czy sa jakies nieuzytki 3 poziomu zyznosc,staraj sie cos zbudowac tam za WSZELKA CENE(no chyba ze ilosc takiego budynku >= 6
2.jesli byl jakis i nie bylo kasy to podejmij decyzje czy zbierac peiniadze(nie budowac innych budnkow) czy budowac budynki na zyznosci < 3
3.Jesli ilosc budynkow gospodarczych kazdego typu > 3 to mozna atakowac(ale to potem :D),jesli sa jakies wyjatki to tez mozna atakowac o ile nie ma
miejsc do zbudowania takich budnykow.Jesli sa to bot stara sie je najpierw zbudowac,tak zeby bylo minimum 3
4.Bot nie buduje farm 1szego poziomu zyznosci.Chyba ze istnieje glod w panstwie.Wtedy wykorzystuje wszystko na to
4.5 (dopisane) . Jesli surowce na koszary i ilosc_koszar <= 4 + ilosc_zamkow / 2 to buduj koszary
5.Jesli surowce na Zamek sa to zbudowac
6.Jesli surowce na Gospode/Kosciol sa to zbudowac
7.Jesli gospoda + Kosciol > 4 to narazie ich nei budujemy
8.
    PETLA
    <
    8.Brak PA?Przerwij petle (Pa >= 2 by kontynuwac petle)
    9.jesli jest jakies pole wroga ktore mozna otoczyc to otaczamy!
    10.Jak by³o to wróc do 9.
    11.Nie ma nic do otoczenia?Jeb losowo w kazde miejsce gdzie mozesz wroga uderzyc,a raczej atakuj jakis teren dopoki starczy PA.
    12.Jesli Teren przejety i PA >= 2 to ufortyfikuj PA / 2 gdzie PA / 2 <= 3
    13.Powtarzaj od 8.
    >
14.Jesli zostalo PA i WOJSKO to fortyfikuj swoje pola,fortyfikuj tylko granice
*/


for(int i = 0;i < map.zwroc_szer() * map.zwroc_wys();i++)
{
     if(map[i].zwroc_gracz() != this  && map[i].zwroc_widocznosc()) //pole JEST NIE MOJE!
    {
        if(map.graniczy(map.index_pola(&map[i]),this))
        graniczace += &map[i];
    }

    if(map[i].zwroc_gracz() != this && map[i].zwroc_gracz() == NULL && map[i].zwroc_widocznosc()) //pole nie jest gracza,nie jest wroga
    {
        if(map.graniczy(map.index_pola(&map[i]),this))
        obok[map[i]-1] += &map[i];
    }
    else if(map[i].zwroc_gracz() != this && map[i].zwroc_gracz() != NULL && map[i].zwroc_widocznosc()) //pole JEST WROGA!
    {
        if(map.graniczy(map.index_pola(&map[i]),this))
        wrog += &map[i];
    }
    else if(map[i].zwroc_gracz() == this)
    {
        if(map[i].zwroc_budynek() == NULL)
        {
        if(map[i].zwroc_typ() != puste)
        nieuzyte[map[i]-1]  += &map[i];
        else
        nic += &map[i];
        if(map[i].zwroc_typ() == las) Nlas = true;
        if(map[i].zwroc_typ() == gory)Ngora = true;
        if(map[i].zwroc_typ() == pole)Npole = true;
        }
    if(map[i - map.zwroc_szer()].zwroc_gracz() != NULL || map[i - map.zwroc_szer()].zwroc_gracz() != this ||
       map[i + map.zwroc_szer()].zwroc_gracz() != NULL || map[i + map.zwroc_szer()].zwroc_gracz() != this ||
       map[i + 1].zwroc_gracz() != NULL || map[i + 1].zwroc_gracz() != this ||
       map[i - 1].zwroc_gracz() != NULL || map[i - 1].zwroc_gracz() != this) //sprawdzlaem czy graniczy z wrogiem
       {
           granica += &map[i];
       }


    }
}

///Krok 1
//1.sprawdzenie czy sa jakies nieuzytki 3 poziomu zyznosc,staraj sie cos zbudowac tam za WSZELKA CENE
for(int i = 0;i < nieuzyte[2].size();i++)
    {

        Pole *gdzie;
        gdzie = nieuzyte[2].operator[](i);
    switch(gdzie->zwroc_typ())
            {
            case las :
                {
                Tartak *nowy = new Tartak();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[2]+1);
                if(zwroc == "Zbudowane!")
                {
                ilosc_budynkow[2]++;
                TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else delete nowy;
                 break;
                }

            case gory :
                {
                Kopalnia *nowy = new Kopalnia();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[1]+1);
                if(zwroc == "Zbudowane!")
                {
                    ilosc_budynkow[1]++;
                    TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else
                delete nowy;


                break;
                }

            case pole:
                {
                Farma *nowy = new Farma();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[0]+1);
                if(zwroc == "Zbudowane!")
                    {
                        ilosc_budynkow[0]++;
                        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                    }

                else
                delete nowy;

                break;
                }
            }
    if(PA < 6) break; //nie ma PA na budowe
    }

//2.jesli byl jakis i nie bylo kasy to podejmij decyzje czy zbierac peiniadze(nie budowac innych budnkow) czy budowac budynki na zyznosci <3 ... 1 sie nie oplaca!chyba ze ilosc budnkow == 0
for(int i = 0;i < nieuzyte[1].size();i++)
    {
        Pole *gdzie;
        gdzie = nieuzyte[1].operator[](i);
    switch(gdzie->zwroc_typ()) //najpierw leci dwojka
            {
            case las :
                {
                if(ilosc_budynkow[2] >= 8)break;
                Tartak *nowy = new Tartak();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[2]+1);
                if(zwroc == "Zbudowane!")
                {
                ilosc_budynkow[2]++;
                TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else delete nowy;
                 break;
                }

            case gory :
                {
                if(ilosc_budynkow[1] >= 8)break;
                Kopalnia *nowy = new Kopalnia();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[1]+1);
                if(zwroc == "Zbudowane!")
                {
                    ilosc_budynkow[1]++;
                    TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else
                delete nowy;


                break;
                }

            case pole:
                {
                if(ilosc_budynkow[0] >= 8 && !glod)break;
                Farma *nowy = new Farma();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[0]+1);
                if(zwroc == "Zbudowane!")
                    {
                        ilosc_budynkow[0]++;
                        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                    }

                else
                delete nowy;

                break;
                }
            }
    if(PA < 6) break; //nie ma PA na budowe
    }

   //2.5 teraz budynki 1szegj zyznosci jesli ich ilosc ==
if( (ilosc_budynkow[0] == 0 && glod == false) || ilosc_budynkow[1] == 0 || ilosc_budynkow[2] == 0)
   for(int i = 0;i < nieuzyte[0].size();i++)
    {

    if(ilosc_budynkow[0] != 0 && ilosc_budynkow[1] != 0 && ilosc_budynkow[2] != 0)break;
        Pole *gdzie;
        gdzie = nieuzyte[0].operator[](i);
    switch(gdzie->zwroc_typ()) //najpierw leci dwojka
            {
            case las :
                {
                if(ilosc_budynkow[2] >= 1)break;
                Tartak *nowy = new Tartak();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[2]+1);
                if(zwroc == "Zbudowane!")
                {
                ilosc_budynkow[2]++;
                TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else delete nowy;
                 break;
                }

            case gory :
                {
                if(ilosc_budynkow[1] >= 1)break;
                Kopalnia *nowy = new Kopalnia();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[1]+1);
                if(zwroc == "Zbudowane!")
                {
                    ilosc_budynkow[1]++;
                    TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                }
                else
                delete nowy;


                break;
                }

            case pole:
                {
                if(ilosc_budynkow[0] >= 1 && glod == false)break;
                Farma *nowy = new Farma();
                string zwroc;
                zwroc = nowy->zbuduj(*gdzie,surka,*this,ilosc_budynkow[0]+1);
                if(zwroc == "Zbudowane!")
                    {
                        ilosc_budynkow[0]++;
                        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
                    }

                else
                delete nowy;

                break;
                }
            }
    if(PA < 6) break; //nie ma PA na budowe
    }
//4.5 (dopisane) . Jesli surowce na koszary i ilosc_koszar <= 4 + ilosc_zamkow / 2 to buduj koszary
    if(nic.size())
        if(ilosc_budynkow[3] <= 5 + ilosc_budynkow[4] / 2)
    {
     Baraki *nowy = new Baraki();
     string zwroc;
     zwroc = nowy->zbuduj(*nic[0],surka,*this,ilosc_budynkow[3]+1);
     if(zwroc == "Zbudowane!")
     {
     ilosc_budynkow[3]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     }
     else
    delete nowy;
    }
//5.Jesli surowce na Zamek sa to zbudowac
    if(nic.size())
    {
     Zamek *nowy = new Zamek();
     string zwroc;
     zwroc = nowy->zbuduj(*nic[0],surka,*this,ilosc_budynkow[4]+1);
     if(zwroc == "Zbudowane!")
     {
         #if DEBUG
            cout << "[BOT - " << nazwa << "] zbudowalem zamek" << endl;
         #endif
     ilosc_budynkow[4]++;
     TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     }

     else
        delete nowy;
    }
//6.Jesli surowce na Gospode/Kosciol sa to zbudowac
//7.Jesli gospoda + Kosciol > 4 to narazie ich nei budujemy
    if(nic.size() && ((ilosc_budynkow[6] + ilosc_budynkow[7] <= 4) || poparcie <= 20))
    {
     Gospoda *nowy = new Gospoda();
     string zwroc;
     zwroc = nowy->zbuduj(*nic[0],surka,*this,ilosc_budynkow[6]+1);
     if(zwroc == "Zbudowane!")
     {
        ilosc_budynkow[6]++;
        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     }
    else
    delete nowy;

     Kosciol *Knowy = new Kosciol();
     zwroc = Knowy->zbuduj(*nic[0],surka,*this,ilosc_budynkow[7]+1);
     if(zwroc == "Zbudowane!")
     {
        ilosc_budynkow[7]++;
        TM.dobra_wiadomosc(x * 50 + 25,y * 50 + 25,zwroc);
     }

     else
    delete Knowy;
    }
/*
    PETLA
    <

    9.jesli jest jakies pole wroga ktore mozna otoczyc to otaczamy!(narazie wykreslone)
    10.Jak by³o to wróc do 9.
    11.Nie ma nic do otoczenia?Jeb losowo w kazde miejsce gdzie mozesz wroga uderzyc,a raczej atakuj jakis teren dopoki starczy PA.
    12.Jesli Teren przejety i PA >= 2 to ufortyfikuj PA / 2 gdzie PA / 2 <= 3
    13.Powtarzaj od 8.
    >
    */
    //8.Brak PA?Przerwij petle (Pa >= 2 by kontynuwac petle)

    while(PA >= 2 && zolnierze)
    {

        if(wrog.size() == 0 && obok[2].size() == 0 && obok[1].size() == 0 && obok[0].size() == 0 && graniczace.size() == 0) break;
        //9.jesli jest jakies pole wroga ktore mozna otoczyc to otaczamy!(w innym wypadku pole obok zostaje)

        while(cel == NULL) //czyli jseli nie ma celu lub
        {
            if(cel && cel->zwroc_gracz() == this && cel->zwroc_obrone() == 10)cel = NULL;
            //sprawdzamy czy da sie otoczyc
            for(int i = 0;i < graniczace.size();i++)
                {
                    int index = map.index_pola(graniczace[i]);
                    switch(mozna_otoczyc(this,graniczace[i],map))
                    {
                        case 'g':
                        index -= map.zwroc_szer();
                        cel = &map[index];
                        break;
                        case 'd':
                        index += map.zwroc_szer();
                        cel = &map[index];
                        break;
                        case 'l':
                        index--;
                        cel = &map[index];
                        break;
                        case 'p':
                        index++;
                        cel = &map[index];
                        break;
                    }
                    if(cel) break;
                }


            if(glod) //jesli god to szuka pierwszego lepszego pola z zywnoscia
            for(int i = 0;i < graniczace.size();i++)
            if(graniczace[i]->zwroc_gracz() != this && graniczace[i]->zwroc_typ() == pole)
            {
            cel = graniczace[i];
            break;
            }

            if(cel) break;
            //odtad przyjmujemy ze cel== NULL,dlaczego patrz linijka wyzej :>
            int szansa = 85;
            if(wrog.size() == 1) szansa-= 30;
            if(!wrog.size())szansa = 0;

            if(rand() % 100 >= szansa) //nic (obok atakujemy)
            {
                for(int i = 2;i >= 0;i--)
                {
                    if(obok[i].size() == 0)continue; //brak oboka,kontynuuj
                    if(cel)break;
                    cel = obok[i].operator[](rand() % obok[i].size());
                    if(cel && cel->zwroc_gracz() == this && cel->zwroc_obrone() >= 3)
                    {
                        cel = NULL;
                        for(int I = 0;I < obok[i].size();I++)
                        {
                            cel = obok[i].operator[](I);
                            if(cel->zwroc_gracz() == this && cel->zwroc_obrone() >= 3)cel = NULL;
                            else break;
                        }

                    }

                }
            }
            else
            {
                    cel = wrog[rand() % wrog.size()];
                    if(cel && cel->zwroc_gracz() == this && cel->zwroc_obrone() >= 3)
                    {
                        cel = NULL;
                        for(int i = 0;i < wrog.size();i++)
                        {
                            cel = wrog[i];
                            if(cel && cel->zwroc_gracz() == this && cel->zwroc_obrone() >= 3) cel = NULL;
                            else break;
                        }
                    }
            }

        }


        while(PA >= 2 && zolnierze )
        {
            if(cel->zwroc_gracz() == this && cel->zwroc_obrone() >= 5)break;
            int index = map.index_pola(cel);
            if(map.atak(index,this,TM))
            {
            PA -= 2;
            #if DEBUG
            cout << "[BOT - " << nazwa << "] zaatakowalem : " << index << endl;
            #endif
            }
            else
                {
                cel = NULL;
                break;
                }
            //12.Jesli Teren przejety i PA >= 2 to ufortyfikuj PA / 2 gdzie PA / 2 <= 3
        }
        if(cel && cel->zwroc_gracz() == this) cel = NULL;

    if(cel == NULL)break; //jesli na koncu petli nie wyznaczono celu to koniec
    }

            #if DEBUG
            cout << "[BOT - " << nazwa << "] koncowe PA  : " << PA << endl;
            cout << "------------------------" << endl;
            #endif
    poprzednia_zyw = surka.zywnosc;
}



char mozna_otoczyc(Gracz *kto,Pole *ktore,Mapa &gdzie)
{
    if(ktore->zwroc_gracz() == kto)return 'n';
    int index = gdzie.index_pola(ktore);
    int ilosc = 0;
    char strona = ' '; //g - gora,d - dol,l - lewo,p - prawo
    if(gdzie[index -1].zwroc_gracz() == kto) ilosc++;
    if(gdzie[index +1].zwroc_gracz() == kto) ilosc++;
    if(gdzie[index - gdzie.zwroc_szer()].zwroc_gracz() == kto) ilosc++;
    if(gdzie[index + gdzie.zwroc_szer()].zwroc_gracz() == kto) ilosc++;
    if(ilosc == 4)return 'n'; //co kur#!?To jest otoczone(lol musialem to ocenzurowac)
    if(ilosc < 3) return 'n'; //nie da sie otoczyc jednym atakiem.sorry koles,szukaj gdzies indziej :>

    if(gdzie.graniczy(index - 1,kto) && gdzie[index -1].zwroc_gracz() != kto) return 'l';
    if(gdzie.graniczy(index + 1,kto) && gdzie[index + 1].zwroc_gracz() != kto) return 'p';
    if(gdzie.graniczy(index - gdzie.zwroc_szer(),kto) && gdzie[index - gdzie.zwroc_szer()].zwroc_gracz() != kto) return 'g';
    if(gdzie.graniczy(index + gdzie.zwroc_szer(),kto) && gdzie[index + gdzie.zwroc_szer()].zwroc_gracz() != kto) return 'd';
    return 'n';
}
