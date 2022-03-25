#include <iostream> //<> kod operatora <> ovaj fajl se nalazi u sistemskom folderu 
#include "Datum.h" // kod dvostrukih navodinika ce se traziti u folderu source.cpp, mi ako zelimo da koristimo <> trebamo otici u sistemski folder i tamo spremiti nase headere
#include "Sala.h"
#include "Bioskop.h"
#include "Radnik.h"
//takodjer pri inludanju mozemo navesti folder na disku gdje se nalazi odredjeni header recimo 
using namespace std;

//Koristene skracenice u komentarima
// dflt. = default
// user-def. = user-defined (korisnicki-definirano)
// ctor = constructor (konstruktor)
// dtor = destructor (destructor)
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

    cout << "Testiranje klase 'Sala'" << endl;
    Sala extreme3("Sala Extreme 3", 7, 7);
    extreme3.Ispis();
    cout << endl;
    Sala realExtreme3(extreme3.GetNaziv(), extreme3.GetBrojRedova(), extreme3.GetBrojKolona());
    realExtreme3.SetNaziv("Sala Real Extreme 3");
    realExtreme3.SetSjedista(10, 10);
    realExtreme3.Ispis();
    cout << endl;
    Sala real3D;
    real3D.SetNaziv("Sala Real 3D");
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
    cout << "Testiranje klase 'Radnik'" << endl;

    Datum datumRodjenja(3, 2, 1967);
    Radnik connanOBrien("Connan", "O'Brien", datumRodjenja, 1, "blagajnik", "Bihac", "teamcoco@gmail.com");
    connanOBrien.SetEmail("orangecoconut@gmail.com");
    connanOBrien.Ispis();
    cout << endl;

    Radnik jimmyKimmel;
    jimmyKimmel.SetIme("Jimmy");
    jimmyKimmel.SetPrezime("Kimmel");
    jimmyKimmel.SetDatumRodjenja(Datum(4, 2, 1966));
    jimmyKimmel.SetSpol(true);
    jimmyKimmel.SetEmail("the_pranklord@hotmail.com");
    jimmyKimmel.SetRadnoMjesto("prodavac kokica");
    jimmyKimmel.SetGrad("Portland");
    jimmyKimmel.Ispis();
    cout << endl;

    Radnik chuckNorris;
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
    Bioskop dejaView("Deja View Cinema", "Bihac Ul. 76", 5);
    Sala d1("Sala 1", 10, 5), d2("Sala 2", 10, 6);
    cout << (dejaView.DodajDvoranu(d1) ?
        "Uspjesno dodavanje dvorane d1." :
        "Bezuspjesno dodavanje dvorane d1.") << endl;
    cout << (dejaView.DodajDvoranu(d2) ?
        "Uspjesno dodavanje dvorane d2." :
        "Bezuspjesno dodavanje dvorane d2.") << endl;;

    Datum datum1(2, 3, 1966), datum2(2, 4, 1969), datum3(1, 5, 1955);
    Radnik u1("Jonah", "Hillside", datum1, 1, "prodavac ulaznica", "Banja Luka", "jonahillside@gmail.com");
    Radnik u2("Dwayne", "'The Mountain' Johnson", datum2, 1, "domar", "Sarajevo", "johnrocksbigtime@gmail.com");
    Radnik u3("Tom", "Cruiser", datum3, 1, "vozac", "Brcko", "thomas_cruiser@gmail.com");

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

int main()
{
    Menu();
    return 0;
}

