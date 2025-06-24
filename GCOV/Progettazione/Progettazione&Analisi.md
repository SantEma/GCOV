Documento trattante l'analisi e la progettazione del catalogo di videogiochi
## File esterni
Il progetto è strutturato in moduli logici, ciascuno gestito da un file `.c` separato favorendo la modularità e l'information hiding.
- **CreazioneFile**: creare il file binario col catalogo con già 20 record
- **Menu**: esistono 3 menu principali:
	- Menu generale: Menu che permette la scelta di autenticazione preferita, se autenticarsi direttamente come utente o admin
	- Menu utente: Menu che permette la ricerca e le funzioni per un utente normale
	- Menu admin: Menu che permette la ricerca e le funzioni per un amministratore
- **OperazioniAdmin**: si trova tutto ciò che riguarda il lato amministratore
- **OperazioniAU**: si trova tutte le operazioni comuni che possono eseguire entrambi e che servono ad altre funzioni
- **OperazioniUtente**: si trova tutto ciò che può fare solo il visitatore
- **Ordinamento**: si trovano i due tipi di ordinamenti eseguibili
- **Ricerca**: viene effettuata la ricerca sul **nome** del gioco e la posizione di esso per eseguire le operazioni richieste o dall'utente o dall'admin
- **TestGCOV**: si trovano le funzioni di test, per visualizzare le asserzioni e verificare tramite Unity il corretto funzionamento delle funzioni create per la gestione del file e del catalogo

L'autenticazione viene fatta in una funzione dedicata, internamente al modulo *Menu.c*. Questa funzione restituisce un flag booleano per constatare se l'utente che vi accede al catalogo abbia digitato una password corretta o errata, nel caso fosse errata, l'utente ha possibilità di riprovare o di procedere come visitatore.
## General Function
- **Ricerca**: la ricerca dev'essere **richiamabile e generica** da ogni contesto, filtrando per il nome inserito. Inoltre la ricerca lavora anche sulle **sottostringhe**.
	- **Ricerca admin**
	- **Ricerca visitatore**
- **Recensioni**:
	- **Recensioni admin (solo visualizzazione)**
	- **Recensioni visitatore (visualizzazione e aggiunta)**
- **Statistiche** in base alle recensioni calcolare la media di quei videogiochi selezionati, in base a due possibili scelte dell'utente.
- **Ordinamento**: Permette di ordinare il catalogo in base a due criteri principali:
	- **Copie Vendute**: Genera una classifica dei videogiochi in base al numero di copie vendute.
	- **Media Recensioni**: Ordina i videogiochi in base al punteggio medio delle recensioni.

	In entrambi i casi, l'ordinamento avviene in **ordine decrescente** per mettere in risalto i videogiochi con i valori più alti. Per l'ordinamento è stato scelto di adottare l'algoritmo **Shell Sort** per le seguenti motivazioni:

	- Ha una complessità computazionale vicina a O(nlogn).
	- È relativamente semplice da implementare, specialmente con strutture di dati semplici come `videogame_t`.
	- Sebbene leggermente meno efficiente di algoritmi come QuickSort nel caso peggiore, lo Shell Sort è più performante dell'Insertion Sort e può risultare sorprendentemente veloce nella pratica per dataset di dimensioni medie (come un catalogo di 20-50+ record).
	- È facilmente adattabile per ordinare in base a diversi campi (copie vendute, media recensioni) modificando solo la funzione di confronto.
	- La sua efficienza è notevole quando i dati sono **parzialmente ordinati**, una situazione comune in un catalogo che viene aggiornato periodicamente.
	- Non essendo un algoritmo stabile, Shell Sort è adatto poiché l'ordine relativo di videogiochi con gli stessi valori di vendite o recensioni non è critico.

	L'ordinamento è accessibile a entrambi i ruoli per permettere una migliore consultazione del catalogo filtrato.

Si ipotizza che per ogni gioco si possa mettere lo stesso titolo, poichè potrebbero esistere diverse versioni come le remastered (come Silent Hill 2 che ha due versioni, una del 2001 e una del 2025)
### Specific Function - Admin
- **Ricerca**: l'admin deve ricercare un videogioco per poter eseguire tre operazioni:
	- **Modificare prodotto** $\to$ modificare le informazioni relative al gioco cercato
	- **Cancellare prodotto** -> rimozione di un gioco dal catalogo
	- **Aggiunta prodotto** -> aggiunta di un nuovo prodotto al catalogo
