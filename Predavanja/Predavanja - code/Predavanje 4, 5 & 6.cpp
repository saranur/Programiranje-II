#include <iostream>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
using namespace std;

char* AlocirajIKopiraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, sadrzaj);
	return novi;
}

class Element {
	int _lokacija;
	int* _putanja;
	int _trenutno;

	void PohraniPutanju(int lokacija) {
		//Trebamo prosiriti niz i dodati novu lokaciju 
		int vel = _trenutno + 1; //da svaki put uvecamo za 1, jer je ona na pocetku 0
		int* temp = new int[vel]; //niz koji je za jedan veci od prethodnog 
		for (size_t i = 0; i < _trenutno; i++)
			temp[i] = _putanja[i]; //iz putanje prebacujemo sve clanove u temo
		if(_putanja!=nullptr)
			delete[] _putanja; 
		_putanja = temp; //pohranjujemo adresu na koju pokazuje nas privremeni niz (temp)
		_putanja[_trenutno] = lokacija; //trenutno nam kaze gdje cemo pohraniti lokaciju 
		//uglatim zagradama vrsimo dereferenciranje
		_trenutno++;
	
	}
public:
	_declspec(property(get = GetLokacija,
		put = SetLokacija)) int Lokacija; //predstavljace formu interface-a

	Element(int lokacija = 0)
	{
		_lokacija = lokacija;
		_trenutno = 0;
		_putanja = nullptr;
		_putanja = nullptr;
	}
	Element(const Element& original) {
		_lokacija = original._lokacija;
		_trenutno = original._trenutno;
		_putanja = new int[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_putanja[i] = original._putanja[i];
		}
	}

	int GetLokacija()const { return _lokacija; }
	void SetLokacija(int lokacija) {
		PohraniPutanju(lokacija);
		_lokacija = lokacija; 
	}

	Element& operator = (const Element& original) {
		/*
		a = a; //a.poperator=(a) //zbog oboga provjeravamo da li se adresa razlikue od originala 
		a = g;
		*/
		if (this != &original) {
			_lokacija = original._lokacija;
			_trenutno = original._trenutno;
			delete[] _putanja;
			_putanja = new int[_trenutno];
			for (size_t i = 0; i < _trenutno; i++)
				_putanja[i] = original._putanja[i];
		}
			return *this;
	}
	bool operator ==(const Element& original) {
		if (_trenutno != original._trenutno || _lokacija != original._lokacija)
			return false;
		for (size_t i = 0; i < _trenutno; i++)
			if (_putanja[i] != original._putanja[i])
				return false;
		return true;
	}
	bool operator !=(const Element& original) {
		 return !(* this == original); //vraca suprotno od onog sto vrati operator ==
			//provjeravamo objekat koji je pozvao nasu operaciju (metodu) i parametar - u nasem slucaju je to "original"
	}
	Element& operator +=(Element obj) { //& da bi izbjegli kopiranje
		_lokacija += obj._lokacija;
		return *this; //vraticemo onoga ko je pozvao metodu
	}
	Element  operator-(Element obj) { //
		return Element(_lokacija - obj._lokacija); //_lokacije ce biti od objekta koji je pozvao funckiju, 
		//u ovom slucaju lokacija ce biti od objekta b, a obj._lokacija se odnosi na c
	}

	int operator [](int lokacija ) {
		if(lokacija>=0 && lokacija<_trenutno)
			return _putanja[lokacija];
		return -1;
	}

	friend Element operator+(Element obj1, Element obj2);
	friend istream& operator >>(istream& CIN, Element& obj);
	~Element()
	{
		if (_putanja != nullptr)
		{ 
		delete[] _putanja;
		_putanja = nullptr;
		}
		_trenutno = 0;
	}
};
//Globalna funkcija
Element  operator+(Element obj1, Element obj2) {
	return Element(obj1._lokacija + obj2._lokacija);
}

//<< ne moze biti funkcija clanica, mora biti globalna funkcija!
ostream& operator<<(ostream& COUT, Element& obj) { //ukoliko zelimo da mozemo ispisati endl, etc ova funkcija mora bit ostream
	COUT << "Lokacija -> " << obj.Lokacija << endl;
	return COUT;
	//ukoliko bismo ovu funkciju proglasili void izgubili bi mogucnost pipinga (redanja jedno za drugom)
	//npr.
	//cout<<a<<b<<c<<endl;
}
istream& operator >>(istream& CIN, Element& obj) {
	CIN >> obj._lokacija;
	return CIN;
}
template<class T>
void Zamijeni(T& prvi, T& drugi) {
	T temp = prvi;
	prvi = drugi;
	drugi = temp;
}


