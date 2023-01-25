#include <iostream>
#include <cstdio>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "kopf.h"


class Spielfeld {
private:
    int matrix[15][15];
    int anzahlMinen;


public:

    /*int size;
    Spielfeld(int feld) {
        size = feld;
        int reihen = size;
        int spalten = size;
        this->size = size;
        double k = (12 + rand()%(9));
        anzahlMinen = (size*size)*(k/100);

        for(int i=0; i<reihen; i++) {
            for(int j=0; j<spalten; j++) {
                matrix[i][j] = 7;
            }
        }

        for (int i=0; i<anzahlMinen; i++){
            int posSpalten = rand()%(spalten);
            int posReihen = rand()%(reihen);
            if (matrix[posSpalten][posReihen]==7){
                matrix[posSpalten][posReihen]=9;
            }
            else{
                i--;
            }
        }
    }*/
    int revealed[15][15];
    int size;
        Spielfeld(int feld) {
            size = feld;
            int reihen = size;
            int spalten = size;
            this->size = size;
            double k = (12 + rand()%(9));
            anzahlMinen = (size*size)*(k/100);

            for(int i=0; i<reihen; i++) {
                for(int j=0; j<spalten; j++) {
                    matrix[i][j] = 7;
                    revealed[i][j] = false;
                }
            }

            for (int i=0; i<anzahlMinen; i++){
                int posSpalten = rand()%(spalten);
                int posReihen = rand()%(reihen);
                if (matrix[posSpalten][posReihen]==7){
                    matrix[posSpalten][posReihen]=9;
                }
                else{
                    i--;
                }
            }
        }
        void setRevealed(int i, int j) {
                revealed[i][j] = true;
            }
    int getAnzahlMinen() {
        return anzahlMinen;
    }

    int getMatrixValue(int i, int j) {
        return matrix[i][j];
    }
    int setMatrixValue(int i, int j, int value)
    {
        matrix[i][j] = value;
        return value;
    }
};

using namespace std;

void Menu();
void Minenzaehlen(Spielfeld&);
void SpielfeldVerloren(Spielfeld&);
void SpfeldAnzeigen(Spielfeld&);
bool Entdecken(Spielfeld&,int,int);
void Feld_0(Spielfeld&,int,int);
void Aktualisieren(Spielfeld&, int, int);
bool gewinnenBool(Spielfeld&);
bool Markieren(int,int,int);

int schritte = 0;
void Minenzaehlen(Spielfeld &spielfeld){
    int size = spielfeld.size;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            int count = 0;
            if (spielfeld.getMatrixValue(i,j) == 9){
                continue;
            }
            for(int x = i-1; x <= i+1; x++) {
                for(int y = j-1; y <= j+1; y++) {
                    if(x < 0 || x >= size || y < 0 || y >= size) {
                        continue;
                    }
                    if(spielfeld.getMatrixValue(x,y) == 9) {
                        count++;
                    }
                }
            }
            spielfeld.setMatrixValue(i,j, count);
        }
    }
}
/*void Minenzaehlen(Spielfeld &spielfeld){
    int size = spielfeld.size;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            int count = 0;
            if (spielfeld.getMatrixValue(i,j) == '*'){
                continue;
            }
            for(int x = i-1; x <= i+1; x++) {
                for(int y = j-1; y <= j+1; y++) {
                    if(x < 0 || x >= size || y < 0 || y >= size) {
                        continue;
                    }
                    if(spielfeld.getMatrixValue(x,y) == '*') {
                        count++;
                    }
                }
            }
            spielfeld.setMatrixValue(i,j, count);
        }
    }
}*/
/*void Minenzaehlen(Spielfeld &spielfeld){
    int size = spielfeld.size;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            int count = 0;
            if (spielfeld.getMatrixValue(i,j) == 9){
                continue;
            }
            for(int x = i-1; x <= i+1; x++) {
                for(int y = j-1; y <= j+1; y++) {
                    if(x < 0 || x >= size || y < 0 || y >= size) {
                        continue;
                    }
                    if(spielfeld.getMatrixValue(x,y) == 9) {
                        count++;
                    }
                }
            }
            spielfeld.setMatrixValue(i,j, count);
        }
    }
}*/

