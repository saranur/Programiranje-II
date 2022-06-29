#include <iostream>
#include <vector>
#include <thread>
#include <regex>
#include <mutex>             
#include <string>

using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

bool ValidirajEmail(string email) {
    /*
     email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj.
    zadovoljavati sljedeća
    pravila:
     - poceti sa jednim brojem nakon cega slijedi donja crtica
     - u imenu posjedovati najmanje 3 karaktera
     - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od
    navedenog
     - u prezimenu posjedovati najmanje 3 karaktera
     - znak @
     - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su
    oznake .com i .org.
     za provjeru validnosti email adrese koristiti globalnu funkciju
    ValidirajEmail, a unutar nje regex
    metode.
     validacija email adrese ce se vrsiti unutar konstruktora klase
    KaratePolaznik, a u slucaju da nije validna
     postaviti je na defaultnu adresu: notSet@edu.karate.ba */
    return regex_match(email, regex("\\d{1}_{1}[a-z]{3,}(.|_)?[a-z]{3,}\\@(edu.)?(karate)(.org|.ba|.com)"));
      
}

template<class T1, class T2, int max = 15>

class Kolekcija {
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    Kolekcija(const Kolekcija& obj)
    {
        _trenutno = new int(*obj._trenutno);
        for (int i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }  
        _dupliranje = obj._dupliranje;
    }
    Kolekcija& operator =(const Kolekcija& obj)
    {
        if (this == &obj)
            return *this;
        if (_trenutno == nullptr)
            _trenutno = new int();
        *_trenutno = *obj._trenutno;
        for (int i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
        _dupliranje = obj._dupliranje;
        return *this;
    }

    Kolekcija<T1, T2>operator ()(int from, int to) {
        if (*_trenutno <= to)
            throw exception("Imamo 10 elemenata");
        if (from < 0)
            throw exception("Lokacija -1 ne postoji! ");

        Kolekcija<T1, T2> temp;
        for (int i = from; i < to; i++)
        {
            temp.AddElement(_elementi1[i], _elementi2[i]);
        }
        return temp;
    }

   
    void AddElement(T1 el1, T2 el2) {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
        if (*_trenutno >= max)
            throw exception("Prekoracen opseg niza! ");
        if (_dupliranje == BEZ_DUPLIKATA) {
            for (int i = 0; i < *_trenutno; i++)
            {
                if (_elementi1[i] == el1 && _elementi2[i] == el2)
                    throw exception("Dupliranje elemenata nije dozvoljeno! ");
            }
        }
        _elementi1[*_trenutno] = el1;
        _elementi2[*_trenutno] = el2;
        *_trenutno += 1;
    }

    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};


class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum& operator =(const Datum& obj)
    {
        if (this == &obj)
            return *this;
        if (_dan == nullptr)
            _dan = new int();

        _dan = new int(*obj._dan);
        if (_mjesec == nullptr)
            _mjesec = new int();
        _mjesec = new int(*obj._mjesec);

        if (_godina == nullptr)
            _godina = new int();
        _godina = new int(*obj._godina);
        return *this;

    }
    int ToDays()const {
       return  *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    friend bool operator ==(const Datum d1, const Datum d2) {
        return d1.ToDays() == d2.ToDays();

    }
    friend bool operator !=(const Datum d1, const Datum d2) {
        return ! (d1 == d2);
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
};


class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
        Kolekcija<Datum, int>* _ocjene;
public:
   Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
       _naziv = GetNizKaraktera(naziv);
       _ocjene = new Kolekcija<Datum, int>();
       if (ocjena > 0)
           AddOcjena(&datum, ocjena);
   }
   Tehnika(const Tehnika& obj)
   {
       _naziv = GetNizKaraktera(obj._naziv);
       _ocjene= new Kolekcija<Datum, int>(*obj._ocjene);
       
   }
   Tehnika& operator =(const Tehnika& obj)
   {         
       if (_naziv != nullptr)
           delete[] _naziv;
       _naziv = GetNizKaraktera(obj._naziv);
       if (_ocjene != nullptr)
           delete _ocjene;
       *_ocjene = *obj._ocjene;
   }

   friend bool operator ==(const Tehnika& t1, const Tehnika& t2) {
       if (t1._naziv != t2._naziv)
           return false;
       if(t1._ocjene->getTrenutno()!= t2._ocjene->getTrenutno())
       for (int i = 0; i < t1._ocjene->getTrenutno(); i++)
       {
           if (t1._ocjene->getElement1(i) != t2._ocjene->getElement1(i) && t1._ocjene->getElement2(i) != t2._ocjene->getElement2(i))
               return false;
       }
       return true;
   }

