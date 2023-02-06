#ifndef __accessory_hpp__
#define __accessory_hpp__

#include <vector>
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
 * @brief Funzione per stampare una matrice
 *
 * @param os è lo stream su cui stampare
 * @param matrix è la matrice da stampare a video
 * @return std::ostream& è un riferimento allo stream su cui si è stampato
 */
std::ostream &printMatrix(std::ostream &os, const std::vector<std::vector<std::string>> &matrix)
{
    std::cout << std::endl;
    for (uint i{0}; i < matrix.size(); ++i)
    {
        for (uint j{0}; j < matrix[i].size(); ++j)
        {
            os << matrix[i][j] << " ";
        }
        os << std::endl; // Fine della i-esima riga
    }
    return os;
}

#endif