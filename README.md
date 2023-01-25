# Snake_Labyrinth

<H2>Progetto richiesto</H2>
Creare un programma che, dato in input un labirinto, trovi un percorso per uscire, tenendo conto di tutti gli elementi presenti all’interno.
Elementi presenti all’interno del labirinto:

- Muri [ # ]: non è possibile attraversare questa casella a meno che non si ha a disposizione un trapano;
- Imprevisti [ ! ]: se raccolto, dimezza il punteggio accumulato fino a quel momento;
- Bonus [ $ ]: se raccolto, aggiunge 10 monete bonus al tuo punteggio;
- Trapani [ T ]: se raccolto, aggiunge 3 trapani nello zaino dando la possibilità di attraversare 3 muri;
- Testa del serpente [ @ ]: deve raggiungere l’uscita del labirinto;
- Coda del serpente [ * ]: ogni casella identifica un pezzo del serpente, se attraversata si riduce la
coda e vengono sottratti dei punti;
- Uscita del labirinto [ _ ]: casella da raggiungere per concludere il gioco.

Ad ogni passo “valido” della testa del serpente il punteggio diminuisce di 1 punto.

Il serpente si allunga quando si prende una moneta bonus ma diminuisce quando si prende un imprevisto oppure si morde la sua coda.
Prima di terminare il programma è necessario visualizzare il punteggio ottenuto, il percorso seguito e le varie mosse effettuate.

<H2>Soluzione proposta</H2>
All’apertura del programma vengono visualizzate tutte le regole del gioco e successivamente viene data la possibilità all’utente di scegliere tra due tipi di mappe di gioco disponibili:

- Mappa standard: già stabilita dallo sviluppatore;
- Mappa manuale: l’utente ha la possibilità di inserire manualmente la mappa suddividendola in righe e inserendo una riga per volta.

Dopo aver scelto la mappa l’utente deve scegliere una delle quattro modalità di gioco disponibili nel programma:

- Modalità manuale: l’utente decide le mosse da fare controllando ad ogni turno la mappa;
- Modalità random: le mosse sono decise dalla CPU in maniera casuale;
- Modalità intelligente: le mosse sono decise dalla CPU secondo algoritmi prestabiliti.
Sono disponibili due tipi di algoritmi a scelta dell’utente:
- Modalità oraria: il serpente arriva all’uscita effettuando un giro orario della mappa;
- Modalità antioraria: il serpente arriva all’uscita effettuando un giro antiorario della mappa.
Dopo aver effettuato la scelta, il gioco inizia.

Il punteggio iniziale viene impostato a 1000, I trapani, i bonus e gli imprevisti iniziali vengono impostati a 0.

Le mosse a disposizione del serpente sono identificate da una lettera e sono:

- Spostamento verso nord -> N;
- Spostamento verso sud  -> S;
- Spostamento verso est  -> E;
- Spostamento verso ovest -> O;

Ogni spostamento viene accuratamente controllato per evitare che il serpente esca dalla mappa o che attraversi caselle non ammesse.
Al raggiungimento dell’uscita da parte della testa del serpente, il gioco finisce e all’utente viene mostrato il punteggio ottenuto, il percorso effettuato dal serpente, ponendo all’interno della mappa il simbolo “.”, e tutte le mosse inserite durante il gioco.

<H3>Librerie incluse nel programma</H3>

- stdio.h, utilizzata per input ed output del programma;
- stdlib.h, utilizzata per creare array e matrice dinamiche;
- time.h, utilizzata per utilizzare la funzione “rand();” e “srand();” nella la modalità casuale;
- unistd.h, utilizzata per poter mettere in pausa il programma attraverso la funzione “sleep.h”.
  
<H3>Errori presenti nel programma</H3>
Gli errori possibili durante l’esecuzione del programma si dividono in due categorie: 

- Errori standard: errori che non compromettono il gioco;
- Errori gravi: errori che chiudono il programma.

Durante lo spostamento del serpente sono presenti tre errori standard:

- input invalido in quanto è presente un muro e non si hanno trapani nello zaino;
- input invalido in quanto si sta uscendo dalla mappa di gioco;
- durante la ricerca automatica del percorso non sempre viene trovata la strada per uscire.
Dopo 15.000 passi eseguiti dalla testa del serpente il programma automaticamente si chiude.

Durante l’inserimento manuale della mappa sono presenti tre errori gravi:

- nel labirinto non è presente l’entrata;
- nel labirinto non è presente l’uscita;
- la mappa è troppo grande per la memoria disponibile nell’elaboratore.
