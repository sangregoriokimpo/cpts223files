

#include "AVLTree.h"
#include "experimentFunctions.h"

using namespace std;



int main()
{
//    auto avl = new AVLTree<int>();
//    avl->insert(1);
//    avl->insert(2);
//    avl->insert(3);
//    avl->insert(4);
//    avl->insert(5);
//    avl->insert(6);
//    avl->insert(7);
//    avl->insert(8);
//    avl->insert(9);
//    avl->insert(10);
//
//    cout << "test" << endl;
//
//    cout << avl->isBST() << endl;
//    cout << avl->isBalanced() << endl;
//    cout << avl->computeHeight() << endl;
//    cout << avl->readRootHeight() << endl;
//    cout << avl->treeSize() << endl;
//    cout << avl->averageDepth() << endl;
//    cout <<"test" << endl;
//    avl->removeByRank(1);
//    cout << avl->treeSize() << endl;

//    avl->insert(1);
//    cout << avl->contains(1) << endl;
//    avl->remove(1);
//    cout << avl->contains(1) << endl;


    // experiment 1: test BST order and AVL height condition
    cout << "================================ Experiment 1 ================================" << endl;
    int numIntegers = 20;
    experiment1(numIntegers);
    cout << endl;

    // experiment 2: test whether the average depth of AVL trees is invariant to random insert/remove pair operations
    cout << "============================ Experiment 2, Stage 1 ============================" << endl;

    // Stage 1: insert random integers into AVL BST, as Figure 4.29 of textbook
    numIntegers = 20;
    auto*avl = new AVLTree<int>();
    stage1(avl, numIntegers);
    cout << endl;

    // Stage 2: 500^2 times of random insert/delete pairs for this AVL tree, as per textbook, Figure 4.30
    int numRandomInsertRemove = 250000;
    cout << "========== Experiment 2, Stage 2 (after " << numRandomInsertRemove << " random insert/delete) ==========" << endl;
    stage2(avl, numRandomInsertRemove);

    // delete this avl
    delete avl;

    return 0;

}