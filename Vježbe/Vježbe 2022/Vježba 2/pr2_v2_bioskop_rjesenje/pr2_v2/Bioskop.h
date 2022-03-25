#pragma once
#include <iostream>
#include "PomocneFunkcije.h"
#include "Sala.h"
#include "Radnik.h"
using namespace std;

class Bioskop {
private:
    char* _naziv;
    char _adresa[100];

    int* _maxBrojDvorana; // pokazivac na varijablu (obezbijediti da sadrzi vrijednost velicine niza)
    int _trenutnoDvorana; //brojac objekata u dinamickom nizu (pocinje od 0)
    Sala* _dvorane; // pokazivac na niz objekata

    int _trenutnoUposlenika; //brojac
    Radnik* _uposlenici[50] = { nullptr }; // niz pokazivaca na objekte tipa Radnik

public:
    //Z4.1
    Bioskop(const char* naziv, const char* adresa, int maxBrojDvorana) {
        _naziv = AlocirajIKopiraj(naziv);
        strcpy_s(_adresa, 100, adresa);
        _maxBrojDvorana = new int;
        *_maxBrojDvorana = maxBrojDvorana;
        _trenutnoDvorana = 0;
        _dvorane = new Sala[*_maxBrojDvorana];
        _trenutnoUposlenika = 0;
    }

    //Z4.3
    void SetNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    //Z4.4
    char* GetNaziv() const { return _naziv; }
    const char* GetAdresa() const { return _adresa; }
    int GetMaxBrojDvorana() const { return *_maxBrojDvorana; }
    int GetTrenutnoDvorana() const { return _trenutnoDvorana; }

    //Z4.5
    bool DodajDvoranu(Sala& dvorana) {
        if (_trenutnoDvorana == *_maxBrojDvorana)
            return false;
        _dvorane[_trenutnoDvorana].SetNaziv(dvorana.GetNaziv());
        _dvorane[_trenutnoDvorana].SetSjedista(dvorana.GetBrojRedova(), dvorana.GetBrojKolona());
        _trenutnoDvorana++;
        return true;
    }
    //Z4.6
    bool DodajUposlenika(Radnik& uposlenik) {
        if (_trenutnoUposlenika == 50)
            return false;
        const char* ime = uposlenik.GetIme();
        const char* prezime = uposlenik.GetPrezime();
        Datum datum = uposlenik.GetDatumRodjenja();
        bool spol = uposlenik.GetSpol();
        const char* radnoMjesto = uposlenik.GetRadnoMjesto();
        const char* grad = uposlenik.GetGrad();
        const char* email = uposlenik.GetEmail();
        _uposlenici[_trenutnoUposlenika] = new Radnik(ime, prezime, datum, spol, radnoMjesto, grad, email);
        _trenutnoUposlenika++;
        return true;
    }
    //Z4.7
     //Ispisati naziv kina, adresu, nazive dvorana, te imena i prezimena uposlenika
    void Ispis()
    {
        cout << "Naziv: " << _naziv << endl;
        cout << "Adresa: " << _adresa << endl;
        cout << "*******************DVORANE**********************\n";
        for (int i = 0; i < _trenutnoDvorana; i++)
            cout << _dvorane[i].GetNaziv() << endl;
        cout << "*******************UPOSLENICI*******************\n";
        for (int i = 0; i < _trenutnoUposlenika; i++)
            cout << _uposlenici[i]->GetIme() << " " << _uposlenici[i]->GetPrezime() << endl;
    }
    //Z4.8
    ~Bioskop() {
        delete[] _naziv;
        _naziv = nullptr;
        delete _maxBrojDvorana;
        _maxBrojDvorana = nullptr;
        delete[] _dvorane;
        _dvorane = nullptr;
        for (int i = 0; i < _trenutnoUposlenika; i++) {
            delete _uposlenici[i]; //Poziva se dtor za objekat na kojeg pokazuje pokazivac '_uposlenici[i]'
            _uposlenici[i] = nullptr;
        }
    }
};