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
// dtor = destructor (destruktor)
// dflt. ctor = default constructor
// user-def. ctor = user-defined constructor

/******KRATAK PODSJETNIK[1] ******
Kreiranje objekata (varijabli) u statickoj memoriji [KORISTENJE KONSTRUKTORA]
    int(5); //Neimenovani objekat
    int broj(5);
    int broj = 5;

Kreiranje objekata (varijabli) u dinamickoj memoriji [KORISTENJE KONSTRUKTORA]
    new int(5);
    int* pok = new int(5);

Ekvivalentno tome imamo sljedece:--->
Staticka memorija:
    Student("IB200200"); //Neimenovani objekat, user-def ctor
    Student student("IB200200"); // user-def ctor
    //Niz:
    Student niz[100]; //poziva se se dflt. ctor za svaki element niza

Dinamicka memorija:
    new Student; //poziva se dflt. ctor
    new Student("IB200200"); // poziva se user-def. ctor
    Student * pok = new Student; //poziva se dflt. ctor
    Student * pok = new Student("IB200200"); //poziva se user-def. ctor
    //Niz:
    Student * niz = new Student[100]; //poziva se se dflt. ctor za svaki element niza
*/

/******KRATAK PODSJETNIK[2] :: Pokazivaci i dinamicka memorija******
    1.Pokazivac na objekat:
        Student * student = new Student; // dflt. ctor se poziva jednom
    2.Pokazivac na niz:
        Student * studenti = new Student[10]; // dflt. ctor se poziva za svaki element niza
    3.Staticki niz pokazivaca [gdje svaki pokazuje na tacno jedan objekat]
        Student * nizPok[100];
        for(int i=0;i<100;i++)
            nizPok[i] = new Student; // poziv dflt. ctor-a
    4.Staticki niz pokazivaca [gdje svaki pokazuje na niz objekata]
        Student * nizPok[100];
        for(int i=0;i<100;i++)
            nizPok[i] = new Student[vel]; // poziv dflt.ctor-a onoliko puta, kolika je vrijednost 'vel'
    5.Pokazivac na pokazivac
        Student ** temp = new Student*;
        *temp = new Student; //poziv dflt. ctora
    6.Dinamicki niz pokazivaca [gdje svaki pokazuje na tacno jedan objekat]
        Student ** temp = new Student*[100];
        for(int i=0;i<100;i++)
            temp[i] = new Student;
    7.Dinamicki niz pokazivaca [gdje svaki pokazuje na niz objekata]
    Student ** temp = new Student*[100];
        for(int i=0;i<100;i++)
            temp[i] = new Student[vel];
*/

//Z1.0
char* AlocirajIKopiraj(const char* tekst)
{
    if (tekst == nullptr)
        return nullptr;
    int len = strlen(tekst)+ 1;
    char* povratni = new char[len];
    strcpy_s(povratni, len, tekst);
    return povratni;
}

class Datum
{
private:
    int _dan;
    int _mjesec;
    int _godina;
public:
    //Z1.1 Dflt. ctor [Postaviti na dflt. vrijednosti (1.1.2021)]
    //Default konstruktor ne prima nikakve paramentre, potrebno je samo staviti default vrijednosti
    //User-defined konstrukor prima parametre i te parametere smjesta u odgovarajuce propertije klase
    //Copy construktor - jedan od najbitnijih konstruktora
    //Od objekta tipa te klase napravi kopiju i alocira svu novu potrebnu memoriju za odredjene propertije

    //Getteri- svrha gettera jeste da vrate vrate vrijednost odredjenog propertija
    //Setteri- svrha settera jeste da se postavi odredjena vrijednost za neki properti
    Datum() //Dflt. ctor
    {
        _dan = 1;
        _mjesec = 1;
        _godina = 2021;
    }

