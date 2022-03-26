#include <iostream>
using namespace std;

//ZO. 1
char* AlocirajIKopiraj(const char* tekst) {

	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst)+1;  //zbog nullterminirajuceg znaka
	char* novi = new char[vel]; 
	strcpy_s(novi, vel, tekst);
	return novi;

}

/* ::NAPOMENA::
Radi jednostavnije izrade i lakseg testiranja zadataka, komentirajte testni dio koda, koji je obuhvacen funkcijama sa prefixom 'Zadatak'.
Kako budete implementirali odredjene funkcionalnosti, tada lagano pocnite sa 'otkrivanjem' komentiranih dijelova koda.
*/

//Z0.1
char* AlocirajIKopiraj(const char* tekst);

struct Datum
{
    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
    //Z1.1
    void Unos(int d, int m, int g) {  //konstruktor 
        _dan = new int(d); 
        _mjesec = new int(m);
        _godina = new int(g);
    }

        //Z1.2
    void Unos(Datum& datum) { // s obzirom da imamo ampersend moramo dodati * kod datuma
        _dan = new int(*datum._dan);
        _mjesec = new int(*datum._mjesec);
        _godina = new int(*datum._godina);
        }
    //Z1.3
    void Unos(Datum* datum) {
        _dan = new int(*datum->_dan); //posto su dan mjesec i godina isto pokazivaci pristupamo sa ->
        _mjesec = new int(*datum->_mjesec);
        _godina = new int(*datum->_godina);
    }
    //Z1.4
    int GetDan()   { return *_dan; }
    int GetMjesec(){ return *_mjesec; }
    int GetGodina(){ return *_godina; }
    //Z1.5
    void SetDan(int dan) { 
        if (_dan == nullptr)
            _dan = new int;
        *_dan = dan;  //mora sa zvjezdicom jer je s lijeve stramne pokazivac, a sa desne varijabla, najlakse je dereferncirati pointer
    /* ili
    delete _dan
        _dan=new int(dan)
        */
    }
    //Z1.6
    void SetMjesec(int mjesec) { 
        if (_mjesec == nullptr)
            _mjesec = new int;
        *_mjesec = mjesec;
    }
    //Z1.7
    void SetGodina(int godina) { 
        if (_godina == nullptr)
            _godina = new int;
        *_godina = godina;
    
    }
    //Z1.8
    void Ispis() {
        if (_dan != nullptr && _mjesec != nullptr && _godina != nullptr)
            cout << *_dan << "." << *_mjesec << "." << *_godina;
    }
    //Z1.9
    void Dealokacija() {
        delete _dan;
        delete _mjesec;
        delete _godina;
    }
    int ToInt() {
        return GetGodina() * 365 + GetMjesec() * 30 + GetDan();
    }

};
//Z1.10
bool JeLiIsti(Datum& d1, Datum& d2) { 
    return d1.GetGodina() == d2.GetGodina() && d1.GetMjesec() == d2.GetMjesec() && d1.GetDan() == d2.GetDan();
}
//Z1.11
Datum& GetStarijiDatum(Datum& d1, Datum& d2) {
    if (d1.ToInt() < d2.ToInt())
        return d1;
    return d2;
}
//Z1.12
Datum& GetNovijiDatum(Datum& d1, Datum& d2) {
    if (d1.ToInt() > d2.ToInt())
        return d1;
    return d2;
}
//Z1.13
Datum* GetNajstarijiDatum(Datum datum[], int size) { 
    
    if (size == 0)
        return nullptr;
    Datum* najstariji = datum + 0;
    for (int i = 0; i < size; i++)
    {
        if (datum[i].ToInt() < najstariji->ToInt())
            najstariji = datum + i;
    }
    return najstariji;
}
//Z1.14
Datum* GetNajnovijiDatum(Datum datum[], int size) {

    if (size == 0)
        return nullptr;
    Datum* najnoviji = datum + 0;
    for (int i = 0; i < size; i++)
    {
        if (datum[i].ToInt() > najnoviji->ToInt())
            najnoviji = datum + i;
    }
    return najnoviji;
}