void SpielfeldVerloren(Spielfeld &spielfeld){ //Spielfeld wenn man verliert.
    for(int i=0; i<spielfeld.size; i++) {
    for(int j=0; j<spielfeld.size; j++) {
   cout<<spielfeld.getMatrixValue(i,j)<<" ";
  }
  cout<<endl;
 }

    cout<<"\nUeberstandene Schritte " << schritte <<endl;
    cout<<"Spiel Verloren, gib deine Name ein: " <<endl;
    string name;
    cin >> name;

    addscore(name,schritte);
    Highscoreanzeigen();
    schritte=0; //Bei Ende des Spiels "Schritte" wieder auf 0 setzen.

    return;
}
/*void SpfeldAnzeigen(Spielfeld &spielfeld){
    int reihen = spielfeld.size;
    int spalten = spielfeld.size;

    for(int i=0; i<reihen; i++) {
        for(int j=0; j<spalten; j++) {
            cout<<spielfeld.getMatrixValue(i,j)<<" ";
        }
        cout<<endl;
    }
}*/
void SpfeldAnzeigen(Spielfeld &spielfeld){
        int reihen = spielfeld.size;
        int spalten = spielfeld.size;
        for(int i=0; i<reihen; i++) {
            for(int j=0; j<spalten; j++) {
                if(spielfeld.revealed[i][j]) {
                    cout<<spielfeld.getMatrixValue(i,j)<<" ";
                }
                else {
                    cout<<"# ";
                }
            }
            cout<<endl;
        }
    }
/*void SpfeldAnzeigen(Spielfeld &spielfeld){
    int reihen = spielfeld.size;
    int spalten = spielfeld.size;

    for(int i=0; i<reihen; i++) {
        for(int j=0; j<spalten; j++) {
            int value = spielfeld.getMatrixValue(i, j);
            char c = (value == 7) ? '+' : '#';
            cout<<c<<" ";
        }
        cout<<endl;
     }
}*/


/*bool Entdecken(Spielfeld &spielfeld, int reihe, int spalte)
{
    if(reihe < 0 || reihe >= spielfeld.size || spalte < 0 || spalte >= spielfeld.size) {
        cout<<"Fehler! Koordinate außerhalb des Spielfeldes. "<<endl;
        return false;
    }

    if (spielfeld.getMatrixValue(reihe, spalte)==0){ //Aufdecken wenn Feld 0 Minen um sich hat.
        Feld_0(spielfeld, reihe, spalte);
        Aktualisieren(spielfeld,reihe ,spalte);
        return true;
    }
    else if(spielfeld.getMatrixValue(reihe, spalte)!='9'){ // Aufdecken wenn keine Mine
        spielfeld.setMatrixValue(reihe, spalte, spielfeld.getMatrixValue(reihe, spalte));
        Aktualisieren(spielfeld,reihe,spalte);
        return true;
    }
    else if(spielfeld.getMatrixValue(reihe, spalte)=='9'){ //Aufdecken wenn Mine (Spiel verloren)
        cout<<"Sie haben eine Mine getroffen. Das Spiel ist verloren."<<endl;
        cout<<endl;
        SpielfeldVerloren(spielfeld);
        return false;
    }
}*/
bool Entdecken(Spielfeld &spielfeld,int x,int y){
    if(spielfeld.getMatrixValue(x,y)==9){
        SpielfeldVerloren(spielfeld);
        return false;
    }
    if(spielfeld.getMatrixValue(x,y)==0){
        Feld_0(spielfeld,x,y);
    }
    spielfeld.setRevealed(x,y);
    Aktualisieren(spielfeld,x,y);
    if(gewinnenBool(spielfeld)){
        cout<<"Gewonnen"<<endl;
    }
    return true;
}

/*bool Markieren(int feld, int reihe, int spalte){
    int reihen=feld;
    int spalten=feld;
    int flag_counter = 0;
    cout << "MARKIEREN" << endl;

    while(reihen<0 || reihe>feld-1 || spalte<0 || spalte>feld-1){
        cout<<"Fehler! Koordinate außerhalb des Spielfeldes. "<<endl;
        cout<<"--> Geben Sie die Reihe an: ";
        cin>>reihe;
        reihe=reihe-1;
        cout<<"--> Geben Sie die Spalte an: ";
        cin>>spalte;
        spalte=spalte-1;
        cout<<endl;
    }
    if(SpielfeldAnzeigen[reihe][spalte] != '#'){
       cout<<"Fehler! Das Feld wurde bereits aufgedeckt."<<endl;
       return false;
    }
    if(flag_counter >= 15) {
       cout<<"Fehler! Sie haben die maximale Anzahl an Flags platziert."<<endl;
       return false;
    }
    SpielfeldAnzeigen[reihe][spalte] = 'F';
    flag_counter++;
    Aktualisieren(feld);
    return true;
}*/

