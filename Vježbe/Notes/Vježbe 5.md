### Generičke klase 

<hr>

**Generička klasa** je klasa koja se generiše na osnovu tipa podatka. 
**Funckija** koja se naknadno generiše, odnosno ne postoji do momenta dok ne počne kompajliranje. 

**Shared pointeri** su instanca odnosno način na koji se generičke klase mogu koristiti.

Izgled generičke klase 
<u>npr.</u> Ako smo proslijedili tip T studenta, onda ce izgledati ovako:

**T** Max(**T** el1, **T** el2)  // ovo T ce biti zamijenjeno sa Student 
**Student** Max(**Student** el1, **Student** el2)  

U slučaju da je T pointer onda bi imali:
**Student*** Max(**Student*** el1, **Student*** el2)  

Da smo rekli da je T npr int onda bi imali 
**int** Max(**int** el1, **int** el2) 

Dakle T mijenja ono što mi specifiziramo. U princpu je logika ista. 

T Max(T el1, T el2) {
    return (el1 >= el2) ? el1 : el2;
}

T Min(T el1, T el2) {
        return (el1 <= el2) ? el1 : el2;
}

**Bitno je napomenuti da, da bi ove generiče funkcije mogle funkcionisati, moramo imati implementiran operator <= i >= ili bilo koji drugi operator koji koristi. npr. Int, float... imati vec preklopljene ove operatore, ali ukoliko koristimo korisniči definiran tip, moramo preklopiti ove operatore. **

**Shared pointer** je klasa (pretežno generička klasa) koji je tip **smart pointera**. 
Imamo tri tipa **smart pointera**:  

- **shared_ptr** - pointer koji može da dijeli vlasništvo sa drugim shared pointerima.
- **weak_ptr**
- **unique_ptr**

Za dinamiču alokaciju koristi se funkcija make_shared. To je generička klasa koja očekuje tip podatka. 

Prilikom debuggiranja, možemo pratiti tok u immediate window-u. npr. ako imamo
shared_ptr<int> novi;
novi=make_shared<int>()
*novi=34;

U immediate window mozemo reci novi.get(). Prva stvar koju možemo primjetiti kada tek pokrenemo program i kažemo novi.get() je da će biti nullptr (???) što znači da je nedefinirana vrijednost. Dakle, objekat 'novi' je objekat generičke klase shared_ptr koji smo generisali preko integera, on u sebi ima već ugrađeni pointer čija je vrijednost nulta vrijednost. 

shared_ptr<int> novi;
novi=make_shared<int>()
*novi=34;
shared_pt<int> novi2=novi; // oni sada dijele istu adresu, odnosno dijele vlasništvo nad tom varijablom. 

Svaki od ova dva ima u sebi ugrađen mehanizam prebrojavanja, tj. prikazuje koliko drugih pokazivča njih dijeli pristup. 







Ukoliko zelimo da vidimo koliko ima referenci koristimo :
**_dan.use_count();**

**Vektor** je kolekcija elemenata i ona se može proširivati, u tom slučaju se elementi dodaju na kraj. To su obično kolekcije podataka koji su istog tipa. 
**Vektori** su koristan koncept zbog mogućnosti paralenog izvršavanja. Vektori su osnova kompjuterske nauke 

Staticka kolekcija nema mogućnost proširivanja za raliku od dinamičke. Služi da istu stvar, specifizira se odredjeni tip podatka i onda elemente koji su tog tipa pohranjujemo u niz elemenata, s tim da je niz fiksne dužine. 
