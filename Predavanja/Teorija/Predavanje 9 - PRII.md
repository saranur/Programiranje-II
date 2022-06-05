### Nasljeđivanje klasa

<hr>

Da bi izbjegli dupliranje, koristimo nasljeđivanje klasa. Ukoliko imamo klasu Student sa svojim obilježjima ime, prezime, broj indeks... i želimo da kreiramo klasu DLStudent sa svim obilježjima koje ima klasa Student, plus neka dodatna obilježja, klasa DLStudent će naslijediti obilježja bazne odnosno parent klase (u ovom slučaju je to Student). Sada DLStudent predstavlja izvedenu klasu, klase Student.

Prilikom nasljeđivanja, ukoliko u izvedenoj klasi želimo pristupiti nekom od članova parent klase (npr. u konstruktoru), to nećemo biti u stanju da uradimo iako su oni u nekoj korelaciji. 

Nije nam opcija da članove parent klase proglasimo public jer narušsavamo koncept enkapsulacije, pa je uveden novi nivo pristupa: **protected** - on nam omogućava da u izvedenoj klasi pristupimo članovima bazne klase.

- **Uvijek se prvo izvrsavaju konstrukcije baznih klasa pa tek onda izvedenih**
- **Kod destrukcije, uvijek ce se prvo izvrsiti destrukcije izvedenih klasa pa tek onda baznih.**

Svakoj klasi bi trebali prepustiti nadzor i upravljanje nad njenim atributima. 

<hr>

### Konstruktori i destruktori

<hr>

Bitno je napomenti da se konstruktori, destruktori i operatori dodjele **NE NASLJEĐUJU**. Od bazne klase cemo naslijediti atribute i njene metode ali necemo naslijediti konstruktore i destruktore i operator dodjele. 

<hr>

### Tipovi nasljeđivanja

<hr>

- **protected nasljeđivanje** : ako imamo javnu metodu i protected nasljeđivanje, ta javna metoda unutar protected nasljeđivanja isto postaje protected. To znaci da ako postoji neka metoda npr 
  void JavnaMetoda(); 
  unutar klase Osoba, a onda Student naslijedi klasu Osoba na nacin da je protected, objekti tipa Student **nece moci pristupiti metodi JavnaMetoda()**
- **public nasljeđivanje** ostaju dostupni public clanovi 
- **private nasljeđivanje **: Kod privatnog nasljedjivanja, privatni clanovi nisu nikad dostupni u izvedenoj klasi 

**PRAVO PRISTUPA UNUTAR KLASE: **

|               | public    | protected | private |
| ------------- | --------- | --------- | ------- |
| **public**    | public    | protected | private |
| **protected** | protected | protected | private |
| **private**   | X         | X         | X       |