   float ProsjekOcjena() const
   {
       float suma = 0.0f;
       for (size_t i = 0; i < _ocjene->getTrenutno(); i++)
       {
           suma += _ocjene->getElement2(i);
       }
       return suma / _ocjene->getTrenutno();
   }

   void AddOcjena(Datum *datum, int ocjena) {
       _ocjene->AddElement(*datum, ocjena);
   }  

   ~Tehnika() {
       delete[] _naziv; _naziv = nullptr;
       delete _ocjene; _ocjene = nullptr;
   }
   friend ostream& operator <<(ostream& COUT, const Tehnika& obj) {
       // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
       // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0 
       COUT << "Naziv: " << obj._naziv << endl;
       for (int i = 0; i < obj._ocjene->getTrenutno(); i++)
       {
           COUT << "Datum: " << obj._ocjene->getElement1(i) << " \tOcjena: " << obj._ocjene->getElement2(i) << endl;
       }
       COUT << "Prosjecna ocjena: " << obj.ProsjekOcjena();
       return COUT;
   }
   char* GetNaziv()const { return _naziv; }
   Kolekcija<Datum, int> GetOcjene() const { return *_ocjene; }
};


class Polaganje {
    Pojas _pojas;
    //string se odnosi na napomenu o polozenoj tehnici
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Polaganje(const Polaganje& obj)
    {
        _pojas = obj._pojas;
        for (int i = 0; i < obj._polozeneTehnike.getTrenutno(); i++)
        {
            _polozeneTehnike.AddElement(new Tehnika(*obj._polozeneTehnike.getElement1(i)), obj._polozeneTehnike.getElement2(i));
        }
    }
    Polaganje& operator =(const Polaganje& obj)
    {
        if(this == &obj)
            return *this;
        _pojas = obj._pojas;
        _polozeneTehnike = obj._polozeneTehnike;
        return *this;
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << obj._pojas << " " << obj._polozeneTehnike << endl;
        return COUT;
    }
};


mutex mtx;

class KaratePolaznik {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Polaganje> _polozeniPojasevi;
    void SaljiMail(Pojas pojas, const Tehnika& tehnika, float prosjekOcjena, float ukupniProsjek) {
        /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
       FROM:info@karate.ba
       TO: emailKorisnika
       Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
       na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
       Pozdrav.
       KARATE Team.
       ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
       slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
       */
        mtx.lock();
        cout << "FROM:info@karate.ba" << endl;
        cout << "TO: emailKorisnika" << endl;
        cout << "Postovani " << _imePrezime << "evidentirana vam je thenika " << tehnika << " za " << pojas << " pojas. ";
        cout << "Dosadasnji uspjeh (prosjek ocjena) na pojasu " << pojas << " iznosi " << prosjekOcjena << " a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi " << ukupniProsjek << endl;
        cout << "Pozdrav. \nKARATE Team" << endl;
        mtx.unlock();

    }
    void SaljiSMS(Pojas pojas, float prosjekOcjena) {
        cout << " Svaka cast za uspjeh " << prosjekOcjena << " na " << pojas << " pojasu" << endl;
    }
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string
        brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = ValidirajEmail(emailAdresa)?_emailAdresa: "notSet@edu.karate.ba";
        _brojTelefona = brojTelefona;
    }
    KaratePolaznik(const KaratePolaznik& obj)
    {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _polozeniPojasevi = obj._polozeniPojasevi;
    }
    KaratePolaznik& operator =(const KaratePolaznik& obj)
    {
        if (this == &obj)
            return *this;
        if (_imePrezime != nullptr)
            delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(obj._imePrezime);

        _emailAdresa = obj._emailAdresa; 
        _brojTelefona = obj._brojTelefona;
        _polozeniPojasevi = obj._polozeniPojasevi;
        return *this;
    }


    bool AddTehniku(Pojas noviPojas, const Tehnika& novaTehnika, string napomena) {
        /* svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju
        tehnike)
         uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
         tom prilikom onemoguciti:
         - dodavanje istih (moraju biti identicne vrijednosti svih atributa)
        tehnika na nivou jednog pojasa,
         - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna
        tehnika za nizi pojas (ne mozemo
        dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI
        pojas)
         - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
         funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja */

        if (novaTehnika.ProsjekOcjena() < 3.5)
            return false;

        auto prethodniPojas = static_cast<Pojas>(noviPojas - 1);
        for (int i = 0; i < _polozeniPojasevi.size(); i++)      //prolazimo kroz vector _polozeniPojasevi 
        {
            if (noviPojas == _polozeniPojasevi.at(i).GetPojas()) {  //ispitujemo da li je nas noviPojas jednak pojasu na lokaciji i, ukoliko jeste proci cemo kroz Tehnike jos jednom for petljom
                for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++) //prolazimo kroz sve tehnike 
                {
                    if (novaTehnika == *_polozeniPojasevi.at(i).GetTehnike().getElement1(j))   //nije dozvoljeno dodavanje identicnih tehnika na nivou jednog pojasa
                        return false;                                                          //ovom for petljom i ifom smo ispitali da li je novaTehnika koju zelimo da dodamo jednaka tehnici koja vec postoji u pojasu, ukoliko jeste, vrati false jer dupliranje nije dozvoljeno 
                }   //Uzimamo getElement1 jer je <Tehnika*, string> tip za _polozeneTehnike (prvi tip je Tehnika*)

            }
            if (prethodniPojas == _polozeniPojasevi[i].GetPojas()) {
                if (_polozeniPojasevi.at(i).GetTehnike().getTrenutno()<1) //gledamo da li prethodni pojas ima ijednu tehniku, ukoliko nema, ne mozemo dodati novu Tehniku  
                    return false;
            }
            
        }

        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (noviPojas == _polozeniPojasevi.at(i).GetPojas()) {
                _polozeniPojasevi.at(i).GetTehnike().AddElement(new Tehnika(novaTehnika), napomena);
                thread worker(&KaratePolaznik::SaljiMail, this, _polozeniPojasevi[i].GetPojas(), _polozeniPojasevi[i].GetTehnike(), novaTehnika.ProsjekOcjena(), );
                    worker.join();
                return true;
             }
        }
        Polaganje prvaTehnika(noviPojas);
        prvaTehnika.GetTehnike().AddElement(new Tehnika(novaTehnika), napomena);
        _polozeniPojasevi.push_back(prvaTehnika);
        return true;

    }

    

    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " <<
            obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
};


