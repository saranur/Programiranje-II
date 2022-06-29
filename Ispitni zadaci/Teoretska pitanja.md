### Ispit 16.07.2021 G2

<hr>

1. **Pojasnite ulogu operatora const_cast?** Const cast operator se  koristi kada zelimo da  uklonimo const obiljezje sa nekog objekta, time pruzajuci  mogucnost izmjene vrijednosti tog objekta/primitivnog tipa.
2. **Ukratko opisite redoslijed kreiranja objekta bazne klase u slucaju visestrukog nasljedjivanja(prilikom instanciranja objekta najizvedenije klase), te koja su moguca rjesenja najznacajnijih problema u tom kontekstu ?**

<hr>

### Ispit 16.07.2021 G1

<hr>

1. **Pojasnite ulogu i nacin koristenja generickog tipa future<>?**
   `future<>` je objekt koji može dohvatiti vrijednost iz nekog objekta ili funkcije, pravilno sinkronizirajući taj pristup ako je u različitim nitima. Najčešće se koristi kada imamo kompleksne kalkulacije ili neku komunikaciju sa serverom koja će potrajati, a trebat će     nam za kasnije i da je ne bismo čekali pohraniti ćemo je u future objekat i na taj način uzeti rezultat tek kada nam zatreba, a nećmo glavni proces držati na čekanju
2. **Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja ?** 

<hr>

### Ispit 25.06.2021 G1

<hr>

1. **Pojasnite ulogu i nacin koristenja generickog tipa future<>?**

   Future je objekat koji moze vratit vrijednost od nekog provider objekta ili funkcije,pravilno sinhronizirajuci taj pristup ako je u razlicitim threadovima.Validni futuri su konstruisani pozivajuci npr.funkciju
   async. promise::get_future.

2. **Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja ?**

<hr>

### Ispit 25.06.2021 G2 

<hr>

1. **Za sta se koriste modovi ios::ate i ios::trunc ?**

   `ios::ate` postavlja indikator pozicije streama na kraj streama pri otvaranju    `ios::trunc` uklanja stari sadrzaj kada otvorimo novi fajl
2. **Pojasniti ulogu i način koristenja iteratora?**
    U C++ iteratori su objekti koji nam omogucavaju da prodjemo kroz elemente nekog niza ili kolekcije i da im preko njega pristupimo. Poznajemo `ostream` iterator preko kojeg mozemo ispisat neke podatke, `sregex` iterator preko kojeg mozemo prebrojat koliko  rijeci ima u nekom tekstu itd.

<hr>

### Ispit  31.08.2020

<hr>

1. **Pojasnite na koji nacin tip nasljedjivanja (javno, zasticeno, privatno) utjece na dostupnost atributa bazne klase unutar izvedene klase?**

    public i protected: atributi dostupni unutar izvedenih klasa - private: atributi nisu dostupni unutar izvedenih klasa

2. **Ukratko pojasnite primjenu funkcija seekg i tellg?**

   - tellg() predstavlja tekuću poziciju get stream pokazivača

   - seekg() služi za mijenjanje pozicije stream pokazivača get

<hr>

### Ispit 15.07.2020

<hr>

1. **Pojasnite ulogu operatora reinterpret_cast.**
   Konverziju pokazivača na objekte klasa koje nemaju nikakvih međusobnih relacija je moguće izvršiti korištenjem reinterpret_cast operatora
2. **Ukratko opisite znacaj i vrste pametnih pokazivaca.**
   korištenjem pametnih pokazivača, ne moramo ručno dealocirati zauzetu memoriju već se ona automatski briše nakon što više nije potrebna -unique_ptr shared_ptr weak_ptr

<hr>

### Ispit  24.06.2020

<hr>

1.  **Na sta se odnosi pojam reprezentacije tipa?**
    Prezentacija instanci nekog tipa je način internog pohranjivanja tih instanci  (najčešće u memoriji računara) izabran od dizajnera softvera.
2.  **Na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja**
    Virtualno nasljeđivanje omogućava da objekti najizvedenijih klasa posjeduju samo 1 podobjekat indirektnih baznih klasa

<hr>


1. **Šta znači ako u listi parametara iz opsega lambda funkcije piše [=, &var]?** - Sve varijable iz opsega će po vrijednosti biti dostupne unutar lambda funkcije, dok će varijabla var biti dostupna po referenci. 

2. **Koji su preduslovi za polimorfizam?** - Ako imamo izvedenu klasu, a želimo sa njenom funkcijom članicom postići različito ponašanje u odnosu na istu funkciju članicu u baznoj klasi, onda funkciju u baznoj klasi proglašavamo virtualnom. To postižemo tako što u deklaraciji funkcije članice osnovne klase pišemo ključnu riječ 'virtual'. Tako, pomoću dinamičkog vezivanja (Dynamic Binding), osiguravamo da se tokom izvršenja programa poziva funkcija izvedene klase, a ne bazne klase.

   

   <hr>
   DODATNA TEORIJA 

   <hr>

   ios::in otvara fajl za citanje
   ios::out otvara fajl za pisanje i brise zateceni sadrzaj
   ios::app Dodaje novi sadrzaj na kraj fajla
   ios::_Noncreate Zahtijevani fajl mora postojati(nece biti automatski kreiran)
   ios::binary Otvara fajl u binarnom modu(podaci se ne prevode)
   getline() funkcija iz fajla uzima prvi red teksta ili oznaceni broj karaktera i upisuje ih u niz koji je naveden kao prvi argument

   eof() koristimo u kombinaciji sa nekom od petlji koja treba da se izvrsava sve dok unutar fajla postoji odredjeni sadrzaj 

   seekp()za zadatu lokaciju pomjera pokazivac za upisivanje sadrzaja fajla, a koristi se sa ofstream objektom

   tellp() vraca poziciju pokazivaca za upisivanje 





