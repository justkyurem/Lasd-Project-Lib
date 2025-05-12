# Algoritmi e Strutture Dati

## Esercizio 1: Vettori, Liste e Insiemi Ordinati di Dati Generici

Questa libreria implementa diverse strutture dati fondamentali in C++, seguendo i principi della programmazione orientata agli oggetti e utilizzando template per garantire il supporto di tipi di dati generici.

### Strutture Dati Implementate

1. **Vector**: Implementazione di un vettore dinamico con ridimensionamento automatico
2. **List**: Implementazione di una lista collegata
3. **Set**: Insiemi ordinati implementati in due varianti:
    - **SetLst**: Implementato utilizzando una lista collegata ordinata
    - **SetVec**: Implementato utilizzando un vettore con ridimensionamento automatico

### Funzionalità Principali

#### Comuni a tutte le strutture:
- Costruzione e distruzione
- Operazioni di assegnamento (operatore `=`)
- Operazioni di confronto (operatori `==` e `!=`)
- Test di vuotezza (`Empty()`)
- Lettura della dimensione (`Size()`)
- Svuotamento della struttura (`Clear()`)
- Accesso non distruttivo all'elemento iniziale (`Front()`) e finale (`Back()`)
- Accesso per indice (operatore `[]`)
- Controllo di esistenza di un dato valore (`Exists()`)
- Attraversamento (`Traverse()`, `PreOrderTraverse()`, `PostOrderTraverse()`)
- Accumulazione (`Fold()`, `PreOrderFold()`, `PostOrderFold()`)

#### Specifiche di Vector:
- Ridimensionamento del vettore (`Resize()`)

#### Specifiche di List:
- Inserimento di un elemento in testa (`InsertAtFront()`) o in coda (`InsertAtBack()`)
- Rimozione dell'elemento in testa (`RemoveFromFront()`) o in coda (`RemoveFromBack()`)
- Rimozione con lettura dell'elemento in testa (`FrontNRemove()`) o in coda (`BackNRemove()`)

#### Specifiche dei Set (SetLst e SetVec):
- Inserimento di un elemento (`Insert()`)
- Rimozione di un elemento (`Remove()`)
- Accesso, rimozione e accesso con rimozione dell'elemento minimo (`Min()`, `RemoveMin()`, `MinNRemove()`)
- Accesso, rimozione e accesso con rimozione dell'elemento massimo (`Max()`, `RemoveMax()`, `MaxNRemove()`)
- Accesso, rimozione e accesso con rimozione del predecessore di un elemento (`Predecessor()`, `RemovePredecessor()`, `PredecessorNRemove()`)
- Accesso, rimozione e accesso con rimozione del successore di un elemento (`Successor()`, `RemoveSuccessor()`, `SuccessorNRemove()`)

### Organizzazione Gerarchica

La libreria è organizzata secondo una gerarchia di classi che implementa i concetti fondamentali:

1. **Container**: Classe base astratta per tutte le strutture dati
    - **TestableContainer**: Container con operazioni di test
    - **TraversableContainer**: Container attraversabile
        - **PreOrderTraversableContainer**: Attraversamento in pre-ordine
        - **PostOrderTraversableContainer**: Attraversamento in post-ordine
    - **MappableContainer**: Container con funzione di mapping
        - **PreOrderMappableContainer**: Mapping in pre-ordine
        - **PostOrderMappableContainer**: Mapping in post-ordine
    - **LinearContainer**: Container lineare
        - **Vector**: Implementazione vettoriale
        - **List**: Implementazione a lista
    - **DictionaryContainer**: Container di tipo dizionario
        - **OrderedDictionaryContainer**: Dizionario ordinato
            - **Set**: Set ordinato
                - **SetLst**: Implementazione a lista
                - **SetVec**: Implementazione vettoriale

### Sistema di Test

È stato implementato un sistema di test completo che permette di:

1. Selezionare la struttura dati da testare (Vector, List, SetLst, SetVec)
2. Selezionare il tipo di test da eseguire
3. Verificare tutte le funzionalità implementate con feedback dettagliato

I test sono organizzati in diverse categorie:
- Test dei costruttori
- Test delle operazioni base
- Test delle funzioni di Map
- Test delle funzioni di Fold
- Test delle eccezioni
- Test con tipi diversi (interi, stringhe, ecc.)
- Test comparativi tra implementazioni diverse

### Come Utilizzare la Libreria

#### Compilazione
```bash
make
```

#### Esecuzione
```bash
./main
```

### Note Implementative

- Tutti i template utilizzano il modello di inclusione, in cui i file `.cpp` sono inclusi nei corrispondenti `.hpp` per garantire la corretta istanziazione dei template
- Le strutture dati rispettano i principi della gestione automatica della memoria per evitare memory leak
- Implementazione efficiente della funzionalità di ridimensionamento per `Vector` e `SetVec`
- Implementazione ottimizzata degli algoritmi di ricerca per `SetVec` (ricerca binaria)

### Requisiti

- Compilatore C++ con supporto per C++11 o superiore
- Librerie standard C++
