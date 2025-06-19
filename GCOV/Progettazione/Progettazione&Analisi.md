Inserire due tipologie di utente:
- **Admin**
- **Visualizzatore**
## FILE ESTERNI
- **Creazione**: creare il file binario col catalogo con già 20 record
- **Menu**: Esistono 3 menu principali:
	- Menu generale: Menu che permette la scelta di autenticazione preferita, se autenticarsi direttamente come utente o admin
	- Menu utente: Menu che permette la ricerca e le funzioni per un utente normale
	- Menu admin: Menu che permette la ricerca e le funzioni per un amministratore

L'autenticazione viene fatta in una funzione differente che restituisce una flag booleana per constatare se l'utente abbia messo una password giusta o meno, nel caso non fosse così l'utente ha possibilità di riprovare e nel caso di loggarsi come utente se non sia autorizzato ad entrare
## General Function
- **Ricerca**: la ricerca dev'essere **richiamabile e generica che soddisfi ogni modalità di scelta** di ricerca che può essere fatta in base a titolo, editore, genere, anno, sviluppatore. La ricerca deve lavorare anche sulle **sottostringhe**.
	- **Ricerca admin**
	- **Ricerca visualizzatore**
- **Recensioni**:
	- **Recensioni admin**
	- **Recensioni visualizzatore**
- **Statistiche** in base alle recensioni calcolare la media di quei videogiochi
- **Ordinamento**: in base alle **copie vendute** e allestire una **classifica di copie vendute**, si è scelto di adoperare in questo contesto un ordinamento di tipo **Shell Sort**, perché ha una complessità vicina a $O(n\log n)$ e anche se di poco superiore all'Insertion Sort è comunque più semplice da implementare rispetto agli altri algoritmi, specialmente se si lavora con strutture di dati semplici, come i campi di un videogioco per l'appunto. Se l’ordine relativo di videogiochi con lo stesso punteggio/vendite non è critico (es. due giochi con media 4.5 possono essere scambiati), Shell Sort è adatto perché **non è stabile**. Shell Sort può essere facilmente adattato per ordinare in base a diversi campi (es. numero di copie vendute, media recensioni), modificando semplicemente il confronto all'interno del ciclo. Questo lo rende comodo e riutilizzabile in più contesti all’interno del progetto. Shell Sort generalizza l’Insertion Sort migliorandone drasticamente le prestazioni nei casi in cui i dati sono **parzialmente ordinati** — una situazione frequente quando i dati nel catalogo sono solo occasionalmente aggiornati. Nel contesto del progetto, il file deve contenere almeno 20 record (anche se il valore potrebbe aumentare in base alle scelte degli admin). Per dataset di queste dimensioni, lo Shell Sort può risultare addirittura **più veloce nella pratica** rispetto a QuickSort.
  
  L'ordinamento può essere fatto  da entrambi per ordinare i videogiochi nel catalogo per filtrare il catalogo in base a due operazioni:
- O per media recensione
- O per copie vendute
### Specific Function - Admin
- **Ricerca**: l'admin deve ricercare un videogioco per poter eseguire tre operazioni:
	- **Modificare prodotto** -> aggiungere o modificare
	- **Cancellare prodotto**
- **Recensioni**: vedere la recensione
### Specific Function - Visualizzatore
- **Ricerca**: il visualizzatore può attuare la ricerca per:
	- **Recensioni**: eventualmente scrivere e visualizzarle anche in seguito da altri utenti quando viene effettuata la ricerca
- **Acquisto**: simulare solo la compravendita di un gioco e conteggiare con un **contatore** le copie vendute per videogioco
## Record videogame e vincoli
Ogni videogioco è caratterizzato da: 
- titolo
- editore
- sviluppatore
- breve descrizione testuale del gioco (*facoltativa*)
- anno di pubblicazione
- uno o più generi
- una o più recensioni (*obbligatoria, che va da 0 a 5*)
## Variabili principali utilizzate

...

