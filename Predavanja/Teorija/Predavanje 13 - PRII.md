### string

<hr>

Tip string je tip koji nam olaksava upravljanje tekstualnim sadrzajem. Tip string nije primitivni tip kao npr int, bool i sl. 

Unutar klase string takodjer imamo i preklopljen operator []. Takodjer imamo mogucnost da mijenjamo pojedine vrijednosti unutar naseg stringa. 

**Metoda insert** nam omogucava da odredjeni sadrzaj dodamo pocevsi od zeljene lokacije.  

Klasa string takodjer ima preklopljen operator +=, postoji i **metoda append** koja radi identicno kao i nas opeartor +=.

**strncpy_s** - kopiraj n znakova, odnosno n clanova odredjenog niza

**iterator** - uglavnom je vezan za konkretan tip, iterator je pokazivac na odredjeni clan odredjene kolekcije/skladista.

**ostream iterator** - omogucava nam da definisemo s kojim skladistem zelimo da radimo, sta treba da se desi - odnosno ispise, i sta ce se desiti nakon ispisa svakog clana. 

<hr>

### Koristenje vektora i list

<hr>

Ono sto lista ima, a vektor nema je mehanizam efikasnijeg dodavanja i uklanjanja clanova s pocetka i kraja. 
Imamo metode npr: push_front i pop_front

 <hr>

### Regex

<hr>

Regular expression  - regex omogucava nam da napravimo kompleksnije upite nad nekim tekstualnim sadrzajem. 

[Regex tester](http://regexstorm.net/tester)

**[A-zZ0-9]{2,4}** bi prikazivao sve clanove, najmanje dva karakera, a najvise 4

**B[a-z]H** -> mora pocinjati s velikim B, zavrsavati s velikim H, a izmedju moze biti samo jedan znak od malih slova od a do z. 

**B[a-z]?H** - oznacava da se [a-z] moze pojaviti i ne mora, sto znaci da bi BH odgovaralo ovom upitu. 

**B[a-z]+H** - ovdje izmjedju moze biti jedan znak a moze biti i vise znakova izmedju B i H.

**B[a-z]*H** - ovim smo rekli da znak u sredini koji moze biti malo slovo [a-z], moze biti izostavljen, a moze i ponavljati puno puta. 

**B[a-zA-Z]*H** 

**\w** skracenica za mala i velika slova,brojeve, i donje crtice 

**B\w{1,3}H** - oznacava da se znakovi izmedju mora biti makar 1, a maksimalno 3 puta

npr. ukoliko bi zeljeli da napravimo upit za nesto tipa: sara.nuredinovski@edu.fit.ba

\w*\\ . ?\w *@(edu.)fit.ba -> ovdje smo naznacili da tacka ne mora biti izmedju imena i prezimena, takodjer smo naznacili da edu. ne mora postojati 

**.** zamjenjuje i ostale karaktere, ukoliko zelimo da referiramo samo tacku unutar regexa, onda stavljamo \.

**\d** - skracenica za brojeve (digit)

**\s** -skracenica za razmak 

**<!?/?\w*\s?\w*>** - ovo bi prepoznalo html tagove 

<hr>

### Regex metode 

<hr>

**Regex match** - omogucava nam da provjerimo eksplicitno odredjeni format sadrzaja. To nam je korisno kod email adresa, brojeva telefona i sl. odnosno tamo gdje znamo gdje nam se nesto nalazi na pocetku/kraju i slicno.

**Regex search** - gledamo da li su odredjena pravila implementirana u bilo kojem dijelu. Ovo je posebno korisno kod passworda, gdje zelimo da provjerimo ima li malo i veliko slovo, specijalni karakter, broj i slicno.