const char* crt = "\n-----------------------------------------------------------------------------------------------------\n";
template<class T>

class FITVector {
	T* _niz; //T moze biti bilo sta, integer, student...
	int _trenutno = 0;
	void ProsiriNiz() {
		T vel = _trenutno + 1;
		T* temp = new T[vel]; //T = Student, Ovdje ce pozvati dflt ctor 
		//U slucaju da operator dodjele bude dobro implementiran
		//Inace ce se kopirati adrese 
		//Ne zelimo da se vezemo za bilo koji tip podatka ali moramo imati implementiran dflt ctor u svakom tipu koji zeli da koristi 

		for (size_t i = 0; i < _trenutno; i++)
			temp[i] = _niz[i]; //operator dodjele
		if (_niz != nullptr)
			delete[] _niz;
		_niz = temp;
	
	
	}
public:
	FITVector()
	{
		_trenutno = 0;
		_niz = nullptr;

	}
	~FITVector()
	{
		if (_niz != nullptr) {
			delete[] _niz;
			_niz = nullptr;
		}
		_trenutno = 0;
	}
	//prijave.push_back(200000 + i)
	void push_back(T obj) {
		ProsiriNiz();
		_niz[_trenutno++] = obj;
	}
	int size()const { return _trenutno; }
	T& operator[] (int lokacija) { return _niz[lokacija]; }
		//Bez reference ne bi mogli mijenjati vrijednosti, ukoliko ne zelimo da dopustimo mijenjanje onda pisemo bez reference 
};

class PolozeniPredmet {};

class Student {
	char* _indeks;
	char* _imePrezime;
	void Dealociraj(){
		if (_indeks != nullptr)
			delete[] _indeks;
		if (_imePrezime != nullptr)
			delete _imePrezime;
		_indeks = nullptr;
		_imePrezime = nullptr;
	}
	//FITVector<PolozeniPredmet> _polozeniPredmeti;
public:
	Student(const char*indeks="", const char* imePrezime="")
	{
		_indeks = AlocirajIKopiraj(indeks);
		_imePrezime = AlocirajIKopiraj(imePrezime);
	}
	Student(const Student& original)
	{
		_indeks = AlocirajIKopiraj(original._indeks);
		_imePrezime = AlocirajIKopiraj(original._imePrezime);
	}

	Student& operator =(const Student& original) {
		if (this != nullptr) {
			Dealociraj(); //kada pozivamo operator = vec imamo alociraj prostor te je potrebno dealoicirati 
			_indeks = AlocirajIKopiraj(original._indeks);
			_imePrezime = AlocirajIKopiraj(original._imePrezime);
		}
		return *this;
	}
	~Student()
	{
		Dealociraj();
	}
	
	friend ostream& operator<<(ostream& COUT, const Student& obj) {
		COUT << "(" << obj._indeks << ") " << obj._imePrezime << endl;
		return COUT;
	}
	bool operator==(const Student& original) {
		return strcmp(_indeks, original._indeks) == 0;
	}
	//bool DodajPolozeni(PolozeniPredmet obj) {
	//	for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
	//		if (_polozeniPredmeti[i] == obj)
	//			return false;
	//			_polozeniPredmeti.push_back(obj);
	//			return true;
	//	
	//}

};

template<class T1, class T2>
class Imenik {
	T1* _niz1;
	T2* _niz2;
	int _trenutno;
	void Dealociraj() {
		if (_niz1 != nullptr)
			delete[] _niz1;
		if (_niz2 != nullptr)
			delete[] _niz2;
		_niz1 = nullptr;
		_niz2 = nullptr;
	}
	void ProsiriNiz() {
		int vel = _trenutno + 1;
		T1* temp1 = new T1[vel]; //ovdje je je jako bitno da imamo dflt ctor za T1 i T2
		T2* temp2 = new T2[vel];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _niz1[i]; //poziva se operator dodjele tipa T1
			temp2[i] = _niz2[i];
		}
		Dealociraj();
		_niz1 = temp1;
		_niz2 = temp2;
	}
	void PostaviPodrazumijevane(){
		_trenutno = 0;
		_niz1 = nullptr;
		_niz2 = nullptr;
	}
