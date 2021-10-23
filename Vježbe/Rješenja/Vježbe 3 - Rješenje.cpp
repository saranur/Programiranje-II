#include <iostream>
using namespace std;

/* ::NAPOMENA::
Radi jednostavnije izrade i lakseg testiranja zadataka, komentirajte testni dio koda, koji je obuhvacen funkcijama sa prefixom 'Zadatak'.
Kako budete implementirali odredjene funkcionalnosti, tada lagano pocnite sa 'otkrivanjem' komentiranih dijelova koda.
*/

//Koristene skracenice u komentarima
// dflt. = default
// user-def. = user-defined (korisnicki-definirano)
// ctor = constructor (konstruktor)
// copy ctor = copy constructor (konstruktor kopije)
// move ctor = move constructor (konstruktor premjestanja)

//Z1.0
char* AlocirajIKopiraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst)+1;
    char *novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
   }

int Min(int a, int b) {return a < b;}
int Max(int a, int b) {return a > b;}

class Datum
{
private:
    int* _dan;
    int* _mjesec;
    int* _godina;
public:
    //Z1.1 Dflt. ctor [Postaviti na dflt. vrijednosti]
    Datum() {
        _dan = new int(0); //ako stavimo na nullpointer, ako se cita nullpointer dodje do read access violation, sigurnije je alocirati novi prostor i stavili smo vrijednost na nula
        _mjesec = new int(0);
        _godina = new int(0);
    }
    //Z1.2 User-def. ctor
    Datum(int d, int m, int g) {
        _dan = new int(d);
        _mjesec = new int(m);
        _godina = new int(g);
    }
    //Z1.3 Copy ctor
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan); //alociramo prostor, s obzirom da se nalazimo u klasi datum koristimo int jer je tipa int
        _mjesec = new int(*obj._mjesec);
        _godina= new int(*obj._godina);
    }
    //Z1.4 Move ctor
    Datum(Datum&& obj) {
        _dan = obj._dan;
        obj._dan = nullptr; //da ne stavimo na nullptr program bi crashao jer bi imali dva pokazivaca koji bi pokazivali na istu vrijednost
        //nema smisla ne staviti na nullptr jer bookiramo memoriju bespotrebno, a cilj nam je da koristimo samo memoriju koju moramo
        _mjesec = obj._mjesec;
        obj._mjesec = nullptr;
        _godina = obj._godina;
        obj._godina = nullptr;
    }
    //Z1.5
    int GetDan() const { return *_dan; }
    int GetMjesec() const { return *_mjesec; }
    int GetGodina() const { return *_godina; }
    //Z1.6
    void SetDan(int dan) {
        if (_dan == nullptr)
            _dan = new int; //ako je nullptr onda alociraj prostor
        *_dan = dan; //ako nije nullptr onda pointer *_dan stavi na dan
    }
    void SetMjesec(int mjesec) { 
        if (_mjesec == nullptr)
            _mjesec = new int;
        *_mjesec = mjesec;
    }
    void SetGodina(int godina){
        if (_godina == nullptr)
            _godina = new int;
        *_godina = godina;
    }
    //Operator dodjele
    Datum& operator = (const Datum& datum) //Za korisnicki definisanu klasu ne mozemo koristiti operator dodjele
    //dok ga ne preklopimo 
    {
        // datum1=datum2;
        if (this == &datum)
            return *this; 
        if (_dan == nullptr)
            _dan = new int;
        if (_mjesec == nullptr)
            _mjesec = new int;
        if (_godina == nullptr)
            _godina = new int;
        *_dan = datum.GetDan();
        *_mjesec = datum.GetMjesec();
        *_godina = datum.GetGodina();
        return *this;
    }

    //Z1.7
    void Ispis()
    {
        cout << *_dan << "." << *_mjesec << "." << *_godina << endl;

    }
    //Z1.8
    ~Datum() {
        delete _dan;
        _dan = nullptr;
        delete _mjesec;
        _mjesec = nullptr;
        delete _godina;
        _godina = nullptr;
    }
};
class Glumac
{
private:
    char* _ime;
    char* _prezime;
    char* _zemljaPorijekla;
    Datum* _datumRodjenja;
    bool* _spol; //1-Muski, 0-Zenski
public:
    //Z2.0 Dflt. ctor
    Glumac() {
        _ime = nullptr; //Ovdje _ime stavlja na nullptr u memoriji 
        _prezime = AlocirajIKopiraj(""); //Ovdje ispisuje prazan prostor
        //Mozemo koristiti ili nullptr ili funkciju AlocirajIKopiraj
        _zemljaPorijekla = nullptr;
        _datumRodjenja = new Datum(); //Pozove se default ctor za Datum, da nemamo default ctora vec u klasi Datum, morali bi manuelno postaviti sve propertije klase datum na nullptr jer to default
        _spol = new bool;
    }
    //Z2.1 User-def. ctor
    Glumac(const char* ime, const char* prez, const char* zemlja, int d, int m, int g, bool spol) {
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prez);
        _zemljaPorijekla = AlocirajIKopiraj(zemlja);
        _datumRodjenja = new Datum(d, m, g);
        _spol = new bool(spol);
    }
    //Z2.2 Copy ctor
    Glumac(const Glumac& obj)
    {
        _ime = AlocirajIKopiraj(obj.GetIme());
        _prezime = AlocirajIKopiraj(obj._prezime);
        _zemljaPorijekla = AlocirajIKopiraj(obj._zemljaPorijekla);
        _datumRodjenja = new Datum(obj.GetDatumRodjenja());
        _spol = new bool(*obj._spol);
    }
    //Z2.3 Move ctor
    Glumac(Glumac&& obj)
    {
        _ime = obj._ime;
        obj._ime = nullptr; //ova logika vazi za sve pokazivace neovisno o tipu podatka
        _prezime = obj._prezime;
        obj._prezime = nullptr;
        _zemljaPorijekla = obj._zemljaPorijekla;
        obj._zemljaPorijekla = nullptr;
        _datumRodjenja = obj._datumRodjenja;
        obj._datumRodjenja = nullptr;
        _spol = obj._spol;
        obj._spol = nullptr;
        /* Da smo imali niz karaktera a ne pointer npr char _ime[40] koristili bi:
        strcpy_s(_ime, 40, obj._ime)
        strypcy_s(obj._ime, 40, "");

          */
    }
    //Z2.4
    char* GetIme() const { return _ime; }
    char* GetPrezime() const { return _prezime; }
    char* GetZemljaPorijekla() const { return _zemljaPorijekla; }
    Datum GetDatumRodjenja() const { return *_datumRodjenja;} //ovako se kreira nova lokacija
    //da je bilo Datum& GetDatumRodjenja() const { return *_datumRodjenja;} na istoj lokaciji bi se desavala promjena
    //Kada specifizramo samo tip podatka onda se poziva konstruktor kopije te klase, klase Datum u ovom slucaju
	
	bool GetSpol() const { return *_spol; }

    //Z2.5
    void SetIme(const char* ime)
    {
        delete[] _ime;
        //delete 0x->nullptr;
        //delete 
        _ime = AlocirajIKopiraj(ime);
    }
    void SetPrezime(const char* prezime)
    {
        delete[] _prezime;
        _prezime = AlocirajIKopiraj(prezime);
    }
    void SetZemljaPorijekla(const char* zemlja)
    {
        delete[] _zemljaPorijekla;
        _zemljaPorijekla = AlocirajIKopiraj(zemlja);
    }
    void SetDatumRodjenja(Datum datumRodjenja) //poziva se copy ctor , kreira se novi objekat i kopiraju se vrijednosti 
    {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum(); //Poziva se dflt ctor 

        _datumRodjenja->SetDan(datumRodjenja.GetDan()); //Dereferenciranje objekta _datumRodjenja sa ->
        _datumRodjenja->SetMjesec(datumRodjenja.GetMjesec());
        _datumRodjenja->SetGodina(datumRodjenja.GetGodina());
    }
    void SetSpol(bool spol)
    {
        if (_spol == nullptr)
            _spol = new bool;
        *_spol = spol;
    }

    //Z2.6
    void Ispis()
    {
        cout << "Ime i Prezime: " << _ime << " " << _prezime << endl;
        cout << "Zemlja porijekla: " << _zemljaPorijekla << endl;
        cout << "Datum rodjenja: ";
        _datumRodjenja -> Ispis();
        cout << "Spol: " << ((*_spol == true) ? "Musko" : "Zensko") << endl;
    }
    //Z2.7
    ~Glumac()
    {
        delete[] _ime;
        _ime = nullptr;
        delete[] _prezime;
        _prezime = nullptr;
        delete[] _zemljaPorijekla;
        _zemljaPorijekla = nullptr;
        delete _spol;
        _spol = nullptr;
    }
};

