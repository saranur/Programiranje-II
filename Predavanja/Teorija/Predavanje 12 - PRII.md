### Exceptions 

<hr>

Izuzetne situacije - **exception**.

**no reference exception** - izuzetak koji podrazumijeva koji podrazumijeva da smo pokusali da pristupimo necemu preko reference odnosno pokazivaca koji je null.

Za bacanje i hvatanje expectiona koristimo throw i try catch blok.
Try blok moze biti jedan, dok catch blokova moze biti vise. Kod catch bloka moramo voditi racuna da je istog tipa kao i throw. 

Da bismo izbjegli vodjenje racuna o razlicitim tipovima, koristimo klasu **exception**. Klasa exception nema metodu za ispis ali mozemo korisiti metodu what() koja vraca ono sto smo napisali u **throw exception(" prouka ")** dijelu. (U ovom slucaju bi vratio poruka).

Prvo se stavljaju catch blokovi naizvedenijih klasa - npr. ukoliko smo napravili svoju klasu Nedozvoljena operacija koja nasljedjuje klasu exception, i u catch bloku prvo pozvali exception klasu, izgubuli bi sve detalje koje smo dodali u nasu klasu Nedozvoljena operacija. 

Ukoliko trenutno nemamo catch blok za neki tip, postoji univerzalni catch blok koji mozemo korisiti za svaki tip.

```c++
catch (...) {

}
```