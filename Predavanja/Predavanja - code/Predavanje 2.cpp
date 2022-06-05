#include <iostream>
#include <iomanip>
using namespace std;

/*
klase
public, private
stanje objekta
ponasanje objekta
identitet objekta
tipovi operacija (konstruktori, modifikatori/set, upiti/get)
const operacije
*/
class Dugmic {
/*
**Funkcije** - termin koji se obicno odnosi na nesto sto je globalno i svima dostupno, mada nemamo globalne funkcije u svim jezicima, ali se uglavnom koristi za nesto sto nije upakovano u jedno cjelinu.
**Metoda** - pojam obicno vezan za nesto sto pripada odredjenoj klasi, nesto sto je dostupno samo ogranicenom dijelu koda, dostupno je unutar klase i nekim nasljedjenim klasama i njihovim metodama.
*/
private: 
	int sirina; //atribute deklarisemo sa pocetnom donjom crticom i na taj nacin jasno napravimo distinkciju izmedju atributa i parametara
	int visina;
public: /* 
	Dugmic() //defaultni konstruktor
	{
		this->sirina = 0; //neke defaultne vrijednosti
		this->visina = 0;
	}
	*/ 
	//zakomentarisali smo defaultni konstrukor jer smo sada metodu PostaviVrijednosti transformisali u konstrukor. Ne mozemo imati oba konstrukora jer bi nam se kompajler bunio, oba imaju neke vec unesene vrijesnosti 
	
	//konstrukor
	Dugmic(int sirina = 15, int visina = 3) { //metoda
		//_sirina = sirina; //sa lijeve strane se nalazi atribut, a sa desne strane se nalazi parametar funkcije
		this->sirina = sirina; //Kljucna rijec **this->** jasno naznacava da zelimo da referenciramo nekoga ko je clanica klase (atribut te klase), a ne nekog ko se nalazi u listi parametara
		this->visina = visina;
	}
	void SetSirina(int sirina) {
		this->sirina = sirina;
	}
	int GetSirina() const{ return sirina; } //obzirom da je ovo const metoda, ne mozemo modifikovati vrijednosti vec iskljucivo vratiti vrijednosti tog atributa.
	void Prikazi() { //ovo je metoda
	/*
	-----------------------------------------
	|					|
	|					|
	|					|
	-----------------------------------------
	*/
		for (int i = 0; i < visina; i++)
		{
			for (int j = 0; j < sirina; j++)
			{
				if (i == 0 || i == visina - 1)
					cout << "-";
				else
					if (j == 0 || j == sirina - 1)
						cout << "|";
					else
						cout << " ";
			}
			cout << endl;
		} 
	}

};

