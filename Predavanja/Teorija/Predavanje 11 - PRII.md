### Višestruko nasljeđivanje 

<hr>

Mogućnost da jedna klasa naslijedi više klasa. 

Višestruko nasljeđivanje se realizuje na identičan način kao i jednostruko uz navođenje više baznih klasa odvojenih zarezima. 

`class Bazna1 {//...`}; 
`class Bazna2 { //... };`
`class Izvedena : public Bazna1, public Bazna2 { //... };`

Ako imamo vise klasa koje nasljedjuju jednu baznu klasu, da bi izbjegli konstantno kreiranje istog objekta, nasljedjivanje mozemo proglasiti virtualnim.

Pravilo: Najizvedenija klasa bude zaduzena za kreiranje baznog podobjekta, u nasem slucaju najizvedenija klasa je klasa AllInOne i ona ce imati obavezu da kreira podobjekat tipa uredjaj. Time se eliminisala obaveza i potreba da bilo koji od ovih podobjekata obavlja interackciju odnosno kreira nas Uredjaj. 

