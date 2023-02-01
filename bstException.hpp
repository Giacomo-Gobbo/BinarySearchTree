#ifndef __bstException_hpp__
#define __bstException_hpp__

#include <exception>
#include <string>

/**
 * @brief Funzione per ottenere la rappresentazione in formato stringa
 * Viene invocato il metodo to_string() se std::to_string() non è definito per il tipo T
 *
 * @tparam T è il tipo dell'oggetto di cui ottenere la stringa
 * @param t è l'oggetto di cui ottenere la stringa
 * @return è la stringa ottenuta
 */
template <typename T>
auto to_string_adl(const T &t)
{
    using std::to_string;
    return to_string(t);
}

/**
 * @brief Classe per la gestione delle eccezioni provocate da chiavi cercate inesistenti
 * 
 * @param value è il valore della chiave cercata che non è presente nell'albero
 * @param valueGiven indica se è stato fornito il valore cercato che ha prodotto l'eccezione
*/
class NonExistingValueException : public std::exception
{
private:
    std::string value;
    bool valueGiven;

public:
    NonExistingValueException() : value{NULL}, valueGiven{false} {} // Costruttore vuoto usato quando non viene fornita la chiave
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
        if (!valueGiven) // Se non è stato fornito il valore non presente nell'albero
        {
            return "Uknown illegal value";
        }
        // Se è stato fornito lo si restituisce dentro la stringa
        return ("The value that throw the exception is " + value);
    }
};

#endif