# BinarySearchTree
Implementazione in c++ di una classe per rappresentare gli alberi di ricerca binaria

## Indice
1. [Informazioni generali](#general-info)
2. [Utilizzo](#usage)
3. [Classi](#classes)
4. [Altro](#other)

## Informazioni generali(#general-info)

Un albero di ricerca binaria (BST), anche chiamato albero binario ordinato, è una albero binario con radice in cui le chiavi di ogni suo nodo sono maggiori di tutte le chiavi nei rispettivi nodi del sottoalbero sinistro e minore di quelli del sottoalbero destro. La complessità delle operazioni di ricerca nel BST sono direttamente proporzionali all'altezza dell'albero e quindi i BST permettono inserimenti e rimozioni rapide di dati.
| Operazione | Complessità al caso pessimo | Complessità al caso medio |
|:--------------|:-------------|:--------------|
| Visita | O(n) | O(n) |
| Ricerca | O(n) | O(h) |
| Inserimento | O(n) | O(h) |
| Cancellazione | O(n) | O(h) |

Maggiori informazioni su: https://it.wikipedia.org/wiki/Albero_binario_di_ricerca

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install foobar.

## Utilizzo
Creazione di un albero
```c++
#include "bst.hpp"

int main()
{
  // Crea un albero con un naturale
  bst<uint> uintTree(3);
  
  // Aggiungi dei nodi figli
  uintTree.insertValue(2);
  uintTree.insertValue(4);
  
  return 0;
}
```
<p align="left"> <img src="https://komarev.com/ghpvc/?username=giacomo-gobbo&label=Visite&color=ed3535&style=flat" alt="giacomo-gobbo" /> </p>

<h3 align="left">Connect with me:</h3>
<p align="left">
</p>

<h3 align="left">Languages and Tools:</h3>
<p align="left"> <a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> </p>