- **Recensioni** -> l'admin può **solamente** vedere la recensione del gioco selezionato
### Specific Function - Visitatore
- **Ricerca**: il visitatore può attuare la ricerca per:
	- **Recensioni**: eventualmente scrivere e visualizzarle anche in seguito da altri utenti quando viene effettuata la ricerca
- **Acquisto**: simulare solo la compravendita di un gioco e conteggiare con un **contatore** le copie vendute per videogioco
## Record videogame e vincoli
Ogni videogioco è rappresentato dalla struttura `videogame_t` caratterizzato da: 
- titolo
- editore
- sviluppatore
- breve descrizione testuale del gioco (*facoltativa*)
- anno di pubblicazione
- uno o più generi
- una o più recensioni (*obbligatoria, che va da 0 a 5*)
- copie vendute
## Variabili principali utilizzate

* `videogame_t`: È la struttura dati centrale che definisce il modello per ogni videogioco, contenendo tutti i suoi attributi come nome, sviluppatore, anno e copie vendute.
* `recensione_t`: Struttura annidata dentro `videogame_t`, utilizzata per memorizzare le informazioni di una singola recensione, sia numerica che testuale.
* `check_admin`: Un flag numerico  che distingue un utente con privilegi di amministratore (`1`) da un visitatore (`0`),determina quali menu e operazioni sono accessibili.
* `nomeFile`: Una stringa che contiene il nome del file di dati `catalogo.dat`e viene passata come parametro alle funzioni che devono interagire con il file.
* `nome_ricerca`: Array di caratteri usato per memorizzare l'input dell'utente quando cerca un gioco specifico nel catalogo.
* `medie_recensioni`: Un array di `float` utilizzato nella funzione di ordinamento per le recensioni. Funziona in parallelo all'array catalogo per memorizzare la media calcolata per ogni gioco, semplificando il processo di ordinamento.
* `media`: Variabile `float` usata nelle funzioni statistiche per calcolare e restituire la media delle recensioni o delle copie vendute.


