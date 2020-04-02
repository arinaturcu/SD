/* Arina Emanuela Turcu 313CA */

------------------------TEMA 1 - MUSIC PLAYLIST----------------------------

    Playlist-ul este reprezentat printr-o lista dublu inlantuita. Ficare
melodie din playlist este reprezentata printr-un nod din lista care are
urmatoarea structura: pointeri catre nodul anterior si urmator si un
pointer catre datele despre melodie care sunt titlul, artistul, albumul,
anul cat si calea catre fisierul mp3 (puse intr-o structura de tip song).

    Codul este imaprtit in 3 fisiere sursa: playlist.c, commands.c 
si list_utils.c. 

    Playlist.c contine functia main() si funtia check_command() care citeste 
datele de intrare si decide ce funtie sa apeleze. Ia primul string 
din linie si in funtie de semnificatia lui apeleaza funtia respectiva
sau citeste urmatorul string si apeleaza functia dupa.

    Exista cate o funtie in commands.c pentru fiecare comanda pe
care o poate primi:
- ADD_FIRST, ADD_LAST si ADD_AFTER functioaneaza asemanator. Creeaza noul
nod care trebuie adaugat si ii adauga informatia necesara structurii song
prin functia get_info(). Functia get_info() deschide fisierul mp3 si ia
datele necesare pe care le aseaza in structura. Acest nod aste adaugat,
in functie de comanda, la inceputul / finalul playlistului sau dupa
cursor.
- DEL_FIRST, DEL_LAST, DEL_CURR si DEL_SONG muta cursorul, daca este
nevoie, si sterg nodul corespunzator melodiei prin functia delete_node().
DEL_SONG stie ce sa stearga construind calea catre fisier porning de la
numele cantecului primit ca parametru pe care il compara cu campul
path_to_file din structura fiecarei melodii din playlist.
- MOVE_PREV si MOVE_NEXT doar muta cursorul in fata sau un spate,
folosindu-se de pointerii din structura Node.
-SHOW_FIRST, SHOW_LAST, SHOW_CURR si SHOW_PLAYLIST scriu in fisierul
media.out informatiile cerute pe care le extrag din structura song a
fiecarui nod.

    In afara de ultima categorie de functii, toate returneaza nodul catre
care pointeaza cursorul.

---------------------------------------------------------------------------