    //Z1.2 User-def. ctor
    Datum(int d, int m, int g)
    {
        _dan = d;
        _mjesec = m;
        _godina = g;
    }
    //Z1.3
    int GetDan() const { return _dan; } //const se koristi kada se na svim propertijima te klase ne vrsi nikakva promjena
    int GetMjesec() const { return _mjesec; }
    int GetGodina() const { return _godina; }
    void SetDan(int dan) { _dan = dan; }
    void SetMjesec(int mjesec) { _mjesec = mjesec; }
    void SetGodina(int godina) { _godina = godina; }
    //Z1.4
    void Ispis()
    {
        cout << _dan << "." << _mjesec << "." << _godina;
    }
    //Z1.5
    ~Datum()
    {

    }
};

//Vraca random string odredjene duzine, kojeg sacinjavaju velika i mala slova 
char* GetRandomString(int duzina) {
    int velicina = duzina + 1;   //Dodajmo +1 radi nullterminirajuceg znaka
    char* randomString = new char[velicina]; //Napravim niz char koji prima velicinu -velicina
    for (int i = 0; i < velicina; i++) {
        int random_ascii = rand() % 26 + 65; //rand_ascii ce vratiti radnom ascii broj od 65, bice integer! Ovjde ce biti sva velika slova
        char slovo = (char)random_ascii; //ovjde cemo taj integer castati u char
        bool pretvoriUMalo = (bool)(rand() % 2); //Radnomly ce biti true i false, ako je true, onda ce prebaciti to slovo npr. A u malo slovo
        if (pretvoriUMalo)
            slovo = tolower(slovo); // tolower ce promijeniti to veliko slovo u malo
        randomString[i] = slovo; //Dobicemo niz velikih i malih slova nasumicno 
    }
    randomString[velicina - 1] = '\0'; //velicina-1 je da bi nullterminirajuci znak stavili da posljednje mjesto u nizu
    return randomString;
}

class Sjediste {
private:
    char* _sjedisteId; // Koristiti GetRandomString funkciju prilikom inicijalizacije [neka je duzina stringa 10]
    char _red; //A-Z
    int _kolona; //1,2,3,..., 100
public:
    //Z2.1
    //Dflt. ctor
    //Postaviti red na ' ' a kolonu na 0
    Sjediste()
    {
        _sjedisteId = GetRandomString(10);
        _red = ' ';
        _kolona = 0;
    }
    //Z2.2
    //User-def. ctor
    Sjediste(char red, int kolona)
    {
        _sjedisteId = GetRandomString(10);
        _red = red;
        _kolona = kolona;
    }
    //Z2.3
    char GetRed() const { return _red; }
    int GetKolona() const { return _kolona; }
    //Z2.4
    void SetRed(char red) { _red = red; }
    void SetKolona(int kolona) { _kolona = kolona; }
    //Z2.5
    //Ispisati sjediste u formatu: "[A-13]"
    void Ispis()
    {
        cout << "[" << _red << "-" << _kolona << "]";
    }
    //Z2.6
    ~Sjediste()
    {
        delete[] _sjedisteId;
        _sjedisteId = nullptr;
    }
};

class Dvorana
{
private:
    char* _naziv;
    int _brojRedova; //max.26 [A-Z]
    int _brojKolona;
    Sjediste** _sjedista; //2D matrica objekata tipa Sjediste. Dimenzije matrice su: (_brojRedova x _brojKolona)
public:
    //Z2.7
    Dvorana()
    {
        _naziv = nullptr;
        _brojRedova = 0;
        _brojKolona = 0;
        _sjedista = nullptr;
    }
    //Z2.8
    //Uraditi dinamicku alokaciju 2D matrice sjedista pomocu pokazivaca na niz pokazivaca (_sjedista)
    //Podesiti vrijednosti atributa objekata matrice na sljedeci nacin -->
    //Polje [0][0] => _red : A, _kolona : 1
    //Polje [0][1] => _red : A, _kolona : 2
    //Polje [0][2] => _red : A, _kolona : 3
    //...
    //Polje [1][0] => _red : B, _kolona : 1
    //itd.
    Dvorana(const char* naziv, int brojRedova, int brojKolona)
    {
        _naziv = AlocirajIKopiraj(naziv);
        _brojRedova = brojRedova;
        _brojKolona = brojRedova;
        _sjedista = new Sjediste * [_brojRedova];
        for (int i = 0; i < _brojRedova; i++)
            _sjedista[i] = new Sjediste[_brojKolona];

        int asciiA = 65;
        //Podesavanje (setovanje) vrijednosti atributa objekata
        for (int i = 0; i < _brojRedova; i++) {
            for (int j = 0; j < _brojKolona; j++) {
                _sjedista[i][j].SetRed((char)(asciiA + i));
                _sjedista[i][j].SetKolona(j + 1);
            }
        }
    }

