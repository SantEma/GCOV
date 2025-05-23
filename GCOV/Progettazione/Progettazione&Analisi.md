Inserire due tipologie di utente:
- **Admin**
- **Visualizzatore**
## FILE ESTERNI
- **Creazione**: creare il file binario col catalogo con già 20 record
- **Menu**: il menu conterrà la chiamata alle general function, sarà controllato tramite un **check_admin** se sarà eseguito da admin e visualizzatore
## General Function
- **Ricerca**: la ricerca dev'essere **richiamabile e generica che soddisfi ogni modalità di scelta** di ricerca che può essere fatta in base a titolo, editore, genere, anno, sviluppatore. La ricerca deve lavorare anche sulle **sottostringhe**.
	- **Ricerca admin**
	- **Ricerca visualizzatore**
- **Recensioni**:
	- **Recensioni admin**
	- **Recensioni visualizzatore**
- **Statistiche** in base alle recensioni calcolare la media di quei videogiochi
- **Ordinamento**: in base alle **copie vendute** e allestire una **classifica di copie vendute**, si è scelto di adoperare in questo contesto un ordinamento di tipo **Shell Sort**, perché ha una complessità vicina a $O(n\log n)$ e anche se di poco superiore all'Insertion Sort è comunque più semplice da implementare rispetto agli altri algoritmi, specialmente se si lavora con strutture di dati semplici, come i campi di un videogioco per l'appunto. Se l’ordine relativo di videogiochi con lo stesso punteggio/vendite non è critico (es. due giochi con media 4.5 possono essere scambiati), Shell Sort è adatto perché **non è stabile**. Shell Sort può essere facilmente adattato per ordinare in base a diversi campi (es. numero di copie vendute, media recensioni), modificando semplicemente il confronto all'interno del ciclo. Questo lo rende comodo e riutilizzabile in più contesti all’interno del progetto. Shell Sort generalizza l’Insertion Sort migliorandone drasticamente le prestazioni nei casi in cui i dati sono **parzialmente ordinati** — una situazione frequente quando i dati nel catalogo sono solo occasionalmente aggiornati. Nel contesto del progetto, il file deve contenere almeno 20 record (anche se il valore potrebbe aumentare in base alle scelte degli admin). Per dataset di queste dimensioni, lo Shell Sort può risultare addirittura **più veloce nella pratica** rispetto a QuickSort.
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
## Variabili utilizzate

## Schema lavorativo
()
In base a questo schema si è deciso di inserire nel file **header** che funge da libreria tutte le informazioni al fine della creazione del progetto, come le funzioni di lavoro e quelle chiamabili ed il record dei videogiochi. Separatamente ci saranno diversi file di lavoro, seguendo la descrizione delle *general function*, in cui saranno richiamate diverse funzioni:
- Il file per il menu
- Il file per la ricerca e la scrittura di recensione
- Il file per l'ordinamento
- il file per le statistiche
In ogni file sarà presente, tramite gli appositi controlli, sia la funzione eseguibile dall'**admin** che dall'**utente**. Questa scelta progettuale è stata adottata per rendere più **snello** il main e favorire l'**information hiding**, tra le varie funzioni e compiti da svolgere. Favorendo una struttura ad albero e un approccio **modulare** alla risoluzione della richiesta.

...