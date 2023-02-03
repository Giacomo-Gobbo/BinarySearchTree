#ifndef __bst_hpp__
#define __bst_hpp__

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "bstException.hpp"

/**
 * @class bst
 *
 * @brief Classe per la rappresentazione degli alberi binari di ricerca.
 * Un albero è definito in modo ricorsivo dal valore della sua radice, dal puntatore al nodo genitore
 * e dai puntatori ai suoi sottoalberi sinistro e destro.
 *
 * Note: in questa classe i termini nodo e albero vengono interscambiati. Nonostante siano entità diverse
 * (un albero è composto da nodi), per come è stata definita la classe un puntatore a bst<T, CMP> indica
 * sia un nodo, perché bst<T, CMP> ha un valore key che è il valore del nodo, sia un albero, perché contiene
 * i puntatori ai nodi (o appunto alberi) figli (si possono pensare come agli archi di un grafo).
 *
 * @tparam key è il valore del nodo
 * @tparam cmp è la relazione d'ordine da utilizzare. È necessario utilizzare un comparatore che esprima la relazione
 * d'ordine di "maggiore" se si vuole ottenere un albero binario ordinato correttamente
 * @param parent è il genitore del nodo
 * @param left è il figlio sinistro del nodo
 * @param right è il figlio destro del nodo
 * @param empty indica la preseza di un valore nel nodo (serve a classificare un nodo vuoto)
 */
template <typename T, typename CMP = std::greater<T>>
class bst
{
private:
    T key;                     // valore del nodo
    class bst<T, CMP> *parent; // puntatore al nodo genitore
    class bst<T, CMP> *left;   // puntatore al nodo figlio sinistro
    class bst<T, CMP> *right;  // puntatore al nodo figlio destro
    bool empty;                // presenza di un valore nel nodo (per classificare il nodo come vuoto)
    CMP cmp;                   // comparatore

    /**
     * @brief Eliminazione di un nodo dall'albero mediante puntatore al nodo da eliminare
     * Sia N il nodo da eliminare, ci sono tre casi possibili:
     * 1 - N è un nodo foglia, il puntatore a N del genitore viene sostituito con nullptr (N.parent non ha più il figlio N)
     *     e quindi N viene rimosso dall'albero.
     * 2 - N ho solo un figlio, il figlio diventa figlio sinistro del genitore di N (se N è il figlio sinistro del suo genitore)
     *     o figlio destro del genitore di N (se N è il figlio destro del suo genitore) e quindi N viene rimosso dall'albero.
     * 3 - N ha entrambi i figli, sia S il successore di N, S prende la posizione di N nell'albero.
     *     Se S è il figlio destro (diretto) di N, allora S sostituisce N e il puntatore al figlio sinistro di S diventa uguale al
     *     puntatore al figlio sinistro di N.
     *     Se S non è il figlio destro immediato di N, allora S viene sostituito dal figlio destro si S e S prende la posizione di N
     *
     * @param keyNode Nodo da eliminare
     */
    void deleteKey(bst<T, CMP> *keyNode);

    /**
     * @brief Sostituzione di un nodo
     *
     * @param nodeA nodo che deve essere sostituito
     * @param nodeB nodo che sostituisce il nodeA
     */
    void nodeChange(bst<T, CMP> *nodeA, bst<T, CMP> *nodeB);

public:
    /**
     * @brief Iteratore costante che previene dalla scrittura del valore puntato
     *
     */
    class const_iterator
    {
    private:
        bst<T> *ptr; //!< puntatore all'elemento associato all'iteratore

        const_iterator(bst<T> *inputPtr) : ptr{inputPtr} {}

    public:
        using iterator_category = std::input_iterator_tag; // categoria di iteratore
        using difference_type = std::ptrdiff_t;            // il tipo della differenza tra iteratori
        using value_type = bst<T>;                         // il valore trattato dall'iteratore
        using pointer = const value_type *;                // il tipo puntatore
        using reference = const value_type &;              // il tipo riferimento

        const_iterator() : ptr{nullptr} {}