class Epizoda {
private:
    char* _naziv;
    int* _trajanje; //u minutama
    char _kratakSadrzaj[100];
    Datum _datumPremijere;
    int _maxBrojOcjena; // velicina niza
    int _trenutnoOcjena; //brojac
    int* _ocjene;
public:
    /* 
    Epizoda& operator = (const Epizoda& obj) 
    {
        if (this == &obj)
            return *this;
        _naziv = AlocirajIKopiraj(obj._naziv);
        _trajanje = obj._trajanje;
        strcpy_s(_kratakSadrzaj, 100, obj._kratakSadrzaj);
        _datumPremijere = obj._datumPremijere;
        _maxBrojOcjena = obj._maxBrojOcjena;
        _trenutnoOcjena = obj._trenutnoOcjena;
        _ocjene = obj._ocjene;
        return *this;
    }
    */
    //Z3.0
    //Settovati vrijednosti na defaultne
    Epizoda() : _datumPremijere() //ovdje se podrazumijeva dlft ctor tako da nije potreban header ovdje
    {
        _naziv = nullptr;
        _trajanje = nullptr;
        strcpy_s(_kratakSadrzaj, 100, "");
        //za _datumPremijere ne moramo nista, kada imamo objekat ne moramo nista raditi ovdje jer je dflt ctor vec pozvan pri inicijalizaciji
        _maxBrojOcjena = 0;
        _trenutnoOcjena = 0;
        _ocjene = nullptr;
    }
    //Z3.1
    Epizoda(const char* naziv, int trajanje, const char* kratakOpis, Datum datum, int ukupnoOcjena)
	    :_datumPremijere(datum.GetDan(), datum.GetMjesec(), datum.GetGodina()) //ovdje je neophodno dodati header inace ce pozvati dflt ctor
        //headere koristimo kada imamo klasicni objekat koji je atribut strukture, da je bilo *_datum premijere headeri ne bi bili potrebni 
	{
        _naziv = AlocirajIKopiraj(naziv);
        _trajanje = new int(trajanje);
        strcpy_s(_kratakSadrzaj, 100, kratakOpis);
        _datumPremijere = datum;
        _maxBrojOcjena = ukupnoOcjena;
        _trenutnoOcjena = 0;
        _ocjene = new int[_maxBrojOcjena];
    }
    //Z3.2
    Epizoda(const Epizoda& obj) //Po konvenciji trebamo koristiti za sve korisnicki definirane propertije, u headeru trebamo koristiti 
        :_datumPremijere(obj._datumPremijere) //ctor kopije od child klase poziva ctor kopije od parent klase
    //Parent klasa je svaka klasa koja ima instancu unutar child klase, u ovom slucaju parent je Datum, a child Epizoda
    {
        _naziv = AlocirajIKopiraj(obj._naziv);
        _trajanje = new int(*obj._trajanje);
        strcpy_s(_kratakSadrzaj, 100, obj._kratakSadrzaj);
        _datumPremijere = obj._datumPremijere;
        _maxBrojOcjena = obj._maxBrojOcjena;
        _trenutnoOcjena = obj._trenutnoOcjena;
        _ocjene = new int[_maxBrojOcjena];
        for (int i = 0; i < _trenutnoOcjena; i++)
            _ocjene[i] = obj._ocjene[i];
        
    }
    //Z3.3
   

