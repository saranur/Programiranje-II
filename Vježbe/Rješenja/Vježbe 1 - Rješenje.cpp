#include <iostream>
using namespace std;
//Zadatak donje funckije jeste da se alocira pokazivac na novi niz karaktera velicine tekst:
char* AlocirajIKopiraj(const char* tekst)
{
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1; //+1 se stavi radi nullterminirajuceg znaka; (/0)
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}

struct Datum
{
    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
    //Z1
    //Zadatak ove funkcije jeste da  unesene parametre dodijeli propertijima dan mjesec i godina:
    void Unos(int d, int m, int g) 
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;
        *_dan = d;
        *_mjesec = m;
        *_godina = g;
    }
    //Z1.2
	//Zadatak ove funkcije jeste da omoguci unos propertia dan mjesec i godina ali ovaj put se to radi preko objekta tipa datum koji je poslan po referenci:
    void Unos(Datum& datum)
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;
        *_dan = *datum._dan; //Zvjezdica na pocetku jer je _dan pointer koji se mora dereferencirati!
        *_mjesec = *datum._mjesec;
        *_godina = *datum._godina;
    }
    
	//Z1.3
	//Zadatak sljedece funckije jeste da omoguci unos propertia dan mjesec i godina ali ovaj put se radi preko pointera tipa datum:
    void Unos(Datum* datum)
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;
        *_dan = *datum->_dan; //Datum se dereferencira sa strelicom a pointer _dan sa zvjezdicom na pocetku;
        *_mjesec = *datum->_mjesec;
        *_godina = *datum->_godina;
    }
    int GetDan() { return *_dan; } //Zadatak ove  funkcije jeste da vrati dan 
    int GetMjesec() { return *_mjesec; } //Zadatak ove  funkcije jeste da vrati mjesec
    int GetGodina() { return *_godina; } //Zadatak ove  funkcije jeste da vrati godinu
    	//Zadatak ove funckije jeste da proslijedjeni parametar postavi za dan:
    void SetDan(int dan)
    {
        if (_dan == nullptr) //Moramo pitati da li je pointer _dan u upotrebi tj. da li pokazuje i na sta, ako ne pokazuje onda napraviti novi int i pokazati na njega
			_dan = new int;
        *_dan = dan;
    }
    	//Zadatak ove funckije jeste da proslijedjeni parametar postavi za mjesec
    void SetMjesec(int mjesec)
    {
        if (_mjesec == nullptr) //Moramo provjeriti da li je pointer " prazan ", u suptronom pokusavali bi da setujemo na nultoj adresi sto ne mozemo raditi
            _mjesec = new int;
        *_mjesec=mjesec;
    }
     	//Zadatak ove funckije jeste da proslijedjeni parametar postavi za godinu
    void SetGodina(int godina)
    {
        if (_godina == nullptr)
            _godina = new int;
        *_godina = godina;
    }
    void Ispis() { cout << *_dan << "." << *_mjesec << "." << *_godina; }
    
    void Dealokacija()
    {
        delete _dan, _mjesec, _godina; //Sve pointere izbrise;
    	_dan =_mjesec = _godina=nullptr; //Sve pointere nullpointa;
    }
};
//Zadatak ove funkcije jeste da provjeri da li su dva datuma ista (0 vrati ako nisu a bilo sta drugo vraceno znaci da jesu):
bool JeLiIsti(Datum& d1, Datum& d2)
{
    	//Oba datuma su primljenja po referenci kako bi se poslali sa svojim adresama!!!
    return *d1._dan == *d2._dan
        && *d1._mjesec == *d2._mjesec
        && *d1._godina == *d2._godina;
    	//Mogli smo korisiti i if i vratiti true/false, ali na ovaj nacin je krace
}
//Zadatak ove funkcije jeste da vrati referencu na objekat (datum) koji je najstariji:
Datum& GetStarijiDatum(Datum& d1, Datum& d2)
{
    if (*d1._godina < *d2._godina)
        return d1;
    else if(*d1._godina == *d2._godina)
        {
            if (*d1._mjesec < *d2._mjesec)
                return d1;
            else if (*d1._mjesec == *d2._mjesec) {
                if (*d1._dan < *d2._dan)
                    return d1;
            }
            else   return d2;
        }
    return d2;
}

