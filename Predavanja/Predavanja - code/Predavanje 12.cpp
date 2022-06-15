#include <iostream>
using namespace std;

char* AlocirajIKopiraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, sadrzaj);
    return novi;
}
const char* crt = "\n----------------------------------------------\n";
class NezodvoljenaOperacija :public exception {

    char* _vrijeme;
    char* _datum;
    char* _metoda;
    char* _fajl;
    int _linijaKoda;
public:
    NezodvoljenaOperacija(const char* poruka, const char* vrijeme, const char* datum, const char* metoda, const char* fajl,int linijaKoda)
        :exception (poruka)
    {
        _vrijeme = AlocirajIKopiraj(vrijeme);
        _datum = AlocirajIKopiraj(datum);
        _metoda = AlocirajIKopiraj(metoda);
        _fajl = AlocirajIKopiraj(fajl);
        _linijaKoda = linijaKoda;
    }
    ~NezodvoljenaOperacija()
    {
        delete[] _vrijeme;
        delete[] _datum;
        delete[] _metoda;
        delete[] _fajl;
        _vrijeme = nullptr;
        _datum = nullptr;
        _metoda = nullptr;
        _fajl = nullptr;
    }
    friend ostream& operator << (ostream & COUT, const NezodvoljenaOperacija & obj) {
        COUT <<crt<< obj.what() << endl;
        COUT << obj._datum << " " << obj._vrijeme << endl;
        COUT << obj._fajl << endl << obj._metoda << " @ " << obj._linijaKoda << crt;
        return COUT;
    }
};

class Calc {
    double _rezultat;
    bool _greska;
public:
    Calc()
    {
        _rezultat = 0;
        _greska = false;
    }
    Calc& operator +=(double vrijednost) {
        _rezultat += vrijednost;
        return *this;
    }
    Calc& operator /=(double vrijednost) {
        if (vrijednost == 0)
            // throw 69874;  //throw prekida izvrsenje metode, ostatak se nece izvrsiti
            throw NezodvoljenaOperacija ("Nije dozvoljeno dijeljenje s nulom! ",
            __TIME__, __DATE__, __FUNCTION__,__FILE__, __LINE__);
        _rezultat /= vrijednost;
        return *this;
    }
    friend ostream& operator <<(ostream& COUT, const Calc& obj) {
        COUT << "Rezultat -> " << obj._rezultat <<"   Greska -> " << boolalpha << obj._greska;
        return COUT;
    }
    bool GetGreska() { return _greska; }
    void ResetGreska() { _greska = false; }
};


void main() {
    Calc fitCalc;
    fitCalc += 20;
    cout << fitCalc << endl;
    double unos;
    try     //try blok mozemo imati samo jedan, dok catch blokova mozemo imati vise 
    {
        cout << "Vrijednost -> ";
        cin >> unos;
        fitCalc /= unos;
        cout << fitCalc << endl;
    }
    catch (NezodvoljenaOperacija & errObj)     //dio koji hvata mora biti istog tipa kao i throw
    {
        cout << "Desila se greska -> " <<endl<< errObj << endl;
    } 
    /*Prvo se stavljaju catch blokovi naizvedenijih klasa - npr. 
    ukoliko smo napravili svoju klasu Nedozvoljena operacija koja nasljedjuje klasu exception,
    i u catch bloku prvo pozvali exception klasu, izgubuli bi sve detalje koje smo dodali u nasu klasu Nedozvoljena operacija. */
     catch (exception& errObj) 
    {
        cout << "Desila se greska -> " << errObj.what() << endl;
    }
         
    catch (const char* errMsg) 
    {
        cout << "Desila se greska -> " << errMsg << endl;
    }
    catch (...) {

    }
    




}