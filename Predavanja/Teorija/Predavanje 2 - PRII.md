
Broj konstruktora ovisi o tome na koliko načina želimo da programeru omogućimo kreiranje objekata. **Destruktor** može postojati samo jedan.

**tm struktura** - u sebi ima set obilježja koje čuvaju vrijednosti o datumu i vremenu

**time_t** - vrati trenutno vrijeme time(0), vraća vrijeme u sekundama koje su prošle od 00:00 u donosu na Jan 1, 1970 godine, (UTC).

**localtime_s() metoda** - možemo korisititi za konvertovanje sekundi koje dobijemo u time_t koje će nam reći trenutni datum.

**strcpy** - je nesigurna funkcija. Kada pokušate kopirati string koristeći strcpy () u bafer koji nije dovoljno velik da ga sadrži, to će uzrokovati prelijevanje bafera.

**strcpy_s** - je sigurnosna verzija strcpy(). Pomoću strcpy_s možete odrediti veličinu odredišnog bafera kako biste izbjegli prelijevanje međuspremnika tokom kopiranja.

**itoa_s** - Pretvara cjelobrojnu vrijednost u string sa nultom završetkom (sa null-terminirajućem znakom na kraju - on naznačava kraj stringa) koristeći navedenu bazu i pohranjuje rezultat u niz dat parametrom str. Ona zahtjeva value, zatim buffer i zatim bazu 

**itoa_s - Integer to aplhabet** - konvertuje broj u niz karaktera  

**strcat_s** funckija dodaje strSource strDestination i završava rezultujući string sa null-terminiraju'im karakterom. Početni znak strSource prepisuje završni null karakter strDestination. Ponašanje strcat_s je nedefinirano ako se izvorni i odredišni nizovi preklapaju.

**strcpy uvijek zanemaruje postojeći sadržaj niza i kreće od nule.**

**strcat zadržava postojeći sadržaj ali na taj sadržaj dodaje neke vrijednosti.** 

npr:

```
char* ToString() {
		int max = 20;
		char* temp = new char[max]; 
		char buffer[10];
		_itoa_s(_dan, buffer, 10); //da bi dobili broj kao niz karaktera koristimo metodu itoa_s(), pohraniće ga   buffer po bazi 10
		//ako je početna vrijednost bila 16 ako dodamo 2 dana, sada će taj buffer imati vrijednost 18
		radimo itoa_s kako bi ga mogli uklapati sa nekim znakovima, s ovom funkcijom ne možemo koristiti matematičke funkcije ali nam to ovdje nije ni potrebno.
		strcpy_s(temp, max, buffer); //16 //bez dodavanja dana
		strcat_s(temp, max, "."); //16.
		_itoa_s(_mjesec, buffer, 10);  //itoa-integer to alphabet 
		//strcpy_s prekopira niz karaktera koji se proslijedi u novi, strcpy uvijek ignorise postojeci sadrzaj
		//krece od lokacije nula i zanemaruje postojeci sadrzaj niza
		strcat_s(temp, max, buffer); //16.3
		strcat_s(temp, max, "."); 
		//strcat_s - zadrzava postojeci sadrzaj niza ali na njega dodaje tacku u ovom slucaju
		//strcat_s 
		_itoa_s(_godina, buffer, 10);
		strcat_s(temp, max, buffer); //13.3.2021
		return temp;
```

**Za pozivanje željenih konstrukora neke klase unutar neke druge klase, u zaglavlju te druge klase možemo napisati znak : i mo\emo naglasiti koji konstrukor želimo da pozovemo.** 

