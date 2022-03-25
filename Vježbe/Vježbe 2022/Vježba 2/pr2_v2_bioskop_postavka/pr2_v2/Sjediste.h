#pragma once
#include <iostream>
#include "PomocneFunkcije.h"
using namespace std;


class Sjediste {
private:
    char* _sjedisteId; // Koristiti GetRandomString funkciju prilikom inicijalizacije [neka je duzina stringa 10]
    char _red; //A-Z
    int _kolona; //1,2,3,..., 100
public:
    //Z2.1
    //Dflt. ctor
    //Postaviti red na ' ' a kolonu na 0
    Sjediste() {
        _sjedisteId = GetRandomString(10);
        _red = ' ';
        _kolona = 0;
    }
    //Z2.2
    //User-def. ctor
    Sjediste(char red, int kolona) {
        _sjedisteId = GetRandomString(10);
        _red = red;
        _kolona = kolona;
    }
    //Z2.3
    char GetRed() const { return _red; }
    int GetKolona() const { return _kolona; }
    //Z2.4
    void SetRed(char red) {
        _red = red;
    }
    void SetKolona(int kolona) {
        _kolona = kolona;
    }
    //Z2.5
    //Ispisati sjediste u formatu: "[A-13]"
    void Ispis() {
        cout << "[" << _red << "-" << _kolona << "]";
    }
    //Z2.6
    ~Sjediste() {
        delete[] _sjedisteId;
        _sjedisteId = nullptr;
    }
};