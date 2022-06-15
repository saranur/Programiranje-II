#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //sluzi za sortiranje 
#include <list>
#include <regex>

using namespace std;
char* AlocirajIKopiraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, sadrzaj);
    return novi;
}
const char* crt = "\n----------------------------------------\n";

class Poruke {
public:
    static const char* GetPorukaByCode(const char* code) {
        if (strcmp(code, "NPL"))
            return " Nepostojeca lokacija ";
        return " Doslo je do greske, molimo pokusajte kasnije! ";
    }
};

class FITString {
    char* _sadrzaj;
public:
    FITString(const char* sadrzaj)
    {
        _sadrzaj = AlocirajIKopiraj(sadrzaj);
    }

    FITString(const FITString& obj)
    {
        _sadrzaj = AlocirajIKopiraj(obj._sadrzaj);
    }

    char& operator [] (int lokacija) {
        if (lokacija < 0 || lokacija >= strlen(_sadrzaj))
            throw exception(Poruke:: GetPorukaByCode("NPL"));
        return _sadrzaj[lokacija];
    }   
    
    FITString& append(const char* sadrzaj)
    {
        int vel = strlen(_sadrzaj) + strlen(sadrzaj) + 1 ;
        char* temp = new char[vel];
        strcpy_s(temp, vel, _sadrzaj);
        strcat_s(temp, vel, sadrzaj);   //da bismo zadrzali ono sto smo dobili sa strcpy_s, koristimo strcat_s
        delete[] _sadrzaj;
        _sadrzaj = temp; //uzecemo adresu novog niza 
        return *this;
    }

    FITString operator +(const FITString& obj) {
        FITString temp(_sadrzaj);  //sara
        temp.append(obj._sadrzaj); //sara Nur
        return temp;
    }

    ~FITString()
    {
        delete[] _sadrzaj;
        _sadrzaj = nullptr;
    }

    friend ostream& operator <<(ostream& COUT, const FITString& obj) {
        COUT << obj._sadrzaj;
        return COUT;
    }

    bool operator ==(const FITString& obj) {
        return strcmp(_sadrzaj, obj._sadrzaj) == 0;
    }

    FITString& insert(int lokacija, const char* sadrzaj) {
        int vel = strlen(_sadrzaj) + strlen(sadrzaj) + 1;
        char* temp = new char[vel];
        strncpy_s(temp, vel, _sadrzaj, lokacija);  //strncpy_s - kopiraj n znakova, odnosno n clanova odredjenog niza
        strcat_s(temp, vel, sadrzaj);
        strcat_s(temp, vel, _sadrzaj + lokacija); //gore u prvom dijelu smo kopirali npr 5 karaktera, 
        //a sada idemo od nulte lokacije + 5 sto znaci da cemo krenuti od te lokacije i kopirati ostatak
        delete[] _sadrzaj;
        _sadrzaj = temp;
        return *this;
    }
       
    FITString& operator +=(const FITString& obj) {
       return append(obj._sadrzaj); //vrati ono sto vraca append, append vraca *this odnosno onoga ko je pozvao metodu 
    }   
};


class Student {
    int _indeks;
    string _ime;
    string _prezime;
public:
    Student(int indeks, string ime, string prezime)
    {
        _indeks = indeks;
        _ime = ime;
        _prezime = prezime;
    }

    bool operator < (const Student& obj) {
        return _indeks < obj._indeks;
    }

    friend ostream& operator << (ostream & COUT, const Student & obj) {
        COUT << obj._indeks << " " << obj._ime << " " << obj._prezime;
        return COUT;
    }
};