struct Glumac {
    char _jmbg[14] = "";
    char* _ime = nullptr;
    char* _prezime = nullptr;
    Datum* _datumRodjenja = nullptr;
    char* _mjestoRodjenja = nullptr;
    char _drzava[100];
    bool _spol; //1:Muski, 0:Zenski
    //Z2.1
    void Unos(const char* jmbg, const char* ime, const char* prezime, Datum& datumRodjenja, const char* mjestoRodjenja, const char* drzava, bool spol)
    {
        strcpy_s(_jmbg, 14, jmbg);
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prezime);
        _datumRodjenja = new Datum;
        _datumRodjenja->Unos(datumRodjenja);
        _mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
        strcpy_s(_drzava, 100, drzava);
        _spol = spol;

    }
    //Z2.2
    void Unos(Glumac& glumac) {
        strcpy_s(_jmbg, 14, glumac._jmbg);
        _ime = AlocirajIKopiraj(glumac._ime);
        _prezime = AlocirajIKopiraj(glumac._prezime);
        _datumRodjenja = new Datum;
        _datumRodjenja->Unos(glumac._datumRodjenja);
        _mjestoRodjenja = AlocirajIKopiraj(glumac._mjestoRodjenja);
        strcpy_s(_drzava, 100, glumac._drzava);
        _spol = glumac._spol;
    }
    //Z2.3
    void SetJmbg(const char* jmbg) {
        strcpy_s(_jmbg, 14, jmbg);
    }
    //Z2.4
    void SetIme(const char* ime) {
        if(_ime!=nullptr)
        delete[]_ime; //greska ako se ne pozove unos, da se preventuje ovo koristimo konstruktore ali isto tako mozemo provjeriti da li je ime nullptr
        _ime = AlocirajIKopiraj(ime);
    }    
    //Z2.5
    void SetPrezime(const char* prezime) {
        if (_prezime != nullptr)
            delete[]_prezime;
        _prezime = AlocirajIKopiraj(prezime);

    }
    //Z2.6
    void SetDatumRodjenja(Datum& datumRodjenja) {
        if(_datumRodjenja==nullptr)
        _datumRodjenja = new Datum;
        _datumRodjenja->Unos(_datumRodjenja);
    }
    //Z2.7
    void SetMjestoRodjenja(const char* mjestoRodjenja) {
        if (_mjestoRodjenja != nullptr)
            delete[] _mjestoRodjenja;
        _mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
    }
    //Z2.8
    void SetDrzava(const char* drzava) {
        strcpy_s(_drzava, 100, drzava);
    }
    //Z2.9
    void SetSpol(bool spol) {
        _spol = spol;
    }
    //Z2.10
    void Ispis() {
        cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
        cout << "Datum rodjenja: ";
        _datumRodjenja->Ispis();
        cout << endl << "Mjesto i drzava rodjenja: " << _mjestoRodjenja <<"  "<< _drzava << endl;
        cout << "Spol: " << ((_spol == true) ? "Muski" : "Zenski") << endl;
    }
    //Z2.11
    void Dealokacija() {
        _datumRodjenja->Dealokacija(); //ovjde se brisu vrijednosti pohranjene u objekat 
        delete _datumRodjenja; //ovdje se brise objekat
        delete[]_ime;
        delete[]_prezime;
        delete[]_mjestoRodjenja;
        _ime = nullptr;
        _prezime = nullptr;
        _mjestoRodjenja = nullptr;
    }
};

