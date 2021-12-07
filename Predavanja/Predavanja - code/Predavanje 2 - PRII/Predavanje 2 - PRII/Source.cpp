#include <iostream>
#include <ctime>
using namespace std;

char* AlocirajIKopiraj(const char* sadrzaj) {
	if (sadrzaj == nullptr) return nullptr; //nece dozvoliti da manipulise praznim sadrzajem
	int vel = strlen(sadrzaj) + 1;
	char* temp= new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int _dan, _mjesec, _godina;
	bool PrestupnaGodina(int godina) {
		return godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0;
	}
	int PosljednjiDanUMjesecu(int mjesec, int godina) {
		if (mjesec == 2)
			return 28 + PrestupnaGodina(godina);
		if (mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11)
			return 30;
		return 31;
	}
	bool ValidanDatum(int dan, int mjesec, int godina) {
		if (dan<1 || dan>PosljednjiDanUMjesecu(mjesec, godina) ||
			mjesec < 1 || mjesec>12 || godina < 1900)
			return false;
		return true;
	}
	void SetDatum(int dan, int mjesec, int godina) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}
	//strukutra tm koja u sebi ima set nekih obiljezja/atributa koji definisu odnosno cuvaju vrijesnoti o datumu i vremenu
	tm GetTrenutniDatum() {
		tm obj;
		time_t trenutno = time(0);
		localtime_s(&obj, &trenutno); //vrati trenutno vrijeme
		return obj;
	}
public: 
	void SetDanasnjiDatum() {
		tm obj = GetTrenutniDatum();
		SetDatum(obj.tm_mday, obj.tm_mon + 1, obj.tm_year + 1900);
	}
	Datum()
	{
		SetDanasnjiDatum(); //on ce pozvati metodu GetTrenutniDatum i on ce pozvati metodu SetDatum

	}

	Datum(int dan, int mjesec, int godina)
	{
		if (ValidanDatum(dan, mjesec, godina))
			SetDatum(dan, mjesec, godina);
		else
			SetDanasnjiDatum(); //u slucaju da korisnik unese datum koji nije validan 
	}
	/*
	16.03.2021 
	zelim da dodam 10 dana
	-ako dodamo 100 dana npr...
	*/
	void DodajDane(int brojDana) {
		if (ValidanDatum(_dan + brojDana, _mjesec, _godina)) {   //gledamo da li ce biti validan datum ako na trenutni dan dodamo neki broj dana
			_dan += brojDana;
			return;
		}
		while (brojDana>0){ 
			int danaDoKrajaMjeseca = 
				PosljednjiDanUMjesecu(_mjesec, _godina) - _dan +1; //_dan+1 ako je 31 da li je ostalo 14 ili 15 dana (ukoliko trenutni dan uzimamo u obzir
			if (brojDana > danaDoKrajaMjeseca) { //ovjde isipitujemo da li prelazimo u naredni mjesec
				brojDana -= danaDoKrajaMjeseca; //ako smo unijeli broj dana 100, a broj preostalih dana u mjesecu je 16, mi cemo od 100 oduzeti 16 i nastaviti sa ispitivanjem
				_dan = 1; //jer smo presli u novi mjesec
				_mjesec++; 
				if (_mjesec > 12) {
					_mjesec = 1;
					_godina++;
				}
			}
			else {
				//ako broj dana koji nam je preostaju nije dovoljno da bismo presli u naredni mjesec
				//dovoljno je da trenutnu vrijednost dana uvecamo za brojDana
				_dan += brojDana;
				brojDana = 0; //zavrsavamo da kojim slucajem se petlja vise ne bi izvrsavala
			}
		}

	}
	char* ToString() {
		int max = 20;
		char* temp = new char[max]; //16
		char buffer[10];
		_itoa_s(_dan, buffer, 10); //da bi dobili broj kao niz karaktera koristimo metodu itoa()
		strcpy_s(temp, max, buffer); //16
		strcat_s(temp, max, "."); //16.
		_itoa_s(_mjesec, buffer, 10);  //itoa-integer to alphabet 
		//strcpy_s prekopira niz karaktera koji se proslijedi u novi, strcpy uvijek ignorise postojeci sadrzaj
		//krece od lokacije nula i zanemaruje postojeci sadrzaj niza
		strcat_s(temp, max, buffer); //16.3
		strcat_s(temp, max, "."); 
		//strcat_s - zadrzava postojeci sadrzaj niza ali na njega dodaje tacku u ovom slucaju
		//strcat_s 
		_itoa_s(_godina, buffer, 10);
		strcat_s(temp, max, buffer); //13.3.2021
		return temp;

		//cout << _dan << "." << _mjesec << "." << _godina<<endl; 
	} 
	//klase manipulisu vrijednostima
	int GetDan() const { return _dan; }
	int GetMjesec() const { return _mjesec; }
	int GetGodina() const { return _godina; }
};

class Osoba {
	char* _imePrezime;
	Datum _datumRodjenja;
public: 
	Osoba(const char* imePrezime, Datum datumRodjenja) 
		: _datumRodjenja(datumRodjenja.GetDan(), datumRodjenja.GetMjesec(),
			datumRodjenja.GetGodina()) //sada za poziv ovog konstrukotra trebamo posjedovati objekat tipa datumRodjenja, a ne tri vrijednosti
	{
		_imePrezime = AlocirajIKopiraj(imePrezime);
	}
	Osoba(const char* imePrezime, int dan, int mjesec, int godina)  //u zaglavlju mozemo pozvati zeljeni konstrukor, dodamo : i pozivamo
	: _datumRodjenja(dan, mjesec, godina) //ako ne dodamo ovaj dio koda, bice poslan default ctor i ispisace trnutni datum
	{
		_imePrezime = AlocirajIKopiraj(imePrezime);
	}
	~Osoba()
	{
		cout << "Unistavam objekat -> " << _imePrezime << endl;
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	void ToString() {
		cout << _imePrezime << " " << _datumRodjenja.ToString() << endl;
	}
};


void main() {
	Datum saraDatumRodjenja(1, 2, 2021);
	//Osoba sara("Sara Nur", 1, 2, 2000);
	Osoba sara("Sara Nur", saraDatumRodjenja);
	sara.ToString();
	Datum danas;
	//int brojDana = 0;
	//do
	//{
	//	danas.SetDanasnjiDatum(); //da bi uvijek modifikovali od danjasnjeg datuma
	//	cout << "Broj dana-> ";
	//	cin >> brojDana; //2 //3
	//	danas.DodajDane(brojDana);
	//	cout << danas.ToString() << endl;
	//} while (1);
	system("pause>0");
}