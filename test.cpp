#include "bst.hpp"
#include "binaryTree.hpp"
#include "bstException.hpp" // include superfluo

void testBinaryTree();
void testBST();

int main()
{
    // testBinaryTree();
    try
    {
        testBST();
    }
    catch(const NonExistingValueException& e)
    {
        std::cerr << "e.what() :  " << e.what() << std::endl;
        std::cerr << "e.getInfo() :  " << e.getInfo() << std::endl;
    }

    return 0;
}

void testBinaryTree()
{
    binaryTree<int> t4(2), t5(1), t6(4), t7(9);       // livello 3
    binaryTree<int> t2(7, &t4, &t5), t3(3, &t6, &t7); // livello 2
    binaryTree<int> t1(5, &t2, &t3);                  // livello 1

    std::cout << "Inorder: " << std::endl;
    t1.inorder();
    std::cout << "\nPreorder: " << std::endl;
    t1.preorder();
    std::cout << "\nPostorder: " << std::endl;
    t1.postorder();
    std::cout << "\nÈ completo? " << (t1.isComplete() ? "Sì" : "No") << std::endl;
    std::cout << "Ci sono " << t1.leavesCount() << " foglie e " << t1.nodesCount() << " nodi" << std::endl;
    std::cout << "La key 3 " << (t1.search(3) ? " è " : " non è ") << " presente" << std::endl;
    std::cout << "La key 8 " << (t1.search(8) ? " è " : " non è ") << " presente" << std::endl;

    t3.deleteTree();
    std::cout << "Inorder: " << std::endl;
    t1.inorder();
    std::cout << std::endl;
}

void testBST()
{
    int intArray[] = {11, 9, 14, 5, 10, 12, 15};
/*
    bst<int> binSearchTree;
    for (u_int i{0}; i < 7; ++i)
    {
        binSearchTree.insertValue(intArray[i]);
    }
    std::cout << "Inorder: " << std::endl;
    binSearchTree.preorder();
    std::cout << "\nPreorder: " << std::endl;
    binSearchTree.preorder();
    std::cout << "\nPostorder: " << std::endl;
    binSearchTree.postorder();
    std::cout << "\n";
    std::cout << std::endl;
*/
    bst<int> bst(intArray, 7);

    std::cout << "min() = " << bst.min()->getKey() << std::endl;
    std::cout << "max() = " << bst.max()->getKey() << std::endl;

    bst.printTree();

    bst.deleteKey(14);

    std::cout << std::endl;

    std::cout << "min() = " << bst.min()->getKey() << std::endl;
    std::cout << "max() = " << bst.max()->getKey() << std::endl;

    bst.printTree();
}