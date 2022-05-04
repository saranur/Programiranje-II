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



**Klasa Dictionary** - obično jedan od članova (pretežno prvi) je unikatan i predstavlja ključ.

**Pair** - par vrijednosti koji mogu biti razlicitog tipa
**Pair** je posebno koristan jer mozemo vratiti set podataka koji su razlicitog tipa

**Tie** nam omogućava da rastavimo vrijednosti koji se nalaze unutar para ili kompleksne strukture na pojedine varijable - na njegove sastavne dijelove. 
Za tie moramo ukljuciti:  #include <tuple>

Kada zelimo da pohranimo veci broj elemenata razlicitog tipa, onda nam par nije opcija jer on cuva samo dva clana. U takvim slucajevima, na raspolaganju nam je **tuple**. Tuple ne ogranicava broj clanova koje mozemo pohraniti.

<hr>

**Lambda funkcije (bezimene funkcije)** 

<hr>

Lambda funkcija se obično sastoji iz tri dijela:

- Prva komponenta nam omogućava da u našu lambda funkciju uvezemo odnosno učinimo dostupnim neke od varijabli /objekata koji se nalaze u okruženju naše lambda funkcije. 
  **Capture list** - lista vrijednosti koje želimo da uvezemo 

  ```c++
  []() {
  	cout << "Pozdrav..." << endl; //ovdje smo je kreirali ali je moramo i pozvati kao i obicnu funkciju 
  } (); // za poziv funckije smo samo dodali () nakon  }
  ```

  

  ```c++
  int broj = 10;
  //ako zelimo da preuzmemo vrijednosti
  [broj]() {
  	cout << broj << endl;
  } ();
  ```

```c++
[](int b) {
	cout << "Pozdrav..." << b << endl;
}(55); //ovo 55 ce biti iskoristeno za inicijalizaciju varijable b
```

<hr>

### **Pokazivaci na funkcije**

<hr>

Pokazivac na funkciju se sastoji iz tri dijela: 

1. Naziv pokazivaca 
2. Da nije obicni pokazivac naznacujemo zagradama (*pok) ->pokazivac na funkciju
3. S lijeve strane stavljamo povratni tip, nakon toga navodimo listu paramtera 

```c++
int max = 5;
int niz[] = { 6,10,3,99,8 };
//Zahvaljujuci pokazivacu na funkciju mozemo vise puta pozvati ovu lambda funkciju 
int (*sumiraj) (int[],int) =  [](int niz[], int max) {
	int suma = 0;
	for (size_t i = 0; i < max; i++)
		suma += niz[i];
	return suma;
}; 
```

<hr>

### **auto - kljucna rijec**

<hr>

```c++
auto sumiraj = [broj](int niz[], int max) {
	int suma = 0;
	for (size_t i = 0; i < max; i++)
		suma += niz[i];
	return suma;
};
//auto sumiraj sada podrzava ulazne caputre list vrijednosti [broj] sto nije bilo moguce sa pokazivacem na funkciju 
```

<hr>

### **Function**

<hr>

**function** zahtjeva da unutar formalnog argumenta opisemo kakva je funkcija. Prvo se navodi povratni tip, zatim unutar zagrade lista parametara

```c++
function<int(int[], int)> sumiraj = [](int niz[], int max) { //moramo ukljuciti #include <functional>
	int suma = 0;
	for (size_t i = 0; i < max; i++)
		suma += niz[i];
	return suma;
};

/* kada bi dodali: 
function<int(int[], int)> sumiraj = [&](int niz[], int max)
sada bi svi clanovi unutar lambda funkcije bili dostupni po referenci.
Takodjer, kada bi stavili znak jednakosti 
--Ukoliko zelimo da modifikujemo i mijenjamo vrijednosti unutar lambda onda je potrebno da posaljemo po referenci
--takodjer mozemo proslijediti specificnog clana [&max]

function<int(int[], int)> sumiraj = [=](int niz[], int max)
tada bi svi clanovi postali dostupni po vrijednosti 

*/
```

<hr>

**Lambda funckija rekurzivnog tipa**

<hr> 

static omogucava da rek uvijek bude dostupno 

```c++
//Lambda funckija rekurzivnog tipa
static int (*rek)(int) = [](int n) {
	if (n <= 0) return 0;
	return n + rek(n - 1);
};
```



