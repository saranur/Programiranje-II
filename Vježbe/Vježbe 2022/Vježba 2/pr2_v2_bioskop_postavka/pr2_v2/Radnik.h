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
    //Z3.1
    Radnik() {
        throw exception("potrebno implementirati");
    }
    //Z3.2
    Radnik(const char* ime, const char* prezime, Datum datum, bool spol, const char* radnoM, const char* grad, const char* email) {
        throw exception("potrebno implementirati");
    }

    //Z3.3
    char* GetIme() const { throw exception("potrebno implementirati"); }
    char* GetPrezime() const { throw exception("potrebno implementirati"); }
    Datum GetDatumRodjenja() const { throw exception("potrebno implementirati"); }
    bool GetSpol() const { throw exception("potrebno implementirati"); }
    const char* GetRadnoMjesto() const { throw exception("potrebno implementirati"); }
    char* GetGrad() const { throw exception("potrebno implementirati"); }
    const char* GetEmail() const { throw exception("potrebno implementirati");; }

    //Z3.4
    void SetIme(const char* ime) {
        throw exception("potrebno implementirati");
    }
    void SetPrezime(const char* prezime) {
        throw exception("potrebno implementirati");
    }
    void SetDatumRodjenja(Datum datum) {
        throw exception("potrebno implementirati");
    }
    void SetSpol(bool spol) {
        throw exception("potrebno implementirati");
    }
    void SetRadnoMjesto(const char* radnoMjesto) {
        throw exception("potrebno implementirati");
    }
    void SetGrad(const char* grad) {
        throw exception("potrebno implementirati");
    }
    void SetEmail(const char* email) {
        throw exception("potrebno implementirati");
    }
    //Z3.5
    void Ispis() {
        throw exception("potrebno implementirati");
    }
    //Z3.6
    ~Radnik() {
        throw exception("potrebno implementirati");
    }
};