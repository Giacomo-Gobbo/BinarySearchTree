#ifndef __bst_hpp__
#define __bst_hpp__

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "bstException.hpp"
#include "accessory.hpp"

/**
 * @class bst
 *
 * @brief Classe per la rappresentazione degli alberi binari di ricerca.
 * Un albero è definito in modo ricorsivo dal valore della sua radice, dal puntatore al nodo genitore (se è un sottoalbero)
 * e dai puntatori ai suoi sottoalberi sinistro e destro.
 *
 * Nota: in questa classe i termini nodo e albero vengono interscambiati. Nonostante siano entità diverse
 * (un albero è composto da nodi), per come è stata definita la classe un puntatore a bst<T, CMP> indica
 * sia un nodo, perché bst<T, CMP> ha un valore key che è il valore del nodo, sia un albero, perché contiene
 * i puntatori ai nodi (o appunto alberi) figli. Un oggetto bst<T, CMP> si può quindi pensare o come a un albero
 * o coma a un nodo più i suoi archi.
 *
 * @tparam T è il tipo di dato delle chiavi associate ai nodi
 * @tparam CMP è la relazione d'ordine del tipo T
 *
 * @param key è il valore dela chiave associata al nodo
 * @param parent è il puntatore al genitore del nodo
 * @param left è il puntatore al figlio sinistro del nodo
 * @param right è il untatore al figlio destro del nodo
 * @param empty indica la presenza di un valore nel nodo (true se non è presente, false se è presente) per classificare i nodo vuoti
 * @param cmp è la relazione d'ordine da utilizzare. È necessario utilizzare un comparatore che esprima la relazione
 * d'ordine di "maggiore" se si vuole ottenere un albero binario ordinato correttamente
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
     *
     * Sia N il nodo da eliminare, ci sono tre casi possibili:
     * -# N è un nodo foglia; il puntatore a N del genitore viene sostituito con nullptr (N.parent non ha più il figlio N)
     *    e quindi N viene rimosso dall'albero.
     * -# N ha solo un figlio; il figlio diventa figlio sinistro del genitore di N (se N è il figlio sinistro del suo genitore)
     *    o figlio destro del genitore di N (se N è il figlio destro del suo genitore) e quindi N viene rimosso dall'albero.
     * -# N ha entrambi i figli; sia S il successore di N, S prende la posizione di N nell'albero.
     *    Se S è il figlio destro (diretto) di N, allora S sostituisce N e il puntatore al figlio sinistro di S diventa uguale al
     *    puntatore al figlio sinistro di N.
     *    Se S non è il figlio destro immediato di N, allora S viene sostituito dal figlio destro si S e S prende la posizione di N
     *
     * @param keyNode puntatore al nodo da eliminare
     */
    void deleteKey(bst<T, CMP> *keyNode);

    /**
     * @brief Sostituzione di un nodo
     *
     * @param nodeA puntatore al nodo che deve essere sostituito
     * @param nodeB puntatore al nodo che sostituisce il nodeA
     */
    void nodeChange(bst<T, CMP> *nodeA, bst<T, CMP> *nodeB);