Datum& GetNovijiDatum(Datum& d1, Datum& d2)
{
    if (JeLiIsti(GetStarijiDatum(d1, d2), d1))
        return d2;
}

Datum* GetNajstarijiDatum(Datum datum[], int size)
{
    Datum* najstariji = datum;
    for (int i=0; i<size; i++)
    {
        najstariji = &GetStarijiDatum(*najstariji, datum[i]);
    }
        return najstariji;
    
}

Datum* GetNajnovijiDatum(Datum datum[], int size) //
{
    Datum* najnoviji = datum; //Inicijaliziramo  pokazivac najnoviji da pokazuje na prvi element niza datum;
    for(int i=0; i<size; i++) 
    {
        najnoviji = &GetNovijiDatum(*najnoviji, datum[i]);  //Size broj puta se uporedi datum na pokazivacu najnoviji i  i-ti element niza datum, te vidi koji je noviji i spremi se adresa tog objekta na pointer najnoviji;
    }
        return najnoviji;
}

struct Glumac {
    char _jmbg[14] = ""; //Staticki nizovi se ne mogu "alocirati" i ne mozemo korisiti znak jednako
    char* _ime = nullptr;
    char* _prezime = nullptr;
    Datum* _datumRodjenja = nullptr;
    char* _mjestoRodjenja = nullptr;
    char _drzava[100]="";
    bool _spol; //1:Muski, 0:Zenski

    void Unos(const char* jmbg, const char* ime, const char* prezime, Datum& datumRodjenja,
        const char* mjestoRodjenja, const char* drzava, bool spol)
    {
        strcpy_s(this->_jmbg, 14, jmbg); //koristimo strcpy_s zato sto je _jmbg staticki niz karaktera
        this->_ime = AlocirajIKopiraj(ime);
        this->_prezime = AlocirajIKopiraj(prezime);
        this->_datumRodjenja = new Datum;
        this->_datumRodjenja->Unos(datumRodjenja);
        this->_mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
        strcpy_s(this->_drzava, 100, drzava);
        this->_spol = spol;
        //this -ispise adresu objekta koji je pozvao funkciju
        //(*this) - sami objekat, refleksija 
    }
    
	//Zadatak ove funkcije jeste da omoguci unos obiljezja ali ovaj put preko reference na objekat tipa Glumac:
    void Unos(Glumac& glumac)
    {
        strcpy_s(this->_jmbg, 14, glumac._jmbg);
        this->_ime = AlocirajIKopiraj(glumac._ime);
        this->_prezime = AlocirajIKopiraj(glumac._prezime);
        this->_datumRodjenja = new Datum;
        this->_datumRodjenja->Unos(glumac._datumRodjenja);
        this->_mjestoRodjenja = AlocirajIKopiraj(glumac._mjestoRodjenja);
        strcpy_s(this->_drzava, 100, glumac._drzava);
        this->_spol = glumac._spol;
    }

    void SetJmbg(const char* jmbg)  //staticki niz karakektera
    {
        strcpy_s(this->_jmbg, 14, jmbg);
    }

    void SetIme(const char* ime)  //dinacki niz karaktera
    {
        delete[] _ime; //ovo radimo da bi prosirili niz
        //Ukoliko je neko prvobitno unio 10 karaktera, kasnije necete moci pohraniti npr. 20 karaktera u taj niz
        //Ne mozemo ga prosiriti, moramo ga unistiti i ponovo kreirati
        _ime = AlocirajIKopiraj(ime);
    }

    void SetPrezime(const char* prezime)
    {
        delete[] _prezime; 
        _prezime = AlocirajIKopiraj(prezime);
    }