    //Z3.4
    char* GetNaziv() const { return _naziv; }
    int GetTrajanje() const { return *_trajanje; }
    const char* GetKratakSadrzaj() const { return _kratakSadrzaj; }
    Datum GetDatumPremijere() const { return _datumPremijere; }
    int GetTrenutnoOcjena() const { return _trenutnoOcjena; }
    int GetMaxBrojOcjena() const { return _maxBrojOcjena; }

    //Z3.5
    //Vratiti vrijednost na lokaciji specificiranoj ulaznim parametrom 'index'
    //Ukoliko je proslijedjena nevalidna vrijednost, potrebno je vratiti element niza sa najblizim validnim indeksom
    //Npr. Ako je index = -5, vratiti vrijednost _ocjene na indexu 0; Isto vazi i za indekse vece od vrijednosti brojaca '_trenutnoOcjena'.
    int GetOcjena(int index) const
    {
            Max(index, 0); //max funkcija od dva broja vraca veci 
            Min( _trenutnoOcjena-1, index); //min od dva broja vraca manji

        return _ocjene[index];
    }
    //Z3.6
    void SetNaziv(const char* naziv)
    {
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    void SetTrajanje(int trajanje)
    {
        if (_trajanje == nullptr)
            _trajanje = new int;
        *_trajanje = trajanje;
    }
    void SetKratakSadrzaj(const char* kratakSadrzaj)
    {
        strcpy_s(_kratakSadrzaj, 100, kratakSadrzaj);
    }
    void SetDatumPremijere(Datum datum)
    {
        _datumPremijere.SetDan(datum.GetDan());
        _datumPremijere.SetMjesec(datum.GetMjesec());
        _datumPremijere.SetGodina(datum.GetGodina());

    }

    //Z3.7
    //Prosiriti niza _ocjene na sljedeci nacin:
    //  *Konstruisati novi niz velicine [_maxBrojOcjena + prosiriZa]
    //  *Kopirati vrijednosti iz starog niza u novi niz
    //  *Dealocirati stari niz
    void ProsiriNizOcjena(int prosiriZa)
    {
        if(_ocjene==nullptr){
            _ocjene = new int[prosiriZa];
            return;
        }
        
        int *temp = _ocjene; //stari niz
        int size = _maxBrojOcjena + prosiriZa;
        _ocjene = new int[size];
        for (int i = 0; i < _trenutnoOcjena; i++)
            _ocjene[i] = temp[i];
        delete[] temp;
        temp=nullptr;
    }

    //Z3.8
    //Ukoliko je brojac dosao do kraja (jednak velicini niza), uraditi prosirivanje niza za 10 elemenata;
    void DodajOcjenu(int ocjena)
    {
        if (_trenutnoOcjena == _maxBrojOcjena)
            ProsiriNizOcjena(10);
        _ocjene[_trenutnoOcjena] = ocjena;
        _trenutnoOcjena++;
    }
    //Z3.9
    bool UkloniZadnjuOcjenu()
    {
        if (_trenutnoOcjena == 0) //ako je nula nemamo sta izbrisati
            return false; //vrati netacno 
        _trenutnoOcjena--; //smanji ocjene 
        return true; //da, izbrisana je ocjena 

    }
    //Z3.10
    float GetProsjecnaOcjena()
    {
        float prosjek = 0.0;
        if (_trenutnoOcjena == 0)
            return prosjek;
        
            for (int i = 0; i < _trenutnoOcjena; i++)
                prosjek += _ocjene[i];
            
    return prosjek /_trenutnoOcjena;
    }
    //Z3.11
    void Ispis()
    {
        cout << "Naziv je: " << _naziv << endl;
        cout << "Trajanje: " << *_trajanje << endl;
        cout << "Kratak sadrzaj: " << _kratakSadrzaj << endl;
        cout << "Datum premijere: ";
        _datumPremijere.Ispis();
        cout << "Prosjecna ocjena: " << GetProsjecnaOcjena() << endl;
    }
    //Z3.12
    
    ~Epizoda()
    {
        delete[] _naziv;
    	delete _ocjene;
        _naziv = nullptr;
        _ocjene = nullptr;
        delete _ocjene;
        delete _trajanje;
        _trajanje = nullptr;
    }
};


class Uloga {
private:
    Glumac* _glumac;
    char* _opis;
    char* _tipUloge; //Glavna, sporedna, epizodna, statista, gostujuca zvijezda, cameo ...
public:
    //Z4.0
    Uloga() 
    {
        _glumac = nullptr;
        _opis = nullptr;
        _tipUloge = nullptr;
    }
    //Z4.1
    Uloga(Glumac& glumac, const char* opis, const char* tip)
    {
        _glumac = new Glumac(glumac);
        _opis = AlocirajIKopiraj(opis);
        _tipUloge = AlocirajIKopiraj(tip);
    }
    //Z4.2
    Uloga(const Uloga& obj)
    {
        _glumac = new Glumac(*obj._glumac);
        _opis = AlocirajIKopiraj(obj._opis);
        _tipUloge = AlocirajIKopiraj(obj._tipUloge);
        //mozemo koristiti ili getere ili direktno pristupati atributima 
    }
    //Z4.3
    Uloga(Uloga&& obj)
    {
        _glumac = obj._glumac;
        obj._glumac = nullptr;
        _opis = obj._opis;
        obj._opis = nullptr;
        _tipUloge = obj._tipUloge;
        obj._tipUloge = nullptr;
    }
    //Z4.4
    Glumac GetGlumac() const { return *_glumac; }
    char* GetOpis() const { return _opis; }
    char* GetTipUloge() const { return _tipUloge; }
    //Z4.5
    void SetGlumac(Glumac glumac)
    { 
        if (_glumac == nullptr)
            _glumac = new Glumac;
        _glumac->SetIme(glumac.GetIme());
        _glumac->SetPrezime(glumac.GetPrezime());
        _glumac->SetDatumRodjenja(glumac.GetDatumRodjenja());
        _glumac->SetSpol(glumac.GetSpol());
        _glumac->SetZemljaPorijekla(glumac.GetZemljaPorijekla());

    }
    void SetOpis(const char* opis)
    {
        delete[] _opis;
        _opis = AlocirajIKopiraj(opis);
    }
    void SetTipUloge(const char* tipUloge)
    {
        delete[] _tipUloge;
        _tipUloge = AlocirajIKopiraj(tipUloge);
    }
    //Z4.6
    void Ispis()
    {
        cout << "Glumac: " << endl;
            _glumac->Ispis();
            cout << "Opis: " << _opis << endl;
            cout << "Tip uloge: " << _tipUloge << endl;
    }
    //Z4.7
    ~Uloga()
    {
        delete _glumac,
        _glumac = nullptr;
        delete[] _opis;
    	delete[] _tipUloge;
        _opis = _tipUloge = nullptr;
    }
};

class Serija {
private:
    char* _naziv;
    int _trenutnoUloga;
    Uloga* _uloge[50] = { nullptr }; //Svi elementi (pokazivaci) se postavljaju na NULL
    int _maxBrojEpizoda;
    int _trenutnoEpizoda;
    Epizoda* _epizode;
public:
    //Z5.0
    Serija()
    {
        _naziv = nullptr;
        _trenutnoUloga = 0;
        _maxBrojEpizoda = 0;
        _trenutnoEpizoda = 0;
        _epizode = nullptr;
    }
    //Z5.1