## Schema lavorativo
![[Pasted image 20250523174021.png]]
In base a questo schema si è deciso di inserire nel file **header** che funge da libreria tutte le informazioni al fine della creazione del progetto, come le funzioni di lavoro e quelle chiamabili ed il record dei videogiochi. Separatamente ci saranno diversi file di lavoro, seguendo la descrizione delle *general function*, in cui saranno richiamate diverse funzioni:
- Il file per i menu
- Il file per la ricerca
- Il file per l'operazioni Admin
- Il file per le operazione Utente
- Il file per le operazioni di entrambi
- Il file per l'ordinamento
- il file per le statistiche
In ogni file sarà presente, tramite gli appositi controlli, sia la funzione eseguibile dall'**admin** che dall'**utente**. Questa scelta progettuale è stata adottata per rendere più **snello** il main e favorire l'**information hiding**, tra le varie funzioni e compiti da svolgere. Favorendo una struttura ad albero e un approccio **modulare** alla risoluzione della richiesta.

...

L'autentificazione dell'utente in admin o visualizzatore viene gestita nella funzione del menu, prima delle possibili scelte effettuabili, attraverso una autentificazione password, la password di accesso per gli admin è *Admin157*, ponendo attenzione alla scrittura poiché non si tollera un upper-case. L'admin se inserisce la password in modo errato può decidere di riscriverla o continuare come visitatore al sito.
Una volta fatta l'autenticazione (e in base all'esito di quest'ultima) si viene reinderizzati al menu corretto e alle funzioni che quel determinato utente può fare (visitatore o amministratore)

...

La ricerca del videogioco da parte dell'admin e dell'utente deve comprende la possibilità di filtrare in sottostringhe e di gestire l'upperCase e il LowerCase.
**SOTTOSTRINGHE**-> Cerchi fif (su 50 fif diversi che stanno, come fifa fifoloide ecc.. fifoloide 3) e poi l'utente deve inserire il nome completo del gioco che vuole selezionare tra quelli mostrati. [Inserire questa operazione]

La ricerca per l'admin per modificare/eliminare un videogioco sarà effettuata filtrando per **nome del videogioco** ognuna di queste azioni sarà eseguita in sotto-funzioni, poste in un nuovo file .c dove ci saranno le 3 azioni eseguibili dall'admin nella scelta 1 della ricerca, dopo di che si sceglierà quale campo vuole modificare l'admin nella modifica.
Per l'eliminazione andiamo ad usare un sistema di scambi: il file catalogo.dat viene riscritto su un file temporaneo temp.dat, quest'ultimo inserisce tutti i giochi fin quando non trova il gioco che si vuole cancellare e lo salta, in modo da non inserire quei byte. Una volta fatto ciò, l'utente in caso positivo viene avvisato del successo dell'operazione (con il file originale rimosso e quello temporaneo rinominato a quello originale), nel caso contrario viene avvisato di non aver trovato quel gioco nel catalogo

L'admin può anche aggiungere un nuovo gioco nel catalogo, sempre specificato nella ricerca come operazione da poter eseguire. Questa operazione permette all'admin di aggiungere un nuovo videogame nel catalogo ponendolo come ultimo presente nella lista dei videogiochi e così via per ogni nuova aggiunta che sarà inserita, la posizione nel file binario sarà riportata all'inizio in caso si vogliano eseguire altre operazioni che richiedono uno spostamento della posizione.

Il gioco ricercato da parte dell'admin sarà lo stesso gioco sul quale si potrà effettuare anche l'operazione di visualizzazione delle recensioni. L'admin visualizzerà le recensioni numeriche e scritte per ogni utente che inserito la recensione, inoltre la recensione sarà gestita da dei messaggi che faranno capire il grado di apprezzamento del gioco in base alla positività o negatività delle recensioni numeriche; le fasce si dividono in:
- Pessimo
- Insufficiente
- Buono
- Eccellente
O valore indesiderato, in caso ci sia un valore numerico che non rientra nei limiti. Dopo di che, attraverso dei contatori, saranno conteggiate le varie fasce di apprezzamento del gioco, infine saranno messe a confronto e come messaggio finale sarà mostrata la fascia con contatore maggiore.
La funzione di visualizzazione delle recensioni viene posta nel file delle operazioni comuni, poiché anche l'utente quando visualizza un prodotto, tramite la sua apposita funzione, deve visualizzare lo stesso tipo di recensioni.

