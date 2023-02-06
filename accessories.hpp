#ifndef __accessories_hpp__
#define __accessories_hpp__

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

#endif