    //Z2.9
    void SetNaziv(const char* naziv)
    {
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    const char* GetNaziv() const { return _naziv; }
    int GetBrojRedova() const { return _brojRedova; }
    int GetBrojKolona() const { return _brojKolona; }

    //Z2.10
    //Uraditi dealokaciju alocirane matrice sjedista, te zatim uraditi ponovnu alokaciju na osnovu novih dimenzija
    void SetSjedista(int brojRedova, int brojKolona)
    {
        for (int i = 0; i < _brojRedova; i++)
        {
            delete[] _sjedista[i];
            _sjedista[i] = nullptr;
        }
        delete[] _sjedista;
        _sjedista = nullptr;

        _brojRedova = brojRedova;
        _brojKolona = brojKolona;
        _sjedista = new Sjediste * [_brojRedova];
        for (int i = 0; i < _brojRedova; i++)
        {
            _sjedista[i] = new Sjediste[_brojKolona];
        }
        int asciiA = 65;
        for (int i = 0; i < _brojRedova; i++)
        {
            for (int j = 0; j < _brojKolona; j++)
            {
                _sjedista[i][j].SetRed((char)(asciiA + i));
                _sjedista[i][j].SetKolona(j + 1);
            }
        }
    }

    //Z2.11
    //Vratiti adresu objekta sjediste, koje odgovara proslijedjenim vrijednostima
    //Ukoliko nije pronadjeno, vratiti nullptr 
    Sjediste* GetSjediste(char red, int kolona)
    {
        if (kolona > _brojKolona)
            return nullptr;
        for (int i = 0; i < _brojRedova; i++)
        {
            for (int j = 0; j < _brojKolona; j++)
            {
                if (_sjedista[i][j].GetRed() == red && _sjedista[i][j].GetKolona() == kolona)
                    return &_sjedista[i][j];
            }
        }
        return nullptr;
    }

    //Z2.12
    //Uraditi ispis na sljedeci nacin --->
    //Dvorana: Dvorana 7 Extreme
    //Redova: 11
    //Kolona: 20
    // -----------------------------
    // [A-1] [A-2] [A-3] .... [A-20]
    // [B-1] [B-2] [B-3] .... [B-20]
    // .
    // .
    // .
    // [K-1] [K-2] [K-3] .... [K-20]
    // -----------------------------
    void Ispis()
    {
        cout << "Dvorana: " << _naziv << endl;
        cout << "Redova: " << _brojRedova << endl;
        cout << "Kolona: " << _brojKolona << endl;
        for (int i = 0; i < _brojRedova; i++)
        {
            for (int j = 0; j < _brojKolona; j++)
            {

                _sjedista[i][j].Ispis();
                cout << " ";
            }
            cout << endl;
        }

    }

    //Z2.13
    ~Dvorana()
    {
        delete[] _naziv;
        _naziv = nullptr;
        for (int i = 0; i < _brojRedova; i++)
        {
            delete[] _sjedista[i]; //dealociranje niza objekata tipa Sjediste
            _sjedista[i] = nullptr;
        }
        delete[] _sjedista;
        _sjedista = nullptr; //dealociranje niza pokazivaca
    }
};

class Uposlenik {
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
    Uposlenik()
    {
        _ime = _prezime = _grad= nullptr;
        _datumRodjenja = nullptr;
        _spol = nullptr;
        strcpy_s(_radnoMjesto, 100, ""); //defaultna vrijednost statickog niza karaktera je empty string, "" stavljamo da ne bi bilo junk vrijednost
        strcpy_s(_email, 100, "");
    }
    //Z3.2
    Uposlenik(const char* ime, const char* prezime, Datum datum, bool spol, const char* radnoM, const char* grad, const char* email)
    {
        _ime = AlocirajIKopiraj(ime); 
        _prezime = AlocirajIKopiraj(prezime);
        _datumRodjenja = new Datum(datum.GetDan(), datum.GetMjesec(), datum.GetGodina());
        _spol = new bool;
    	*_spol= spol; //konstruise novi objekat tipa bool, poziva se defaultna vrijednost tipa bool, mozemo koristiti new bool(spol) jer predstavlja instancu primitivnog tipa podatka, male zagrade kopiraju vrijednost unutar njih u _spol
        strcpy_s(_radnoMjesto, 100, radnoM);
        _grad = AlocirajIKopiraj(grad); 
        strcpy_s(_email, 100, email);
    }
    //Z3.3
    char* GetIme() const { return _ime; }
    char* GetPrezime() const { return _prezime; }
    Datum GetDatumRodjenja() const{return *_datumRodjenja;}
    //kada imamo Datum samo koristice se konstruktor kopije, dakle vrijednost *_datumRodjenja ce se kopirati u GetDatumRodjenja kreirajuci kopiju objekata i ta kopija ce se vratiti tamo gdje je pozvana
    //Kada imamo samo Datum prave se novi objekat koji ce imati iste vrijednosti kao element nase klase 
	//Da je bilo Datum& ne bi se koristio konstruktor kopije vec bi se vratio objekat koji je element(atribut) te klase
    bool GetSpol() const { return *_spol; }
    const char* GetRadnoMjesto() const { return _radnoMjesto; }
    char* GetGrad() const { return _grad; }
    const char* GetEmail() const { return _email; }

