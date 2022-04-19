### Operatori 

<hr>

Postoje preklopivi i nepreklopivi operatori. Uglavnom ćemo se korisiti preklopivim operatorima 

**Overloading operators (C++ only)**

| +    | -    | *    |
| :--- | :--- | :--- |
| !    | =    | <    |
| ‸=   | &=   | \|=  |
| <=   | >=   | &&   |
| ( )  | [ ]  | new  |

Operatori su funkcije kao i svaka druga, jedina razlika u pisanju operatora i funkcije je u nazivu. 

Operatori = Operatorske funkcije 
npr. **Operator =** (operator dodjele) se smije pojaviti samo kao clanica funkcije, ne moze se pojaviti neovisno

**Cilj operatora dodjele** je da primi objekat koji je istog tipa, obavezno po referenci i koji je konstantan, te onda uradi kopiranje sadrzaja iz atributa ovog objekta u atribute objekta s kojim trenutno radimo. Slican je copy konstruktoru.