#ifndef __bstException_hpp__
#define __bstException_hpp__

#include <exception>
#include <string>

#include "accessory.hpp"

/**
 * @brief Classe per la gestione delle eccezioni provocate dalla ricerca di nodi non presenti nell'albero
 *
 * @param value è il valore della chiave del nodo cercato che non è presente nell'albero
 * @param valueGiven indica se è stato fornito il valore della chiave associata al nodo cercato che ha prodotto l'eccezione
 */
class NonExistingValueException : public std::exception
{
private:
    std::string value;
    bool valueGiven;

public:
    /**
     * @brief Costruttore vuoto usato quando non viene fornita la chiave
     *
     */
    NonExistingValueException() : valueGiven{false} {}

    /**
     * @brief Costruttore per l'eccezione con informazioni sul nodo cercato
     *
     * @tparam T è il tipo di dato memorizzato dalla chiave del nodo
     * @param inputValue è il dato memorizzato dalla chiave del nodo
     */
    template <typename T>
    NonExistingValueException(const T inputValue) : value(to_string_adl(inputValue)), valueGiven{true} {}

    /**
     * @brief Resituisce informazioni sull'errore
     *
     * @return stringa con le informazioni sull'errore
     */
    const char *what() const throw()
    {
        return "Value searched does not exist in the tree";
    }

    /**
     * @brief Resituisce informazioni sul valore cercato che ha generato l'errore
     *
     * @return stringa con il valore cercato che ha generato l'errore
     */
    std::string getInfo() const
    {
        if (!valueGiven) // Se non è stato fornito il valore della chiave associato al nodo non presente nell'albero
        {
            return "Uknown illegal value";
        }
        // Se è stato fornito lo si restituisce dentro la stringa
        return ("The value that throw the exception is " + value);
    }
};

#endif