    Serija(const char* naziv, int maxBrojEpizoda)
    {
        _naziv = AlocirajIKopiraj(naziv);
        _maxBrojEpizoda = maxBrojEpizoda;
        _trenutnoUloga = 0;
        _trenutnoEpizoda = 0;
        _epizode = new Epizoda[_maxBrojEpizoda];
    }
    //Z5.2
    Serija(const Serija& obj)
    {
        _naziv = AlocirajIKopiraj(obj._naziv);
        _trenutnoUloga = obj._trenutnoUloga;
        _maxBrojEpizoda = obj._maxBrojEpizoda;
        for (int i = 0; i < _trenutnoUloga; i++)
            _uloge[i] = new Uloga(*obj._uloge[i]);
        _trenutnoEpizoda = obj._trenutnoEpizoda;
        _epizode = new Epizoda[_maxBrojEpizoda];

         for (int i = 0; i < _trenutnoEpizoda; i++)
        {
        _epizode[i].SetNaziv(obj._epizode[i].GetNaziv());
        _epizode[i].SetTrajanje(obj._epizode[i].GetTrajanje());
        _epizode[i].SetKratakSadrzaj(obj._epizode[i].GetKratakSadrzaj());
        _epizode[i].SetDatumPremijere(obj._epizode[i].GetDatumPremijere());
        for (int j = 0; j < obj._epizode[i].GetTrenutnoOcjena(); j++)
            _epizode[i].DodajOcjenu(obj._epizode[i].GetOcjena(j));
        }

    }


