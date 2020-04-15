### Leaning Tower of Pisa

In arhiva se gasesc toate imaginile pe care le-am folosit: pisa_no_filter.png este exercitiul 1 exportat la png, iar pisa-filtered.png este exercitiul 2.
plains.xcf este fisierul GIMP pentru exercitiul 1 si plains-filtered.xcf este cel pentru exercitiul 2.

## Pasi
- am gasit o poza cu o campie pe care am folosit-o ca fundal
- am cropat imaginea de turn cu scissors
- a mai fost nevoie sa sterg din colturile turnului unde a mai ramas din "cer" cu eraser
- am adaugat o poza cu catedrala din pisa
- am aplicat pe ea horizontal flip
- am folosit perspective tool pana cand a inceput sa arate cat de cat asemanator cu imaginea originala
- am mai folosit eraser tool pentru a sterge "cerul vechi" din catedrala
- am mutat in jos imaginea de fundal
- am creat un layer nou de culoarea cerului din fundal (poza cu campia)
- am folosit healing tool pentru a repara unde au fost "taiati" norii pentru a da un aspect mai natural
- am folosit healing tool pentru a crea un gradient in dreapta ecranului la tranzitia dintre cele doua imagini de cer
- am copiat cu fuzzy select un grup de nori pe care l-am asezat de mai multe (3 - 4) ori in cerul "secundar" pentru a crea un efect mai natural
- norii aratau identic, deci am folosit clone tool pentru a sterge din ei si a le modifica forma
- Am cropat o casuta din poza pe care incerc sa o replichez si am pus-o langa turn (unde este si in poza originala)
- Am duplicat layerul de mai multe ori
- Pentru stanga turnului am folosit perspective tool pe layerul duplicat si l-am duplicat mai departe
- Dupa ce am asezat taote casutele cu perspectiva, am mai folosit odata perspective tool pentru a finisa detalii

## Exercitiul 2
- Am aplicat filtrul de sharpen pe catedrala deoarece avea o rezolutie mai mica decat celelalte elemente. Cu filtrul sharpen, am putut reliefa contrastul de pe catedrala. Astfel, pare ca imaginea este mai detaliata si nu iese atat de tare in evidenta din cauza rezolutiei proaste. Acum catedrala chiar pare ca face parte din acelasi peisaj.
- Desi am modificat catedrala cu filtrul sharpen, inca se observa o distinctie intre ea si celelalte elemente. De asemenea, toate elementele sunt in mod vizibil "distincte". Filtrul gaussian blur cauzeaza o pierdere uniforma de detalii asupra intregii imagini astfel incat toate elementele sa aiba acelasi efect, ca si cum ar fi facut mereu parte din acelas ansamblu.
- Am creat un filtru cu matricea a11 = 3 si a33 = 1 (restul 0), cu normalise debifat. Astfel, s-a creat un efect prin care casutele par iluminate din stanga sus, directia soarelui din fundal. Am dezactivat alpha channel din matrice, caci se creau margini negre din cauza acestuia. Am adaugat aceste modificarid pentru a apropia nuanta casutelor de cele ale turnului si a catedralei, dand o imagine mai credibila.