## Schema lavorativo
![[Pasted image 20250523174021.jpg]]
In base a questo schema si è deciso di inserire nel file **header**, che funge da libreria, tutte le informazioni al fine della creazione del progetto, come le funzioni di lavoro, quelle chiamabili, le costanti ed il record dei videogiochi e delle recensioni. Separatamente ci saranno diversi file di lavoro, seguendo la descrizione delle *general function*, in cui saranno richiamate diverse funzioni:
- Il file per i menu e autenticazione
- Il file per la ricerca
- Il file per l'operazioni Admin
- Il file per le operazione Utente
- Il file per le operazioni di entrambi
- Il file per l'ordinamento
- il file per le statistiche
- (e quello per i test)
Questa scelta progettuale è stata adottata favorendo una struttura ad albero e un approccio **modulare** alla risoluzione della richiesta.
### Autenticazione
L'autenticazione dell'utente in admin o visitatore viene gestita nella funzione del menu, prima delle possibili scelte effettuabili, attraverso una autenticazione password, la password di accesso per gli admin è *Admin157*, ponendo attenzione alla scrittura poiché case-sensitive.
L'admin se inserisce la password in modo errato può decidere di riscriverla o continuare come visitatore al sito.
Una volta fatta l'autenticazione (e in base all'esito di quest'ultima) si viene rindirizzati al menu corretto e alle funzioni che quel determinato utente può fare (visitatore o amministratore)
### Ricerca
La funzione di ricerca, utilizzata sia dall'admin che dall'utente, consente di filtrare i videogiochi per nome, gestendo sia la ricerca per **sottostringhe** sia la corrispondenza case-insensitive.
- **Ricerca per sottostringa**: L'utente può inserire una porzione del nome del gioco (es. "fif"). La funzione visualizzerà tutti i giochi che contengono quella sottostringa (es. "Fifa 24", "fifone&birba 3"). L'utente dovrà poi selezionare il nome completo del gioco desiderato tra quelli proposti.
- La funzione `strstr()` della libreria standard C `<string.h>` è utilizzata per trovare le occorrenze delle sottostringhe.
### Modifica
Per l'admin, la ricerca di un videogioco per **nome** è il prerequisito per eseguire operazioni di modifica o eliminazione. Queste azioni sono implementate in sotto-funzioni all'interno del file `OperazioniAdmin.c`. Dopo la ricerca e la selezione del gioco, l'admin potrà scegliere quale campo specifico modificare.
### Cancella
La **cancellazione** di un gioco avviene tramite un processo di riscrittura: il contenuto del file `catalogo.dat` viene copiato in un file temporaneo (`temp.dat`), omettendo il record del gioco da eliminare. Una volta completata la copia, il file originale viene rimosso e il file temporaneo viene rinominato con il nome del file originale. L'utente riceve un messaggio di conferma in caso di successo o di fallimento (se il gioco non viene trovato).
### Aggiunta gioco
L'admin può anche aggiungere un nuovo gioco nel catalogo, sempre specificato nella ricerca come operazione da poter eseguire. Questa operazione permette all'admin di aggiungere un nuovo videogame nel catalogo ponendolo come ultimo nella lista dei videogiochi e così via per ogni nuova aggiunta che sarà inserita, la posizione nel file binario sarà riportata all'inizio in caso si vogliano eseguire altre operazioni che richiedono uno spostamento della posizione.
### Recensioni
Il gioco ricercato da parte dell'admin sarà lo stesso gioco sul quale si potrà effettuare anche l'operazione di visualizzazione delle recensioni. L'admin visualizzerà le recensioni numeriche e scritte per ogni utente che inserito la recensione, inoltre la recensione sarà gestita da dei messaggi che gestiranno il grado di apprezzamento del gioco in base alla positività o negatività delle recensioni numeriche, le fasce si dividono in:
- Pessimo
- Insufficiente
- Buono
- Eccellente
O valore indesiderato, in caso ci sia un valore numerico che non rientra nei limiti o se non è presente ancora alcuna recensione. Dopo di che, attraverso dei contatori, saranno conteggiate le varie fasce di apprezzamento del gioco, infine saranno messe a confronto e come messaggio finale sarà mostrata la fascia con contatore maggiore.
La funzione di visualizzazione delle recensioni viene posta nel file delle operazioni comuni (`OperazioniAU.c`), poiché anche l'utente quando visualizza un prodotto, tramite la sua apposita funzione, deve visualizzare lo stesso tipo di recensioni.
### Visualizzazione gioco
La prima funzione possibile da svolgere per quanto riguarda l'utente è la possibilità di visualizzare tutte le informazioni del videogioco che è stato precedentemente richiesto nella fase di ricerca. Questa funzione viene facilmente implementata cercando nel file il gioco desiderato, come eseguito per le funzioni precedenti ad essa, e mostrare a schermo le informazioni relative a quello specifico gioco, se trovato, infine si richiama la funzione di visualizzazione delle recensioni per mostrare anche quest'ultimo parametro.

