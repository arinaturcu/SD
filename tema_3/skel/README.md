===================================TEMA 3===================================
Turcu Arina-Emanuela 313CA & Isar Ioana-Teodora 313CA

	In functia add_paper() se adauga articolele si tot ce e necesar in toate
hashtable-urile create (ht, ht_cit, ht_venue, ht_influence, ht_field, ht_authors).
In ht s-au adaugat articolele primite dupa id-ul lor. Restul hashtable-urilor sunt
folosite pentru rezolvarea task-urilor asa cum e explicat mai jos.


                                   Task 1		
	S-a implementat un algoritm BFS pentru a vedea dependentele dintre articole.
Pentru reinitializarea variabilei visited a fiecarui articol, articolele vizitate au 
fost puse intr-o lista. Lista a fost parcursa la final reinitializand cu 0 variabila
visited. Pentru a afla numarul de citari ale fiecarui articol, s-a implementat un
hashtable ht_cit in care se adauga mereu in add_paper() astfel: cand se adauga un
articol se iau id-urile articolelor din referinte si se adauga un ht_cit cu numarul
de citari actualizat


                                   Task 2
	S-a implementat hashtable-ul ht_venue pentru eficienta in care fiecare intrare
are cheia formata din venue si ca value are o lista inlantuita de articole care au
fost publicate la acel venue. S-a luat din ht_venue lista ceruta si s-a facut media
aritmemtica a numarului de citari ale fiecarui articol (luat din ht_cit).


                                   Task 3
	S-a implementat un hashtable ht_influence in care intrarile au cheia formata
din id-ul articolului si value o lista inlantuita de articole pe care le-a influentat
cel cu id-ul din cheie. Pe acest hashtable s-a folosit un BFS in care se retin si
distantele dintre articole. Se numara articolele pana la distanta data ca parametru.


                                   Task 4
	S-a creat un hashtable pentru autori, ht_authors, in care intrarile au cheia
data de id-ul autorului si value este o lista de id-uri are tuturor autorilor cu care
cel cu id-ul dat de cheie a colaborat. S-a facut din nou un BFS pe acesti autori si
s-au aflat distantele dorite. 

                                   Task 6

    In add_paper a fost construit un hashtable avand cheia reprezentata de
campul id. Functia get_number_of_papers_between_dates va parcurge acest hashtable
si va numara fiecare articol al carui an de publicatie se afla in intervalul
dorit. Se va returna numarul cautat.


                                    Task 7

    In add_paper a fost construit un hashtable avand cheia formata prin concatenarea
campului field cu campul institution atribuit fiecarui autor. Functia
get_number_of_authors_with_field va realiza o cheie formata din numele institutiei
si domeniul dorit. Functia get din hashtable va returna lista articolelor cu 
aceasta cheie. Se parcurge aceasta si pentru fiecare articol se va verifica daca
este din domeniul dorit. Se vor parcurge autorii fiecarui articol si daca un autor este
din institutia cautata se va verifica daca acesta fusese deja numarat intr-un vector cu
autori. Daca nu a mai fost luat in considerare se va adauga in vectorul de autori si se
va creste numarul dorit.
Se va returna numarul de autori distincti care indeplinesc cerintele.

===================================================================================


