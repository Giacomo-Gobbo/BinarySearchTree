#ifndef __City_hpp__
#define __City_hpp__

#include <iostream>
#include <string>

/**
 * @brief Classe per rappresentare una città
 * 
 * @param name è il nome della città
 * @param population è il numero di abitanti della città * 
 */
class City
{
private:
    std::string name;
    uint population;

public:
    City() : name{""}, population{0} {}
    City(std::string inputName) : name{inputName}, population{0} {}
    City(std::string inputName, uint inputPopulation) : name{inputName}, population{inputPopulation} {}

    /**
     * @brief Ottiene il nome della città
     * 
     * @return const std::string 
     */
    inline const std::string getName() const
    {
        return name;
    }

    /**
     * @brief Ottiene la popolazione della città
     * 
     * @return const uint 
     */
    inline const uint getPopulation() const
    {
        return population;
    }
};

/**
 * @brief Overload dell'operatore ()
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
 * @brief Overload dell'operatore ()
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
 * @brief Metodo per ottenere una stringa di un oggetto città
 * 
 * @param city è la città di cui si vuole ricavare la stringa
 * @return std::string 
 */
inline std::string to_string(const City &city)
{
    return city.getName();
}

#endif