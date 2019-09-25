# SD_tema3

README

PROBLEMA 1:
  In ceea ce priveste citirea, citesc pe rand actorii si asociez fiecarui nume
nou o cheie(actorul 1 are cheia 1, .., actorul n are cheia n). Vectorul de 
chei retine doar cheile actorilor din filmul curent. Retin numele actorilor 
intr-un vector de caractere pe care il definesc in structura grafului. Pentru 
fiecare actor citit, verific daca a mai jucat intr-un film. In caz afirmativ, 
initializez cheia cu cheia care i-a fost asociata (pozitia la care se afla 
numele in vectorul de nume reprezinta cheia asociata). Altfel, retin numele 
si ii atribui o noua cheie. Ulterior, fac legatura intre actorul al carui 
nume l-am citit si restul actorilor care joaca in filmul respectiv.
  Task1: Parcurg nodurile grafului si cand gasesc un nod nevizitat, fac dfs 
pornind din acel nod si marchez faptul ca am gasit o noua componenta conexa.
  Task2: Calculez distanta de la nodul sursa la nodul destinatie folosindu-ma 
de o coada in care introduc vecinii fiecarui nod prin care trec si retinand 
la fiecare pas care este parintele fiecarui nod pe care l-am vizitat. La 
final, reconstitui drumul mergand din parinte in parinte si incrementand
distanta parcursa. Gradul de inrudire e distanta de la nodul destinatie la 
nodul sursa.
  Task3: Functia dfsCV gaseste punctele de articulatie folosindu-se de o
parcurgere de tip dfs. Pentru fiecare nod u, parcurg vecinii acestuia.
Daca un vecin v e nevizitat, ii marchez nodul parinte ca fiind u si verific in
mod recursiv daca v e punct de articulatie. Verific daca subgraful cu radacina 
in u se leaga de unul dintre stramosii nodului u actualizand valoarea minima
(low[u]). Daca nodul v e vizitat, muchia v->u e muchie inapoi. Nodul u e punct
de articulatie daca e radacina si are cel putin doi copii sau daca nu e 
radacina si valoarea minima a unuia dintre copiii lui e mai mare decat timpul 
de descoperire al lui u. 

PROBLEMA 2:
  Singura observatie pe care o am de facut in cazul citirii este ca atunci 
cand citesc o latura care deja se gaseste in graf, compar costul laturii 
citite cu costul laturii din graf. Daca primul este mai mic, modific costul
laturii din graf. Fac acest lucru pentru ca imi doresc sa obtin distanta 
minima. Folosesc algoritmul lui Dijkstra pentru a calcula distantele minime 
de la camera din care pornesc la toate celelalte camere. Pentru fiecare camera
in care ma aflu, calculez intarzierea in felul urmator: verific daca in camera
X se afla un paznic la momentul de timp in care am ajuns acolo; in caz 
afirmativ, intarzierea reprezinta secventa maxima de intervale consecutive 
in care se gaseste un paznic in camera X. Ma folosesc de o coada in care 
introduc camerele nevizitate, pentru care timpul de evadare e mai mare decat
suma dintre timpul de evadare al parintelui, costul de la parinte pana la 
camera nevizitata si intarzierea. Dupa ce coada s-a golit, caut camera care 
are iesire si al carei timp de evadare este minim si reconstitui drumul de la
aceasta pana la camera din care am pornit.
