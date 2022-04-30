#include <iostream>
using namespace std;


int prvaGodina = 1 , drugaGodina = 2;
int brojIndeksa = 200000;


char* AlocirajIKopiraj(const char* sadrzaj) {
	if(sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, sadrzaj);
	return novi;
}

class Datum {
	int _dan, _mjesec, _godina;
public:
	Datum(int dan, int mjesec, int godina) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}
	void Info() { cout << _dan << "." << _mjesec << "." << _godina << endl; }
	int GetDan() const { return _dan; }
	int GetMjesec() const { return _mjesec; }
	int GetGodina() const { return _godina; }
	int SetDan(int dan) { _dan = dan; }
	int SetMjesec(int mjesec) { _mjesec = mjesec; }
	int SetGodina(int godina) { _dan = godina; }

};
class Student {
private: 
	const int _indeks; //=200000, mozemo kreirati i neku globalnu varijablu 
	int& _godinaStudija;
	char* _imePrezime;
	Datum _datumRodjenja;
public: 
	Student(const char* imePrezime, int &godinaStudija, int dan, int mjesec, int godina)  //zelimo da se nasa referenca usmjeri na nesto sto ce postojati i nakon sto se konstruktor zavrsi 
		//jer smo godinaStudija pozvali po referenci, znaci da se nece kreirati nova lokacija vec ce biti drugo ime za nasu varijablu prvaGodina ili drugaGodina
		: _indeks(brojIndeksa++), 
		  _godinaStudija(godinaStudija), // i reference mozemo inicijalizovati u headeru 
		  _datumRodjenja(dan, mjesec, godina)
		/* : je operator koji koristimo kada zelimo uticati na inicijalizaciju objektata prilikom inicijalizije memorije
		Najčešća tri momenta zbog kojih imamo potrebu da reagujemo u zaglavlju konstruktora su kada imamo :
	    - Konstante
		- Reference
		- Objekti drugih klasa
		*/

		//kod inicijalizacije u zaglavlju smo sigurni da ce se sigurno kreirati _datumRodjenja na osnovu nekog konstruktora 
		//ovjde smo izvrisili i konstrukciju i inicijalizaciju
	{
		_imePrezime = AlocirajIKopiraj(imePrezime);
		/* Ukoliko ne konstruisemo i inicijalizujemo u zaglavlju konstrukora, ono sto ce se desiti je da ce se
		* prvo pozvati defaultni konstruktor za _datumRodjenja, a tek nakon toga, preko settera cemo postaviti vrijednosti 
		_datumRodjenja.SetDan(dan);
		_datumRodjenja.SetMjesec(mjesec);
		_datumRodjenja.SetGodina(godina);
		Mnogo je efikasnije raditi u zaglavlju konstrukora da bi izbjegli vise poziva i linija koda koje su bespotrebne 
		*/
	}
	~Student()
	{
		delete[] _imePrezime;
		_imePrezime = nullptr;
	}
	void Info() {
		
		cout << "Broj indeksa: " << _indeks << endl;
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Godina studija: " << _godinaStudija << endl;
		//cout << "Datum Rodjenja: " << _datumRodjenja << endl;
	}
};
class Fakultet {
	const int _id;
	char* _naziv;
public:
	static int _brojacId;
	Fakultet(const char* naziv)
		:_id (_brojacId++)
	{
		cout << "Konstrukcija-> " << naziv << endl;
		_naziv = AlocirajIKopiraj(naziv);
	}
	Fakultet(const Fakultet &original) 
		:_id(_brojacId++)

	{ //zbog & ona ne zahtjeva kopiju vec radi sa originalom
		cout << "Copy konstrukcija-> " << original._naziv << endl;
		_naziv = AlocirajIKopiraj(original._naziv);
	} 
	Fakultet(Fakultet&& original)
		:_id(original._id)
	{ //zbog & ona ne zahtjeva kopiju vec radi sa originalom
		cout << "Move konstrukcija-> " << original._naziv << endl;
		_naziv = original._naziv;
		original._naziv = nullptr;
	}
		
	~Fakultet()
	{
		if (_naziv != nullptr)
			cout << "Destrukcija-> " << _naziv << endl;
		delete[]_naziv; _naziv = nullptr;
	}
	void Info() {
		cout << "Fakultet-> " << _naziv << endl;
	}
	int _fakultetRang; //atribut koji je na nivou objekta 
	static int GetBrojacId() {
		return _brojacId;
	}
};
int Fakultet::_brojacId = 1;

Fakultet GetFakultet() {
	Fakultet tmp = "Neki novi faukltet";
	return tmp;
}


void main() {
	
	Fakultet fit = "Fakultet Informacijskih Tehnologija";
	Fakultet mf = "Masinski fakultet";
	cout << Fakultet::_brojacId << endl;
	Fakultet fit2(fit);
	cout << mf._brojacId;
	Fakultet::GetBrojacId();
	/* 
	Fakultet novi = GetFakultet();
	Fakultet mf= move(novi); //drugi nacin pozivanje move ctora 
	fit.Info();
	fit2.Info();
	mf.Info();
	*/
	//Fakultet fit2(fit); //mi smo dozvolili samo jedan nacin konstrukcije objekta, a to je da se posalje neki niz karaktera
	//ovjde bi imali jednu konstrukciju, a dvije destrukcije 
	//mi smo ovdje objekat fit2 kreirali na osnovu vec postojeceg objekta 
	//Da bi mogli napisati Fakultet fit2(fit); moramo imati konstruktor kopije, gdje ce se vrijednosti iz objekta fit kopirati u objekat fit2
	//fit2.Info();
	/* 
	Prvi problem : Imamo situaciju da kod _naziv oba objekta (fit i fit2) imaju adrese, tako da bilo koje promjene koje su izvrsene, bice vidljive na oba objekta 
	Drugi problem: Imamo dva objekta na stacku koje smo ispisali, medjutim u momentu kada istice zivotni vijek
	oba objekta, ono sto ce se desiti je da ce se reci fit2 da se dealocira, poziva se njegov destruktor i brise se njegov naziv na koji on pokazuje
	Posto oba objekta imaju istu adresu, on ce ponovo pokusati da obrise _naziv, dakle pokusava da obrise vec obrisanu memorijsku lokaciju
	Zbog toga nam program pada 
	*/

	//Rjesenje ovog probema je implementacija vlastitog konstruktora kopije 
	//Fakultet fit2(fit);
	//Fakultet fit2=fit; //identicno ovome Fakultet fit2(fit);
	/* 
	fit2.Info();
	cout << endl;
	Datum datumRodjenja(6, 6, 1222);
	Student sara("Sara Nur", prvaGodina, 2, 2, 1992);
	Student aras("Aras ", drugaGodina, 8, 8, 2000);
	sara.Info();
	cout << endl;
	aras.Info();
	cout << endl;
	*/
	     //Drugi nacin : 
	     //Student sara = "Sara Nur";
		 //Student ema(sara); ->ne mozemo ovo uraditi 
}