    //Z5.3
    bool DodajUlogu(Uloga& uloga)
    {
        if (_trenutnoUloga == 50)
            return false;
        _uloge[_trenutnoUloga] = new Uloga(uloga);
        _trenutnoUloga++;
        return true;
    }
    //Z5.4
    bool DodajEpizodu(Epizoda& ep)
    {
        /* 
        if (_trenutnoEpizoda == _maxBrojEpizoda)
            return false;   
        _epizode[_trenutnoEpizoda] = ep;
        _trenutnoEpizoda++;
        return true;
        */
        if (_trenutnoEpizoda == _maxBrojEpizoda)
            return false;

        _epizode[_trenutnoEpizoda].SetNaziv(ep.GetNaziv());
        _epizode[_trenutnoEpizoda].SetTrajanje(ep.GetTrajanje());
        _epizode[_trenutnoEpizoda].SetKratakSadrzaj(ep.GetKratakSadrzaj());
        _epizode[_trenutnoEpizoda].SetDatumPremijere(ep.GetDatumPremijere());

        for (int i = 0; i < ep.GetTrenutnoOcjena(); i++) {
            int ocjena = ep.GetOcjena(i);
            _epizode[_trenutnoEpizoda].DodajOcjenu(ocjena);
        }
        _trenutnoEpizoda++;
        return true;

    }
    //Z5.5
    Epizoda* GetNajboljeOcijenjenaEpizoda()
    {
        float najboljeOcjene = 0.0;
    	Epizoda* povratni = _epizode;
        for (int i = 0; i < _trenutnoEpizoda; i++)
        {
            if(najboljeOcjene<=_epizode[i].GetProsjecnaOcjena())
            {
                najboljeOcjene = _epizode[i].GetProsjecnaOcjena();
                povratni = _epizode+ i;
            }
        }
            return povratni;
    }
    //Z5.6 :: Pored ostalih atributa ispisati i sve uloge i sve epizode
    void Ispis()
    {
        cout << "Naziv serije: " << _naziv << endl;
        cout << "Broj uloga: " << _trenutnoUloga << endl;
        for (int i = 0; i < _trenutnoUloga; i++)
        {
            cout << "**************************************************\n";
            cout << "Uloga " << "[" << i + 1 << "]" << endl;
            cout << "---------------------------------------------\n";
            _uloge[i]->Ispis();
            cout << "---------------------------------------------\n";
        }
        cout << "Broj epizoda: " << _trenutnoEpizoda << endl;
        for (int i = 0; i < _trenutnoEpizoda; i++)
        {
            cout << "**************************************************\n";
            cout << "Epizoda " << "[" << i + 1 << "]" << endl;
            cout << "---------------------------------------------\n";
            _epizode[i].Ispis();
            cout << "---------------------------------------------\n";
        }

    }
    //Z5.7
   
