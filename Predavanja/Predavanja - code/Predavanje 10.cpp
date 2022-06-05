#include <iostream>
using namespace std;

char* AlocirajIKopiraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj)+1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, sadrzaj);
    return novi;
}

class Osoba
{
protected:
    char* _ime;
    char* _prezime;
public:
    Osoba(const char* ime, const char* prezime) {
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prezime);
    }
    Osoba(const Osoba& obj)
    {
        _ime = AlocirajIKopiraj(obj._ime);
        _prezime = AlocirajIKopiraj(obj._prezime);
    }
    virtual ~Osoba() {
        delete[] _ime;
        _ime = nullptr;
        delete[] _prezime;
        _prezime = nullptr;
    }

    friend ostream& operator<<(ostream& COUT, Osoba& obj) {
        COUT << "Ime i prezime: " << obj._ime << " " << obj._prezime;
        return COUT;
    }

    virtual void PredstaviSe()
    {
        cout << _ime << " " << _prezime;
    }  


};

class Student : public Osoba
{
    static int _indeksBrojac;
protected:
    int _indeks;
    int _semestar;
public:
    //user-def ctor
    Student(const char* ime, const char* prezime, int semestar = 1)
       : _indeks(_indeksBrojac++), Osoba(ime, prezime)
    {
        _semestar = semestar;
    }
    //copy ctor
        Student(const Student &obj)
       : _indeks(_indeksBrojac++), Osoba(obj) //bice pozvan konstrukor kopije klase obj
    {
        _semestar = obj._semestar;
        obj.Test1();
      
        Test2(const_cast<Student&>(obj));    //mozemo ukloniti konstantnost iz nekog parametra pomocu const_cast
            //castamo obj ovdje 
    }
    
    void Test2(Student & obj) {

    }

    void Test1() const {

    }
    ~Student() {
        
    }

    friend ostream& operator<<(ostream& COUT, const Student &obj)
    {
        COUT <<"(" <<obj._indeks<<")"<< " " << (Osoba&)obj << " " << obj._semestar;
        return COUT;
    }

    void PredstaviSe() {
    cout << "Student ";
    cout << "(" << _indeks << ")" << " " << (Osoba&)*this <<" Semestar: "<<_semestar;
    }
};
int Student::_indeksBrojac = 200000;

class DLStudent  : public Student
{
    char* _lokacijaPolaganjaIspita;
    void Dealociraj() {
        delete[] _lokacijaPolaganjaIspita;
        _lokacijaPolaganjaIspita = nullptr;
    }
public:
    DLStudent(const char* ime, const char* prezime, const char* lokacijaPolaganjaIspita, int semestar = 1)
        :  Student(ime, prezime, semestar) //ovjde pozivamo konstruktor bazne klase koji nam treba 
        //uvijek se prvo izvrsavaju konstrukcije baznih klasa pa tek onda izvedenih
    {
        _lokacijaPolaganjaIspita = AlocirajIKopiraj(lokacijaPolaganjaIspita);
    }
    //Kod destrukcije, uvijek ce se prvo izvrsiti destrukcije izvedenih klasa pa tek onda baznih.
   
    ~DLStudent() {
        Dealociraj();
    }
    friend ostream& operator<<(ostream& COUT, DLStudent& obj)
    {
        COUT << (Student&)obj; //ne zelim da ispisem obj vec zelim da ispisem samo dio koji pripada Studentu unutar obj
        //ako bismo stavili Student, onda bismo napravili kopiju, ako bismo stavili Student& onda ne bi imali bespotrebnu kopiju i imati cemo interakciju sa originalom
        COUT << " i ispit polaze u: " << obj._lokacijaPolaganjaIspita << endl;
            return COUT;
    }
    void PredstaviSe() {
        cout << "DL student ";
        cout << "(" << _indeks << ")" << " " << (Osoba&)*this << " Semestar: " << _semestar << " Lokacija: " << _lokacijaPolaganjaIspita;
    }
    void PromijeniLokacijuPolaganja(const char* novaLokacija) {
        Dealociraj();
        _lokacijaPolaganjaIspita = AlocirajIKopiraj(novaLokacija);
    }

};
     
class Asistent : public Osoba  
{
    char* _titula;
public:
    Asistent(const char* ime, const char* prezime, const char *titula) : Osoba(ime, prezime) {
        _titula = AlocirajIKopiraj(titula);
    }

    ~Asistent() {
        delete[] _titula;
        _titula = nullptr;
    }
    void PredstaviSe() {
        cout << "Asistent ";
        cout << (Osoba&)*this << " Titula: " << _titula;
    }

};
 /* 
void Info(Osoba& obj) {
    obj.PredstaviSe();
}
void Info(Osoba* obj) {
    obj->PredstaviSe();
}
*/
/*   ovo ne bi bilo moguce jer imamo cistu virtuelnu metodu u klasi Osoba
void Info(Osoba obj) {
    obj.PredstaviSe();
}   */

const char *crt= "\n---------------------------------------------\n";

void main() {
    const int max = 5;
    int izbor;
    Osoba* fit[max];

    for (size_t i = 0; i < max; i++)
    {
        cout << "1. Student; 2. DLStudent; 3. Asistent ->";
        cin >> izbor;
        if(izbor==1)
    fit[i] = new Student("Denis", "Music");
        else  if(izbor==2)
    fit[i] = new DLStudent("Amar", "Music", "Mostar");
        else 
    fit[i] = new Asistent("Ismir", "Azemovic", "mr");
    }
    DLStudent* dlStudent = nullptr;

    for (int i = 0; i < max; i++)
    {
       dlStudent= dynamic_cast<DLStudent*>(fit[i]);
       if (dlStudent != nullptr)
           dlStudent->PromijeniLokacijuPolaganja("Tuzla");
           //izdvojili smo jedan pokazivac jer je to tip koji trazimo, u ovim tipovima i pokusavamo sve ove pokazivace tumaciti kao DLStudenta 
           //za one za koje je moguce cemo dobiti adresu, a za one za koje to nije moguce cemo dobiti nullptr 
           //sada ce se za sve DL studente lokacija promijeniti iz Mostar u Tuzla 

    }

    for (int i = 0; i < max; i++)
    {
        cout << crt;
        fit[i]->PredstaviSe();
    }
    for (int i = 0; i < max; i++)
    {
        delete fit[i];
    }

        Osoba* sara = new Student("Sara", "Nur");
    sara->PredstaviSe();
}