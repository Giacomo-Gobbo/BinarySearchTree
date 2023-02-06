#include "bst.hpp"
#include "City.hpp"

void testBST_1();
void testBST_2();
void testBST_City();
void testBST_Iterator();

/**
 * @brief Programma di prova per testare la classe bst
 * Sono definite le seguenti funzioni di prova:
 * 1 - testBST_1() per creare un albero binario di naturali e visitarlo in modo simmetrico, anticipato e posticipato
 * 2 - testBST_2() per creare un albero binario di interi e visualizzarlo graficamente
 * 3 - testBST_City() per creare un albero binario di città
 */
int main()
{
    testBST_1();
    // testBST_City();
    try
    {
        // testBST_2();
    }
    catch (const NonExistingValueException &e) // Gestione dell'eccezione
    {
        std::cerr << "e.what() :  " << e.what() << std::endl;
        std::cerr << "e.getInfo() :  " << e.getInfo() << std::endl;
    }
    // testBST_Iterator();

    return 0;
}

void testBST_1()
{
    uint intArray[] = {8, 3, 2, 5, 6, 12, 15};

    bst<uint> binSearchTree;

    for (u_int i{0}; i < 7; ++i)
    {
        binSearchTree.insertValue(intArray[i]);
    }

    std::cout << "Nodi totali: " << binSearchTree.nodesCount() << std::endl;
    std::cout << "Nodi foglia: " << binSearchTree.leavesCount() << std::endl;
    std::cout << "Altezza albero: " << binSearchTree.height() << std::endl;

    std::cout << binSearchTree << std::endl;

    std::cout << "Inorder visit: " << std::endl;
    binSearchTree.inorder();
    std::cout << "\nPreorder visit: " << std::endl;
    binSearchTree.preorder();
    std::cout << "\nPostorder visit: " << std::endl;
    binSearchTree.postorder();
    std::cout << "\n";
    std::cout << std::endl;
}

void testBST_2()
{
    int intArray[] = {8, 3, 8, 2, 5, 6, 12, 15, 13, 18, 16, -2, -1, -10};

    bst<int> bst_example(intArray, sizeof(intArray) / sizeof(intArray[0]));

    std::cout << "min() = " << bst_example.min()->getKey() << std::endl;
    std::cout << "max() = " << bst_example.max()->getKey() << std::endl;

    std::cout << bst_example;

    bst<int> bstNew(bst_example); // Utilizzo il costruttore di copia

    // bst_example.deleteKey(14); // Errore!!! 14 non è presente nell'albero
    bst_example.deleteKey(15); // Elimino il nodo con chiave 15 solo in bst_example

    std::cout << bst_example
              << "Albero copiato: " << std::endl;
    std::cout << bstNew; // bstNew resta invariato
}

void testBST_City()
{
    City cities[] = {City("Noventa di Piave", 6984),
                     City("Tokyo", 13960000),
                     City("New York", 8468000),
                     City("Roma", 2873000),
                     City("Londra", 8799800),
                     City("Hong Kong", 7413000),
                     City("Parigi", 2229095),
                     City("Singapore", 5454000),
                     City("Madrid", 3223000),
                     City("Dubai", 3331000)};

    bst<City> bstCity(cities, sizeof(cities) / sizeof(cities[0]));

    std::cout << "min() = " << bstCity.min()->getKey() << std::endl;
    std::cout << "max() = " << bstCity.max()->getKey() << std::endl;

    std::cout << bstCity;
}

template <typename T>
void const_rvalue_iterator(bst<T> &tree)
{
    std::cout << "Stampa dell'albero tramite iteratori: ";
    for (auto &elem : tree) // È presente l'iteratore di input quindi è possibile questa sintassi compatta
    {
        std::cout << elem.getKey() << " ";
    }
    std::cout << std::endl;
}

void testBST_Iterator()
{
    int intArray[] = {8, 3, 8, 2, 5, 6, 12, 15, 13, 18, 16, -2, -1, -10};

    bst<int> bst_example(intArray, sizeof(intArray) / sizeof(intArray[0]));

    std::cout << "bst_example:\n"
              << bst_example << std::endl;

    const_rvalue_iterator(bst_example);

    bst_example.getLeft()->remove();
    std::cout << "bst_example senza ramo sinistro:\n"
              << bst_example << std::endl;
}

// METTIAMOLA NEL README
/** @mainpage Presentazione del progetto
 *
 * @author Giacomo Gobbo
 *
 * @date 25.jan.2023 - 6.feb.2023
 *
 * @section A Caratteristiche di un albero di ricerca binario
 *
 * Un albero di ricerca binaria (BST), anche chiamato albero binario ordinato, è un albero binario con radice in cui
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
 * 
 * @subsection BD accessory.hpp
 * Contiene funzioni utilizzate dalla classe bst, ma non specifiche degli alberi binari di ricerca
 */