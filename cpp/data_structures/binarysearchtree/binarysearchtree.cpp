#include <assert.h>
#include <iostream>

#include "binarysearchtree.hpp"
#include "../utils/utils.hpp"

static void testPQInitCorrect(PrintQueue<Node<int>> &pq);
static void testPQEnqueueDequeue(PrintQueue<Node<int>> &pq);

static void testBSTInitCorrect(BinarySearchTree<int> &bst);
static void testBSTInsertNodes(BinarySearchTree<int> &bst);
static void testBSTRemoveNodes(BinarySearchTree<int> &bst);

Node<int> A(7), B(20), C(5), D(15), E(10), F(4), G(4), H(33), I(2), J(25), K(6);

int main(void)
{
    printStartOfTest();

    PrintQueue<Node<int>> pq(5);
    testPQInitCorrect(pq);
    testPQEnqueueDequeue(pq);

    BinarySearchTree<int> bst;
    testBSTInitCorrect(bst);
    testBSTInsertNodes(bst);
    testBSTRemoveNodes(bst);

    printEndOfTest();
    return 0;
}

static void testPQInitCorrect(PrintQueue<Node<int>> &pq)
{
    assert(5 == pq.GetCapacity());
    assert(0 == pq.GetSize());
    printPass(__FUNCTION__);
}

static void testPQEnqueueDequeue(PrintQueue<Node<int>> &pq)
{
    Node<int> A(10), B(9), C(8), D(7), E(6);
    pq.Enqueue(&A);
    pq.Enqueue(&B);
    pq.Enqueue(&C);
    pq.Enqueue(&D);
    pq.Enqueue(&E);
    pq.Print();
    assert(5 == pq.GetSize());
    assert(10 == (pq.Dequeue())->data);
    assert(9 == (pq.Dequeue())->data);
    assert(8 == (pq.Dequeue())->data);
    assert(7 == (pq.Dequeue())->data);
    assert(6 == (pq.Dequeue())->data);
    assert(0 == pq.GetSize());
    pq.Enqueue(&E);
    pq.Enqueue(&D);
    pq.Enqueue(&C);
    pq.Enqueue(&B);
    pq.Enqueue(&A);
    pq.Print();
    assert(5 == pq.GetSize());
    assert(6 == (pq.Dequeue())->data);
    assert(7 == (pq.Dequeue())->data);
    assert(8 == (pq.Dequeue())->data);
    assert(9 == (pq.Dequeue())->data);
    assert(10 == (pq.Dequeue())->data);
    assert(0 == pq.GetSize());
}

static void testBSTInitCorrect(BinarySearchTree<int> &bst)
{
    assert(0 == bst.GetSize());
    printPass(__FUNCTION__);
}

static void testBSTInsertNodes(BinarySearchTree<int> &bst)
{
    // Node<int> nodeList[] = {{7}, {20}, {5}, {15}, {10},
    //                         {4}, {4}, {33}, {2}, {25}, {6}};
    // for (auto i = 0; i < sizeof(nodeList) / sizeof(Node<int>); i++)
    // {
    //     bst.Insert(nodeList[i]);
    //     bst.PrintTreeBreadthFirst();
    // }

    //  OR ...
    bst.Insert(A); bst.PrintTreeBreadthFirst();
    bst.Insert(B); bst.PrintTreeBreadthFirst();
    bst.Insert(C); bst.PrintTreeBreadthFirst();
    bst.Insert(D); bst.PrintTreeBreadthFirst();
    bst.Insert(E); bst.PrintTreeBreadthFirst();
    bst.Insert(F); bst.PrintTreeBreadthFirst();
    bst.Insert(G); bst.PrintTreeBreadthFirst();
    bst.Insert(H); bst.PrintTreeBreadthFirst();
    bst.Insert(I); bst.PrintTreeBreadthFirst();
    bst.Insert(J); bst.PrintTreeBreadthFirst();
    bst.Insert(K); bst.PrintTreeBreadthFirst();

    printPass(__FUNCTION__);
}

static void testBSTRemoveNodes(BinarySearchTree<int> &bst)
{
    // case I: remove a leaf
    bst.PrintTreeBreadthFirst();
    bst.Remove(25); bst.PrintTreeBreadthFirst();

    // case II: remove root of a left-only subtree
    bst.Remove(4); bst.PrintTreeBreadthFirst();

    // case III: remove root of a right-only subtree
    bst.Remove(2); bst.PrintTreeBreadthFirst();
    bst.Remove(5); bst.PrintTreeBreadthFirst();

    // case IV: remove root of a left and right subtree
    bst.Remove(7); bst.PrintTreeBreadthFirst();
    printPass(__FUNCTION__);
}