const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Za sta se koriste modovi ios::ate i ios::trunc ?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasniti ulogu i način koristenja iteratora?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}


void main() {

//    cout << GetOdgovorNaPrvoPitanje() << endl;
//    cin.get();
//    cout << GetOdgovorNaDrugoPitanje() << endl;
//    cin.get();

    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
            //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
            //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu
   kolekcija1 nalaze na lokacijama
   1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa
   vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti  izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
   //svaka tehnika moze imati vise ocjena i polaze se u vise navrata (istog ili drugog dana)
   //parametri: nazivTehnike, prva ocjena, datum polaganja
   Tehnika choku_zuki("choku_zuki", datum19062021, 5),
       gyaku_zuki("gyaku_zuki", datum20062021, 5),
       kizami_zuki("kizami_zuki", datum30062021, 2),
       oi_zuki("oi_zuki", datum05072021, 5);

       choku_zuki.AddOcjena(&datum05072021, 3);
       choku_zuki.AddOcjena(&datum05072021, 5);

        // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
        // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
    cout << choku_zuki << endl;

    /*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj.
   zadovoljavati sljedeća
   pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od
   navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su
   oznake .com i .org.
    za provjeru validnosti email adrese koristiti globalnu funkciju
   ValidirajEmail, a unutar nje regex
   metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase
   KaratePolaznik, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.karate.ba
    */

   if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
       cout << "Email validan" << crt;
   if (ValidirajEmail("3_ime_prezime@karate.ba"))
       cout << "Email validan" << crt;
   if (ValidirajEmail("4_imeprezime@karate.com"))
       cout << "Email validan" << crt;
   if (ValidirajEmail("8_imeprezime@karate.org"))
       cout << "Email validan" << crt;
   if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
       cout << "Email NIJE validan" << crt;
   if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
       cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic",
        "1_jasmin.azemovic@karate.ba",
        "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic",
        "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime",
        "korisnik@karate.ru", "033 281 170");

    /*
    svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju
   tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa)
   tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna
   tehnika za nizi pojas (ne mozemo
   dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI
   pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ne treba dodati kizami_zuki jer ne postoji niti jedna tehnika za ZUTI pojas
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodan! 1" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodan! 2" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodan! 3" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodan! 4" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodan! 5" << crt;
    //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana! 6" << crt;

    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje
   email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas.
   Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima
   iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS
   sa porukom: "Svaka cast za
   uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << *jasmin << crt;

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu  u periodu izmedju
        // proslijedjenih datuma
        //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06,
        2021), Datum(21, 06, 2021));
    for (size_t i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " <<
        jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}