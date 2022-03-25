#pragma once
#include <iostream>
#include "PomocneFunkcije.h"
#include "Sjediste.h"
using namespace std;


class Sala
{
private:
    char* _naziv;
    int _brojRedova; //max.26 [A-Z]
    int _brojKolona;
    Sjediste** _sjedista; //2D matrica objekata tipa Sjediste. Dimenzije matrice su: (_brojRedova x _brojKolona)
public:
    //Z2.7
    Sala() {
        throw exception("potrebno implementirati");
    }
    //Z2.8
    //Uraditi dinamicku alokaciju 2D matrice sjedista pomocu pokazivaca na niz pokazivaca (_sjedista)
    //Podesiti vrijednosti atributa objekata matrice na sljedeci nacin -->
    //Polje [0][0] => _red : A, _kolona : 1
    //Polje [0][1] => _red : A, _kolona : 2
    //Polje [0][2] => _red : A, _kolona : 3
    //...
    //Polje [1][0] => _red : B, _kolona : 1
    //itd.
    Sala(const char* naziv, int brojRedova, int brojKolona) {
        throw exception("potrebno implementirati");
    }

    //Z2.9
    void SetNaziv(const char* naziv) {
        throw exception("potrebno implementirati");
    }
    const char* GetNaziv() const { throw exception("potrebno implementirati"); }
    int GetBrojRedova() const { throw exception("potrebno implementirati"); }
    int GetBrojKolona() const { throw exception("potrebno implementirati"); }

    //Z2.10
    //Uraditi dealokaciju alocirane matrice sjedista, te zatim uraditi ponovnu alokaciju na osnovu novih dimenzija
    void SetSjedista(int brojRedova, int brojKolona) {
        //dealociranje niza objekata tipa Sjediste
        
        //dealociranje niza pokazivaca
 
        //Podesavanje atributa na nove vrijednosti
  
        //Ponovna alokacija
        //alokacija niza pokazivaca        
        //alokacija niza objekata za i-ti pokazivac u nizu
 
    }

    //Z2.11
    //Vratiti adresu objekta sjediste, koje odgovara proslijedjenim vrijednostima
    //Ukoliko nije pronadjeno, vratiti nullptr 
    Sjediste* GetSjediste(char red, int kolona) {
        throw exception("potrebno implementirati");
    }

    //Z2.12
    //Uraditi ispis na sljedeci nacin --->
    //Sala: Sala 7 Extreme
    //Redova: 11
    //Kolona: 20
    // -----------------------------
    // [A-1] [A-2] [A-3] .... [A-20]
    // [B-1] [B-2] [B-3] .... [B-20]
    // .
    // .
    // .
    // [K-1] [K-2] [K-3] .... [K-20]
    // -----------------------------
    void Ispis() {
     
        throw exception("potrebno implementirati");
    }

    //Z2.13
    ~Sala() {
        throw exception("potrebno implementirati");
    }
};