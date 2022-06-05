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
    ~Osoba() {
        delete[] _ime;
        _ime = nullptr;
        delete[] _prezime;
        _prezime = nullptr;
    }

    friend ostream& operator<<(ostream& COUT, Osoba& obj) {
        COUT << "Ime i prezime: " << obj._ime << " " << obj._prezime;
        return COUT;
    }


};

class Student : protected Osoba
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
    }

    //dtor
    ~Student() {
    }


    friend ostream& operator<<(ostream& COUT, const Student &obj)
    {
        COUT <<"(" <<obj._indeks<<")"<< " " << (Osoba&)obj << " " << obj._semestar;
        return COUT;
    }

        void PredstaviSe() {
        cout << "(" << _indeks << ")" << " " << (Osoba&)*this << _semestar;
    }
};
int Student::_indeksBrojac = 200000;

class DLStudent  : public Student
{
    char* _lokacijaPolaganjaIspita;

public:
    DLStudent(const char* ime, const char* prezime, const char* lokacijaPolaganjaIspita, int semestar = 1)
        :  Student(ime, prezime, semestar) //ovjde pozivamo konstruktor bazne klase koji nam treba 
        //uvijek se prvo izvrsavaju konstrukcije baznih klasa pa tek onda izvedenih
    {
        _lokacijaPolaganjaIspita = AlocirajIKopiraj(lokacijaPolaganjaIspita);
    }
    //Kod destrukcije, uvijek ce se prvo izvrsiti destrukcije izvedenih klasa pa tek onda baznih.
   
    ~DLStudent() {
        delete[] _lokacijaPolaganjaIspita;
        _lokacijaPolaganjaIspita = nullptr;
    }
    friend ostream& operator<<(ostream& COUT, DLStudent& obj)
    {
        COUT << (Student&)obj; //ne zelim da ispisem obj vec zelim da ispisem samo dio koji pripada Studentu unutar obj
        //ako bismo stavili Student, onda bismo napravili kopiju, ako bismo stavili Student& onda ne bi imali bespotrebnu kopiju i imati cemo interakciju sa originalom
        COUT << " i ispit polaze u: " << obj._lokacijaPolaganjaIspita << endl;
            return COUT;
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

};

void Info(Student& obj) {
    obj.PredstaviSe();
}

class Baza {};

template<class T, class Pk>    //bilo koji tip moze da koristi ovaj Repozitorij 
class Repozitory {
    Baza _db;
public:
    void Save(T& obj) {

    }
    T* GetById(Pk id) { return nullptr; }

};

class StudentRepozitory : public Repozitory<Student, int> {

};
class AsistentRepozitory : public Repozitory<Asistent, int > {
public:
    Asistent* GetByPredmet(const char* nazivPredmeta) { return nullptr; }
};

void main() {
    AsistentRepozitory asistentDB;
    StudentRepozitory studentDB;

    Student jasmin("Jasmin", "Jasminovi");
    studentDB.Save(jasmin);
    studentDB.GetById(3);

    Asistent kemal("Kemal", "Maric", "mr");
    asistentDB.Save(kemal);
    asistentDB.GetByPredmet("PRII"); //sada mozemo pristupiti i metodama u Repozitory i kod asistenta mozemo pristupiti metodama koje se nalaze unutar AsistentRepozitory

    /* 
    DLStudent sara("Sara", "Nur", "Mostar");
    Info(sara);
    Osoba* fit[10]; //kreiramo niz od 10 osoba
    fit[0] = new Student("Sara", "Nur"); //klasa Student je u direktnoj vezi sa klasom Osoba
    fit[1] = new DLStudent("Sara", "Nur", "Sarajevo");  //klasa DLStudent je u indirektnoj vezi sa klasom Osoba jer je s njom u vezi preko klase Student
    fit[2] = new Asistent("Sara", "Nur", "dr");  //klasa Asistent je u direktnoj vezi sa klasom Osoba
    */
}