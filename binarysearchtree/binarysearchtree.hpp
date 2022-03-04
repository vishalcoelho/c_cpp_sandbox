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
    Node *rightChild = nullptr;
    Node *leftChild = nullptr;
    Node *parent = nullptr;
    T data;

    Node() {}
    Node(T data) : data(data) {}

    void Print() { printf("%d, ", data); }

    void CopyDataAndChildren(const Node *src)
    {
        this->data = src->data;
        this->rightChild = src->rightChild;
        this->leftChild = src->leftChild;
    }

    void CopyData(const Node *src)
    {
        this->data = src->data;
    }

    void Remove()
    {
        this->rightChild = nullptr;
        this->leftChild = nullptr;
        this->parent = nullptr;
    }
};

template <class T>
class PrintQueue
{
public:
    PrintQueue(int size) : capacity(size)
    {
        printQueue = new T[size];
        headOfQueue = printQueue;
        tailOfQueue = printQueue;
    }

    void Enqueue(const T *node)
    {
        if (size >= capacity)
            throw std::length_error("Cant accept any more!");

        memcpy(tailOfQueue, node, sizeof(T));
        size++;
        IncrementWraparound(&tailOfQueue);
    }

    T *Dequeue()
    {
        T *retval = headOfQueue;
        IncrementWraparound(&headOfQueue);
        size--;
        return (retval);
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
        if (*ptr >= (printQueue + capacity))
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

    int GetSize(void) const { return size; }

    /** Debug Only. */
    void PrintTreeBreadthFirst();

    /** Get the reference to a node in the BST. */
    Node<T> *Find(T data) const;

    /** Remove a node from the tree and return true if the node was found. */
    bool Remove(T data);

private:
    int size = 0;
    Node<T> *root = nullptr;
    PrintQueue<Node<T>> *pq = nullptr;

    Node<T> *FindSmallestInRightSubtree(Node<T> &rootOfSubtree)
    {
        Node<T> *currNode = &rootOfSubtree;
        if (nullptr == currNode)
            return currNode;

        // start at the root of the right subtree
        currNode = currNode->rightChild;

        // Keep going down the left path of the right subtree till you cant anymore,
        // you have found the smallest node in the right subtree.
        while (nullptr != currNode->leftChild)
        {
            currNode = currNode->leftChild;
        }
        return currNode;
    }

    Node<T> *FindLargesttInLeftSubtree(Node<T> &rootOfSubtree)
    {
        Node<T> *currNode = &rootOfSubtree;
        if (nullptr == currNode)
            return currNode;

        // start at the root of the left subtree
        currNode = currNode->leftChild;
        
        // Keep going down the right path of the right subtree till you cant anymore,
        // you have found the largest node in the left subtree.
        while (nullptr != currNode->rightChild)
        {
            currNode = currNode->rightChild;
        }
        return currNode;
    }

    bool cameFromLeftOfParent(Node<T> &node) const
    {
        bool retval = false;
        Node<T> &nodeParent = *node.parent;
        if (nodeParent.leftChild->data == node.data)
            retval = true;
        return retval;
    }
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
                if (currNode->rightChild)
                    currNode = currNode->rightChild;
                else
                {
                    currNode->rightChild = &node;
                    node.parent = currNode;
                    size++;
                    exit = true;
                }
            }
            else if (node.data < currNode->data)
            {
                // go down the left path if it has a left child, else make it
                // the left child.
                if (currNode->leftChild)
                    currNode = currNode->leftChild;
                else
                {
                    currNode->leftChild = &node;
                    node.parent = currNode;
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
    Node<T> *currNode = root;

    pq->Enqueue(currNode);

    printf("BST: ");
    // Start with the root node at the head of the queue
    // While the queue isnt empty, do:
    //   1. dequeue head of the queue
    //   2. print its Data
    //   3. add its left and right child to the queue, in that order
    //   4. rinse and repeat
    while (!pq->IsEmpty())
    {
        currNode = pq->Dequeue();
        currNode->Print();
        if (currNode->leftChild)
            pq->Enqueue(currNode->leftChild);
        if (currNode->rightChild)
            pq->Enqueue(currNode->rightChild);
    }
    printf("\n");
    delete pq;
}

template <typename T>
Node<T> *BinarySearchTree<T>::Find(T data) const
{
    Node<T> *currNode = root;
    while (!IsLeaf(*currNode))
    {
        if (data < currNode->data)
            currNode = currNode->leftChild;
        else if (data > currNode->data)
            currNode = currNode->rightChild;
        else // (data == currNode->data)
            break;
    }

    // Either found the data or at a leaf node
    if (data != currNode->data)
        currNode = nullptr;

    return currNode;
}

template <typename T>
bool BinarySearchTree<T>::Remove(T data)
{

    Node<T> *nodeToRemove = Find(data);

    if (nullptr == nodeToRemove)
        return false;

    while (nodeToRemove)
    {
        // Case I: leaf node? snip-snip
        if (IsLeaf(*nodeToRemove))
        {
            if (cameFromLeftOfParent(*nodeToRemove))
                (nodeToRemove->parent)->leftChild = nullptr;
            else
                (nodeToRemove->parent)->rightChild = nullptr;
            nodeToRemove->parent = nullptr;
            nodeToRemove = nullptr;
        }

        // Case II: root of left subtree, no right subtree?
        //          node left of root replaces it as the root of the subtree
        else if (nullptr == nodeToRemove->rightChild)
        {
            Node<T> &leftChild = *nodeToRemove->leftChild;
            nodeToRemove->CopyDataAndChildren(&leftChild);
            leftChild.Remove();
            nodeToRemove = nullptr;
        }

        // Case III: root of right subtree, no left subtree?
        //           node right of root replaces it as the root of the subtree
        else if (nullptr == nodeToRemove->leftChild)
        {
            Node<T> &rightChild = *(nodeToRemove->rightChild);
            nodeToRemove->CopyDataAndChildren(&rightChild);
            rightChild.Remove();
            nodeToRemove = nullptr;
        }

        // Case IV: root of both left and right subtrees? Pick either
        //          a. smalest node in right subtree as root replacement
        //          b. largest node in left subtree as root replacement
        else
        {
            Node<T> *smallestNodeRight = FindSmallestInRightSubtree(*nodeToRemove);
            nodeToRemove->CopyData(smallestNodeRight);
            nodeToRemove = smallestNodeRight;

            // or

            // Node<T> 8largestNodeLeft = FindLargesttInLeftSubtree(*nodeToRemove);
            // nodeToRemove->CopyData(largestNodeLeft);
            // nodeToRemove = largestNodeLeft;
        }
    }

    size--;
    return true;
}

#endif /* BINARYSEARCHTREE_HPP_ */