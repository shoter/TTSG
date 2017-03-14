#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <ctime>
using namespace std;
extern void game();
extern void Menu();
ALLEGRO_FONT* font;
int main(int argc, char **argv)
{
    if(al_init())
        cout << "Inicjalizacja allegro" << endl;
    else
    {
        cout << "Nieudana inicjalizacja allegro" << endl;
        return -1;
    }
    if(al_install_mouse())
    cout << "Inicjalizacja myszki" << endl;
    else
    {
        cout << "Nieudana inicjalizacja myszki" << endl;
        return -2;
    }
    if(al_init_primitives_addon())
    cout << "Inicjalizacja addonu prymitywow" << endl;
    else
    {
        cout << "Nieudana inicjalizacja addonu prymitywow" << endl;
        return -3;
    }
    if(al_install_keyboard())
    cout << "Inicjalizacja myszki" << endl;
    else
    {
        cout << "Nieudana inicjalizacja klawiatury" << endl;
        return -4;
    }
    al_init_font_addon();
    if(al_init_image_addon())
    cout << "Inicjalizacja addonu obrazkow" << endl;
    else
    {
        cout << "Nieudana inicjalizacja addonu obrazkow" << endl;
        return -5;
    }

if (al_create_display(800,600))
        cout << "Inicjalizacja ekranu 800x600 pikseli" << endl;
    else
    {
        cout << "Nieudana inicjalizacja ekranu" << endl;
        return -6;
    }
    font = al_load_bitmap_font( "font\\a4_font.tga" );
    srand(time(NULL));
    al_set_blender(ALLEGRO_ADD,ALLEGRO_ALPHA,ALLEGRO_INVERSE_ALPHA);
    Menu();


   return 0;
}