public:
    /**
     * @brief Iteratore costante per un albero binario di ricerca
     * 
     * Non viene fornito un iteratore non costante perché non è permessa la scrittura in un albero binario di ricerca
     * (bisogna mantenere l'ordinamento)
     */
    class const_iterator
    {
    private:
        bst<T> *ptr; // puntatore all'elemento associato all'iteratore

        /**
         * @brief Costruttore privato
         *
         * @param inputPtr è il puntatore da associare all'iteratore
         */
        const_iterator(bst<T> *inputPtr) : ptr{inputPtr} {}

    public:
        using iterator_category = std::input_iterator_tag; // categoria di iteratore (nota: in realtà è un'estensione di un operatore di input
                                                           // con funzionalità di un operatore ad accesso casuale)
        using difference_type = std::ptrdiff_t;            // il tipo della differenza tra iteratori
        using value_type = bst<T>;                         // il valore trattato dall'iteratore
        using pointer = const value_type *;                // il tipo puntatore
        using reference = const value_type &;              // il tipo riferimento

        /**
         * @brief Costruttore vuoto pubblico
         */
        const_iterator() : ptr{nullptr} {}

        /**
         * @brief Operatore di incremento prefisso
         *
         * @return const_iterator& restituisce il riferimento al successivo elemento
         */
        const_iterator &operator++()
        {
            ptr = ptr->successor();
            return *this;
        }

        /**
         * @brief Operatore di incremento postfisso
         *
         * @return const_iterator è una copia dell'iteratore precedente all'incremento
         */
        const_iterator operator++(int)
        {
            const_iterator current{*this}; // copia dell'iteratore corrente
            ptr = ptr->successor();
            return current;
        }

        /**
         * @brief Operatore di decremento prefisso
         *
         * @return const_iterator& è il riferimento al precedente elemento
         */
        const_iterator &operator--()
        {
            ptr = ptr->predecessor();
            return *this;
        }

        /**
         * @brief Operatore di decremento postfisso
         *
         * @return const_iterator è una copia dell'iteratore precedente all'incremento
         */
        const_iterator operator--(int)
        {
            const_iterator current{*this}; // copia dell'iteratore corrente
            ptr = ptr->predecessor();
            return current;
        }

        /**
         * @brief Overload dell'operatore somma per un iteratore
         *
         * @param i è l'incremento dell'indice
         * @return const_iterator& è il riferimento all'elemento i-esimo a partire da quello corrente
         */
        const_iterator &operator+(uint i)
        {
            while (i > 0)
            {
                ++(*this);
                --i;
            }
            return *this;
        }

        /**
         * @brief Overload dell'operatore differenza per un iteratore
         *
         * @param i è il decremento dell'indice
         * @return const_iterator& è il riferimento all'elemento in i posizioni precedenti
         */
        const_iterator &operator-(uint i)
        {
            while (i > 0)
            {
                --(*this);
                --i;
            }
            return *this;
        }

        const_iterator &operator+=(uint i)
        {
            while (i > 0)
            {
                ++(*this);
                --i;
            }
            return *this;
        }

        const_iterator &operator-=(uint i)
        {
            while (i > 0)
            {
                --(*this);
                --i;
            }
            return *this;
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
     *
     * Il nodo non punta a genitori o figli e la sua condizione di essere un nodo vuoto è espressa dall'inizializzazione di empty a true.
     * Ovviamente il membro key presenta un certo valore, ma questo non viene reso disponibile dalla funzione getKey()
     * e quindi di fatto il nodo è come se il nodo non avesse una chiave.
     */
    bst() : parent{nullptr}, left{nullptr}, right{nullptr}, empty{true} {}

    /**
     * @brief Costruttore con passaggio dei parametri per riferimento
     *
     * @param inputKey è il riferimento al valore del nodo
     */
    bst(const T &inputKey) : key{inputKey}, parent{nullptr}, left{nullptr}, right{nullptr}, empty{false} {}

    /**
     * @brief Costruttore con passaggio dei parametri per valore
     *
     * @param inputKey è la copia del valore del nodo
     */
    bst(const T &&inputKey) : key{inputKey}, parent{nullptr}, left{nullptr}, right{nullptr}, empty{false} {}

    /**
     * @brief Costruttore per convertire un array in un albero binario di ricerca
     *
     * Gli elementi vengono inseriti in ordine dall'elemento in posizione zero dell'array, quindi è preferibile un array
     * di input non ordinato in modo da non ottenere un albero completamente sbilanciato.
     *
     * @param array che si vuole convertire nell'albero binario di ricerca
     * @param length è il riferimento alla lunghezza dell'array
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
     * Gli elementi vengono inseriti in ordine dall'elemento in posizione zero dell'array, quindi è preferibile un array
     * di input non ordinato in modo da non ottenere un albero completamente sbilanciato.
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
     * Viene costruito un albero uguale all'albero puntato da orig
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
     * @brief Restituisce il valore della chiave del nodo
     *
     * @return const T& è il valore della chiave del nodo
     */
    inline const T &getKey() const
    {
        if (isEmpty()) // Se è vuoto sicuramente non è presente il valore cercato
        {
            throw NonExistingValueException();
        }
        return key;
    }

    /**
     * @brief Restituisce un puntatore al genitore
     *
     * @return puntatore al nodo genitore
     */
    inline bst<T, CMP> *const getParent() const
    {
        return parent;
    }

    /**
     * @brief Restituisce un puntatore al sottoalbero sinistro
     *
     * @return puntatore al nodo figlio sinistro
     */
    inline bst<T, CMP> *const getLeft() const
    {
        return left;
    }

    /**
     * @brief Restituisce un puntatore al sottoalbero destro
     *
     * @return puntatore al nodo figlio destro
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
     * @return true se l'albero è vuoto
     * @return false se l'albero ha almeno un nodo
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
    bst<T, CMP> *const min()
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
    bst<T, CMP> *const max()
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
     * @brief Funzione ausiliaria di insertValue() per inserire un nodo nel sottoalbero sinistro di un nodo
     *
     * @param node è l'albero su cui si sta aggiungendo il nodo
     * @param value è il valore del nodo da aggiungere
     * @return bst<T, CMP>* puntatore all'albero aggiornato con il nuovo nodo
     */
    static bst<T, CMP> *insertLeft(bst<T, CMP> *node, const T &value);

    /**
     * @brief Funzione ausiliaria di insertValue() per inserire un nodo nel sottoalbero destro di un nodo
     *
     * Aggiorna il sottoalbero destro di node con il nuovo nodo
     *
     * @param node è l'albero su cui si sta aggiungendo il nodo
     * @param value è il valore del nodo da aggiungere
     * @return bst<T, CMP>* puntatore all'albero aggiornato con il nuovo nodo
     */
    static bst<T, CMP> *insertRight(bst<T, CMP> *node, const T &value);

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
     * @brief Restituisce il puntatore al successore del nodo
     * Il successore di un nodo A è il nodo con la chiave più piccola maggiore di quella di A
     *
     * @return puntatore al nodo successore
     */
    bst<T, CMP> *const successor()
    {
        if (right != nullptr)
        {
            return right->min();
        }
        if (parent == nullptr) // Se il nodo è radice e non ha un ramo destro allora non c'è il successore
        {
            throw NonExistingValueException();
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
     * @brief Restituisce il puntatore al predecessore del nodo
     * Il predecessore di un nodo A è il nodo con la chiave più grande minore di quella di A
     *
     * @return puntatore al nodo successore
     */
    bst<T, CMP> *const predecessor()
    {
        if (left != nullptr)
        {
            return left->max();
        }
        if (parent == nullptr) // Se il nodo è radice e non ha un ramo sinistro allora non c'è il predecessore
        {
            throw NonExistingValueException();
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
     * @return restituisce un naturale che esprime il numero di nodi dell'albero
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
     * @return resituisce un naturale che esprime il numero di foglie dell'albero
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
     *
     * Fornita una chiave viene fornito il puntatore al nodo che ha come valore dell' attributo key tale chiave.
     * La ricerca è veloce perché è dicotomica, ovvero in base alla chiave che si sta cercando sappiamo
     * se si trova nel sottoalbero sinistro o destro, escludendo quindi ogni volta un ramo dell'albero
     * (non metà chiavi perché non è detto che l'albero sia completo). @n
     * Note: se la chiave non è presente nell'albero viene lanciata un'eccezione.
     *
     * @return puntatore al nodo che presenta la chiave desiderata
     */
    bst<T, CMP> *const binarySearch(const T value)
    {
        if (isEmpty()) // Se l'albero/sottoalbero è vuoto
        {
            throw NonExistingValueException(value);
        }
        else
        {
            if (value == key) // Nodo trovato
            {
                return this;
            }
            else
            {
                if (cmp(value, key)) // In un BST i nodi con valori maggiori si trovano a destra
                {
                    return (right->binarySearch(value));
                }
                else // In un BST i nodi con valori minori (o uguali) di un nodo si trovano a sinistra
                {
                    return (left->binarySearch(value));
                }
            }
        }
    }

    /**
     * @brief Metodo che informa se è presente nell'albero un nodo (almeno uno) con un determinato valore della chiave
     *
     * @return true se il nodo è presente nell'albero
     * @return false se il nodo non è presente nell'albero
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
     *
     * Il genitore del nodo su cui è chiamato il metodo non lo considera più suo figlio (diventa nullptr)
     * e si libera la memoria occupata dal nodo
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
     * @brief Eliminazione del nodo associato a una determinata chiave dall'albero
     *
     * Il metodo calcola il puntatore del nodo corrispondente alla chiave fornita e utilizza una funzione ausiliaria
     * per eliminare il nodo che prende in input il puntatore di tale nodo
     *
     * @param key chiave corrispondente al nodo da eliminare
     */
    void deleteKey(T key)
    {
        deleteKey(binarySearch(key)); // viene chiamata una funzione ausiliaria che eliminerà effettivamente il nodo corrispondente alla chiave fornita
    }

    /**
     * @brief Metodo per ottenere l'altezza dell'albero
     *
     * @return naturale che rappresenta il numero di livelli dell'albero (altezza)
     */
    uint height() const
    {
        if (isEmpty()) // Caso base: non ci sono più nodi
        {
            return 0;
        }
        uint hl{left->height()};        // Calcoliamo l'altezza del ramo di sinistra
        uint hr{right->height()};       // Calcoliamo l'altezza del ramo di destra
        return 1 + (hl < hr ? hr : hl); // E confrontiamoli prendendo il maggiore e sommandoci 1 per il nodo corrente
    }

    /**
     * @brief Metodo per rappresentare un albero sotto forma di matrice
     *
     * Si calcola la posizione del nodo radice all'interno della matrice (centrato rispetto alle colonne e sulla prima riga)
     * e successivamente si richiama il metodo sul nodo sinistro e destro in modo ricorsivo per posizionare i nodi figli
     *
     * @param matrix riferimento alla matrice in cui vogliamo salvare l'albero
     * @param level livello dell'albero
     * @param offset offset da sinistra per posizionare il nodo nella matrice
     * @param width larghezza (in colonne) dell'albero/sottoalbero nella matrice
     */
    void fillMatrix(std::vector<std::vector<std::string>> &matrix, uint level, uint offset, uint width) const
    {
        if (!isEmpty())
        {
            matrix[level][(offset + width) / 2] = to_string_adl(key);              // Inserisco il nodo radice
            left->fillMatrix(matrix, level + 1, offset, (offset + width) / 2);     // Riempio la matrice con il sottoalbero sinistro
            right->fillMatrix(matrix, level + 1, (offset + width + 1) / 2, width); // Riempio la matrice con il sottoalbero destro
        }
    }

    /**
     * @brief Metodo che restituisce l'iteratore corrispondente al primo valore dell'albero (si prende il minimo)
     *
     * @return const_iterator è l'iteratore corrispondente al primo valore dell'albero
     */
    inline const_iterator begin()
    {
        return const_iterator{min()};
    }

    /**
     * @brief Metodo che restituisce l'iteratore corrispondente all'ultimo valore dell'albero (si prende il massimo)
     *
     * @return const_iterator è l'iteratore corrispondente all'ultimo puntatore dell'albero
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
            empty = false; // Non è più vuoto
            key = value;   // inizializza valore della chiave
            return this;
        }
        else // Se l'albero è vuoto e non punta a nulla
        {
            return new bst<T, CMP>(value); // Restituisce un albero creato con value come chiave associata alla radice
        }
    }
    else
    {
        if (cmp(value, key))                 // Se il valore da inserire è maggiore della chiave del nodo
            return insertRight(this, value); // Inserisci valore nel sottoalbero destro
        else                                 // Se il valore da inserire è minore (o uguale) della chiave del nodo
            return insertLeft(this, value);  // Inserisci valore nel sottoalbero sinistro
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
        if (cmp(value, key))                 // Se il valore da inserire è maggiore della chiave del nodo
            return insertRight(this, value); // Inserisci valore nel sottoalbero destro
        else                                 // Se il valore da inserire è minore (o uguale) della chiave del nodo
            return insertLeft(this, value);  // Inserisci valore nel sottoalbero sinistro
    }
}

template <typename T, typename CMP>
bst<T, CMP> *bst<T, CMP>::insertLeft(bst<T, CMP> *node, const T &value)
{
    node->left = node->left->insertValue(value); // Inserisci valore nel sottoalbero sinistro
    node->left->parent = node;
    return node;
}

template <typename T, typename CMP>
bst<T, CMP> *bst<T, CMP>::insertRight(bst<T, CMP> *node, const T &value)
{
    node->right = node->right->insertValue(value); // Inserisci valore nel sottoalbero destro
    node->right->parent = node;
    return node;
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
 * @brief Stampare un albero binario
 *
 * L'albero viene salvato in una matrice [m x n] con numero di righe m uguale all'altezza dell'albero binario
 * e numero di colonne n dispari, pari al numero di foglie dell'ultimo livello fosse completo più uno.
 * La radice viene posizionata in posizione [0, roundInf(n/2)] ovvero nella prima riga e nella colonna centrale.
 * La colonna e la riga della radice divide la matrice in due zone:
 * #- zona sinistra, conterrà il sottoalbero sinistro
 * #- zona destra, conterrà il sottoalbero destro
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
    uint h{tree.height()};                                                                     // altezza dell'albero
    uint leaves{(uint)(1 << h)};                                                               // numero massimo di nodi dell'ultimo livello. Viene calcolato come 2^h - 1
    std::vector<std::vector<std::string>> matrix(h, std::vector<std::string>(leaves + 1, "")); // creo una matrice [h x leaves]
    tree.fillMatrix(matrix, 0, 0, leaves);                                                     // riempo la matrice
    return printMatrix(os, matrix);
}

#endif