    ~Serija()
    {
        delete[] _naziv;
        _naziv = nullptr;
        for (int i = 0; i < 50; i++)
        {
            delete _uloge[i];
            _uloge[i] = nullptr;
        }
        delete[] _epizode;
        _epizode = nullptr;
    }
};


void Zadatak1() {
    cout << "Testiranje klase 'Datum'\n\n";
    Datum novaGodina; //Def. ctor
    novaGodina.SetDan(1);
    novaGodina.SetMjesec(1);
    novaGodina.SetGodina(2021);
    novaGodina.Ispis();
    cout << endl;
    //
    Datum prviFebruar(novaGodina.GetDan(), novaGodina.GetMjesec() + 1, novaGodina.GetGodina());
    prviFebruar.Ispis();
    cout << endl;

    Datum prviMart(1, 3, 2021); //User-def. ctor
    prviMart.Ispis();
    cout << endl;

    Datum danSale(prviMart); //Copy ctor
    danSale.SetMjesec(4);
    danSale.Ispis();
    cout << endl;

    Datum praznikRada(move(danSale)); //Move ctor
    praznikRada.SetMjesec(5);
    praznikRada.Ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;
}

void Zadatak2() {
    cout << "Testiranje klase 'Glumac'\n\n";
    Glumac ryanGosling; //Def. ctor
    ryanGosling.SetIme("Ryan");
    ryanGosling.SetPrezime("Gosling");
    ryanGosling.SetSpol(1);
    ryanGosling.SetDatumRodjenja(Datum(1, 1, 1980));
    ryanGosling.SetZemljaPorijekla("Kanada");
    ryanGosling.Ispis();
    cout << endl;
    //
    Glumac harrisonFord("Harrison", "Ford", "SAD", 2, 2, 1955, 1); //User-def. ctor
    Glumac michellePfeifer("Michelle", "Pfeiffer", "SAD", 3, 3, 1966, 0); //User-def. ctor
    harrisonFord.Ispis();
    cout << endl;
    michellePfeifer.Ispis();
    cout << endl;

    Glumac jackNicholson(harrisonFord); // copy ctor
    jackNicholson.SetIme("Jack");
    jackNicholson.SetPrezime("Nicholson");
    jackNicholson.SetDatumRodjenja(Datum(1, 4, 1945));
    jackNicholson.Ispis();
    cout << endl;

    Glumac heathLedger(move(jackNicholson)); //move ctor
    heathLedger.SetIme("Heath");
    heathLedger.SetPrezime("Ledger");
    heathLedger.SetDatumRodjenja(Datum(5, 3, 1983));
    heathLedger.SetZemljaPorijekla("Australija");
    heathLedger.Ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;
}

void Zadatak3() {
    cout << "Testiranje klase 'Epizoda'\n\n";
    Epizoda e1;
    e1.SetNaziv("What's Cooking?");
    e1.SetTrajanje(21);
    e1.SetKratakSadrzaj("Bender decides to become a chef so ...");
    e1.SetDatumPremijere(Datum(5, 5, 2021));
    e1.Ispis();
    cout << endl;

    Epizoda e2("This Mission is Trash", 22, "Fry, Leela, and Bender travel to the garbage meteor and discover loads of discarded junk.", Datum(13, 5, 2021), 10);
    e2.Ispis();
    cout << endl;

    Epizoda e3(e2);
    e3.SetNaziv("Smell-o-Scope");
    e3.SetTrajanje(20);
    e3.SetKratakSadrzaj("Using Professor Farnsworth's Smell-o-Scope, Fry locates the stinkiest object in the universe.");
    e3.SetDatumPremijere(Datum(21, 5, 2021));
    e3.Ispis();
    cout << endl;

    Epizoda e4(move(e3));
    e4.SetNaziv("Electric Drug");
    e4.SetTrajanje(24);
    e4.SetKratakSadrzaj("Bender's electricity addiction puts the Planet Express crew in danger");
    e4.SetDatumPremijere(Datum(29, 5, 2021));
    for (size_t i = 0; i < 15; i++)
        e4.DodajOcjenu(rand() % 10 + 1);
    e4.UkloniZadnjuOcjenu();
    e4.UkloniZadnjuOcjenu(); //Brisemo zadnje dvije ocjene
    cout << endl;
    e4.Ispis();
    cout << "Dealokacija ..." << endl;
}

void Zadatak4() {
    cout << "Testiranje klase 'Uloga'\n\n";
    Glumac seanConnery("Sean", "Connery", "Velika Britanija", 25, 8, 1930, 1);
    Glumac danielCraig("Daniel", "Craig", "Velika Britanija", 2, 3, 1968, 1);
    Uloga jamesBond(seanConnery, "MI6 Detective James Bond ....", "Main role");
    jamesBond.SetGlumac(danielCraig);
    jamesBond.SetOpis("After earning 00 status and a licence to kill, Secret Agent James Bond sets out on his first mission as 007.");
    jamesBond.SetTipUloge("Main role");

    Uloga bond25(jamesBond);
    Uloga bond26(move(bond25));
    bond26.Ispis();
    cout << "Dealokacija ..." << endl;
}

void Zadatak5() {
    cout << "Testiranje klase 'Serija'\n\n";
    Serija teorijaVelikogPraska("The Big Bang Theory", 200);

    Glumac jimParsons("Jim", "Parsons", "SAD", 17, 7, 1967, 1);
    Glumac johnnyGalecki("Johnny", "Galecki", "SAD", 15, 3, 1975, 1);
    Glumac kaleyCuoco("Kaley", "Cuoco", "SAD", 13, 4, 1985, 0);
    Uloga sheldonCooper(jimParsons, "Dr. Sheldon Cooper, a theoretical physicist at Caltech", "Series regular");
    Uloga leonardHofstadter(johnnyGalecki, "Dr. Leonard Hofstadter, a experimental physicist at Caltech", "Series regular");
    Uloga penny(kaleyCuoco, "Penny, a waitress at Cheesecake factory", "Series regular");
    //Serija::Dodavanje uloga
    teorijaVelikogPraska.DodajUlogu(sheldonCooper);
    teorijaVelikogPraska.DodajUlogu(leonardHofstadter);
    teorijaVelikogPraska.DodajUlogu(penny);

    Epizoda E1("The Big Bran Hypothesis", 22, "When Sheldon and Leonard drop off a box of flat pack furniture...", Datum(1, 6, 2021), 100);
    Epizoda E2("The Luminous Fish Effect", 21, "Sheldon is fired from his job as a physicist after insulting his new boss...", Datum(8, 6, 2021), 100);
    Epizoda E3("The Bat Jar Conjecture", 22, "The guys decide to compete in a university quiz called physics bowl...", Datum(15, 6, 2021), 100);
    Epizoda E4("The Nerdvana Annihilation", 21, "In an online auction, Leonard buys a full-sized replica of the time machine...", Datum(22, 6, 2021), 100);

    //Epizoda::DodajOcjenu
    int ocjene1[] = { 5,7,8 }, ocjene2[] = { 10,5,7,10,9 }, ocjene3[] = { 9,8,9,9 }, ocjene4[] = { 10,5,3,7,6,6 };
    for (size_t i = 0; i < size(ocjene1); i++)
        E1.DodajOcjenu(ocjene1[i]);
    for (size_t i = 0; i < size(ocjene2); i++)
        E2.DodajOcjenu(ocjene2[i]);
    for (size_t i = 0; i < size(ocjene3); i++)
        E3.DodajOcjenu(ocjene3[i]);
    for (size_t i = 0; i < size(ocjene4); i++)
        E4.DodajOcjenu(ocjene4[i]);

    //Serija::DodajEpizodu
    teorijaVelikogPraska.DodajEpizodu(E1);
    teorijaVelikogPraska.DodajEpizodu(E2);
    teorijaVelikogPraska.DodajEpizodu(E3);
    teorijaVelikogPraska.DodajEpizodu(E4);

    Serija bigbangTheory1(teorijaVelikogPraska);
    bigbangTheory1.Ispis();

    Epizoda* ep = bigbangTheory1.GetNajboljeOcijenjenaEpizoda();
    cout << "Najbolje ocijenjena epizoda: " << ep->GetNaziv() << endl;
    cout << "Ocjena: " << ep->GetProsjecnaOcjena() << endl;
    cout << "Dealokacija ..." << endl;
}

void Menu() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 5);
        switch (izbor) {
          case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
          case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
          case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
          case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
          case 5: Zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}

int main() {
    Menu();
    return 0;
}