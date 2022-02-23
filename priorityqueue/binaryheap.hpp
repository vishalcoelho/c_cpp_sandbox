#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "../arraylist/arraylist.hpp"

/**
 * @brief Binary Heap as an implementation of a priority queue.
 *
 * Note that the binary heap maintains an invariant relationship between parent
 * and child. For a MinHeap this relationship is A<=B while for a maxHeap the
 * relationship is A>=B.
 *
 * The tree is maintained as an array, shown below. The left and right child of
 * any node are always 2i+1 and 2i+2 positions to the right.
 *
 *                      +---+
 *                      | A |
 *                      +---+
 *                 ____/     \_____
 *            +---+                +---+
 *            | B |                | C |
 *            +---+                +---+
 *            /  \                 /   \
 *       +---+    +---+       +---+      +---+
 *       | D |    | E |       | F |      | G |
 *       +---+    +---+       +---+      +---+
 *       /\         /\          /\           /\
 *  +---+ +---+ +---+ +---+ +---+ +---+ +---+ +---+
 *  | H | | I | | J | | K | | L | | M | | N | | O |
 *  +---+ +---+ +---+ +---+ +---+ +---+ +---+ +---+
 *
 * Nodes are stored in an array as root to leaf, left to right.
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *       ^       ^   ^       ^           ^   ^           ^   ^
 *       i=1     |   j = 4   |           |   |           |   |
 *     left@2i+1=3   |       | left@2j+1=9   |           |   |
 *        right@2i+2=4       |   right@2j+2=10           |   |
 *                          k=6<---(left-1)/2-------left@13  |
 *                          k=6<-------(right-1)/2----right@14
 *  Note: backtracking the right child to its parent, I did (right-1)/2 
 *        instead of (right-2)/2 as integer division gives the same answer in 
 *        both cases. So, i use the same math on both left and right child to 
 *        get back to the parent.
 */
template <typename T>
class BinaryHeap
{
public:
    static constexpr int MIN_STACK_SIZE = 1;

    BinaryHeap(): size(0), capacity(0), arrayList(new ArrayList<T>(MIN_STACK_SIZE)) {}

    BinaryHeap(int size): size(0), capacity(size) {
        this->arrayList = new ArrayList<T>(size);
    }

    int GetSize() const { return size; }

    int GetCapacity() const { return capacity; }

    bool IsEmpty() const { return (0 == GetSize()); }

    void Clear()
    {
        arrayList->Clear();
        size = 0;
    }

    /** Removes the root of the heap
     *  1. exchange the root of the tree with the furthest right leaf.
     *  2. clip the new furthest right leaf
     *  3. Bubble down (sink) the root to its proper position in the tree to be removed
     *     maintain the "heap invariant"
     * 
     * heap_invariance->nodes in alphabetical order
     *                   +---+                             +---+
     *                   | A | ---switch root<->leaf--->   | G |
     *                   +---+                             +---+
     *                 /      \                           /     \
     *            +---+        +---+                +---+        +---+
     *            | B |        | C |                | B |        | C |
     *            +---+        +---+                +---+        +---+
     *            /  \          /  \                /  \        /  \
     *       +---+    +---+ +---+   +---+      +---+    +---+ +---+   +---+
     *       | D |    | E | | F |   | G |      | D |    | E | | F |   | A |
     *       +---+    +---+ +---+   +---+      +---+    +---+ +---+   +---+
     *                                                      |
     *                                                  trim leaf
     *                                                      |
     *                                                      V
     *                +---+                               +---+
     *                | C | <---bubble down(sink)-------  | G |
     *                +---+                               +---+
     *               /      \                           /      \
     *         +---+        +---+                  +---+        +---+
     *         | B |        | F |                  | B |        | C |
     *         +---+        +---+                  +---+        +---+
     *         /  \           /                    /  \          /
     *    +---+    +---+ +---+               +---+    +---+ +---+
     *    | D |    | E | | G |               | D |    | E | | F |
     *    +---+    +---+ +---+               +---+    +---+ +---+
     * 
     * Takes O(log2(n)) to complete.
     */
    T poll(void){
        return RemoveAt(ROOT);
    }

    void Add(T val){
        // Add a value to end of the arraylist.
        arrayList->Add(val);
        // Reorder the heap to maintain the heap invariant.
        Swim(size);
        size++;
    }

    /** Test to verify heap is a min heap. */
    bool IsMinHeap(int parent)
    {
        // base condition is: we have exceeded the bounds of the tree
        if (parent >= size)
            return true;

        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;

        // Assuming int in the format specifier.
        printf("[P@%d:%d, L@%d:%d, R@%d:%d]", parent, arrayList->Get(parent),
        leftChild, arrayList->Get(leftChild), rightChild, arrayList->Get(rightChild));

        if ((leftChild < size) && (!LessThan(parent, leftChild)))
            return false;
        if ((rightChild < size) && (!LessThan(parent, rightChild)))
            return false;

        // Recurse on the children.
        return (IsMinHeap(leftChild) && IsMinHeap(rightChild));
    }

private:
    static constexpr int ROOT = 0;
    ArrayList<T> *arrayList = nullptr;

    int size = 0;
    int capacity = 0;

    void Swap (int i, int j)
    {
        T val_i = arrayList->Get(i);
        T val_j = arrayList->Get(j);

        arrayList->Set(i, val_j);
        arrayList->Set(j, val_i);
    }
    
    T RemoveAt(int index)
    {
        T removedNodeValue = nullptr;
        if(!IsEmpty())
        {
            removedNodeValue = arrayList->Get(index);

            // Swap node-to-remove with last leaf on the right.
            int lastLeafOnRight = size;
            Swap(index, lastLeafOnRight);

            // Destroy last leaf on right.
            arrayList->Set(lastLeafOnRight, nullptr);
            size--;

            if(index == lastLeafOnRight)
            {
                // If removing the last leaf on the right? Obliterate, then quit.
                return removedNodeValue;
            }

            T currNodeValue = arrayList->Get(index);

            // Try sinking the node just swapped in.
            Sink(index);

            // If sinking doesn't work, try swimming (bubbling up).
            if(arrayList->Get(index) == currNodeValue)
                Swim(index);

        }

        return removedNodeValue;
    }

    void Sink(int index)
    {
        while (true)
        {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = leftChild; // assume left child is the smallest.

            // Havent exceeded heap and right child is the smallest, bubble down
            // the right hand path.
            if ((rightChild < size) && LessThan(rightChild, leftChild))
                smallest = rightChild;

            // stop if we have exceeded the boundary of the tree or cannot sink
            // any further.
            if ((leftChild >= size) || LessThan(index, smallest))
                break;

            Swap(index, smallest);
            index = smallest;
        }
    }

    bool LessThan(int first, int second)
    {
        T val_first = arrayList->Get(first);
        T val_second = arrayList->Get(second);

        return(val_first < val_second);
    }

    void Swim(int index)
    {
        int parent = (index - 1) / 2;

        // If i havent gone to a zero index (root) and parent is smaller,
        // swap parent with index and run again.
        while ((index > 0) && LessThan(index, parent))
        {
            Swap(index, parent);
            index = parent;
            // Get the next parent
            parent = (index - 1) / 2;
        }
    }
};

#endif /* BINARY_HEAP_H_ */