    //Z3.4
    void SetIme(const char* ime)
    {
        delete[] _ime; //uvijek dealcoriamo niz prvo kada imamo dinamicki kreiran niz karaktera
        _ime = AlocirajIKopiraj(ime);
    }
    void SetPrezime(const char* prezime)
    {
        delete[] _prezime;
        _prezime = AlocirajIKopiraj(prezime);
    }
    void SetDatumRodjenja(Datum datum) //pokazivac na objekat
    {
        if (_datumRodjenja == nullptr) //Provjerimo da li je nullptr jer ako jeste nema poente pozivati settere nad nultom adresom 
            _datumRodjenja = new Datum;
       _datumRodjenja->SetDan(datum.GetDan()); 
       _datumRodjenja->SetMjesec(datum.GetMjesec());
       _datumRodjenja->SetGodina(datum.GetGodina());
    }
    void SetSpol(bool spol)
    {
        delete _spol;
        _spol = new bool;
        *_spol = spol;
    }
    void SetRadnoMjesto(const char* radnoMjesto)
    {
        strcpy_s(_radnoMjesto, 100, radnoMjesto);
    }
    void SetGrad(const char* grad)
    {
        delete[] _grad;
        _grad = AlocirajIKopiraj(grad);
    }
    void SetEmail(const char* email)
    {
        strcpy_s(_email, 100, email);
    }
    //Z3.5
    void Ispis()
    {
        cout << "Ime: " << _ime;
        cout << "Prezime: " << _prezime;
        _datumRodjenja->Ispis();
        cout << " Spol: " << ((*_spol == 1) ? "Musko" : "Zensko") << endl;
        cout << " Radno mjesto: " << _radnoMjesto;
        cout << " Grad: " << _grad;
        cout << "Email: " << _email;
    }
    //Z3.6
    ~Uposlenik()
    {
        delete[] _ime, delete[] _prezime, delete[] _grad; //S obzirom da su dati pokazivaci istog tipa mozemo ih brisati u jednoj liniji 
        _ime = _prezime = _grad = nullptr;
    	delete _datumRodjenja; //njegov destrukor se automatksi poziva 
        _datumRodjenja = nullptr;
        delete _spol;
        _spol = nullptr;
    }
};

class Kino {
private:
    char* _naziv;
    char _adresa[100];
    int* _maxBrojDvorana; // pokazivac na varijablu (obezbijediti da sadrzi vrijednost velicine niza)
    int _trenutnoDvorana; //brojac objekata u dinamickom nizu (pocinje od 0)
    Dvorana* _dvorane; // pokazivac na niz objekata
    //Velicina niza _dvorane ce upravo biti _maxBrojDvorana
    int _trenutnoUposlenika; //brojac
    //brojace ne setujemo preko settera 
    Uposlenik* _uposlenici[50] = { nullptr }; // niz pokazivaca na objekte tipa Uposlenik
    //Ovdje je svaki pokazivac prazan na pocetku
//ALternativa, proci for petljom i reci _uposlenici[i]=nullptr 
public:
    Kino()
    {
        _naziv = nullptr;
        strcpy_s(_adresa, 100, "");
        _maxBrojDvorana = nullptr; //velicina niza
        _trenutnoDvorana = 0; //brojac
        _dvorane = nullptr;
        _trenutnoUposlenika = 0; //brojac
    }
    //Z4.1
    Kino(const char* naziv, const char* adresa, int maxBrojDvorana) //Korisnicki definiran konstrukor
    {
        _naziv = AlocirajIKopiraj(naziv);
        strcpy_s(_adresa, 100, adresa);
        _maxBrojDvorana = new int(maxBrojDvorana); //moramo alocirati jer kasnije ne mozemo setovati ako nismo alocirali
        //_maxBrojDvorana ima nevalidnu vrijednost u trenutnku kada se kreira i dereferenciranje nevalidne vrijednosti dovodi do greske, zato alociramo
        //_maxBrojDvorana = new int(maxBrojDvorana); poziva konstruktor kopije za primitivni tip integer
        _trenutnoDvorana = 0;
        _dvorane = new Dvorana[*_maxBrojDvorana]; //konsturise se niz velicine _maxBrojDvorana i za svaki element koji je tipa Dvorana poziva se defaultni konstruktor
        //_maxBrojDvorana je pokazivac pa moramo dereferencirati da bi dobili tu vrijednost
        _trenutnoUposlenika = 0; //jer je brojac
    }
    //Z4.3
    void SetNaziv(const char* naziv)
    {
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    //Z4.4
    char* GetNaziv() const { return _naziv; }
    const char* GetAdresa() const { return _adresa; }
    int GetMaxBrojDvorana() const { return *_maxBrojDvorana; }
    int GetTrenutnoDvorana() const { return _trenutnoDvorana; }

    //Z4.5
    bool DodajDvoranu(Dvorana& dvorana) //primamo dvoranu po referenci 
    {
        if (_trenutnoDvorana == *_maxBrojDvorana) //u ovom slucaju je brojac dosao do maksimalnog broja dvorana i nije moguce dodavati jos dvorana
            return false; //vrati false kao indikator da nije uspjesno dodan element
        //Za promjenu vrijednosti koristimo Settere
        //S obzirom da je _dvorane vec kreiran, nema potrebe da ih ponovo kreiramo sa new vec mozemo samo pristupiti vrijednostima
        _dvorane[_trenutnoDvorana].SetNaziv(dvorana.GetNaziv());
        _dvorane[_trenutnoDvorana].SetSjedista(dvorana.GetBrojRedova(), dvorana.GetBrojKolona());
        
        _trenutnoDvorana++;
    	return true;
    }
    //Z4.6
    bool DodajUposlenika(Uposlenik& uposlenik)
    {
        if (_trenutnoUposlenika == 50)
            return false;
        _uposlenici[_trenutnoUposlenika] = new Uposlenik; //Ovjde trebamo kreirati jer nije kreiran u konstruktoru
        _uposlenici[_trenutnoUposlenika]->SetIme(uposlenik.GetIme());
        _uposlenici[_trenutnoUposlenika]->SetPrezime(uposlenik.GetPrezime());
        _uposlenici[_trenutnoUposlenika]->SetDatumRodjenja(uposlenik.GetDatumRodjenja());
        _uposlenici[_trenutnoUposlenika]->SetGrad(uposlenik.GetGrad());
        _uposlenici[_trenutnoUposlenika]->SetSpol(uposlenik.GetSpol());
        _uposlenici[_trenutnoUposlenika]->SetEmail(uposlenik.GetEmail());
        _uposlenici[_trenutnoUposlenika]->SetRadnoMjesto(uposlenik.GetRadnoMjesto());
	    
	    /*Drugi nacin
	    const char* ime = uposlenik.GetIme();
		const char* prezime = uposlenik.GetPrezime();
		Datum datum = uposlenik.GetDatumRodjenja();
		bool spol = uposlenik.GetSpol();
		const char* radnoMjesto = uposlenik.GetRadnoMjesto();
		const char* grad = uposlenik.GetGrad();
		const char* email = uposlenik.GetEmail();
		_uposlenici[_trenutnoUposlenika] = new Uposlenik(ime, prezime, datum, spol, radnoMjesto, grad, email);
		_trenutnoUposlenika++;
		return true;
	    */
    }
    //Z4.7
     //Ispisati naziv kina, adresu, nazive dvorana, te imena i prezimena uposlenika
    void Ispis()
    {
        cout << "Naziv: " << _naziv << endl;
        cout << "Adresa: " << _adresa << endl;
        cout << "*******************DVORANE**********************\n";
        for (size_t i = 0; i < _trenutnoDvorana; i++)
            cout << _dvorane[i].GetNaziv() << endl;
        cout << "*******************UPOSLENICI*******************\n";
        for (size_t i = 0; i < _trenutnoUposlenika; i++)
            cout << _uposlenici[i]->GetIme() << " " << _uposlenici[i]->GetPrezime() << endl;
    }
    //Z4.8
    ~Kino()
    {
        delete[] _naziv;
        _naziv = nullptr;
        delete _maxBrojDvorana;
        _maxBrojDvorana = nullptr;
        delete[] _dvorane;
        _dvorane = nullptr;
        for (int i = 0; i < 50; i++)
        {
            delete _uposlenici[i];
            _uposlenici[i] = nullptr;
        }
    }
};
void Zadatak1() {
    cout << "Testiranje klase 'Datum'" << endl;
    Datum euro2021; // Testiranje dflt. ctora
    euro2021.SetDan(11);
    euro2021.SetMjesec(6);
    euro2021.SetGodina(2021);
    Datum olimpijskeIgre(24, 7, 2021); // Testiranje user-def. ctora
    Datum paraOlimprijskeIgre(olimpijskeIgre.GetDan(), olimpijskeIgre.GetMjesec(), olimpijskeIgre.GetGodina());
    paraOlimprijskeIgre.SetMjesec(8);
    cout << "EURO 2021:" << endl;
    euro2021.Ispis();
    cout << endl;
    cout << "Olimpijske igre 2021:" << endl;
    olimpijskeIgre.Ispis();
    cout << endl;
    cout << "Paraolimpijske igre 2021:" << endl;
    paraOlimprijskeIgre.Ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;
}

void Zadatak2() {
    cout << "Testiranje klase 'Sjediste'" << endl;
    Sjediste s1, s2('C', 4);
    Sjediste s3(s2.GetRed(), s2.GetKolona());
    s3.Ispis();
    cout << endl;
    s3.SetRed('M');
    s3.SetKolona(16);
    s3.Ispis();
    cout << endl;
    cout << "Done." << "\n\n";

    cout << "Testiranje klase 'Dvorana'" << endl;
    Dvorana extreme3("Dvorana Extreme 3", 7, 7);
    extreme3.Ispis();
    cout << endl;
    Dvorana realExtreme3(extreme3.GetNaziv(), extreme3.GetBrojRedova(), extreme3.GetBrojKolona());
    realExtreme3.SetNaziv("Dvorana Real Extreme 3");
    realExtreme3.SetSjedista(10, 10);
    realExtreme3.Ispis();
    cout << endl;
    Dvorana real3D;
    real3D.SetNaziv("Dvorana Real 3D");
    real3D.SetSjedista(15, 8);
    real3D.Ispis();
    cout << endl;

    Sjediste* pok = real3D.GetSjediste('B', 2);
    cout << "Trazimo sjediste B-2 U dvorani Real 3D." << endl;
    if (pok != nullptr) {
        pok->Ispis();
        cout << endl << "Nadjeno." << endl;
    }
    else {
        cout << "Nije nadjeno." << endl;
    }
    pok = real3D.GetSjediste('X', 3);
    cout << "Trazimo sjediste X-3 u dvorani Real 3D." << endl;
    if (pok != nullptr) {
        pok->Ispis();
        cout << endl << "Nadjeno." << endl;
    }
    else {
        cout << "Nije nadjeno." << "\n\n";
    }
    cout << "Dealokacija dvorana..." << endl;
}
void Zadatak3() {
    cout << "Testiranje klase 'Uposlenik'" << endl;

    Datum datumRodjenja(3, 2, 1967);
    Uposlenik connanOBrien("Connan", "O'Brien", datumRodjenja, 1, "blagajnik", "Bihac", "teamcoco@gmail.com");
    connanOBrien.SetEmail("orangecoconut@gmail.com");
    connanOBrien.Ispis();
    cout << endl;

    Uposlenik jimmyKimmel;
    jimmyKimmel.SetIme("Jimmy");
    jimmyKimmel.SetPrezime("Kimmel");
    jimmyKimmel.SetDatumRodjenja(Datum(4, 2, 1966));
    jimmyKimmel.SetSpol(true);
    jimmyKimmel.SetEmail("the_pranklord@hotmail.com");
    jimmyKimmel.SetRadnoMjesto("prodavac kokica");
    jimmyKimmel.SetGrad("Portland");
    jimmyKimmel.Ispis();
    cout << endl;

    Uposlenik chuckNorris;
    chuckNorris.SetIme("Chuck");
    chuckNorris.SetPrezime("Norris");
    chuckNorris.SetDatumRodjenja(Datum(30, 2, 1940));
    chuckNorris.SetSpol(true);
    chuckNorris.SetEmail("gmail@chucknorris.com");
    chuckNorris.SetRadnoMjesto("redar, domar, financijski menadzer, projekcijski menadzer, direktor, ...");
    chuckNorris.SetGrad("Planeta Zemlja");
    chuckNorris.Ispis();
    cout << endl;
    cout << "Dealokacija uposlenika..." << endl;
}

void Zadatak4() {
    Kino dejaView("Deja View Cinema", "Bihac Ul. 76", 5);
    Dvorana d1("Dvorana 1", 10, 5), d2("Dvorana 2", 10, 6);
    cout << (dejaView.DodajDvoranu(d1) ?
        "Uspjesno dodavanje dvorane d1." :
        "Bezuspjesno dodavanje dvorane d1.") << endl;
    cout << (dejaView.DodajDvoranu(d2) ?
        "Uspjesno dodavanje dvorane d2." :
        "Bezuspjesno dodavanje dvorane d2.") << endl;;

    Datum datum1(2, 3, 1966), datum2(2, 4, 1969), datum3(1, 5, 1955);
    Uposlenik u1("Jonah", "Hillside", datum1, 1, "prodavac ulaznica", "Banja Luka", "jonahillside@gmail.com");
    Uposlenik u2("Dwayne", "'The Mountain' Johnson", datum2, 1, "domar", "Sarajevo", "johnrocksbigtime@gmail.com");
    Uposlenik u3("Tom", "Cruiser", datum3, 1, "vozac", "Brcko", "thomas_cruiser@gmail.com");

    if (dejaView.DodajUposlenika(u1))
        cout << "Uspjesno dodan " << u1.GetIme() << " " << u1.GetPrezime() << endl;
    if (dejaView.DodajUposlenika(u2))
        cout << "Uspjesno dodan " << u2.GetIme() << " " << u2.GetPrezime() << endl;
    if (dejaView.DodajUposlenika(u3))
        cout << "Uspjesno dodan " << u3.GetIme() << " " << u3.GetPrezime() << endl;
    dejaView.Ispis();
    cout << endl;
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
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 4);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
            case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
            case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
            case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
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
