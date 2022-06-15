### Polimorfizam

<hr>

Sposobnost objekta odnosno pokazivaca da se u razlicitim slucajevima da se ponasaju razlicito.

<hr>

### Virtualne metode

<hr>

Virtualne metode nam omogućuju da pogledamo u objekte na koje pokazujemo, da vidimo da kojim slučajem metoda koju pozivamo nema implementirana i unutar te klase odnosno da je dostupna i tom objektu.

Ukoliko unuatar bazne klase imamo metodu 
void PredstaviSe(){}
a unutar izvedene klase Student takodjer imamo metodu istog imena, metoda unutar klase Student ce biti potpuno ignorisana pri ispisu 

Kod virutalnih metoda (sada govorimo za klase Osoba i Student), ako bi se preko pokazivača tipa Osoba pristupio metodi koji se naziva PredstaviSe(), a taj pokazivac pokazuje na objekat neke od izvedenih klasa, onda ce nam virtualni mehanizam omoguciti da provjerimo da li u toj izvedenoj klasi postoji istomeimena metoda, ako postoji, on ce pozvati tu metodu.

<hr>

### Apstraktne klase

<hr>

Mislimo na nesto sto znamo da postoji, ali nije nam bas dostupno. 

U programiranju, to mozemo predstaviti tako sto nesto zelimo kreirati, da imamo u nasem programu ali ne zelimo da imamo njihove konkretne primjerke (njihove objekte). To podrazumijeva mogucnost da odredjenoj klasi dodjelimo status apstraktne klase i taj status nece dozvoliti da kreiramo objekte te klase. 

Najbolji primjer zasto su nam potrebne apstraktne klase, je upravo klasa Osoba. Kada kazemo da je neko Osoba previse je genericki da bi shvatili kakve autorizacije imaju i ne bi mogli nista da zakljucimo na osnovu toga. 

Virtualne metode nam omogucavaju da klasu proglasimo apstraktnom. 
**Cista virtualna metoda** se dobija na nacin da metodu izjednacimo sa = 0, npr:

virtual void PredstaviSe() = 0;

Ciste virtualne metode nam omogucavaju jos jedan mehanizam koji nije jednostavno postici.. Taj mehanizam omogucava da odredjene klase ili barem narednu klasu koja nasljedjuje klasu Osoba, natjeramo da nesto implementira. Dakle, ako klasa koja je naslijedila klasu osoba ili bilo koju apstraktnu klasu ne implementira cistu virtualnu metodu i ta klasa postaje apstraktna.

Apstrakcija se proteze i na klase koje nasljedjuju tu klasu, odnosno na izvedene klase  ukoliko one ne implementiraju cistu virtualnu metodu.

Ako klasa student ne implementira klasu PredstaviSe, onda ce i ona postati apstraktna. 

#### Drugi nacin proglasenja klase apstraktnom

Ako zelimo da odredjenu klasu proglasimo apstraktnom, a pritome nemamo potrebu da izvedene klase obavezujemo nekim implementacijama, kao sto smo imali mogucnost da to uradimo sa cistom virtualnom metodom, na raspolaganju nam je kljucna rijec abstract koja se pise iza naziva klase.

#### Destrukcija objekata

Obzirom na to da se destrukcija prvo vrsi od najizvedenije klase do bazne, neko pravilo ukoliko imamo makar jednu virtualnu metodu u nasoj klasi, onda bi i nas destructor trebao biti virtuelan. 

#### Virtualni mehanizam

Virtualni mehanizam se aktivira podjednako i za pokazivace i za reference, s druge strane, virtualni mehanizam nece raditi s objektima i prosljedivanju po vrijednosti.

<hr>

### Cast operatori 

<hr>

Cast operatori nam omogucavaju da izvrsimo konverziju iz jednog tipa u drugi. Uglavnom cemo govoriti o castanju za reference i pokazivace. 

dynamic_cast<DLStudent*>(fit[i]);

//ako dynamic_cast ako ne pokazuje na objekat koji mi zahtjevamo, on ce nama vratiti NULL. dynamic_cast

static_cast – Koristi se za konverziju normalnog/običnog tipa. Ovo je također uloga odgovorna za implicitnu koerziju tipa i također se može eksplicitno pozvati. Trebali biste ga koristiti u slučajevima kao što je pretvaranje float u int, char u int, itd. dynamic_cast −Ovo prevođenje se koristi za rukovanje polimorfizmom. Za rad na dynamic_cast mora postojati jedna virtualna funkcija u osnovnoj klasi.

**static_cast** je logika odozgo prema dole, gdje npr mozemo castati iz Studenta u DL Studenta. 
**dynamic_cast** 
**const_cast** ukoliko imamo neki const parametar, kao sto znamo, konstantni objekti ne dozvoljavaju da ostvarimo interakciju s bilo kim.

- Konstantni objekti ostvaruju interkaciju samo sa konstantnim metodama.
- mozemo ukloniti konstantnost iz nekog parametra pomocu const_cast

<hr>

### Interface

<hr>

Mehanizam koji nama omogucava da za odredjenu klasu, natjeramo programera da nesto implementira. Ideja interface-a predstavlja ugovor koji odredjena klasa ispostovati na nacin da ce sve stavke koje su navedene u tom ugovoru morati postojati. 





