void main() {
    string html = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>My First Heading</h1><p>My first paragraph.</p></body></html>";
    regex regObj;
    string praviloUnos;
      do{
        cout << "Pravilo -> ";
        getline(cin, praviloUnos);
        regObj = praviloUnos;
        cout << regex_replace(html, regObj, "") << crt;
    } while (1);  

    /* 
        //pravimo regex za lozinku 
    string minimalnoZnakova = "(?=.{8})",
        malaSlova = "(\?=.*[a-z])", //sa zvjezdicom ispred smo rekli da se ispred malog znaka moze nalaziti bilo koji znak, ali se ne mora nalaziti nijedan znak
        velikaSlova = "(\?=.*[A-Z])",
        brojevi = "(\?=.*\\d)",
        specijalniZnakovi = "(\?=.*[!$_])", //mora imati neki od specijalnih karaktera !, $ ili _
        pravilo = minimalnoZnakova + malaSlova + velikaSlova + brojevi + specijalniZnakovi;
                                            
    //. mijenja bilo koji znak 
    //nije nam bitno gdje se nalazi karakter pa koristimi ?= 
    //Ovdje provjeravamo da imamo minimalno 8 znakova 
 
    regex regObj(pravilo);
    string unos;
    do
    {
        cout << "Lozinka: ";
        getline(cin, unos);
        if (regex_search(unos, regObj))
            cout << "\tFormat ispravan" << endl;

    } while (1); */
 
    /* 
    //pravilo za broj telefona.
    //+387 36 111 222
    string pravilo = "(\\+)(\\d{3})\\s(\\d{2})\\s(\\d{3})([\\s-])(\\d{3})";
    //ako zelimo nesto da grupisemo, to stavljamo unutar ()
    //imamo po dva backslasha jer sa \\ backlasa zelimo da dobijemo \d
    regex regObj(pravilo);
    string unos;
    do
    {
        cout << "Telefon: ";
        getline(cin, unos); 
        if (regex_match(unos, regObj))
            cout << "\tFormat validan. " << endl;

    } while (1);   */

    /* 
    string pravilo = "\\w*\\.?\\w*@(edu.)?fit.ba";
    regex regObj(pravilo);
    string unos;
    do
    {
        cout << "Email: ";
        getline(cin, unos); 
        if (regex_match(unos, regObj))
            cout << "\tEmail validan. " << endl;

    } while (1);  */

    /* 
    list<Student>prvaGodina;
    for (int i = 0; i < 5; i++)
        prvaGodina.push_back(Student(200000+i, "Ime_" +to_string(i), "Prezime_"+to_string(i)));
      
   // for (int i = 0; i < prvaGodina.size(); i++)
   //      cout << prvaGodina[i] << endl;    //list nema preklopljen operator []
   // cout << endl;  

    //s obrizom na to da list nema preklopljen operator [], mozemo korisiti auto 
    for (auto cl : prvaGodina)
        cout << cl << endl;

   // sort(prvaGodina.begin(), prvaGodina.end());   //lista takodjer ne moze soritati na ovaj nacin ali ona ima svoju sort metodu
    prvaGodina.sort();
    cout << endl;
    list<Student>::iterator pok = prvaGodina.begin();
    for (pok; pok != prvaGodina.end(); pok++)
        cout << *pok << endl;
    cout << endl;

    ostream_iterator<Student> ostIter(cout, "\n");
    copy(prvaGodina.begin(), prvaGodina.end(), ostIter);
    */

    /* 
    vector<Student>prvaGodina;
    for (int i = 0; i < 5; i++)
        prvaGodina.push_back(Student(200000+i, "Ime_" +to_string(i), "Prezime_"+to_string(i)));

    for (int i = 0; i < prvaGodina.size(); i++)
        cout << prvaGodina[i] << endl;
    cout << endl;

    sort(prvaGodina.begin(), prvaGodina.end());    //kod sortiranja studenata,
    //posto on ne zna kako da sortira studente,jer to moze biti po imenu prezimenu, indeksu...
    //onda u Studentu moramo implemenirati opeator <

    vector<Student>::iterator pok = prvaGodina.begin();
    for (pok; pok != prvaGodina.end(); pok++)
        cout << *pok << endl;
    cout << endl;

    ostream_iterator<Student> ostIter(cout, "\n");
    copy(prvaGodina.begin(), prvaGodina.end(), ostIter);
    */

    /* 
    vector<int>brojevi; //vektor zahtjeva od nas podatak o tome sta on treba da cuva 
    for (int i = 0; i < 10; i++)
        brojevi.push_back(rand());
     */

    /* 
    vector<int>::iterator pok = brojevi.begin(); //pokazivac na prvi clan 
    cout << *pok << endl;
    pok++;
    cout << *pok << endl;
     */

    /* 
    for (int i = 0; i < brojevi.size(); i++)
        cout << brojevi[i] << ", ";
    cout << endl;
    
    sort(brojevi.begin(), brojevi.end());//ako hocemo da sortiramo od pocetka do kraja, a nemamo neki nas iterator, uglavnom cemo se koristiti metodama begin i end 
    vector<int>::iterator pok = brojevi.begin(); //pokazivac na prvi clan 
    
    for (pok; pok != brojevi.end(); pok++)
        cout << *pok<<", ";
    cout << endl;

    ostream_iterator<int>ostIter(cout, ", ");
    copy(brojevi.begin(), brojevi.end(), ostIter);


    cout << endl;
    */

    /* 
    //string web(3, 'w'); //bice ispisano www
    string tacanOdgovor = "Prof.Dr. Safet Krkic";
    string ponudjeniOdgovor = "Prof.Dr. _____ _____";
    string vratiKursorUnazad(11, '\b'); //pomocu \b cemo se vratiti na pocetak gore ispisanih crtica

    string unos;
    cout << "Unesite ime osnivaca i prvog dekana FIT-a... " << endl;
    cout << ponudjeniOdgovor << vratiKursorUnazad;
    //ovjde ne mozemo korisiti cin>>, u ovakvom slucaju bi cin uzeo vrijednosti do prvog zareza 
    getline(cin, unos); //na ovaj nacin cemo preuzeti sve sto je korisnik unio  
    int lokacija = ponudjeniOdgovor.find('_');
    ponudjeniOdgovor.replace(lokacija, unos.size(), unos);
    if (tacanOdgovor == ponudjeniOdgovor)
        cout << "Tacan odgovor! " << endl;
    else
        cout << "Netacan odgovor! " << endl;
     */

    /* 
    string fit = "Fakultet Informacijskih Tehnologija";
    cout << "Size -> "<<fit.size() << endl;    //vraca velicinu trenutnog niza
    cout << "Capacity -> " << fit.capacity() << endl;   //metoda koja vraca trenutno velicinu alocirane memorije za potrebe ovog objekta 
    cout << "Max size -> " << fit.max_size() << endl;   //koliko moze pohraniti znakova unutar ovog objekta 
     */

    /*
    FITString ime = "Sara";
    FITString prezime("Nur");
    ime[0] = 's';
    cout << ime << " " << prezime << endl;

    FITString imePrezime = ime + " " + prezime;
    cout << imePrezime << endl;
    
    if (imePrezime == "sara Nur")
        cout << "Ime i prezime validno! " << endl;

    imePrezime.insert(0, "uposelnik ");
    cout << imePrezime << endl;
     
    imePrezime += " @FIT";
    cout << imePrezime << endl;
     
     
    imePrezime.append(" UNMO Mostar"); 
    cout << imePrezime << endl;
     

    */

}