        const_iterator &operator++() // operatore di incremento prefisso
        {
            ptr = ptr->successor();
            return *this;
        }
        const_iterator operator++(int) // operatore di incremento postfisso
        {
            const_iterator current{*this}; // copia dell'iteratore corrente
            ptr = ptr->successor();
            return current;
        }

        inline reference operator*() const
        {
            return *ptr;
        }

        inline pointer operator->() const
        {
            return ptr;
        }

        inline bool operator==(const const_iterator &it) const
        {
            return ptr == it.ptr;
        }

        inline bool operator!=(const const_iterator &it) const
        {
            return ptr != it.ptr;
        }

        friend class bst<T>;
    };

    /**
     * @brief Costruttore vuoto
     * Il nodo non punta a genitori o figli e la sua condizione di essere un nodo vuoto è espressa dall'inizializzazione di empty a true.
     * Inoltre anche se ovviamente il membro key presenta un certo valore, questo non viene reso disponibile dalla funzione getKey()
     * e quindi di fatto il nodo è come se non avesso una chiave.
     *
     */
    bst() : parent{nullptr}, left{nullptr}, right{nullptr}, empty{true} {}

    /**
     * @brief Costruttore con passaggio dei parametri per valore
     *
     * @param inputKey è la copia del valore del nodo
     */
    bst(const T &&inputKey) : key{inputKey}, parent{nullptr}, left{nullptr}, right{nullptr}, empty{false} {}

    /**
     * @brief Costruttore con passaggio dei parametri per riferimento
     *
     * @param inputKey è il riferimento al valore del nodo
     */
    bst(const T &inputKey) : key{inputKey}, parent{nullptr}, left{nullptr}, right{nullptr}, empty{false} {}

    /**
     * @brief Costruttore per convertire un array in un albero binario di ricerca
     *
     * @param array che si vuole convertire nell'albero binario di ricerca
     * @param length è la lunghezza dell'array (lvalue)
     */
    bst(const T array[], uint &length) : bst<T, CMP>()
    {
        for (u_int i{0}; i < length; ++i)
        {
            insertValue(array[i]);
        }
    }

    /**
     * @brief Costruttore per convertire un array in un albero binario di ricerca
     *
     * @param array che si vuole convertire nell'albero binario di ricerca
     * @param length è la lunghezza dell'array (rvalue)
     */
    bst(const T array[], uint &&length) : bst<T, CMP>()
    {
        for (u_int i{0}; i < length; ++i)
        {
            insertValue(array[i]);
        }
    }

    /**
     * @brief Costruttore di copia
     * Viene costruito un albero uguale all'albero orig
     *
     * @param orig è il nodo radice dell'albero che si vuole copiare
     */
    bst(const bst<T, CMP> &orig) : bst<T, CMP>()
    {
        if (!orig.isEmpty())
        {
            key = orig.getKey();
            empty = false;
            parent = orig.parent;
            if (orig.left == nullptr) // Se il figlio sinistro non c'è non serve usare l'operatore di copia
            {
                left = nullptr;
            }
            else
            {
                left = new bst<T, CMP>(*(orig.left));
            }
            if (orig.right == nullptr) // Se il figlio destro non c'è non serve usare l'operatore di copia
            {
                right = nullptr;
            }
            else
            {
                right = new bst<T, CMP>(*(orig.right));
            }
        }
    }

    /**
     * @brief Restituisce il valore della radice
     *
     * @return valore della radice
     */
    inline const T &getKey() const
    {
        if (isEmpty())
        {
            throw NonExistingValueException();
        }
        return key;
    }

    /**
     * @brief Restituisce un puntatore al genitore
     *
     * @return puntatore al genitore
     */
    inline bst<T, CMP> *const getParent() const
    {
        return parent;
    }

    /**
     * @brief Restituisce un puntatore al sottoalbero sinistro
     *
     * @return puntatore al sottoalbero sinistro
     */
    inline bst<T, CMP> *const getLeft() const
    {
        return left;
    }