    void SetDatumRodjenja(Datum& datumRodjenja)
    {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum;
        _datumRodjenja->SetDan(*datumRodjenja._dan);
        _datumRodjenja->SetMjesec(*datumRodjenja._mjesec);
        _datumRodjenja->SetGodina(*datumRodjenja._godina);
        //Ili mozemo koristiti
        /*_datumRodjenja->Unos(datumRodjenja); jer smo ga vec napravili u strukturi Datum*/
    }

    void SetMjestoRodjenja(const char* mjestoRodjenja)
    {
        delete[] _mjestoRodjenja;
        _mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
    }
    
    void SetDrzava(const char* drzava)
    {
        strcpy_s(this->_drzava, 100, drzava);
    }
    
    void SetSpol(bool spol)
    {
        _spol = spol;
    }
    
    void Ispis()
    {
        cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
        cout << "Datum rodjenja: ";
            _datumRodjenja->Ispis();
            cout << endl << " Mjesto i drzava rodjenja: " << _mjestoRodjenja << _drzava << endl;
            cout << "Spol: "<<((_spol == true) ? "Muski" : "Zenski") << endl;
    }
    
    void Dealokacija()
    {
        delete[] _ime, _prezime,  _mjestoRodjenja;
        _ime = _prezime  = _mjestoRodjenja = nullptr;
        _datumRodjenja->Dealokacija(); //Posto je ovaj ptr tipa Datum strukture, prvo se njegovi properties brisu pa onda sam on!;
        delete _datumRodjenja;
        _datumRodjenja = nullptr;
    }
};

struct Film {
    char _filmID[50] = ""; //prema ISAN standardu
    //Defaultnu vrijednost za atribut
    char* _naziv = nullptr;
    char _zanr[40] ;
    int _godinaIzlaska;
    int _trenutnoGlumaca = 0;
    Glumac _glumackaPostava[20];
    int _trenutnoOcjena = 0;
    int* _ocjene = nullptr; //Dinamicki prosirivati ovaj niz svakim novim dodavanjem
    
    void Unos(const char* filmID, const char* naziv, const char* zanr, int godinaIzlaska)
    {
        strcpy_s(_filmID, 50, filmID);
        _naziv = AlocirajIKopiraj(naziv);
        strcpy_s(_zanr, 40, zanr);
        _godinaIzlaska = godinaIzlaska;
    }
    
    void Unos(Film& film)
    {
        strcpy_s(_filmID, 50, film._filmID);
        _naziv = AlocirajIKopiraj(film._naziv);
        strcpy_s(_zanr, 40,film._zanr);
        _godinaIzlaska = film._godinaIzlaska;
        _trenutnoGlumaca = film._trenutnoGlumaca;
        for(int i=0; i<_trenutnoGlumaca; i++)
        {
            _glumackaPostava[i].Unos(film._glumackaPostava[i]);
        }
        _trenutnoOcjena = film._trenutnoOcjena;
        _ocjene = new int[film._trenutnoOcjena];
        for (int i=0; i<_trenutnoOcjena; i++)
        {
            _ocjene[i] = film._ocjene[i];
        }
    }
    
    bool DodajGlumca(Glumac& g)
    {
        if (_trenutnoGlumaca == 20)
            return false;
        _glumackaPostava[_trenutnoGlumaca].Unos(g); //Za trenutnog glumca u nizu od 20 glumaca unesi obiljezja iz glumca "g";
        _trenutnoGlumaca++;
        return true;
    } 

