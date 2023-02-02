# BinarySearchTree
Implementazione in c++ per gli alberi di ricerca binaria

## Installation

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install foobar.

```bash
pip install foobar
```

## Usage

```python
import foobar

# returns 'words'
foobar.pluralize('word')

# returns 'geese'
foobar.pluralize('goose')

# returns 'phenomenon'
foobar.singularize('phenomena')
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
/** @mainpage Presentazione del progetto
 *
 * @author Giacomo Gobbo
 *
 * @date 25.jan.2023 - 6.feb.2023
 *
 * @section A Caratteristiche di un albero di ricerca binario
 *
 * Un albero di ricerca binaria (BST), anche chiamato albero binario ordinato, è una albero binario con radice in cui
 * le chiavi di ogni suo nodo sono maggiori di tutte le chiavi nei rispettivi nodi del sottoalbero sinistro e minore di
 * quelli del sottoalbero destro. La complessità delle operazioni di ricerca nel BST sono direttamente proporzionali all'altezza dell'albero
 * e quindi i BST permettono inserimenti e rimozioni rapide di dati.
 * Le prestazioni di un BST dipendono dall'ordine di inserimento dei nodi nell'albero, e la complessità nel caso medio per
 * l'inserimento, la ricerca e l'eliminazione è Olog(n) per n nodi. Nel caso peggiore un BST si comporta come una lista concatenata (complessità O(n)).
 *
 * Operazione    | Complessità al caso pessimo | Complessità al caso medio
 * ------------- | ------------- | -------------
 * Visita        | O(n)          | O(n)
 * Ricerca       | O(n)          | O(h)
 * Inserimento   | O(n)          | O(h)
 * Cancellazione | O(n)          | O(h)
 *
 * Maggiori informazioni su: https://it.wikipedia.org/wiki/Albero_binario_di_ricerca
 *
 *
 * @image html example.png Esempio di un BST con 9 nodi e alto 4
 *
 * @section B Elenco dei file presenti
 *
 * @subsection BA bst.hpp
 * Contiene il codice sorgente dell'implementazione di un albero binario di ricerca
 *
 * @subsection BB City.hpp
 * Contiene il codice sorgente per implementare una classe che rappresenti una città
 *
 * @subsection BC bstException.hpp
 * Contiene il codice sorgente per implementare una classe che estende std::exception utile per gestire eccezioni in un oggetto BST
 */