    /**
     * @brief Restituisce un puntatore al sottoalbero destro
     *
     * @return puntatore al sottoalbero destro
     */
    inline bst<T, CMP> *const getRight() const
    {
        return right;
    }

    /**
     * @brief Restituisce true se l'albero è vuoto.
     * Un albero è vuoto se il puntatore a tale albero è un nullptr ovvero che non punta
     * a nulla oppure se punta a un nodo con attributo empty = true
     *
     * @return condizione di verità per l'albero vuoto
     */
    bool isEmpty() const
    {
        if (this == nullptr)
        {
            return true;
        }
        return empty;
    }

    /**
     * @brief Restituisce il puntatore al nodo con l'elemento più piccolo dell'albero
     *
     * @return puntatore al nodo con valore minimo
     */
    bst<T, CMP> *min()
    {
        if (left == nullptr) // Se siamo alla fine del ramo sinistro (dove ci sono i numeri minori per definizione di bst)
        {
            return this;
        }
        else // Se l'albero continua a sinistra
        {
            return left->min();
        }
    }

    /**
     * @brief Restituisce il puntatore al nodo con l'elemento più grande dell'albero
     *
     * @return puntatore al nodo con valore massimo
     */
    bst<T, CMP> *max()
    {
        if (right == nullptr) // Se siamo alla fine del ramo destro (dove ci sono i numeri maggiori per definizione di bst)
        {
            return this;
        }
        else // Se l'albero continua a destra
        {
            return right->max();
        }
    }

    /**
     * @brief Inserisce un valore nell'albero (passaggio per riferimento)
     *
     * @return puntatore al nuovo albero
     */
    bst<T, CMP> *insertValue(const T &value);

    /**
     * @brief Inserisce un valore nell'albero (passaggio per valore)
     *
     * @return puntatore al nuovo albero
     */
    bst<T, CMP> *insertValue(const T &&value);

    /**
     * @brief Visita simmetrica
     * L'albero binario viene visitato partendo dal sottoalbero sinistro continuando con la radice e poi con il sottoalbero destro
     */
    void inorder() const
    {
        if (!isEmpty())
        {
            left->inorder();
            std::cout << key << " ";
            right->inorder();
        }
    }

    /**
     * @brief Visita anticipata
     * L'albero binario viene visitato partendo dalla radice e continuando con il sottoalbero sinistro e poi con il sottoalbero destro
     */
    void preorder() const
    {
        if (!isEmpty())
        {
            std::cout << key << " ";
            left->preorder();
            right->preorder();
        }
    }

    /**
     * @brief Visita posticipata
     * L'albero binario viene visitato partendo dal sottoalbero sinistro continuando con il sottoalbero destro e poi con la radice
     */
    void postorder() const
    {
        if (!isEmpty())
        {
            left->postorder();
            right->postorder();
            std::cout << key << " ";
        }
    }