    bool DodajOcjenu(int ocjena)
    {
        int* temp = _ocjene; //Napravimo pomocni pokazivac na niz ocjena;
        _ocjene = new int[_trenutnoOcjena + 1]; //Stari niz ocjena prosirimo za jednu, odatle +1; Brojac se ovdje ne POVECAVA!
        for (int i = 0; i < _trenutnoOcjena; i++)
            _ocjene[i] = temp[i]; //Za svako i prekopiramo ocjene ali posto se niz prosirio za jednu, jedna (zadnja) ocjena je ne popunjena;
        delete[] temp; //Obrisemo dinamicki niz;
        temp = nullptr; //Nullpointamo pointer temp;
        _ocjene[_trenutnoOcjena]; //Zadnjoj ocjeni dodijelimo  ocjenu iz parametra;
        _trenutnoOcjena++; //Povecamo brojac;
        return true;
    }
    //Z3.5
	//Zadatak ove funkcije jeste da ispise obiljezja:
    void Ispis()
    {
        cout << "Naziv filma: " << _naziv << endl;
        cout << "Zanr: " << _zanr << endl;
        cout << "Godina izlaska: " << _godinaIzlaska << endl;
        cout << "Trenutno glumaca: " << _trenutnoGlumaca << endl;
        cout << "====================================================" << endl;
        for (int i=0; i<_trenutnoGlumaca; i++)
        {
            _glumackaPostava[i].Ispis(); //Izvrsi ispis svakog glumca i njegovih obiljezja iz niza;
        }
        cout << "====================================================" << endl;
        cout << "Prosjecna ocjena: " << GetProsjecnaOcjena() << endl;
        cout << "Ukupno ocjena: " << _trenutnoOcjena << endl;
    }
    
    float GetProsjecnaOcjena()
    {
        float suma = 0.f;
        for (int i = 0; i < _trenutnoOcjena; i++)
            suma += _ocjene[i];
       return suma / _trenutnoOcjena;
    }
    
    void Dealokacija()
    {
        delete[] _naziv;
        delete[] _ocjene;
        _naziv = nullptr;
        _ocjene = nullptr;
        for (int i = 0; i < _trenutnoGlumaca; i++)
            _glumackaPostava[i].Dealokacija();
    }
};

void Zadatak1() {
    cout << ":Zadatak 1:" << endl;
    Datum prviMart, danNezavisnosti, danDrzavnosti;
    prviMart.Unos(1, 3, 2021);
    danNezavisnosti.Unos(prviMart);
    danDrzavnosti.Unos(&prviMart);
    danDrzavnosti.SetDan(25);
    danDrzavnosti.SetMjesec(11);
    danDrzavnosti.SetGodina(2021);

    cout << "Dan nezavisnosti: " << endl;
    danNezavisnosti.Ispis();
    cout << endl << "Dan drzavnosti: " << endl;
    danDrzavnosti.Ispis();
    prviMart.Dealokacija();
    danNezavisnosti.Dealokacija();
    danDrzavnosti.Dealokacija();

    Datum danD, operacijaBarbarossa, sarajevskiAtentat, apolloSlijetanje, blackThursday;
    danD.Unos(6, 6, 1944);
    operacijaBarbarossa.Unos(22, 6, 1941);
    sarajevskiAtentat.Unos(28, 6, 1914);
    apolloSlijetanje.Unos(24, 7, 1969);
    blackThursday.Unos(24, 10, 1929);

    Datum historijskiDogadjaji[5];
    historijskiDogadjaji[0].Unos(danD); //Funkcija unos sa ampersandom se poziva
    historijskiDogadjaji[1].Unos(operacijaBarbarossa);
    historijskiDogadjaji[2].Unos(sarajevskiAtentat);
    historijskiDogadjaji[3].Unos(apolloSlijetanje);
    historijskiDogadjaji[4].Unos(blackThursday);

    cout << endl << "Najstariji datum: " << endl;
    GetNajstarijiDatum(historijskiDogadjaji, 5)->Ispis();
    cout << endl << "Najnoviji datum: " << endl;
    GetNajnovijiDatum(historijskiDogadjaji, 5)->Ispis();

    //DEALOKACIJE
    danD.Dealokacija();
    operacijaBarbarossa.Dealokacija();
    sarajevskiAtentat.Dealokacija();
    apolloSlijetanje.Dealokacija();
    blackThursday.Dealokacija();
    for (size_t i = 0; i < 5; i++)
        historijskiDogadjaji[i].Dealokacija();
    cout << endl << "Dealokacija uspjesna!" << endl;
}

