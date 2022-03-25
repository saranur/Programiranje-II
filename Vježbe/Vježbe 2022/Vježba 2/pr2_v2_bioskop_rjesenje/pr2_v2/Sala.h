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
        _naziv = nullptr;
        _brojRedova = 0;
        _brojKolona = 0;
        _sjedista = nullptr;
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
        _naziv = AlocirajIKopiraj(naziv);
        _brojRedova = brojRedova;
        _brojKolona = brojKolona;
        _sjedista = new Sjediste *[brojRedova];  
            for(int i = 0; i < brojRedova; i++)
            {
                _sjedista[i] = new Sjediste[_brojKolona]; 
                for (int j = 0; j < brojKolona; j++)
                {
                    _sjedista[i][j].SetKolona(j + 1);
                    _sjedista[i][j].SetRed(i + 65);
                }
            }
    }

    //Z2.9
    void SetNaziv(const char* naziv) {
        if (_naziv != nullptr)
            delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    const char* GetNaziv() const { return _naziv; }
    int GetBrojRedova() const { return _brojRedova; }
    int GetBrojKolona() const { return _brojKolona; }

    //Z2.10
    //Uraditi dealokaciju alocirane matrice sjedista, te zatim uraditi ponovnu alokaciju na osnovu novih dimenzija
    void SetSjedista(int brojRedova, int brojKolona) {
        //dealociranje niza objekata tipa Sjediste
        for (int i = 0; i < _brojRedova; i++)
        {
            delete[] _sjedista[i];
            _sjedista[i] = nullptr;
        }
        //dealociranje niza pokazivaca
        delete[] _sjedista;
        _sjedista = nullptr;
        //Podesavanje atributa na nove vrijednosti
        _brojRedova = brojRedova;
        _brojKolona = brojKolona;
        //Ponovna alokacija
        //alokacija niza pokazivaca  
        _sjedista = new Sjediste * [brojRedova];
        //alokacija niza objekata za i-ti pokazivac u nizu
        for (int i = 0; i < brojRedova; i++)
        {
            _sjedista[i] = new Sjediste[_brojKolona];
            for (int j = 0; j < brojKolona; j++)
            {
                _sjedista[i][j].SetKolona(j + 1);
                _sjedista[i][j].SetRed(i + 65);
            }
        }
    }

    //Z2.11
    //Vratiti adresu objekta sjediste, koje odgovara proslijedjenim vrijednostima
    //Ukoliko nije pronadjeno, vratiti nullptr 
    Sjediste* GetSjediste(char red, int kolona) {
        for (int i = 0; i < _brojRedova; i++)
        {
            _sjedista[i] = new Sjediste[_brojKolona];
            for (int j = 0; j < _brojKolona; j++)
            {
                if (_sjedista[i][j].GetRed() == red && _sjedista[i][j].GetKolona() == kolona)
                    return &_sjedista[i][j];

            }return nullptr;
        }
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
        cout << "Sala: " << _naziv << endl;
        cout << "Redovi: " << _brojRedova << endl;
        cout << "Kolone: " << _brojKolona << endl;
        for (int i = 0; i < _brojRedova; i++)
        {
            for (int j = 0; j < _brojKolona; j++)
            {
                Sjediste &s = _sjedista[i][j]; //bez & bi program pao jer bi pokusavali da izbrisemo nesto sto je vec obrisano u dealokaciji
                    s.Ispis();
                cout << " ";
            }cout << endl;
        }
    }

    //Z2.13
    ~Sala() {
        delete[] _naziv;
        _naziv = nullptr;
        for (int i = 0; i < _brojRedova; i++)
        {
            delete[] _sjedista[i];
            _sjedista[i] = nullptr;
        }
        delete[] _sjedista;
        _sjedista = nullptr;
    }
};