#include <iostream>

using namespace std;

char* AlocirajIKopiraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, sadrzaj);
    return novi;
}

class Uredjaj {
    char* _proizvodjac;
    char* _model;
    int _godinaGarancije;
    void Dealociraj(){
        delete[] _proizvodjac;
        _proizvodjac = nullptr;
        delete[] _model;
        _model = nullptr;
    }
public: 
    //user-def ctor
    Uredjaj(const char* proizvodjac, const char* model, int godinaGarancije)    {
        _proizvodjac = AlocirajIKopiraj(proizvodjac);
        _model = AlocirajIKopiraj(model);
        _godinaGarancije = godinaGarancije;
    }
    //copy ctor
    Uredjaj(const Uredjaj& obj)
    {
        _proizvodjac = AlocirajIKopiraj(obj._proizvodjac);
        _model = AlocirajIKopiraj(obj._model);
        _godinaGarancije = obj._godinaGarancije;
    }
    //operator dodjele 
    Uredjaj& operator=(const Uredjaj& obj) {
        if (this == &obj)
            return *this;
        Dealociraj();
        _proizvodjac = AlocirajIKopiraj(obj._proizvodjac); 
        _model = AlocirajIKopiraj(obj._model);
        _godinaGarancije = obj._godinaGarancije;
        return *this;
    }
    //COUT
    friend ostream& operator <<(ostream& COUT, const Uredjaj& obj) {
        COUT << "Proizvodjac: " << obj._proizvodjac << "\nModel:" << obj._model << "\nGodina garancije: " << obj._godinaGarancije;
        return COUT;
    }
    //Destruktor
    ~Uredjaj()
    {
        Dealociraj();
    }
};

class Dokument {
    char* _sadrzaj;
public:
    //user-def ctor
    Dokument(const char* sadrzaj)
    {
        _sadrzaj = AlocirajIKopiraj(sadrzaj);
    }
    //Copy ctor
    Dokument(const Dokument& obj)
    {
        _sadrzaj = AlocirajIKopiraj(obj._sadrzaj);
    }
    //Operator dodjele
    Dokument& operator =(const Dokument& obj) {
        if (this == &obj)
            return *this;
        delete[] _sadrzaj;
        _sadrzaj = obj._sadrzaj;
    }
    //Destruktor
    ~Dokument()
    {
        delete[] _sadrzaj;
        _sadrzaj = nullptr;
    }
    //operator <<
    friend ostream& operator <<(ostream &COUT, const Dokument& obj) {
        COUT <<obj._sadrzaj;
        return COUT;
    }

};

class Printer : virtual public Uredjaj {
    bool _laserski;
public:
    //user-def ctor
    Printer(const char* proizvodjac, const char* model, int godinaGarancije, bool laserski)
        : Uredjaj(proizvodjac, model, godinaGarancije){
        _laserski = laserski;
    }
    //metoda Printaj
    void Printaj(Dokument obj) {
        cout << "Printam .... " << obj;
    }
    //operator <<
    friend ostream& operator<<(ostream& COUT, const Printer& obj) {
        COUT <<(Uredjaj&)obj<< "\nLaserski: " << boolalpha << obj._laserski;
        return COUT;
    }
};

class Skener : virtual public Uredjaj{
    int _dpi;
public:
    //user-def ctor
    Skener(const char* proizvodjac, const char* model, int godinaGarancije, int dpi)
        :Uredjaj(proizvodjac, model, godinaGarancije){
        _dpi = dpi;
    }
    //Metoda Skeniraj
    Dokument Skeniraj(Dokument obj){
        cout << "Skeniram.... " << obj;
        return Dokument("Rezultat skeniranja....");
    }
    //operator <<
    friend ostream& operator<<(ostream& COUT,const Skener& obj) {
        COUT <<(Uredjaj&)obj<< "\nDPI: " << obj._dpi;
        return COUT;
    }
};

class Fax : virtual public Uredjaj{
    int _brojStranicaUMinuti;
public:
    //user-def ctor
    Fax(const char* proizvodjac, const char* model, int godinaGarancije, int brojStranicaUMinuti)
        :Uredjaj(proizvodjac, model, godinaGarancije)
    {
        _brojStranicaUMinuti = brojStranicaUMinuti;
    }
    void PosaljiFax() {
        cout << "Saljem Fax.. ";
    }
    //operator <<
    friend ostream& operator <<(ostream& COUT, const Fax& obj) {
        cout << (Uredjaj&)obj << "\nBroj stranica u minuti: " << obj._brojStranicaUMinuti << endl;
        return COUT;
    }
};

const char* crt = "\n-------------------------------\n";

/*Pravilo: Najizvedenija klasa bude zaduzena za kreiranje baznog podobjekta, 
u nasem slucaju najizvedenija klasa je klasa AllInOne i ona ce imati obavezu da kreira podobjekat tipa uredjaj.
Time se eliminisala obaveza i potreba da bilo koji od ovih podobjekata obavlja interackciju odnosno kreira nas Uredjaj. 
*/
class AllInOne : public Printer, public Skener, public Fax{
public:
    AllInOne(const char* proizvodjac, const char* model, int godinaGarancije, bool laserski, int dpi, int brojStranicaUMiuti)
        : Uredjaj(proizvodjac, model, godinaGarancije),
          Printer(proizvodjac, "PRINTER", godinaGarancije, laserski),
          Skener(proizvodjac, "SKENER", godinaGarancije, dpi),
          Fax(proizvodjac, "FAX", godinaGarancije, brojStranicaUMiuti)
    {
    
    }
    friend ostream& operator <<(ostream& COUT, const AllInOne obj) {
        COUT << (Printer&)obj << crt;
        COUT << (Skener&)obj << crt;
        COUT << (Fax&)obj << crt;
        return COUT;
    }


};


void main() {
    AllInOne hpStudentska("HP", "LaserJet H985sq", 3, true, 500, 5);
    cout << hpStudentska;

  //  Dokument potvrda("Kojom se potvrdjuje da potvrda...");
  //  hpStudentska.Printaj(potvrda);
  //  hpStudentska.PosaljiFax();
  //  cout << hpStudentska.Skeniraj(potvrda) << endl;

}                                                 