void Zadatak2() {
    cout << ":Zadatak 2:" << endl;

    Glumac alPacino, deNiro;
    Datum temp1, temp2;
    temp1.Unos(25, 4, 1940);
    temp2.Unos(17, 8, 1943);
    alPacino.Unos("1304996055555", "Alfredo", "Pacino", temp1, "Manhattan, NYC", "SAD", 1);
    deNiro.Unos(alPacino);
    deNiro.SetIme("Robert");
    deNiro.SetPrezime("De Niro");
    deNiro.SetDatumRodjenja(temp2);
    deNiro.SetMjestoRodjenja("Greenwich Village");
    deNiro.SetDrzava("SAD");
    deNiro.SetSpol(1);

    Datum datumi[5];
    datumi[0].Unos(7, 6, 1995);
    datumi[1].Unos(7, 11, 1991);
    datumi[2].Unos(3, 6, 1995);
    datumi[3].Unos(5, 6, 1992);
    datumi[4].Unos(1, 6, 1993);
    Glumac glumciNarodnogPozorista[5];
    glumciNarodnogPozorista[0].Unos("0706995088888", "Barb", "Dwyer", datumi[0], "Mostar", "BiH", 1);
    glumciNarodnogPozorista[1].Unos("0711991144488", "Anna", "Graham", datumi[1], "Ostrozac", "BiH", 0);
    glumciNarodnogPozorista[2].Unos("0306995099999", "Benjamin", "Button", datumi[2], "Sarajevo", "BiH", 1);
    glumciNarodnogPozorista[3].Unos("0506992011993", "Jack", "Pott", datumi[3], "Vogosca", "BiH", 1);
    glumciNarodnogPozorista[4].Unos("0106993094444", "Justin", "Case", datumi[4], "Kotor-Varos", "BiH", 1);

    cout << "Ispis svih glumaca:: " << endl;
    for (size_t i = 0; i < 5; i++) {
        cout << "-----------------------------------------------" << endl;
        glumciNarodnogPozorista[i].Ispis();
    }
    cout << "-----------------------------------------------" << endl;
    cout << endl;

    //DEALOKACIJE
    temp1.Dealokacija();
    temp2.Dealokacija();
    alPacino.Dealokacija();
    deNiro.Dealokacija();
    for (size_t i = 0; i < 5; i++) {
        datumi[i].Dealokacija();
        glumciNarodnogPozorista[i].Dealokacija();
    }
    cout << "Dealokacija uspjesna!" << endl;
}

void Zadatak3() {
    Datum temp1, temp2;
    temp1.Unos(25, 4, 1940);
    temp2.Unos(17, 8, 1943);
    Glumac alPacino, deNiro;
    alPacino.Unos("2504940555551", "Alfredo", "Pacino", temp1, "Manhattan, NYC", "SAD", 1);
    deNiro.Unos("1708943055555", "Robert", "De Niro", temp2, "NYC", "SAD", 1);

    Film irishman;
    irishman.Unos("XXXX-AAAA-BBBB-CCCC", "The Irishman", "Biografija, krimi, drama", 2019);
    irishman.DodajGlumca(alPacino);
    irishman.DodajGlumca(deNiro);
    irishman.DodajOcjenu(10);
    irishman.DodajOcjenu(8);
    irishman.DodajOcjenu(9);
    irishman.DodajOcjenu(8);
    irishman.DodajOcjenu(8);
    Film kopija;
    kopija.Unos(irishman);
    kopija.Ispis();
    //DEALOKACIJE
    irishman.Dealokacija();
    kopija.Dealokacija();
    alPacino.Dealokacija();
    deNiro.Dealokacija();
    temp1.Dealokacija();
    temp2.Dealokacija();
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
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 3);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Done." << endl; break;
        case 2: Zadatak2(); cout << "Done." << endl; break;
        case 3: Zadatak3(); cout << "Done." << endl; break;
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


