#include <iostream>
#include "feld.h"

using namespace std;

int main()
{
    cout << "**********************Minesweeper Spiel*****************"<<endl <<endl <<endl;
    bool spielverlauf = true ;

    //initialisierung des Arrays
    initialisieren(AnzahlMinen);

    cout << "Debug ansicht : " << endl;
    //debug ansicht
    darstellen();

    cout << endl << endl;

    //darstellung vor dem Spielverlauf
    darstellung(spielverlauf);


    do{
        cout << "Bitte geben Sie nun Ihren naechsten Zug ein.\nZeile (1-12) _Leerzeichen_ Spalte: (1-12):" << endl;

        if(wahl() == false)
        {
            cout << "LEIDER BOOM. Sie haben verloren." <<endl;
            spielverlauf = false;
        }
        else
        {
            harmloseNachbar();

            if (offeneFelder <= 0)
            {
                spielverlauf = false;
                cout << offeneFelder <<endl;
                offeneFelder = 0;
                cout << "Sie haben gewonnen,\nHerzlichen Glueckwunsch!";
            }

        }

        cout << "Verbleidende offene Felder : " << offeneFelder << endl;

        //darstellung nach bestimmten Eingaben
        darstellung(spielverlauf);

    }while (spielverlauf);

    return 0;
}



void initialisieren(int anzahl_minen)
{
    // initialisierung der Felden
    for (int i = 0; i < Hoehe ; i++){
        for (int j = 0; j < Breite ; j++)
        {
            spielFeld[i][j].anzahl_minen = 0;
            spielFeld[i][j].beleg = offen;
        }
    }
    // Zufalligen minen verteilen
    srand(time(NULL));//wieder
    while (anzahl_minen > 0) { //solange es gibt minen
        int i , j;
        i = rand()%Hoehe;
        j = rand()%Breite;
        //pruefen ob das Spielfeld schon verteilt ist
        if(spielFeld[i][j].beleg== mine)
        {
            continue;
        }
        else
            spielFeld[i][j].beleg = mine;
        anzahl_minen--;
    }
    //anzahl der minen in der Nachbarschaft berechnen fur jedes feld
    for (int i =  0; i<Hoehe; i++)
    {
        for(int j =0; j <Breite ; j++)
        {
            total_minen(i,j);

        }
    }


}