const int redova = 3;
const int kolona = 3;
class XO {
	char niz[redova][kolona];
	int igracNaPotezu;
	bool krajIgre; //sluzi kao oznaka da vise nema popunjavanja polja, ako nemamo ovoga, mogli bi da nastavimo da unosimo odnosno popunjavamo lokacije i nakon pobjede jednog korisnika
	void OcistiMatricu() {
		for (size_t i = 0; i < redova; i++)
			for (size_t j = 0; j < kolona; j++)
				niz[i][j] = ' ';
	}
	void GetKoordinateIzLokacije(int lokacija, int& r, int& k) {
		 /*if (lokacija <= 3)
			r = 0, k = lokacija - 1; //ili mozemo uraditi na ovaj nacin, s tim da ispitmano za lokaciju <=3,6 i 9.
			*/
		switch (lokacija)
		{
		case 1: r = 0; k = 0; break;
		case 2: r = 0; k = 1; break;
		case 3: r = 0; k = 2; break;
		case 4: r = 1; k = 0; break;
		case 5: r = 1; k = 1; break;
		case 6: r = 1; k = 2; break;
		case 7: r = 2; k = 0; break;
		case 8: r = 2; k = 1; break;
		case 9: r = 2; k = 2; break;
		}
	}
	char GetNaredniZnak() {
		char znak = (igracNaPotezu % 2 == 0) ? 'X' : 'O';
		igracNaPotezu++; //ovim znamo da je igrac igrao i samim time uvecavamo vrijednost ovog atributa
		return znak;
	}
	bool ProvjeriRedove() {
		char znak;
		int brojac;
		for (size_t i = 0; i < redova; i++)
		{
			brojac = 0; //nuliramo brojac na nivou svakog reda
			znak = niz[i][0]; //zanima nas prva kolona u svakom redu trenutno
			if (znak != ' ') {
				for (size_t j = 0; j < kolona; j++)
				{
					if (znak == niz[i][j])
						brojac++;
					if (brojac == 3)
						return true; //znaci da je neko pobjedio na nivou tog reda
				}
			}
		}
		return false;
	}
	bool ProvjeriKolone() {
		char znak;
		int brojac;
		for (size_t j = 0; j < kolona; j++)
		{
			brojac = 0; //nuliramo brojac na nivou svake kolone
			znak = niz[0][j]; //uzimamo onaj koji se nalazi u prvom redu uvijek, a ono sto se mijenja jesu kolone
			if (znak != ' ') {
				for (size_t i = 0; i < redova; i++)
				{
					if (znak == niz[i][j])
						brojac++;
					if (brojac == 3)
						return true; //znaci da je neko pobjedio na nivou te kolone 
				}
			}
		}
		return false;
	}
	bool ProvjeriLDijagonale() {
		char znak = niz[0][0];
		int brojac = 0;
		if (znak == ' ')
			return false;
		for (size_t i = 0;i < redova; i++)
		{
			for (size_t j = 0; j< kolona; j++)
			{
				if (i == j && znak == niz[i][j]) //znamo da se nalazimo na dijagonali ukoliko su vrijednosti iste 
					brojac++;
			}		
		}
		return brojac==3; //on je sada na nivou dijagonale, a ne na nivou svakog reda i svake kolone pa ga mozemo izbaciti 
	}
	bool ProvjeriDDijagonale() {
		char znak = niz[0][2]; //prvi red ali posljednja kolona nas zanima
		int brojac = 0;
		if (znak == ' ')
			return false;
		for (size_t i = 0; i < redova; i++)
		{ 
		
			for (size_t j = 0; j < kolona; j++)
			{	/*
						0,2
					1,1
				2,0
			Lokacije desne dijagonale, sve
			*/
				if (i + j==redova-1 && znak == niz[i][j]) //znamo da se nalazimo na dijagonali ukoliko su vrijednosti iste 
					brojac++;
			}
		}
		return brojac == 3; //on je sada na nivou dijagonale, a ne na nivou svakog reda i svake kolone pa ga mozemo izbaciti 
	}

public:
	XO() //dflt ctor
	{
		igracNaPotezu = 1;
		krajIgre = false; //igra tek starta, objekat se tek kreira 

		OcistiMatricu(); //sve vrijesnosti postavi na prazan prostor
		//ovo cemo sakriti u private jer ne zelimo da korisnici imaju mmogucnost usred igre da iskoriste ovu metodu
	}
	void Prikazi() {
		/* 
		+---+---+---+
		|	|	|	|
		+---+---+---+
		*/
		for (size_t i = 0; i < redova; i++)
		{
			for (size_t j = 0; j < kolona; j++)
			{
				cout << "+---"; //napravice +---+---+---

			}cout << "+" << endl; //ispisuje taj posljenji plusic
			for (size_t j = 0; j < kolona; j++)
			{
				cout << "|" << setw(3)<<niz[i][j]; // stavljamo na setw(3) jer smo koristili 3 crtice

			}cout << "|" << endl;  //ispisuje posljenji pipe 
		
		} //ovjde necemo dobiti zadnji red pluseva i crtica, pa izlaskom iz for petlje kreiramo jos jednu
		for (size_t j = 0; j < kolona; j++)
		{
			cout << "+---"; 

		}cout << "+" << endl;


	}
	void Igraj(int pozicija) {

		if (krajIgre) {
			return; //ako je kraj igre nece se moci unositi vise lokacije  u matrici
			cout << "KRAJ IGRE " << endl;
		}
		int r = 0, k = 0; //pozicije reda i kolone
		GetKoordinateIzLokacije(pozicija, r, k);
		//provjeravamo da li je lokacija koju je korisnik izabrao vec zauzeta
		if (niz[r][k] == ' ') {//ako je na tim lokacijama prazan prostor znaci da je slobodna lokacija
			niz[r][k] = GetNaredniZnak();
			if (ProvjeriRedove() || ProvjeriKolone() || ProvjeriLDijagonale() || ProvjeriDDijagonale() ) {
				krajIgre = true; //oznacava kraj igre
				cout << "KRAJ IGRE " << endl;
			}
		}
		else
			cout << "LOKACIJA ZAUZETA" << endl;
	}
};

void main() {

	//Dugmic spasi;
	//Dugmic spasi(23, 4); //mozemo direktno uticati na vrijednosti atributa pomocu konstrukora 
	//spasi.PostaviVrijednosti(30, 4); //trenutno stanje objekta spasi je 30 i 4 
	//spasi.Prikazi();
	XO xo;
	int lokacija;
	do {
		xo.Prikazi();
		cout << "Pozicija-> ";
		cin >> lokacija;
		system("cls");
		xo.Igraj(lokacija);
	} while (1);
}
