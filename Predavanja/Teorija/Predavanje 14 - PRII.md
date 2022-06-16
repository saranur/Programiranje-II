### File-ovi

<hr>

**Tekstualni file-ovi** i **binarni file-ovi** koji predstavljaju neke podatke.

**<fstream>** // biblioteka koja je zaduzena za interakciju s filovima

ofstream //out to file stream, tip podatka koji ce nam omoguciti da ostavarimo interakciju s odredjenim file-om

ifstream //za citanje fajla koristimo ifstream (input from file stream)

Ukoliko zelimo da odjredjeni tekst ostane u fajlu nakon dodavanja, moramo korisiti modove. Modovi se navode unutar samog konstruktora ili unutar metode open(), a omogucavaju da definisemo kako ce se objekat ponasati u interakciji sa fajlom. 

mode **app()**- append, npr ios:: app();

**eof()** - end of file (ide sve dok ne dodje do kraja fajla)

seekg() - mozemo poslati broj za koji cemo pomjeriti nas pokazivac u odnosu na trenutnu poziciju. npr. ako kazemo seekg(0, ios::end) - pomjeri se nula mjesta u odnosu na kraj, odnosno sad ce nas pokazivac bit pomjeren na kraj fajla 

tellg() - koristi se ocitavanje lokacije. 
Dodatak g kod seek i tell predstavlja 'get'. 

tellp() - koristi se kod upisa, a p predstavlja 'put'

<hr>

#### Upravljanje binarnim i tekstualnim fajlovima 

<hr>

Upravljanje binarnim fajlovima se razlikuje od upravljanja tektualnog fajla.
Da bismo objektu rekli da ne radi sa teksutalnim vec sa binarnim fajlom potrebno je da kazemo da je to mode binary, npr ios:: binary
**write** i **read** pripadaju istream i ostream objektu

write 

read 

<hr>

### Multithreading 

<hr>

Ukljucujemo biblioteku <thread>
this_thread se odnosi na thread unutar kojeg se izvrsava odredjeni zadatak.
nit.join(); //da bi rekli compileru da ispise sve vezano za odredjenu nit i da bi izbjegli run time errore. 

Da bi se izbjegao problem dijeljena objekta, npr cout, postoji tip podatka koji se zove mutex.

Mutex ima metode lock i unlock

**lock()** prije korisitenja couta zelimo da zakljucamo objekat
**unlock()** kada smo zavrsili s koristenjem objekta, otkljucali smo drugima na koristenje 

Kod metoda clanica je potrebno dodati znak and &, npr
 thread slanjeEmail(&TelekomOperater::DodajObavijest, bhTelecom,
        "Danas su planirani kraci prekidi u radu kablovske televizije");

 this_thread::sleep_for(chrono::seconds(2)); //prilikom slanja svakog emaila uspavaj se na 2 sekunde 

#include <future> //daje obecanje da cemo nesto vratiti, odnosno da cemo kreatora odredjene niti notificirati o tome sta se desilo kao rezultat izvresenja te niti 