### Aggiungi recensione
La funzione di aggiunta di una recensione da parte dell'utente sarà possibile eseguirla sia nel menu delle scelte dell'utente, sia a fine di un acquisto per inserire una recensione prima che esca dal catalogo.
Questa funzione, dopo aver trovato il gioco desiderato, verifica se ci sono altre recensioni presenti, nelle 70 possibili recensioni inseribili, se questo valore è diverso da -1 (non c'è una recensione), alla prima posizione libera inserisce la recensione dettata dall'utente, altrimenti continua a ciclare fin quando non trova la prima posizione libera, ammesso che ci sia. Se l'utente vuole può anche inserire quella scritta, oltre al valore numerico. Inoltre se non ci sono recensione al momento dell'apertura del catalogo per quel gioco sarà fatta presente questa info all'utente.

### Acquista videogioco
La funzione di acquisizione di un videogioco propone di acquisire un gioco presente nel catalogo specificato nella fase di ricerca dall'utente, con gli appositi controlli. Una volta trovata la corrispondenza tra il gioco inserito dall'utente e quello presente nel file viene salvata la posizione presente sul file così da poter aggiornare il contatore delle copie vendute e viene simulato un acquisto tra il software e l'utente, tramite scambi di messaggi. Dopo di che vi si aggiorna il file completo e si richiede se vuole inserire una recensione del gioco appena riscontrato, se l'esito è positivo viene chiamata la funzione di aggiunta recensione, altrimenti viene salvato e chiuso il file e si torna alle scelte nel Menù.
### Statistica
La statistica è stata suddivisa in due possibili scelte in base a come l'utente o l'admin vogliano visualizzarle. Possono scegliere di visualizzare la statistica in base alle medie recensioni del gioco inserito nella ricerca o in base alla medie delle loro copie vendute in relazione alla sua distribuzione. Nelle due funzioni viene eseguita una classica somma dei valori per ogni valore presente e che sia valido e diviso per il totale dei valori validi,  ed in entrambi i casi ritorna il valore della media per far visualizzare i risultati fuori dalla funzione, questo perché si tende a rendere le funzioni il più neutrali possibile per poter essere richiamate nei due ordinamenti, in maniera tale da agevolare il lavoro dell'implementazione degli ordinamenti delle medie recensioni e delle copie vendute.
### Ordinamento
Nel menu è possibile ordinare in due modi:
- Per media recensione
- Per copie vendute
Per evitare ricalcoli, le funzioni che calcolano le statistiche vengono richiamate e i loro valori assegnati a un catalogo temporaneo in memoria. Questo catalogo temporaneo viene poi ordinato (utilizzando lo Shell Sort) e visualizzato; viene sovrascritto ad ogni nuova richiesta di ordinamento.
Si fa uso delle funzioni di statistica.
## Problemi riscontrati e risoluzioni
1. Durante la compilazione del progetto, anche se il file esisteva e non si specificava il file `CreazioneFile.c` durante la compilazione, l'intero progetto non veniva eseguito, poiché il main non riusciva a capire dove fosse specificata la funzione ScriviCatalogo, funzione che possiede già il controllo di uscire se il file è già creato. 
   **Risoluzione**: Per risolvere questo problema è bastato togliere dal repository di GitHub il file, in maniera tale che anche se esistente non venga considerato univoco per tutti, e specificare ugualmente tutti i file del progetto nella fase di compilazione, così da poter essere eseguito.
2. Durante l'esecuzione del progetto ad un certo punto il file veniva aperto correttamente ma il contenuto non veniva più letto.
   **Risoluzione**: Avendo modificato la struttura del record del catalogo il file era andando in contrasto, è bastato ricrearlo una nuova volta.
3. Durante l'inserimento di una recensione, alla sua verifica il file veniva corrotto, poiché non era presente il break nel ciclo in cui veniva cercata la posizione, quindi una volta trovata continuava a contare le altre arrivando a fine file e renderlo inaccessibile. Dopo aver risolto questo problema si è riscontrato che il valore -1 delle recensioni (posto di deafault) era impostato solo al primo non a tutte le possibili recensioni.
   **Spiegazione**: Questo è avvenuto perché nel codice si è usato le {} classiche, che andavano bene per la gestione di array di char, come la descrizione, ma non per un array di record, in cui per impostare quel valore a tutti i record serve la notazione {{{}}}, in modo tale che le prime parentesi fanno riferimento al record e le seconde all'array della struttura.
   **Prima `{`**: Inizia l'inizializzazione della struttura `videogame_t`
   **Seconda `{`**: Inizia l'inizializzazione dell'array `recensione[MAX_RECENSIONI]`
   **Terza `{`**: Inizia l'inizializzazione della struttura `recensione_t`
   In più si va ad implementare nel file di CreazioneFile, un ciclo per impostare inizialmente tutti i valori numerici della recensione a -1 in maniera pulita e comprensibile, così da non creare contrasto nella dichiarazione precedente dell'array del catalogo. (Per sicurezza nell'aggiunta di una recensione si è inserito un flag per controllare se gli slot per le recensioni fossero liberi o meno).
## Test Unity
Per i test delle funzioni è stato utilizzato il framework Unity, verificando le asserzioni restituite dalle loro corrispettive funzioni di test.
In particolare sono state testate le seguenti funzioni create durante il programma:
- **La Creazione del file**, verifica la corretta creazione del file del catalogo e l'inserimento dei record di test senza errori.
- **La Statistica delle medie recensioni**, verifica che il valore ritornato dalla media delle recensioni sia corretto
- **La Statistica delle copie vendute rispetto alla produzione**, verifica che qualsiasi videogioco passato faccia tornare la statistica delle sue copie vendute qualsiasi esso sia e che questo valore sia corretto
- **La Cancellazione del gioco**, verifica che dopo la cancellazione di un gioco, il file dei test contenga solamente i giochi rimanenti, escluso quello eliminato