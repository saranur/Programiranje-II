#pragma once
#include <iostream>
using namespace std;


//Z1.0
char* AlocirajIKopiraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}


//Vraca random string odredjene duzine, kojeg sacinjavaju velika i mala slova 
char* GetRandomString(int duzina) {
    int velicina = duzina + 1;
    char* randomString = new char[velicina];
    for (int i = 0; i < velicina; i++) {
        int random_ascii = rand() % 26 + 65;
        char slovo = (char)random_ascii;
        bool pretvoriUMalo = (bool)(rand() % 2);
        if (pretvoriUMalo)
            slovo = tolower(slovo);
        randomString[i] = slovo;
    }
    randomString[velicina - 1] = '\0';
    return randomString;
}