public: 
	Imenik()
	{
		PostaviPodrazumijevane();
		
	}
	~Imenik() {
		Dealociraj();
	}
	Imenik(const Imenik& original)
	{
		PostaviPodrazumijevane();
		for (size_t i = 0; i < original._trenutno; i++)
		{
			Add(original._niz1[i], original._niz2[i]);
		}
	}
	void Add(T1 obj1, T2 obj2) {
		ProsiriNiz();
		_niz1[_trenutno] = obj1;
		_niz2[_trenutno] = obj2;
		_trenutno++;
	}

	friend ostream& operator<<(ostream& COUT, const Imenik& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._niz1[i] << " " << obj._niz2[i] ;
		return COUT;
	}
	Imenik operator[] (T1 obj1) { //jer ne znamo sta ce se pretrazivati, stavimo T1, funckija vraca Imenik
		Imenik<T1, T2> temp;
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (obj1 == _niz1[i])
				temp.Add(_niz1[i], _niz2[i]);
			//dodajemo parove koji odgovaraju uslovu pretrage
		}
		return temp; //dobili bi u ovom slucaju broj telefona i ime
	}

};

pair<int, float>GetPodatke() { //pair je posebno koristan jer mozemo vratiti set podataka koji su razlicitog tipa
	return make_pair(135322, 5.5);
}
tuple<int, Student, float, char>GetPodatke2() {
	 Student sara("198703", "Sara Nur");
	 tuple<int, Student, float, char>podaci(170071, sara, 6.8, 'M');
	 return podaci;
}
bool Poredjenje(int prvi, int drugi)
{ return prvi < drugi; }