/*void Aktualisieren(Spielfeld& spielfeld){

    for(int i=0; i<spielfeld.size; i++) {
        for(int j=0; j<spielfeld.size; j++) {
            int value = spielfeld.getMatrixValue(i, j);
            char c = (value == 7) ? '+' : '#';
            cout<<c<<" ";
        }
        cout<<endl;
     }
    schritte++;
}*/
void Aktualisieren(Spielfeld& spielfeld, int x, int y){
    int value = spielfeld.getMatrixValue(x, y);
    if (value == 9) { // if the cell has a mine
        SpielfeldVerloren(spielfeld);
        return;
    } else if (value == 0) { // if the cell has no mines nearby
        Feld_0(spielfeld, x, y);
    } else { // if the cell has a number of mines nearby
        spielfeld.setMatrixValue(x, y, 0); // change the value of the cell to 0
        }
        SpfeldAnzeigen(spielfeld); // display the updated game board
        schritte++; // increase the step counter
        }




void Feld_0(Spielfeld &spielfeld, int reihe, int spalte){
    spielfeld.setMatrixValue(reihe, spalte, spielfeld.getMatrixValue(reihe, spalte));
//----------------------------------------------------Die Ecken zählen---------------------------------------------------------------------
    if (reihe==0 && spalte==0){ //Ecke oben links
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte+1, spielfeld.getMatrixValue(reihe+1, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));

    }

    else if (reihe==0 && spalte==spielfeld.size-1){ //Ecke oben rechts
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte-1, spielfeld.getMatrixValue(reihe+1, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));
    }

    else if (reihe==spielfeld.size-1 && spalte==0){ //Ecke unten links
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte+1, spielfeld.getMatrixValue(reihe-1, spalte+1));
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1));
    }

    else if (reihe==spielfeld.size-1 && spalte==spielfeld.size-1){ //Ecke unten rechts
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte-1, spielfeld.getMatrixValue(reihe-1, spalte-1));
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
    }

        //----------------------------------------------------Zählen der Felder die keine Ecken sind.---------------------------------------------------------------------
    else if (reihe==0){ //Feld mitte oben
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1)) ;
        spielfeld.setMatrixValue(reihe+1, spalte+1, spielfeld.getMatrixValue(reihe+1, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte-1, spielfeld.getMatrixValue(reihe+1, spalte-1));
    }

    else if (reihe==spielfeld.size-1){ //Feld mitte unten
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte+1, spielfeld.getMatrixValue(reihe-1, spalte+1));
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1));
        spielfeld.setMatrixValue(reihe-1, spalte-1, spielfeld.getMatrixValue(reihe-1, spalte-1));
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
    }

    else if (spalte==0 ){ //Feld mitte links
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte+1, spielfeld.getMatrixValue(reihe-1, spalte+1));
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte+1, spielfeld.getMatrixValue(reihe+1, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));
    }

    else if (spalte==spielfeld.size-1){ //Feld mitte rechts
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte-1, spielfeld.getMatrixValue(reihe-1, spalte-1));
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte-1, spielfeld.getMatrixValue(reihe+1, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));
    }

    else{//Feld mitte
        spielfeld.setMatrixValue(reihe-1, spalte, spielfeld.getMatrixValue(reihe-1, spalte)) ;
        spielfeld.setMatrixValue(reihe-1, spalte-1, spielfeld.getMatrixValue(reihe-1, spalte-1));
        spielfeld.setMatrixValue(reihe, spalte-1, spielfeld.getMatrixValue(reihe, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte-1, spielfeld.getMatrixValue(reihe+1, spalte-1));
        spielfeld.setMatrixValue(reihe+1, spalte, spielfeld.getMatrixValue(reihe+1, spalte));
        spielfeld.setMatrixValue(reihe-1, spalte+1, spielfeld.getMatrixValue(reihe-1, spalte+1));
        spielfeld.setMatrixValue(reihe, spalte+1, spielfeld.getMatrixValue(reihe, spalte+1));
        spielfeld.setMatrixValue(reihe+1, spalte+1, spielfeld.getMatrixValue(reihe+1, spalte+1));
    }

}
bool gewinnenBool(Spielfeld &spielfeld){
    int cont=0;
    for(int i=0; i<spielfeld.size; i++) {
      for(int j=0; j<spielfeld.size; j++) {
       if (/*(spielfeld.setMatrixValue(i,j)=='#' )&& */(spielfeld.getMatrixValue(i,j)!='9')){
        cont++;
       }
       spielfeld.setMatrixValue(i,j,cont);
      }
     }
    if(cont==0){
        return true;
    }
    else{
        return false;
    }
}
int main ()
{
    Menu();
}
void Menu()
{
    int auswahl;
    do
    {

        cout << "\nWilkommen bei Minesweeper\n" << endl;
        cout <<"(1) Anleitung\n(2) Spielen\n(3) Highscores\n(4) Beenden\n\n";
        cin >> auswahl;
                switch (auswahl)
                {
                case 1:
                    cout<<"REGELN:"<<endl;
                    cout<<"1. Die Groesse des Spielfeldes muss ein Wert zwischen 6 und 15 sein."<<endl;
                    cout<<"2. Du darfst keine Bombe treffen."<<endl;
                    cout<<"3. Spaß haben."<<endl;
                    cout<<endl;
                    break;
                case 2:{

                    int feld = 0;
                    srand(time(NULL));

                    cout<<"     ------------- Minesweeper -------------"<<endl;
                    cout<<endl;
                    cout<<endl;

                    cout<<"--> Geben Sie die Groesse des Spielfelds an: ";
                    cin>>feld;
                    cout<<endl;

                    while (feld < 6 || feld > 15){
                    cout<<"Fehler! Geben Sie eine Zahl zwischen 6 und 15 ein."<<endl;
                    cout<<"--> Geben Sie die Groesse des Spielfelds an: ";
                    cin>>feld;
                    }

                    Spielfeld spielfeld(feld);
                    Minenzaehlen(spielfeld);
                    SpfeldAnzeigen(spielfeld);
                    cout<<endl;
                    cout<<"Lass uns anfangen!"<<endl;
                    cout<<"--> Geben Sie die Koordinaten der Felder ein, die Sie auswaehlen moechten: "<<endl;
                    int reihe=0;
                    int spalte =0;
                    char charReihe;

                    cout<<"--> Geben Sie die Reihe an: ";
                    cin>>charReihe;
                    charReihe=toupper(charReihe);
                    reihe = charReihe - 64;
                    reihe=reihe-1;
                    cout<<"--> Geben Sie die Spalte an: ";
                    cin>>spalte;
                    spalte=spalte-1;
                    cout<<endl;

                    while(reihe<0 || reihe>feld-1 || spalte<0 || spalte>feld-1){
                    cout<<endl;
                    cout<<"Fehler: Koordinate außerhalb des Spielfelds "<<endl;
                    cout<<"--> Geben Sie die Reihe an: ";
                    cin>>charReihe;
                    charReihe=toupper(charReihe);
                    reihe = charReihe - 64;
                    reihe=reihe-1;
                    cout<<"--> Geben Sie die Spalte an: ";
                    cin>>spalte;
                    spalte=spalte-1;
                    cout<<endl;
                    }
                    bool EntdeckenBool=true;
                    bool Gewinnen=false;
                    cout<<"--> Falls sie Markieren wollen, schreiben sie: MARK "<<endl;
                    string mark;
                    cin >> mark;
                    if(mark == "MARK")
                    {
                        //Markieren(feld,reihe,spalte);
                    }
                    else
                    {
                        EntdeckenBool=Entdecken(spielfeld,reihe,spalte);
                    }
                    while (EntdeckenBool==true){
                        cout<<endl;
                        cout<<"--> Geben Sie die Reihe an: ";
                        cin>>charReihe;
                        charReihe=toupper(charReihe);
                        reihe = charReihe - 64;
                        reihe=reihe-1;
                        cout<<"--> Geben Sie die Spalte an: ";
                        cin>>spalte;
                        cout<<endl;
                        spalte=spalte-1;
                        cout<<"--> Falls sie Markieren wollen, schreiben sie: MARK. "<<endl;
                        cout<<"--> Falls sie Entdecken wollen, schreiben sie egal was anderes. "<<endl;
                        string mark;
                        cin >> mark;
                        if(mark == "MARK")
                        {
                            //Markieren(feld,reihe,spalte);
                        }
                        else
                        {
                           EntdeckenBool=Entdecken(spielfeld,reihe,spalte);
                        }
                        Gewinnen=gewinnenBool(spielfeld);
                        if (Gewinnen==true){
                            cout<<endl;
                            cout<<"HERZLICHEN GLÜCKWUNSCH!! ... SIE HABEN DAS SPIEL GEWONNEN"<<endl;
                            EntdeckenBool=false;
                            cout<<endl;
                        }

                    }

                    break;}
                case 3:
                    cout << "Highscores:\n" << endl;
                    cout << "Top 10: " << endl;
                    Highscoreanzeigen();

                    break;
                case 4:
                    exit(0);
                    break;
                }

    } while (auswahl !=4);
}