La prima funzione possibile da svolgere per quanto riguarda l'utente è la possibilità di visualizzare tutte le informazioni del videogioco che è stato precedentemente richiesto nella fase di ricerca. Questa funzione viene facilmente implementata cercando nel file il gioco desiderato, come eseguito per le funzioni precedenti ad essa, e mostrare a schermo le informazioni relative a quello specifico gioco, se trovato, infine si richiama la funzione di visualizzazione delle recensioni per mostrare anche quest'ultimo parametro.

[APPORTARE MODIFCA DELLO SPOSTAMENTO DEL CONTROLLO DEL NOME IN RICERCA E NON IN OGNI SINGOLA FUNZIONE]

La funzione di aggiunta di una recensione da parte dell'utente sarà possibile eseguirla sia nel menu delle scelte dell'utente, sia a fine di un acquisto per inserire una recensione prima che esca dal catalogo.
Questa funzione, dopo aver trovato il gioco desiderato, verifica se ci sono altre recensioni presenti, nelle 70 possibili recensioni inseribili, se questo valore è diverso da -1 (non c'è una recensione), alla prima posizione libera inserisce la recensione dettata dall'utente, altrimenti continua a ciclare fin quando non trova la prima posizione libera, ammesso che ci sia. Se l'utente vuole può anche inserire quella scritta oltre al valore numerico.
## Problemi riscontrati e risoluzioni
1. Durante la compilazione del progetto, anche se il file esisteva e non si specificava il file c CreazioneFile durante la compilazione, l'intero progetto non veniva eseguito, poiché il main non riusciva a capire dove fosse specificata la funzione ScriviCatalogo, funzione che possiede già il controllo di uscire se il file è già creato. 
   **Risoluzione**: Per risolvere questo problema è bastato togliere dal repository di GitHub il file, in maniera tale che anche se esistente non venga considerato univoco per tutti, e specificare ugualmente tutti i file del progetto nella fase di compilazione, così da poter essere eseguito.
2. Durante l'esecuzione del progetto ad un certo punto il file veniva aperto correttamente ma il contenuto non veniva più letto.
   **Risoluzione**: Avendo modificato la struttura del record del catalogo il file era andando in contrasto, è bastato ricrearlo una nuova volta.
3. Durante l'inserimento di una recensione, alla sua verifica il file veniva corrotto, poiché non era presente il break nel ciclo in cui veniva cercata la posizione, quindi una volta trovata continuava a contare le altre arrivando a fine file e renderlo inaccessibile. Dopo aver risolto questo problema si è riscontrato che il valore -1 delle recensioni (posto di deafault) era impostato solo al primo non a tutte le possibili recensioni.
   **Spiegazione**: Questo è avvenuto perché nel codice si è usato le {} classiche, che andavano bene per la gestione di array di char, come la descrizione, ma non per un array di record, in cui per impostare quel valore a tutti i record serve la notazione {{{}}}, in modo tale che le prime parentesi fanno riferimento al record e le seconde all'array della struttura.
   **Prima `{`**: Inizia l'inizializzazione della struttura `videogame_t`
   **Seconda `{`**: Inizia l'inizializzazione dell'array `recensione[MAX_RECENSIONI]`
   **Terza `{`**: Inizia l'inizializzazione della struttura `recensione_t`
   In più si va ad implementare nel file di CreazioneFile, un ciclo per impostare inizialmente tutti i valori numerici della recensione a -1 in maniera pulita e comprensibile, così da non creare contrasto nella dichiarazione precedente dell'array del catalogo. (Per sicurezza nell'aggiunta di una recensione si è inserito un flag per controllare se gli slot per le recensioni fossero liberi o meno).