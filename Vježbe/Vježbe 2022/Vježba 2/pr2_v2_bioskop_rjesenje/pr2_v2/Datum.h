#pragma once
#include <iostream>
using namespace std;

class Datum
{
private:
    int _dan;
    int _mjesec;
    int _godina;
public:
    //Z1.1 Dflt. ctor [Postaviti na dflt. vrijednosti (1.1.2021)]
    Datum() {
        _dan = 1;
        _mjesec = 1;
        _godina = 2021;
    }
    //Z1.2 User-def. ctor
    Datum(int d, int m, int g) {
        _dan = d;
        _mjesec = m;
        _godina = g;
    }
    //Z1.3
    int GetDan() const { return _dan; } //const govori da se ta varijabla/objekat ili bilo sta u ovom dijelu(funkciji) nece modificirati vec se se samo preuzimati vrijednost  
    int GetMjesec() const { return _mjesec; }
    int GetGodina() const { return _godina; }
    void SetDan(int dan) {
        _dan = dan;
    }
    void SetMjesec(int mjesec) {
        _mjesec = mjesec;
    }
    void SetGodina(int godina) {
        _godina = godina;
    }
    //Z1.4
    void Ispis() {
        cout << _dan << "." << _mjesec << "." << _godina;
    }
    //Z1.5
    ~Datum() {
    }
};