struct Film {
    char _filmID[50] = ""; //prema ISAN standardu
    char* _naziv = nullptr;
    char _zanr[40];
    int _godinaIzlaska;
    int _trenutnoGlumaca = 0;
    Glumac _glumackaPostava[20];
    int _trenutnoOcjena = 0;
    int* _ocjene = nullptr; //Dinamicki prosirivati ovaj niz svakim novim dodavanjem
    //Z3.1
    void Unos(const char* filmID, const char* naziv, const char* zanr, int godinaIzlaska) {
         strcpy_s(_filmID, 50, filmID);
        _naziv = AlocirajIKopiraj(naziv);
        strcpy_s(_zanr, 40, zanr);
        _godinaIzlaska = godinaIzlaska;
    }
    //Z3.2
    void Unos(Film& film) {
        strcpy_s(_filmID, 50, film._filmID);
        _naziv = AlocirajIKopiraj(film._naziv);
        strcpy_s(_zanr, 40, film._zanr);
        _godinaIzlaska = film._godinaIzlaska;
        _trenutnoGlumaca = film._trenutnoGlumaca;
        for (int i = 0; i < _trenutnoGlumaca; i++)
            _glumackaPostava[i].Unos(film._glumackaPostava[i]); //objekat glumackaPostava ima svoj unos tako da tome i pristupamo
        _trenutnoOcjena = film._trenutnoOcjena;
        _ocjene = new int[_trenutnoOcjena];
            for (int i = 0; i < _trenutnoOcjena; i++)
                _ocjene[i] = film._ocjene[i];
    }
    //Z3.3
    bool DodajGlumca(Glumac& g) {
        if (_trenutnoGlumaca == 20)
            return false; //ukoliko ima maksimalno glumaca (20), vrati da se nije dodao glumac
        _glumackaPostava[_trenutnoGlumaca].Unos(g); //ukoliko se moze dodati glumac, dodaj glumca opet preko unosa
        _trenutnoGlumaca++; //povecaj brojac za trenutni broj glumaca
        return true; //vrati da se uspjesno dodao glumac 
    } 
    //Z3.4
    bool DodajOcjenu(int ocjena) {
        int *temp = _ocjene;
        _ocjene = new int[_trenutnoOcjena+1];
        for (int i = 0; i < _trenutnoOcjena; i++)
            _ocjene[i] = temp[i];
        delete[] temp;
        temp = nullptr;
        _ocjene[_trenutnoOcjena] = ocjena;
        _trenutnoOcjena++;
        return true;
    }
    //Z3.5
    void Ispis() {
        cout << "Film ID: " << _filmID << endl;
        cout << "Naziv: " << _naziv << endl;
        cout << "Zanr: " << _zanr << endl;
        cout << "Godina izlaska: " << _godinaIzlaska << endl;
        cout << "Trenutno glumaca: " << _trenutnoGlumaca << endl;
        cout << "==============================================" << endl;
        for (int i = 0; i < _trenutnoGlumaca; i++)
            _glumackaPostava[i].Ispis();
        cout << "==============================================" << endl;
        cout << "Prosjecna ocjena: " << GetProsjecnaOcjena() << endl;
        cout << "Ukupno ocjena: " << _trenutnoOcjena << endl;
    }
    //Z3.6
    float GetProsjecnaOcjena() {
        
        float suma = 0.0f;
        for (int i = 0; i < _trenutnoOcjena; i++)
        {
            suma += _ocjene[i];
        }
       return suma / _trenutnoOcjena;
    }
    //Z3.7
    void Dealokacija() {
        delete[]_naziv;
        delete[]_ocjene;
        for (int i = 0; i < _trenutnoGlumaca; i++)
        _glumackaPostava[i].Dealokacija();
        _naziv = nullptr;
        _ocjene = nullptr;

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
    historijskiDogadjaji[0].Unos(danD);
    historijskiDogadjaji[1].Unos(operacijaBarbarossa);
    historijskiDogadjaji[2].Unos(sarajevskiAtentat);
    historijskiDogadjaji[3].Unos(apolloSlijetanje);
    historijskiDogadjaji[4].Unos(blackThursday);

    cout << endl << "Najstariji datum: " << endl;
    GetNajstarijiDatum(historijskiDogadjaji, 5)->Ispis();
    cout << endl << "Najnoviji datum: " << endl;
    GetNajnovijiDatum(historijskiDogadjaji, 5)->Ispis();

   // DEALOKACIJE
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

