#ifndef __bstException_hpp__
#define __bstException_hpp__

#include <exception>
#include <string>

/**
 * @brief Classe per la gestione delle eccezioni provocate da chiavi cercate inesistenti
 * 
 * @param value è il valore della chiave cercata che non è presente nell'albero
*/
class NonExistingValueException : public std::exception
{
private:
    const unsigned int value;
    const bool valueGiven;

public:
    NonExistingValueException() : value{NULL}, valueGiven{false} {} // Costruttore vuoto usato quando non viene fornita la chiave
    NonExistingValueException(const unsigned int inputValue) : value(inputValue), valueGiven{true} {}

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
        return ("The value that throw the exception is " + std::to_string(value));
    }
};

#endif