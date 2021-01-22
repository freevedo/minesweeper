#ifndef FELD_H
#define FELD_H
#include <string>
#include <iostream>
#include <string>
#include <array>
#include "time.h"

using namespace std;



enum Belegung {offen, mine,aufgedeckt};

struct feld{
    Belegung beleg;
    int anzahl_minen;

};

//constante
const int Hoehe = 12;
const int Breite = 12;
feld spielFeld[Hoehe][Breite];
int AnzahlMinen = (int) Hoehe * Breite * 0.17;
int offeneFelder = Hoehe * Breite - AnzahlMinen;

//deklaration aller funktionnen
void initialisieren(int anzahl_minen);
void total_minen(int x, int y);
void darstellung(bool b);
bool wahl();
bool harmloseNachbar();
void felderOffen (int &x);
void darstellen();
#endif // FELD_H