void main() {

	vector<int>brojevi{ 6,10,3,99,8 };
	auto poredjenje = [](int prvi, int drugi) {return prvi < drugi; };
	sort(brojevi.begin(),
		brojevi.end(),
		poredjenje); //radi preglednosti 
	//ili mozemo pozvati globalnuFunkciju Poredjenje
		//[](int prvi, int drugi) {return prvi < drugi; }); //bice sortiranje od najmanjeg do najveceg 
		//sada mozemo poslati lambda funkciju koja se opisati proces sortiranja i organizacije elemenata 
		//sve brojeve od pocetka do kraja ce se sortirati putem lambda funckije 

	for (size_t i = 0; i < brojevi.size(); i++)
		cout << brojevi[i] << ", "; 











	int broj = 10;
 /* Lambda funkcije(bezimene funkcije)
		Lambda funkcija se obično sastoji iz tri dijela :

	-Prva komponenta nam omogućava da u našu lambda funkciju uvezemo odnosno učinimo dostupnim neke od varijabli / objekata koji se nalaze u okruženju naše lambda funkcije.
		Capture list -lista vrijednosti koje želimo da uvezemo
		*/

	/* 
	//Lambda funkcija
	[]() {
		cout << "Pozdrav..." << endl; //ovdje smo je kreirali ali je moramo i pozvati kao i obicnu funkciju 
	} ();

	[broj]() {
		cout << broj << endl;
	} ();

	[](int b) {
		cout << "Pozdrav..." << b << endl;
	}(55); //ovo 55 ce biti iskoristeno za inicijalizaciju varijable b

	*/

	
	/* Pokazivavi na funkcije
	Pokazivac na funkciju se sastoji iz tri dijela: 
	1. Naziv pokazivaca 
	2. Da nije obicni pokazivac naznacujemo zagradama (*pok) ->pokazivac na funkciju
 	3. S lijeve strane stavljamo povratni tip, nakon toga navodimo listu paramtera 
	*/
	int max = 5;
	int niz[] = { 6,10,3,99,8 };
	//Zahvaljujuci pokazivacu na funkciju mozemo vise puta pozvati ovu lambda funkciju 
	/* 
	int (*sumiraj) (int[],int) =  [](int niz[], int max) {
		int suma = 0;
		for (size_t i = 0; i < max; i++)
			suma += niz[i];
		return suma;
	}; 
	*/
	//Drugi nacin
	/* 
	auto sumiraj = [broj](int niz[], int max) {
		int suma = 0;
		for (size_t i = 0; i < max; i++)
			suma += niz[i];
		return suma;
	};*/
	//auto sumiraj sada podrzava ulazne caputre list vrijednosti [broj] sto nije bilo moguce sa pokazivacem na funkciju 

	/* 
	function<int(int[], int)> sumiraj = [](int niz[], int max) { //moramo ukljuciti #include <functional>
		int suma = 0;
		for (size_t i = 0; i < max; i++)
			suma += niz[i];
		return suma;
	};
	*/
	function<int(int[], int)> sumiraj = [](int niz[], int max) { //moramo ukljuciti #include <functional>
		int suma = 0;
		for (size_t i = 0; i < max; i++)
			suma += niz[i];
		return suma;
	};
	/* kada bi dodali:
		function<int(int[], int)> sumiraj = [&](int niz[], int max)
		sada bi svi clanovi unutar lambda funkcije bili dostupni po referenci.
		Takodjer, kada bi stavili znak jednakosti
		--Ukoliko zelimo da modifikujemo i mijenjamo vrijednosti unutar lambda onda je potrebno da posaljemo po referenci
		--takodjer mozemo proslijediti specificnog clana [&max]
		
		function<int(int[], int)> sumiraj = [=](int niz[], int max)
		tada bi svi clanovi postali dostupni po vrijednosti

*/

	
	//Lambda funckija rekurzivnog tipa
	static int (*rek)(int) = [](int n) {
		if (n <= 0) return 0;
		return n + rek(n - 1);
	}; 
	/* 
	cout << rek(5) << endl;
	cout << sumiraj(niz, max) << endl;
	cout << sumiraj(niz, max) << endl;
	cout << sumiraj(niz, max) << endl;
	cout << sumiraj(niz, max) << endl;
	*/ 



	Imenik<Student, int> prvaGodina;
	Student sara("198703", "Sara Nur"),
		jasmin("155345", "Jasmin Maksumic"),
		goran("1843465", "Goran Gogo");
	prvaGodina.Add(sara, 346547345);
	prvaGodina.Add(jasmin, 464563454);
	prvaGodina.Add(goran, 346346563);

	//cout << prvaGodina;
	//cout << prvaGodina[sara] << endl;
	
	pair<int, float>par1(150051, 8.7);
	pair<int, float>par2 = make_pair(160051, 8.7);
	//cout << par1.first << endl; //vratice par1(150051, 8.7)

	int indeks;
	float prosjek;

	//za tie moramo ukljuciti:  #include <tuple>
	//tie(indeks, prosjek) = par1; //funkcijski poziv se nalazi sa lijeve strane 
	//cout << indeks << " " << prosjek << endl;

	// get<1>(par1);
		//get zahtjeva lokaciju clana 
	//Kada zelimo da pohranimo veci broj elemenata razlicitog tipa, onda nam par nije opcija jer on cuva samo dva clana
	//U takvim slucajevima, na raspolaganju nam je tuple
	//Tuple ne ogranicava broj clanova koje mozemo pohraniti
	tuple<int, Student, float, char>podaci(170071, sara, 6.8, 'M');
	//cout << get<2>(podaci) << endl;









	//FITVector<int> prijave; //dobili smo mogucnost da cuvamo znacajan broj vrijednosti tipa integer
	//for (size_t i = 0; i < 30; i++)
	//	prijave.push_back(i);
	//bez da brinemo o alokaciji, dealokaciji...
	//nas zanima kako da dodamo element u to skladište i kako da pristupimo tom elementu

	//for (size_t i = 0; i < prijave.size(); i++)
	//	cout << prijave[i] << ", "; //operator[]
	//cout << crt;
	//FITVector<float> prosjeci; 
	//for (size_t i = 0; i < 20; i++)
	//	prosjeci.push_back(5.5 + i);
	//
	//for (size_t i = 0; i < prosjeci.size(); i++)
	//	cout << prosjeci[i] << ", "; //operator[]
	//cout << crt;

	//vector<Element> elementi;
	//for (size_t i = 0; i < 20; i++)
	//	elementi.push_back(Element(i));


	//int x = 10, y = 21;
	//cout << "x = " << x << " y = " << y << endl;
	//Zamijeni(x, y);
	//cout << "x = " << x << " y = "<< y << endl;

	//double f = 3.4, m = 44.4;
	//cout << "f = " << f << " m = " << m << endl;
	//Zamijeni(f, m);
	//cout << "f = " << f << " m = " << m << endl;

	//

	//Element a = 10;
	//a.SetLokacija(556);
	//Element g = a; //U ovom momentu objekat se tek kreira tako da ce se pozvati konstruktor kopije 
	//g.SetLokacija(576);
	//g.SetLokacija(576);
	//g.SetLokacija(576);
	//
	//Operatorske metode imaju potrebu da ne

	//a = g; //u ovom momentu se poziva operator dodjele 
	//
	//cout << g[0] << endl;
	//
	//
	//Element b = a + 10; // operator + (a, 10);
	//Element c = b-a;
	//cout << "Unesite a i b " << endl;
	//cin >> a >> b;
	//cout << c.Lokacija << endl;
	//c += 20;
	//cout << c.Lokacija << endl;
	//cout << c << endl;
	//Element d = b - c; //b.operator-(c) -- poziv metode clanice
	//
	//cin.get();
}