//minen in der Nachbarschaft ermitteln
//alle 8 Moglichkeiten pruefen
//Wenn eine Moglichkeit nicht im Spielfeld liegt dann wird es uberspring bis zum naechsten
void total_minen(int x, int y)
{
    if(x-1 >=0 && y-1 >=0){
        if(spielFeld[x-1][y-1].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(x-1 >=0){
        if(spielFeld[x-1][y].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(x-1 >=0 && y+1 <Breite)
    {
        if(spielFeld[x-1][y+1].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(y-1 >=0 ){
        if(spielFeld[x][y-1].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(y+1 <Breite){
        if(spielFeld[x][y+1].beleg == mine)
        {
            spielFeld[x][y].anzahl_minen++;
        }
    }
    if(x+1<Hoehe && y-1 >=0)
    {
        if(spielFeld[x+1][y-1].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(x+1 < Hoehe)
    {
        if(spielFeld[x+1][y].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
    if(x+1 < Hoehe && y+1<Breite)
    {
        if(spielFeld[x+1][y+1].beleg == mine)
            spielFeld[x][y].anzahl_minen++;
    }
}


void darstellung(bool bedingung)
{

    if( bedingung == true)
        {
            for(int i = 0; i < Hoehe ; i++)
            {
                if (i < 9)
                cout << "0" << i + 1 << "|";
                else
                    cout << i  + 1 << "|";

                for(int j = 0; j < Breite ; j++)
                {
                    //offene felder und minen abdecken
                    if(spielFeld[i][j].beleg == offen || spielFeld[i][j].beleg == mine)
                    {
                    cout << " * ";
                    }
                    else if (spielFeld[i][j].beleg == aufgedeckt && spielFeld[i][j].anzahl_minen == 0  ){
                    cout << " . ";
                    }
                    else if(spielFeld[i][j].beleg == aufgedeckt && spielFeld[i][j].anzahl_minen > 0){
                      cout << " " << spielFeld[i][j].anzahl_minen << " ";
                    }


                }

         cout << endl;
        }
        /*cout << "   " << "--------------------------------------" << endl
             << "   " << " 1  2  3  4  5  6  7  8  9  10 11 12 " << endl ;*/
            cout << "   _";
            for (int i = 0; i < Breite; i++){
                cout << "___";
            }
            cout << '\n';

            cout << "  ";
            for (int i = 0; i < Breite; i++) {
                if (i<9)
                    cout << "  " << i+1;
                else
                    cout << " " <<  i+1;
            }
            cout << '\n';

        }
        //wenn bedingung false ist
        //mine wurde getroffen
        else{
            for(int i = 0; i < Hoehe ; i++)
            {
                if (i < 9)
                cout << "0" << i + 1 << "|";
                else
                    cout << i  + 1 << "|";

                for(int j = 0; j < Breite ; j++)
                {
                    if(spielFeld[i][j].beleg == offen)
                    {
                    cout << " * ";
                    }
                    else if (spielFeld[i][j].beleg == aufgedeckt && spielFeld[i][j].anzahl_minen == 0    ){
                    cout << " . ";
                    }
                    else if(spielFeld[i][j].beleg == aufgedeckt && spielFeld[i][j].anzahl_minen > 0){
                      cout << " " << spielFeld[i][j].anzahl_minen << " ";
                    }
                    else if(spielFeld[i][j].beleg == mine ){
                      cout << " X " ;
                    }


                }

             cout << endl;
            }
            /*cout << "   " << "--------------------------------------" << endl
                 << "   " << " 1  2  3  4  5  6  7  8  9  10 11 12 " << endl ;*/

            cout << "   _";
            for (int i = 0; i < Breite; i++){
                cout << "___";
            }
            cout << '\n';

            cout << "  ";
            for (int i = 0; i < Breite; i++) {
                if (i<9)
                    cout << "  " << i+1;
                else
                    cout << " " <<  i+1;
            }
            cout << '\n';

        }
}


bool wahl()
{

    bool b = true;
    int x , y;
    //eingabe der Koordinate
    do {
        cout << "Geben Sie die Zeile : " << endl;
        cin >> x;
        cout << "Geben Sie die Spalte : " << endl;
        cin >> y;
    }while (x < 1 || x > Hoehe || y < 1 || y > Breite);

    if (spielFeld[x-1][y-1].beleg == mine)
    {

        return b = false;//brecht das programm ab
    }
    else {
        /*
         * Wenn spielfeld kein mine hat wird es aufgedeckt und
         * offene felder zuruck ziehen
         *
         */
        spielFeld[x-1][y-1].beleg = aufgedeckt;
        felderOffen(offeneFelder);
    }
    return b;
}


/* uberpruefen ob ein spielfeld aufgedect ist und hat kein nechbar mit minen
 *
 * falls so
 * noch die 8 moglichkeiten uberpruefen
 *
 */
bool harmloseNachbar()
{
    bool b =  false;
    while (!b) {
        b = true;
        for(int i = 0; i < Hoehe ; i++)
        {
            for (int j = 0 ; j < Breite ; j++)
            {
                if(spielFeld[i][j].beleg == aufgedeckt && spielFeld[i][j].anzahl_minen == 0)
                {
                    if(i-1 >=0 && j-1 >=0 )
                    {
                        /* Uberpruefen ob das Feld schon aufgedeckt
                         * falls nein wird es aufgedeckt  und offene felder --
                         * b = false wird die  schleife hier beendet
                         */
                        if(spielFeld[i-1][j-1].beleg != aufgedeckt)
                        {
                            spielFeld[i-1][j-1].beleg = aufgedeckt;
                            b=false;
                            felderOffen(offeneFelder);
                        }

                    }
                    if(i-1 >=0){
                        if(spielFeld[i-1][j].beleg !=aufgedeckt)
                        {
                            spielFeld[i-1][j].beleg =aufgedeckt;
                            b = false;
                            felderOffen(offeneFelder);
                        }

                    }
                    if(i-1 >=0 && j+1 <Breite)
                    {
                        if(spielFeld[i-1][j+1].beleg != aufgedeckt)
                        {
                            spielFeld[i-1][j+1].beleg = aufgedeckt;
                            b=false;
                           felderOffen(offeneFelder);
                        }

                    }
                    if(j-1 >=0)
                    {
                        if(spielFeld[i][j-1].beleg != aufgedeckt)
                        {
                            spielFeld[i][j-1].beleg = aufgedeckt;
                            b =false;
                            felderOffen(offeneFelder);
                        }

                    }
                    if(j+1 < Breite)
                    {
                        if(spielFeld[i][j+1].beleg != aufgedeckt)
                        {
                            spielFeld[i][j+1].beleg = aufgedeckt;
                            b = false;
                           felderOffen(offeneFelder);
                        }

                    }
                    if(i+1 <Hoehe && j-1 >=0)
                    {
                        if(spielFeld[i+1][j-1].beleg != aufgedeckt)
                        {
                            spielFeld[i+1][j-1].beleg = aufgedeckt;
                            b = false;
                            felderOffen(offeneFelder);
                        }

                    }
                    if(i+1 < Hoehe)
                    {
                        if(spielFeld[i+1][j].beleg != aufgedeckt)
                        {
                            spielFeld[i+1][j].beleg = aufgedeckt;
                            b  = false;
                            felderOffen(offeneFelder);
                        }

                    }
                    if(i+1 < Hoehe && j+1 < Breite)
                    {
                        if(spielFeld[i+1][j+1].beleg != aufgedeckt)
                        {
                            spielFeld[i+1][j+1].beleg = aufgedeckt;
                            b = false;
                            felderOffen(offeneFelder);
                        }

                    }
                }

            }
        }
    }

    return b;
}

//
void felderOffen (int &x)
{
    x--;
}

void darstellen(){
    for (int i = 0; i < Hoehe; i++) {
        if (i < 9)
            cout << "0" << i+1 << "|";
        else
            cout << i+1 << "|";
        for (int j = 0; j < Breite; j++) {
            if (spielFeld[i][j].beleg == mine)
                cout << " X ";
            else
                if (spielFeld[i][j].beleg == offen)
                    cout << " * ";
                else
                    if (spielFeld[i][j].anzahl_minen == 0)
                        cout << " . ";
                    else
                        cout << " " << spielFeld[i][j].anzahl_minen << " ";
        }
        cout << '\n';
    }

    cout << "   _";
    for (int i = 0; i < Breite; i++){
        cout << "___";
    }
    cout << '\n';

    cout << "  ";
    for (int i = 0; i < Breite; i++) {
        if (i<9)
            cout << "  " << i+1;
        else
            cout << " " <<  i+1;
    }
    cout << '\n';
}