    /**
     * @brief  Restituisce il puntatore al successore del nodo
     * Il successore di un nodo A è il nodo con la chiave più piccola maggiore di quella di A
     *
     * @return puntatore al nodo successore
     */
    bst<T, CMP> *successor()
    {
        if (right != nullptr)
        {
            return right->min();
        }
        bst<T, CMP> *y = parent;
        bst<T, CMP> *x = this;
        while ((y != nullptr) && (x == y->right))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    /**
     * @brief  Restituisce il puntatore al predecessore del nodo
     * Il predecessore di un nodo A è il nodo con la chiave più grande minore di quella di A
     *
     * @return puntatore al nodo successore
     */
    bst<T, CMP> *predecessor()
    {
        if (left != nullptr)
        {
            return left->max();
        }
        bst<T, CMP> *y = parent;
        bst<T, CMP> *x = this;
        while ((y != nullptr) && (x == y->left))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    /**
     * @brief Contatore dei nodi dell'albero
     *
     * @return resituisce un unsigned int con il valore della quantità di nodi dell'albero
     */
    u_int nodesCount() const
    {
        if (isEmpty()) // Se l'albero è vuoto non ha nodi
        {
            return 0;
        }
        else // Per ogni nodo visitato si somma 1 alle chiamate ricorsive
        {
            return 1 + left->nodesCount() + right->nodesCount();
        }
    }

    /**
     * @brief Contatore delle foglie dell'albero
     *
     * @return resituisce un unsigned int con il valore della quantità di foglie dell'albero
     */
    u_int leavesCount() const
    {
        if (isEmpty()) // Se l'albero è vuoto non ha foglie
        {
            return 0;
        }
        else
        {
            if (left == nullptr && right == nullptr) // Se non ha figli l'albero è un nodo foglia
            {
                return 1;
            }
            else // Se ha figli il numero di foglie è la somma del numero di foglie dei suoi figli
            {
                return left->leavesCount() + right->leavesCount();
            }
        }
    }

    /**
     * @brief Ricerca di un valore nell'albero binario
     * Fornita una chiave viene fornito il puntatore al nodo che ha come attributo key tale chiave.
     * La ricerca è veloce perché è dicotomica, perché in base alla chiave che si sta cercando sappiamo
     * se cercarla nel sottoalbero sinistro o destro, escludendo quindi ogni volta metà albero
     * (non metà chiavi perché non è detto che l'albero sia completo)
     *
     * Note: se la chiave non è presente nell'albero viene lanciato un'eccezione
     *
     * @return puntatore al nodo che presenta la chiave desiderata
     */
    bst<T, CMP> *binarySearch(const T value)
    {
        if (isEmpty()) // Se l'albero/sottoalbero è vuoto
        {
            throw NonExistingValueException(value);
        }
        else
        {
            if (value == key)
            {
                return this;
            }
            else
            {
                if (cmp(value, key)) // In un BST i valori maggiori di un nodo si trovano a sinistra
                {
                    return (right->binarySearch(value));
                }
                else // In un BST i valori minori (o uguali) di un nodo si trovano a destra
                {
                    return (left->binarySearch(value));
                }
            }
        }
    }

    /**
     * @brief Metodo che informa se una certa chiave è presente o meno nell'albero
     *
     * @return valore di verità per la presenza della chiave nell'albero
     */
    bool isPresent(const T value) const
    {
        if (binarySearch(value) == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    /**
     * @brief Metodo per l'eliminazione di un albero/sottoalbero
     * Viene eliminato dal nodo genitore del nodo su cui è chiamato al metodo il puntatore a tale nodo
     */
    void remove()
    {
        if (parent != nullptr) // Se la radice del sottoalbero ha il genitore
        {
            if (this == parent->left) // Se il nodo radice è il figlio sinistro
            {
                parent->left = nullptr; // Elimino il puntatore al figlio sinistro del genitore
            }
            else // Se il nodo radice è il figlio sinistro
            {
                parent->right = nullptr; // Elimino il puntatore al figlio destro del genitore
            }
        }
        delete this;
    }

    /**
     * @brief Eliminazione di un nodo dall'albero mediante chiave del nodo da eliminare
     * Il metodo calcola il puntatore del nodo corrispondente alla chiave fornita e utilizza una funzione ausiliaria
     * per eliminare il nodo che prende in input il puntatore del nodo da eliminare
     *
     * @param key  chiave corrispondente al nodo da eliminare
     */
    void deleteKey(T key)
    {
        deleteKey(binarySearch(key)); // viene chiamata una funzione ausiliare che eliminerà effettivamente il nodo corrispondente alla chiave fornita
    }

    /**
     * @brief Metodo per ottenere l'altezza della classe
     *
     * @return intero senza segno che rappresenta l'altezza
     */
    uint getHeight() const
    {
        if (isEmpty()) // Caso base: non ci sono più nodi
        {
            return 0;
        }
        uint hl{left->getHeight()};     // Calcoliamo l'altezza del ramo di sinistra
        uint hr{right->getHeight()};    // Calcoliamo l'altezza del ramo di destra
        return 1 + (hl < hr ? hr : hl); // E confrontiamoli prendendo il maggiore e sommandoci 1 per il nodo corrente
    }

    /**
     * @brief Metodo per rappresentare un albero sotto forma di matrice
     * Si calcola la posizione del nodo radice all'interno della matrice e poi si richiama il metodo
     * sul nodo sinistro e destro in modo ricorsivo per posizionare i nodi figli
     *
     * @param matrix riferimento a matrice in cui fornire il risultato
     * @param level livello dell'albero (da 0 fino all'altezza dell'albero)
     * @param offset offset da sinistra per posizionare il nodo nella matrice
     * @param width larghezza (in colonne) dell'albero nella matrice
     */
    void fillMatrix(std::vector<std::vector<std::string>> &matrix, uint level, uint offset, uint width) const
    {
        if (isEmpty())
        {
            return;
        }
        matrix[level][(offset + width) / 2] = to_string_adl(key);              // Inserisco il nodo radice
        left->fillMatrix(matrix, level + 1, offset, (offset + width) / 2);     // Riempio la matrice con il sottoalbero sinistro
        right->fillMatrix(matrix, level + 1, (offset + width + 1) / 2, width); // Riempio la matrice con il sottoalbero destro
    }

    /**
     * @brief Metodo che restituisce il primo valore dell'albero (si prende il minimo)
     *
     * @return const_iterator è il puntatore al primo valore dell'albero
     */
    inline const_iterator begin()
    {
        return const_iterator{min()};
    }

    /**
     * @brief Metodo che restituisce l'ultimo valore dell'albero (si prende il massimo)
     *
     * @return const_iterator è il puntatore all'ultimo puntatore dell'albero
     */
    inline const_iterator end()
    {
        return const_iterator{max()};
    }

    ~bst()
    {
        delete left;
        delete right;
    }
};

template <typename T, typename CMP>
bst<T, CMP> *bst<T, CMP>::insertValue(const T &value)
{
    if (isEmpty())
    {
        if (this != nullptr) // Se l'albero è stato realizzato dal costruttore vuoto
        {
            empty = false;
            key = value; // inizializza valore della chiave
            return this;
        }
        else // Se l'albero è vuoto e non punta a nulla
        {
            return new bst<T, CMP>(value); // Restituisce un albero creato con il value come radice
        }
    }
    else
    {
        if (cmp(value, key)) // Se il valore da inserire è maggiore della chiave del nodo
        {
            right = right->insertValue(value); // Inserisci valore nel sottoalbero destro
            right->parent = this;
            return this;
        }
        else // Se il valore da inserire è minore (o uguale) della chiave del nodo
        {
            left = left->insertValue(value); // Inserisci valore nel sottoalbero sinistro
            left->parent = this;
            return this;
        }
    }
}

template <typename T, typename CMP>
bst<T, CMP> *bst<T, CMP>::insertValue(const T &&value)
{
    if (isEmpty())
    {
        if (this != nullptr) // Se l'albero è stato realizzato dal costruttore vuoto
        {
            empty = false;
            key = value; // inizializza valore della chiave
            return this;
        }
        else // Se l'albero è vuoto e non punta a nulla
        {
            return new bst<T, CMP>(value); // Restituisce un albero creato con il value come radice
        }
    }
    else
    {
        if (cmp(value, key)) // Se il valore da inserire è maggiore della chiave del nodo
        {
            right = right->insertValue(value); // Inserisci valore nel sottoalbero destro
            right->parent = this;
            return this;
        }
        else // Se il valore da inserire è minore (o uguale) della chiave del nodo
        {
            left = left->insertValue(value); // Inserisci valore nel sottoalbero sinistro
            left->parent = this;
            return this;
        }
    }
}

template <typename T, typename CMP>
void bst<T, CMP>::deleteKey(bst<T, CMP> *keyNode)
{
    if (keyNode->left == nullptr) // Se non ha un figlio sinistro
    {
        nodeChange(keyNode, keyNode->right); // Il figlio destro prende il suo posto
    }
    else if (keyNode->right == nullptr) // Se non ha un figlio destro
    {
        nodeChange(keyNode, keyNode->left); // Il figlio sinistro prende il suo posto
    }
    else // Se ha entrambi i figli
    {
        bst<T, CMP> *S{keyNode->successor()};
        if (S->parent != keyNode) // Se il successore non è il figlio del nodo da eliminare
        {
            nodeChange(S, S->right);   // Il figlio destro sostituisce il successore
            S->right = keyNode->right; // Il nuovo figlio del successore diventa il figlio destro del nodo da eliminare
            S->right->parent = S;      // Aggiorno il puntatore al genitore per il nuovo figlio
        }
        nodeChange(keyNode, S); // Unisco il sottoalbero sinistro del nodo eliminato al successore
        S->left = keyNode->left;
        S->left->parent = S;
    }
    keyNode->left = nullptr;  // È necessario eliminare i puntatori ai figli (che adesso non riconoscono più keyNode come padre)
    keyNode->right = nullptr; // altrimenti verrano erroneamente eliminati dal distruttore
    delete keyNode;
}

template <typename T, typename CMP>
void bst<T, CMP>::nodeChange(bst<T, CMP> *nodeA, bst<T, CMP> *nodeB)
{
    if (nodeA->parent == nullptr) // Se nodeA è la root
    {
        nodeA = nodeB; // nodeB diventa la nuova root
    }
    else if (nodeA == nodeA->parent->left) // Se nodeA è il figlio sinistro
    {
        nodeA->parent->left = nodeB; // nodeB diventa il nuovo figlio sinistro del genitore di nodeA
    }
    else // Se nodeA è il figlio destro
    {
        nodeA->parent->right = nodeB; // nodeB diventa il nuovo figlio destro del genitore di nodeA
    }
    if (!nodeB->isEmpty()) // Se nodeB non è un nullptr posso aggiornare le sue informazioni sul genitore
    {
        nodeB->parent = nodeA->parent; // il genitore di nodeB è il genitore di nodeA
    }
}

/**
 * @brief Funzione per stampare una matrice
 *
 * @param os è lo stream su cui stampare
 * @param matrix è la matrice da stampare a video
 * @return std::ostream& è un riferimento allo stream su cui si è stampato
 */
std::ostream &printMatrix(std::ostream &os, const std::vector<std::vector<std::string>> &matrix)
{
    for (uint i{0}; i < matrix.size(); ++i)
    {
        for (uint j{0}; j < matrix[i].size(); ++j)
        {
            os << matrix[i][j] << " ";
        }
        os << std::endl; // Fine della riga i
    }
    return os;
}

/**
 * @brief Stampare un albero binario
 * L'albero viene salvato in una matrice [m x n] con numero di righe m uguale all'altezza dell'albero binario
 * e numero di colonne n un numero dispari. La radice viene posizionato in posizione [0, roundInf(n/2)]
 * ovvero nella prima riga e nella colonna centrale. La colonna e la riga della radice divide la matrice in due zone:
 * - zona sinistra, conterrà il sottoalbero sinistro
 * - zona destra, conterrà il sottoalbero destro
 * La rappresentazione dei sottoalberi avviene in modo ricorsivo
 *
 * @tparam T è il tipo di elementi dell'albero
 * @tparam CMP è la relazione d'ordine degli elementi dell'albero
 * @param os è lo stream su cui stampare
 * @param tree è l'albero da stampare
 * @return std::ostream& è un riferimento allo stream su cui abbiamo stampato
 */
template <typename T, typename CMP>
std::ostream &operator<<(std::ostream &os, const bst<T, CMP> &tree)
{
    if (tree.isEmpty())
    {
        std::cout << "Albero vuoto" << std::endl;
    }
    uint h{tree.getHeight()};                                                              // altezza dell'albero
    uint leaves{(uint)((1 << h) - 1)};                                                     // numero massimo di nodi dell'ultimo livello. Viene calcolato come 2^h - 1
    std::vector<std::vector<std::string>> matrix(h, std::vector<std::string>(leaves, "")); // creo una matrice [h x leaves]
    tree.fillMatrix(matrix, 0, 0, leaves);
    return printMatrix(os, matrix);
}

#endif