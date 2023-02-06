# BinarySearchTree
Implementazione in c++ di una classe per rappresentare gli alberi di ricerca binaria

## Indice
1. [Informazioni generali](#informazioni-generali)
2. [Utilizzo](#utilizzo)
3. [Classi](#classi)
4. [Note](#note)

## Informazioni generali

Un albero di ricerca binaria (BST), anche chiamato albero binario ordinato, è una albero binario con radice in cui le chiavi di ogni suo nodo sono maggiori di tutte le chiavi nei rispettivi nodi del sottoalbero sinistro e minore di quelli del sottoalbero destro. La complessità delle operazioni di ricerca nel BST sono direttamente proporzionali all'altezza dell'albero e quindi i BST permettono inserimenti e rimozioni rapide di dati.
| Operazione | Complessità al caso pessimo | Complessità al caso medio |
|:--------------|:-------------|:--------------|
| Visita | O(n) | O(n) |
| Ricerca | O(n) | O(h) |
| Inserimento | O(n) | O(h) |
| Cancellazione | O(n) | O(h) |

Maggiori informazioni su: https://it.wikipedia.org/wiki/Albero_binario_di_ricerca

## Utilizzo
Scaricare i file con estensione hpp e il file make. Per utilizzare test.cpp, compilare con i seguenti comandi:
```bash
cmake . -G Ninja
ninja
```
Altrimenti modificare il file CMakeList.txt sostituendo "test.cpp" con il file da voi creato.

Creazione di un albero
```cpp
#include "bst.hpp"

int main()
{
  // Crea un albero di interi
  bst<int> uintTree(3);
  
  // Aggiungi dei nodi figli
  uintTree.insertValue(2);
  uintTree.insertValue(4);
  
  return 0;
}
```
Analisi di un albero
```cpp
// Eliminazione di un nodo
uintTree.deleteKey(4) // Viene eliminato il nodo con chiave uguale a 4 (se è presente)

// Stampa di un albero
std::cout << uintTree; // L'operatore << è sovvracaricato

// Ottieni minimo
// Bisogna prima ottenere il puntatore al valore minimo, dopodiché se ne ottiene il valore della chiave con il metodo getKey()
uintTree.min()->getKey();
```

## Classi
Per una dettagliata documentazione sulle classi si consiglia di scaricare il file compresso html.rar.
### bst.hpp
Classe per la rappresentazione degli alberi binari di ricerca. Un albero è definito in modo ricorsivo dal valore della sua radice, dal puntatore al nodo genitore e dai puntatori ai suoi sottoalberi sinistro e destro.
#### const_iterator
Iteratore costante per gli alberi binari di ricerca.
### bstException.hpp
Classe che implementa l'eccezione di valore non trovato in un albero.
### City.hpp
Classe che implementa la rappresentazione di una città.

## Note
È disponibile la documentazione realizzata con il tool [Doxygen](https://www.doxygen.nl/), scaricando l'archivio compresso "html".\
È stato anche utilizzato il framework [Valgrind](https://valgrind.org/) per l’analisi della gestione della memoria dinamica con il risultato che non sono stati generati memory leak o errori di accesso alla memoria.

<p align="left"> <img src="https://komarev.com/ghpvc/?username=giacomo-gobbo&label=Visite&color=ed3535&style=flat" alt="giacomo-gobbo" /> </p>

<h3 align="left">Languages and Tools:</h3>
<p align="left"> <a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> </p>
