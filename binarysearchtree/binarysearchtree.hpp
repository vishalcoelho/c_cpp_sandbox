#ifndef BINARYSEARCHTREE_HPP_
#define BINARYSEARCHTREE_HPP_

#include <stdexcept>

/**
 * @brief Binary Search Tree
 *
 * @author Vishal Coelho
 * 
 */

template <typename T>
struct Node
{
    Node* rightChild = nullptr;
    Node* leftChild = nullptr;
    Node* parent = nullptr;
    T data;

    Node(){}
    Node(T data): data(data) {}
    void Print() { printf("%d, ", data);}
};

template <class T>
class PrintQueue
{
public:
    PrintQueue(int size): capacity(size) { 
        printQueue = new T[size];
        headOfQueue = printQueue;
        tailOfQueue = printQueue;
        }

    void Enqueue(T & node) {
        if(size >= capacity)
            throw std::length_error("Cant accept any more!");

        memcpy(tailOfQueue, &node, sizeof(Node<T>));
        size++;
        IncrementWraparound(&tailOfQueue);
    }

    T &Dequeue() {
        T *retval = headOfQueue;
        IncrementWraparound(&headOfQueue);
        size--;
        return(*retval);
    }

    int GetSize() const { return size; }

    int GetCapacity() const { return capacity; }

    bool IsEmpty() const { return (0 == GetSize()); }

    void Print() const
    {
        printf("PQ: ");
        for (auto i = 0; i < size; i++)
        {
            printQueue[i].Print();
        }
        printf("\n");
    }

private:
    int size = 0;
    int capacity = 0;
    T *printQueue = nullptr;
    T *headOfQueue = nullptr;
    T *tailOfQueue = nullptr;

    void IncrementWraparound(T **ptr)
    {
        *ptr = *ptr + 1;
        if(*ptr >= (printQueue + capacity))
            *ptr = printQueue;
    }
};

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() {}

    void Insert(Node<T> &node);

    bool IsLeaf(Node<T> &node) const
    {
        return ((node.leftChild == nullptr) && (node.rightChild == nullptr));
    }

    int GetSize(void) const { return size;}
    
    /** Debug Only. */
    void PrintTreeBreadthFirst();

    /** Get the reference to a node in the BST. */
    Node<T> &Find(T data) const;

private:
    int size = 0;
    Node<T> *root = nullptr;
    PrintQueue<Node<T>> *pq = nullptr;
};

template <typename T>
void BinarySearchTree<T>::Insert(Node<T> &node)
{
    if (nullptr == root)
    {
        root = &node;
        size++;
    }
    else
    {
        Node<T> *currNode = root;
        bool exit = false;
        while (!exit)
        {
            if (node.data > currNode->data)
            {
                // go down the right path if it has a right child, else make it 
                // the right child.
                if(currNode->rightChild)
                    currNode = currNode->rightChild;
                else {
                    currNode->rightChild = &node;
                    size++;
                    exit = true;
                }
            }
            else if (node.data < currNode->data)
            {
                // go down the left path if it has a left child, else make it 
                // the left child.
                if(currNode->leftChild)
                    currNode = currNode->leftChild;
                else {
                    currNode->leftChild = &node;
                    size++;
                    exit = true;
                }
            }
            else
            {
                // Ignore duplicate nodes.
                exit = true;
            }
        }
    }
}

template <typename T>
void BinarySearchTree<T>::PrintTreeBreadthFirst()
{
    pq = new PrintQueue<Node<T>>(size);
    Node<T> currNode = *root;
    pq->Enqueue(currNode);

    printf("BST: ");
    // Start with the root node at the head of the queue
    // While the queue isnt empty, do:
    //   1. dequeue head of the queue
    //   2. print its Data
    //   3. add its left and right child to the queue, in that order
    //   4. rinse and repeat
    while(!pq->IsEmpty())
    {
        currNode = pq->Dequeue();
        currNode.Print();
        if(currNode.leftChild)
            pq->Enqueue(*(currNode.leftChild));
        if(currNode.rightChild)
            pq->Enqueue(*(currNode.rightChild));
    }
    printf("\n");
    delete pq;
}

template <typename T>
Node<T> &BinarySearchTree<T>::Find(T data) const
{ 
    Node<T> &currNode = *root;
    while(!IsLeaf(currNode))
    {
        if (data == currNode.data)
            break;
        if (data < currNode.data)
            currNode = *(currNode.leftChild);
        else
            currNode = *(currNode.rightChild);
    }

    return currNode;
}


#endif /* BINARYSEARCHTREE_HPP_ */