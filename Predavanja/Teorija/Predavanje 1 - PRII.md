### Klase

<hr>

**private:** //obicno dio gdje se navode atributi/obiljezja klase ali moze biti i mnostvo funkcija, vidjeljivo je samo unutar klae odnosno jedino vidimo iz funkcija koje su clanice klase, ovo je oblik neke zastite

**public:** //nalaze se oni dijelovi koje mogu pozivati svi objekti ove kalase

**protected pristup** - omogucava samo izvedenim klasama da ostvare interakciju sa odredjenim atributima u klasi 

**atribute** inicijalizujemo pocetnom donjom crticom tako da jasno napravimo distinkciju izmedju atributa i parametra. 

**this**//interni pokazivac, ukoliko zelimo da nam se parametar funkcije i atribut/obiljezje funkcije nazivaju isto mozemo korisititi ovaj interni pokazivac.

Kljucna rijec **this->** jasno naznacava da zelimo da referenciramo nekoga ko je clanica klase (atribut te klase), a ne nekoga ko se nalazi u listi parametara

**Klasa** - mehanizam objektno-orjentisanog programiranja koji nam omogucava da kreiramo vlastite entitete i da u okviru njih upakujemo sve ono sto im je potrebno i da sve te entitete iz realog okruzenja preslikamo u programski kod

Jedna od osobina objektno-orjentisanog programskog jezika upravo jeste enkapsulacija upravo zbog toga imamo neke segmente koji su privatni i segmente koji su javni 

Klasa bi trebala da se vodi samo **logikom**, a nacin ispisa i nacin preuzimanja odredjenih podataka koji nastaju u interakciji sa korisnikom bi treba biti prepusten tom nekom interface-u kakav god on bio. 



### Funkcija i metoda

<hr>

**Globalne funkcije**

Programski jezik C++ dozvoljava globalne funkcije, odnosno funkcije koje su vidjljive svima i kojima svako moze da pristupa. 

**Funkcije clanice**

Funkcije koje se nalaze unutar struktura i njima se jedino moze pristupiti preko objekata koji su tipa te strukture 

**Funkcije** - termin koji se obicno odnosi na nesto sto je globalno i svima dostupno, mada nemamo globalne funkcije u svim jezicima, ali se uglavnom koristi za nesto sto nije upakovano u jedno cjelinu

**Metoda** - termin koji je je obicno vezan za nesto sto pripada odredjenoj klasi, nesto sto je dostupno samo ogranicenom dijelu koda, dostupno je unutar klase i nekim nasljedjenim klasama i njihovim metodama.



### Objekti

<hr>

**Stanje objekta**- predstavljaju vrijednosti njihovih atributa 

**Ponasanje objekta** se odnosi na one metode koje su njemu dostupne odnosno koje se mogu izvrsiti nad odredjenim objektom. Dakle, sta sve odredjeni objekat u odredjenom momentu moze da realizuje, npr da li se tu moze promijeniti boja pozadine, da li se moze npr. taj dugmic sakriti ili rotirati, ili da li se moze pomjeriti na drugu lokaciju. 

**Identitet objekta** - uglavnom se misli na neku vrijednost koja jednoznacno odnosno jedinstveno identificira odredjeni objekat. Vrijednost koja pripada samo i jedno jednom odredjenom objektu, moze biti neki ID. 

Ako govorimo o pokazivacima, onda mozemo govoriti i odredjenoj memorijskoj lokaciji objekta. Dakle, jedan objekat bi trebao da se nalazi na jednoj memorijskoj adresi i ta memorijska adresa bi trebala biti jedinstvena.



### Tipovi operacija

<hr> 

**Konstruktor** - metoda koja ce se zasigurno pozvati, ne oslanjamo se na programera da pozove odredjene metode i ukoliko zaboravi da ih pozove, ozbirom da se kontruktori sigurno pozivaju, program ce se moci izvrsiti. 

**Konstruktori** ucestvuju u konstrukciji objekta, oni se ne moraju pozivati, to su metode koje se automatski pozivaju u momentu kada kreiramo odredjeni objekat. 

Da bi neka metoda bila oznacena kao **konstruktor** odnosno da bi bila konstuktorskog tipa, ona mora postovati **dva glavna pravila:** 

1. ***ta metoda se mora nazivati identicno kao klasa***
2. ***ne moze imati povratni tip, pa cak ni void***

snippet konstruktora - ctor

**Defaultni konstruktor** - onaj koji nema parametre, postavlja vrijednosti na neke defaultne. Automatski se poziva pri kreiranju objekta.  

**Destruktor** - metoda koja je suprotna konstruktorskim metodama. Destruktor se automatski poziva u momentu kada odredjeni objekat zavrsava svoj zivotni vijek/umire ili vise nije potreban. Destrukor vrsi dealokaciju ili oslobadnjanje onih dijelova u memoriji koji je taj objekat koristio.

**Destrukotri** se od konstrukora razlikuju po znaku tilda (~). 



### Const operacije

<hr>

Konstante metode se oznacavaju na nacin da se kljucna rijec **const** postavi nakon zagrada (izmjedju obicnih i viticastih zagrada), a const metode se obavezuju da unutar sebe nece modifikovati stanje objekta -> odnosno vrijednosti njegovih atributa.















