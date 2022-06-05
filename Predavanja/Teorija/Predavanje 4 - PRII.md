### Konstante i reference

<hr>

Prilikom deklaracije varijable možemo, a i ne moramo dodijeli neku vrijednost, dok kod konstanti to nije slučaj. **Konstantama** se vrijednost mora dodijeliti neporedno prilikom inicijalizacije. 
**const int k=10;**

Referenca zahtjeva da joj se odmah dodjeli vrijednost, ali se vrijednost može naknadno mijenjati za razliku od kontsanti.

**int a=55;**
**int &ref=a;** // ovdje ce ref biti drugo ime za varijablu a, sve promjene na **ref** će se reflektovati na varijablu a. i sve promjene na **a** će se reflektovati na ref

**Referenca** je drugo ime za neku već postojeću memorijsku lokaciju. 

Drugi način inicijalizacije je:
**int a(10);**

Da reference ne bi usmjeravali na lokacije koje imaju kratak vijek trajanja, možemo našu referencu usmjeriti na globalnu varijablu.

<hr>

### Zaglavlje konstruktora 

<hr>

Najčešća tri momenta zbog kojih imamo potrebu da reagujemo u zaglavlju konstruktora su kada imamo: 

- Konstante
- Reference 
- Objekti drugih klasa

<hr>

### Konstruktor kopije

<hr>

Vlastiti **konstruktor kopije** imamo razloga implementirati kada imamo neke pokazivače u našoj klasi jer želimo da izbjegnemo kopiranje adresa pokazivača i time izbjegnemo padanje programa. 

Parametar u konstruktoru kopije **MORA BITI PO REFERENCI**. Kada bi konstruktor kopije primao vrijednosti po vrijednost, a ne po referenci, konstruktor kopije bi zahtjevao kopiju. Da ne bi imali beskonačnu petlju, u konstruktoru kopije parametar mora biti po referenci. 

<hr>

### Konstruktor move 

<hr>

On se od konstruktora kopije razlikuje po tome što kod svog parametra ima dva znaka ampersand (&&). U move konstruktoru, mi preuzimamo adresu i kažemo originalu da je zaboravi. 

<hr>

### Statički članovi

 <hr>





