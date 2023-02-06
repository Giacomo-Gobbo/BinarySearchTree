#ifndef __City_hpp__
#define __City_hpp__

#include <iostream>
#include <string>

/**
 * @brief Classe per rappresentare una città
 *
 * @param name è il nome della città
 * @param population è il numero di abitanti della città
 */
class City
{
private:
    std::string name;
    uint population;

public:
    /**
     * @brief Costruttore vuoto
     */
    City() : name{""}, population{0} {}

    /**
     * @brief Costruttore con parametro per il nome della città
     *
     * @param inputName è la stringa che rappresenta il nome della città
     */
    City(std::string inputName) : name{inputName}, population{0} {}

    /**
     * @brief Costruttore con parametro per il nome e la popolazione della città
     *
     * @param inputName è la stringa che rappresenta il nome della città
     * @param inputPopulation è il naturale che rappresenta la popolazione di una città
     */
    City(std::string inputName, uint inputPopulation) : name{inputName}, population{inputPopulation} {}

    /**
     * @brief Ottiene il nome della città
     *
     * @return const std::string è il riferimento alla stringa che rappresenta il nome della città
     */
    inline const std::string &getName() const
    {
        return name;
    }

    /**
     * @brief Ottiene la popolazione della città
     *
     * @return const uint è il riferimento al naturale che rappresenta la popolazione di una città
     */
    inline const uint &getPopulation() const
    {
        return population;
    }
};

/**
 * @brief Overload dell'operatore () per la classe std::less
 * È un "less invertito", cioè considera minori le città con popolazione maggiore
 *
 * @param a prima città da confrontare
 * @param b seconda città da controntare
 * @return true se la popolazione di a è maggiore della popolazione di b
 * @return false se la popolazione di a è minore della popolazione di b
 */
template <>
bool std::less<City>::operator()(const City &a, const City &b) const
{
    return a.getPopulation() > b.getPopulation();
}

/**
 * @brief Overload dell'operatore () per la classe std::greater
 * È un "greater invertito", cioè considera maggiori le città con popolazione minore
 *
 * @param a prima città da confrontare
 * @param b seconda città da controntare
 * @return true se la popolazione di a è minore della popolazione di b
 * @return false se la popolazione di a è maggiore della popolazione di b
 */
template <>
bool std::greater<City>::operator()(const City &a, const City &b) const
{
    return a.getPopulation() < b.getPopulation();
}

/**
 * Stampa il nome di una città su uno stream
 *
 * @param os è lo stream di output
 * @param city è la città da stampare
 * @return è il riferimento allo stream di output
 */
std::ostream &operator<<(std::ostream &os, const City &city)
{
    os << city.getName();
    return os;
}

/**
 * @brief Metodo per ottenere una rappresentazione mediante stringa di un oggetto città
 *
 * @param city è l'istanza della classe città di cui si vuole ricavare una rappresentazione mediante stringa
 * @return std::string
 */
inline std::string to_string(const City &city)
{
    return city.getName();
}

#endif