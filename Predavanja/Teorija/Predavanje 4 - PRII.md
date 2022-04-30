### Operatorske metode/funkcije

<hr>

**Operatore** preklapamo kako bi ih mogli koristiti kao i kako smo navikli sa ugrađenim tipovima
npr. Element b = a + 10;  //da nismo implementirali operator + ne bi mogli ovako sabirati 

Ime funkcije mora biti operator, zatim operacija (+, -, ...). Povratna vrijednost treba biti tipa klase (tipa Element operator...)

Za korisniči definirane tipove, moramo kreirati zasebne operatore. 

**Property** - nacin da u jednoj liniji koda kreiramo i atribut i njegovu getter i setter metodu. npr.
`class Student`
`{`

`public int Indeks {}`

`}`

Metode članice bi trebale biti sve one koje mijenjaju stanje objekta npr c+=20; za slucaj c+20, ovdje se pravi neka nova lokacija i dobija se nova vrijednost, tako da operator + mozemo implementirati kao globalnu funkciju 

Kada imamo pokazivač kao član klase, najbolji prijatelji su nam konstruktor kopije i operator dodjele. One vode računa da ne dođe do međuzavisnosti između objekata. Prilikom nastajanja nekog novog objekta, on dobija identične vrijednosti, ali kada govorimo o dinamičkim osobinama, on vodi računa da svako ima zasebni memorijski prostor, alokaciju... 

```c++
Element a = 10;
Element g = a; //U ovom momentu objekat se tek kreira tako da ce se pozvati konstruktor kopije 
a = g; //u ovom momentu se poziva operator dodjele jer nema konstrukcije novog objekta 

```

Kada govorimo o konstrukciji objekta uvijek je konstruktorska metoda!

**Konstruktorske metode** obično nemaju nekih dealokacija jer objekat tek nastaje.
S druge strane, **Operatorske metode** obično imaju potrebu da nešto prošire, smanje, modifikuju nešto s aspekta količine memorije neophodne za pohranu podataka i u takvim slučajevima one vrše i dealokaciju. 

<hr>

### Generičke klase

<hr>

**Template funkcija** je funkcija koja će se generisati za raličite tipove podataka. Ovo će nam pomoći da izbjegnemo ponavljanje koda. 

template<typename TipPodatka>
TipPodatka se najćešće naziva T
Umjesto typename se najčešće koristi class

<hr>

**Vektori (vector)**

<hr>

Vektori su primjeri generičke klase koja nam omogućava da čuvamo podatke razliočitog tipa. Da bi koristili vector moramo uključiti biblioteku 
`#include <vector>`

```c++
vector<int> prijave; //dobili smo mogucnost da cuvamo znacajan broj vrijednosti tipa integer
//bez da brinemo o alokaciji, dealokaciji...
//nas zanima kako da dodamo element u to skladište i kako da pristupimo tom elementu
	prijave.push_back(190091);
	prijave.push_back(190089);
	prijave.push_back(190052);
	for (size_t i = 0; i < prijave.size(); i++)
		cout << prijave[i] << ", ";
//size() ce pokazati broj elemenata 
```

Ili na drugi nacin dodavanja 

```c++
vector<int> prijave; 
for (size_t i = 0; i < 30; i++)
	prijave.push_back(200000 + i);
for (size_t i = 0; i < prijave.size(); i++)
	cout << prijave[i] << ", "; //operator[]
```