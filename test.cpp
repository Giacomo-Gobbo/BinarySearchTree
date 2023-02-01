#include "bst.hpp"
#include "bstException.hpp" // include superfluo
#include "City.hpp"

void testBST_1();
void testBST_2();
void testBST_City();

/**
 * @brief Programma di prova per testare la classe bst
 * Sono definite le seguenti funzioni di prova:
 * 1 - testBST_1() per creare un albero binario di naturali e visitarlo in modo simmetrico, anticipato e posticipato
 * 2 - testBST_2() per creare un albero binario di interi e visualizzarlo graficamente
 * 3 - testBST_City() per creare un albero binario di città
 */
int main()
{
    // testBST_1();
    // testBST_2();
    try
    {
        testBST_2();
    }
    catch (const NonExistingValueException &e) // Gestione dell'eccezione
    {
        std::cerr << "e.what() :  " << e.what() << std::endl;
        std::cerr << "e.getInfo() :  " << e.getInfo() << std::endl;
    }

    return 0;
}

void testBST_1()
{
    uint intArray[] = {8, 3, 2, 5, 6, 12, 15, 13, 18, 16};

    bst<uint> binSearchTree;

    for (u_int i{0}; i < 7; ++i)
    {
        binSearchTree.insertValue(intArray[i]);
    }
    std::cout << "Inorder: " << std::endl;
    binSearchTree.inorder();
    std::cout << "\nPreorder: " << std::endl;
    binSearchTree.preorder();
    std::cout << "\nPostorder: " << std::endl;
    binSearchTree.postorder();
    std::cout << "\n";
    std::cout << std::endl;
}

void testBST_2()
{
    int intArray[] = {8, 3, 8, 2, 5, 6, 12, 15, 13, 18, 16, -2, -1, -10};

    bst<int> bst(intArray, sizeof(intArray) / sizeof(intArray[0]));

    std::cout << "min() = " << bst.min()->getKey() << std::endl;
    std::cout << "max() = " << bst.max()->getKey() << std::endl;

    bst.printTree(); 

    bst.deleteKey(15);

    std::cout << std::endl;

    std::cout << "min() = " << bst.min()->getKey() << std::endl;
    std::cout << "max() = " << bst.max()->getKey() << std::endl;

    bst.printTree();
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

    bst<City> bst(cities, sizeof(cities) / sizeof(cities[0]));

    std::cout << "min() = " << bst.min()->getKey() << std::endl;
    std::cout << "max() = " << bst.max()->getKey() << std::endl;

    bst.printTree();
}