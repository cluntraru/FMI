## Tema 3

#### i) Nicovala
Resurse: https://www.youtube.com/playlist?list=PLjEaoINr3zgHJVJF3T3CFUAZ6z11jKg6a

1. Am pornit de la un plan
2. Am extrudat planul vertical in sus pt a obtine baza nicovalei
3. Am extrudat iarasi fata de sus a formei obtinute pentru a obtine "gatul"
4. Am adaugat taieturi pe noul paralelipiped pentru a il putea scala convenabil
5. Am scalat vertecsii unei sectiuni ale paralelipipedului cu proportional editing mode pentru a obtine curbatura
6. Am extrudat iarasi pentru a crea un paralelipiped din care se vor extinde cele 2 "ramuri"
7. Am extrudat pentru a obtine ramurile
8. Am selectat partea de jos a ramurii lungi si am ascuns (hide) restul meshului pentru a putea curba doar partea de jos a ramurii cu proportional editing cu optiunea "sphere"
9. Am taiat nicovala in 2 si am sters jumatate
10. Am adaugat un cilindru in scena care se suprapune cu nicovala unde urmeaza sa fie decalajul din baza
11. Am adaugat pe nicovala un modifier de tip boolean pentru a "scadea" din ea forma cilindrului
12. Am adaugat pe nicovala un modifier "mirror" pentru a oglindi jumatatea ramasa de nicovala (astfel evitam probleme de asimetrie si duplicare a muncii)
13. Am aplicat modifierul boolean (altfel nu se generau vertecsii noi)
14. Am sters cilindrul din moment ce deja a fost aplicat modifierul
15. Am folosit knife tool, apoi edge sliding si merge vertices - by distance pentru a reconstrui fetele determinate de cate 4 vertecsi - modifierul boolean a "stricat" aceasta proprietate care poate cauza probleme
16. In mijlocul zonei decupate, a ramas o muchie verticala "dezlegata" de mesh, deci am folosit din nou loop cut pentru a taia meshul in 2 pe verticala
17. Am mutat muchia verticala pusa prost astfel incat vertexul sau de sus sa fie peste acela nou creat de taietura
18. Am unit cele 2 varfuri suprapuse
19. Partea de jos a nicovalei nu avea fete deci am folosit extrude pe vertecsi si create face pentru a completa modelul
20. Am extrudat in directia "tepei" de la nicovala
21. Am modificat "merge limit" in modifierul de mirror pentru a nu se face 2 bucati separate
22. Am folosit inset apoi extrude din nou pentru a crea teapa efectiva
23. Proportional editing cu partea de sus a tepei ascunsa si sharp mode pentru a finaliza teapa
24. Ascutit "colturi" dupa aplicarea modifierului de subsarface division cu ajutorul unor loop cut
25. Sters bucata de loop cut de pe teapa pentru a pastra forma veche, convenabila
26. Adaugat mai multe loop cut in zona cilindrica de la baza
27. Doua loop cut verticale din care pastram doar partea din jurul taieturii cilindrive
38. Inca un loop cut pentru partea de pe podea a nicovalei

#### ii) Formate
Blender suporta aproape orice format popular, ca de exemplu arhicunoscutul .obj. Am folosit functionalitatea export din blender pentru a crea un fisier obj cu nicovala de la i).

#### iii) 
