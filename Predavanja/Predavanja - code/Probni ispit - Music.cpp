#include <iostream>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
*****************************************************************************/

char* AlocirajIKopiraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;

}
const char* crt = "\n----------------------------------------------------\n";

class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int d, int m, int g) {
        _dan = new int(d);
        _mjesec = new int(m);
        _godina = new int(g);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator =(const Datum& obj) {
        //nemamo potrebe za ponovnom alokacijom 
       *_dan = *obj._dan;
       *_mjesec = *obj._mjesec;
       *_godina = *obj._godina;
       return *this;
    }
    ~Datum() {
        delete _dan;  _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<<(ostream& COUT, Datum obj) {
        COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina << endl;
        return COUT;
    }
};

template<class T, int velicina>
class FITArray {
    T _niz[velicina];
    int _trenutno;
    bool _dozvoliDupliciranje;
    bool ProvjeriDaLiPostoji(T obj) {
        for (size_t i = 0; i < _trenutno; i++)
            if (_niz[i] == obj) //u nasoj klasi tipa T moramo imati operator ==
                return true;
        return false; 
    }
public:

    FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
    FITArray(const FITArray& obj) {
        _trenutno = obj._trenutno;
        _dozvoliDupliciranje = obj._dozvoliDupliciranje;
        for (size_t i = 0; i < _trenutno; i++)
            _niz[i] = obj._niz[i]; //operator dodjele 
    }
    int GetTrenutno() { return _trenutno; }
    T* GetNiz() { return _niz; }
    bool operator +=(T obj) { //bool jer se koristi za provjeru 
        if (_trenutno >= velicina)
            return false;
        if (!_dozvoliDupliciranje && ProvjeriDaLiPostoji(obj))
            return false;
        _niz[_trenutno++] = obj;
        return true;
    }
    bool operator -=(T obj) {
        bool uklonjen = false;
        for (size_t i = 0; i < _trenutno; i++)
        {
            if (_niz[i] == obj) {
                for (size_t j = i; j < _trenutno - 1; j++)
                    _niz[j] = _niz[j + 1];
                uklonjen = true;
                _trenutno--;
            }
        }
        return uklonjen;
    }
    friend ostream& operator <<(ostream& COUT, const FITArray &obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj._niz[i] <<", ";
        return COUT;
    }
    FITArray operator() (int OD, int DO){
        FITArray<T, velicina>temp;
        if (OD >= 0 && OD < DO) {
            if (DO > _trenutno)
                DO = _trenutno;
            for (size_t i = OD; i < DO; i++)
                temp += _niz[i];

        }
        return temp;
    }
    ~FITArray()
    {

    }
};


class PolozeniPredmet {
    char* _naziv;
    int _ocjena;
    Datum _datumPolaganja;
    void Dealociraj() {
        if (_naziv != nullptr)
            delete[] _naziv;
        _naziv = nullptr;
    }
public:
    PolozeniPredmet(Datum datumPolaganja=Datum(1,1,1900), const char* naziv="", int ocjena=5)
        :_datumPolaganja(datumPolaganja)
    {
        _ocjena = ocjena;
        _naziv = AlocirajIKopiraj(naziv);
    }
    PolozeniPredmet(const PolozeniPredmet &obj)
        :_datumPolaganja(obj._datumPolaganja)
    {
        _ocjena = obj._ocjena;
        _naziv = AlocirajIKopiraj(obj._naziv);
    }  

    PolozeniPredmet & operator =(const PolozeniPredmet& obj)
    {
        if(this!=&obj){
            _datumPolaganja = obj._datumPolaganja;
            _ocjena = obj._ocjena;
            Dealociraj();
            _naziv = AlocirajIKopiraj(obj._naziv);
        }
        return *this;
    }
    ~PolozeniPredmet() { Dealociraj(); }

    friend ostream& operator<<(ostream& COUT, const PolozeniPredmet& obj) {
        COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
        return COUT;
    }
    int GetOcjena() { return _ocjena; }
    bool operator==(const PolozeniPredmet& obj) {
        return strcmp(obj._naziv, _naziv) == 0 && obj._ocjena == _ocjena;
    }
};



class Student {
    static int _indeksBrojac; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 200000
    const int _indeks;
    char* _imePrezime;
    FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
    void Dealociraj() {
        if (_imePrezime != nullptr)
            delete[] _imePrezime;
        _imePrezime = nullptr;
    }
public:
    Student(const char* imePrezime)
        :_indeks(_indeksBrojac++)
    {
        _imePrezime = AlocirajIKopiraj(imePrezime);
    }
    Student(const Student& obj)
        :_indeks(_indeksBrojac++),
        _polozeniPredmeti(obj._polozeniPredmeti)
    {
        _imePrezime = AlocirajIKopiraj(obj._imePrezime);
    }
    Student& operator=(const Student& obj)
    {
        if (this != &obj) {
            _polozeniPredmeti = obj._polozeniPredmeti; //operator dodjele za FITArray
            Dealociraj();
            _imePrezime = AlocirajIKopiraj(obj._imePrezime);
        }
        return *this;
    }
    ~Student() {
        Dealociraj();
    }
    friend ostream& operator<<(ostream& COUT, Student& obj) {
        COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
        return COUT;
    }
    bool DodajPredmet(PolozeniPredmet &obj) {
       return  _polozeniPredmeti += obj;
    }
    float GetProsjek() {
        float suma = 0;
        int trenutnoOcjena = _polozeniPredmeti.GetTrenutno();
        if (trenutnoOcjena == 0)
            return 5;
        for (size_t i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
        {
            suma += _polozeniPredmeti.GetNiz()[i].GetOcjena();
        }
        return suma / trenutnoOcjena;
    }
};
int Student::_indeksBrojac = 200000;
void main() {
    const int max = 20;

    Datum jucer(19, 4, 2021), danas(20, 4, 2021), sutra(21, 4, 2021);
    cout << jucer << danas << sutra << endl;
    jucer = danas;
    cout << jucer << danas << sutra << endl;

    //parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
    FITArray<int, max> nizIntegera(false);

   for (size_t i = 0; i < max - 1; i++)
       nizIntegera += i;//dodaje novog clana niza

    if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
        cout << "Element nije dodan u niz" << endl;

    cout << crt << nizIntegera << crt; //ispisuje sve clanove niza


    nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
    nizIntegera -= 17;

    FITArray<int, max> noviNizIntegera(nizIntegera);

    cout << crt << noviNizIntegera << crt;

    /*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. 
    U slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */
    
    cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

    Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

    PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);

    adel.DodajPredmet(prII);
    adel.DodajPredmet(prIII);
    cout << adel << endl;
    //vraca prosjecnu ocjenu studenta
    cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

    jasmin = adel;
    cout << jasmin << endl;
    cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
}
