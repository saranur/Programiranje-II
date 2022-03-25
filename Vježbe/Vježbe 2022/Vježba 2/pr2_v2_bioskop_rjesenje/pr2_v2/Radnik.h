#pragma once
#include <iostream>
#include "PomocneFunkcije.h"
#include "Datum.h"
using namespace std;


class Radnik {
private:
    char* _ime;
    char* _prezime;
    Datum* _datumRodjenja;
    bool* _spol;
    char _radnoMjesto[100];
    char* _grad;
    char _email[100];
public:
    //Z3.1 - dflt construktor 
    Radnik() {
        _ime = nullptr;
        _prezime = nullptr;
        _datumRodjenja = nullptr;
        _spol = nullptr;
        strcpy_s(_radnoMjesto, 100, " nema radnog mjesta ");
        _radnoMjesto ;
        _grad = nullptr;
        strcpy_s(_email, 100, " nije unesen email ");

    }
    //Z3.2 - korisnicki definiran konstruktor 
    Radnik(const char* ime, const char* prezime, Datum datum, bool spol, const char* radnoM, const char* grad, const char* email) {
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prezime);
        _datumRodjenja = new Datum(datum.GetDan(), datum.GetMjesec(), datum.GetGodina());
        _spol = new bool(spol);
        strcpy_s(_radnoMjesto, 100,radnoM);
        _grad = AlocirajIKopiraj(grad);
        strcpy_s(_email, 100, email);
    }

    //Z3.3
    char* GetIme() const { return _ime; }
    char* GetPrezime() const { return _prezime; }
    Datum GetDatumRodjenja() const { return *_datumRodjenja; }
    bool GetSpol() const { return *_spol; }
    const char* GetRadnoMjesto() const { return _radnoMjesto; }
    char* GetGrad() const { return _grad; }
    const char* GetEmail() const { return _email; }

    //Z3.4
    void SetIme(const char* ime) {
        
        _ime = AlocirajIKopiraj(ime);

    }
    void SetPrezime(const char* prezime) {
        
        _prezime = AlocirajIKopiraj(prezime);
    }
    void SetDatumRodjenja(Datum datum) {
        _datumRodjenja = new Datum(datum.GetDan(), datum.GetMjesec(), datum.GetGodina());
    }
    void SetSpol(bool spol) {
        _spol = new bool(spol);
    }
    void SetRadnoMjesto(const char* radnoMjesto) {
        strcpy_s(_radnoMjesto, 100, radnoMjesto);
    }
    void SetGrad(const char* grad) {
        _grad = AlocirajIKopiraj(grad);
    }
    void SetEmail(const char* email) {
        strcpy_s(_email, 100, email);
    }
    //Z3.5
    void Ispis() {
        cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
        cout << "Datum Rodjenja: ";
            _datumRodjenja->Ispis();
            cout << endl;
            cout << "Spol: " << ((*_spol == 1) ? "Musko" : "Zensko") << endl;
            cout << "Radno mjesto: " << _radnoMjesto << endl;
            cout << "Grad: " << _grad << endl;
            cout << "Email: " << _email << endl;

    }
    //Z3.6
    ~Radnik() {
        delete[] _ime;
        delete[] _prezime;
        delete[] _datumRodjenja;
        delete _spol;
        delete[] _grad;
    }
};