============================== TEMA 2 ==============================

1. VECTOR DE FRECVENTA

    Se citesc de la stdin valori si se retine maximul dupa fiecare
citire in fuctie de care se realoca vectorul de frecventa. Daca
numarul citit a mai fost citit si mai devreme se actualizeaza pozitia
corespunzatoare (data de valoarea lui) din vectorul de frecventa.

2. HASTABLE CU OPEN ADDRESSING

    Fiecare sir de caractere citit este pus in hashtable la pozitia
data de hash-ul obtinut din aplicarea functiei de hash pe sir daca 
pozitia este libera. Daca nu este libera si cele doua chei (cea 
noua si cea deja existenta in bucket) au acceasi valoare, frecventa
bucketului respectiv va creste. Daca si cheile sunt diferite, atunci
se va cauta urmatoarea pozitie libera si se va aseza acolo.

3. ESTIMATORI PROBABILISTICI
    La fiecrae citire din fisierul de intrare, se ia numarul, se trece
prin functia de hash si se selecteaza bitii pentru pozitia din
hashtable (primii 11 din stanga). In fuctie de pozitie si de bitii
care mai raman din hash se adauga in bucket lungimea secventei de 0
+ 1. Daca apar coliziuni, ramane in bucket valoarea maxima. Media
elementelor de calculeaza dupa formula Z = (sum(2^-map[j]))^-1 si in
functie de ea se aproximeaza numarul de numere distincte din fisierul
de intrare.
