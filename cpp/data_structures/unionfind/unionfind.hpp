#ifndef UNIONFIND_HPP_
#define UNIONFIND_HPP_

#include <stdexcept>

/**
 * @brief Union Find/Disjoint Set
 *
 * @author Vishal Coelho
 * 
 */

class UnionFind
{
public:
    UnionFind(int size)
    {
        if (0 > size)
            throw std::length_error("Cant have a negatively sized set.");

        this->size = size;
        numOfComponents = size;

        groupSizes = new int[size];
        parentOf = new int[size];

        for(auto i = 0; i < size; i++)
        {   
            parentOf[i] = i; // Each element in the set is its own root.
            groupSizes[i] = 1; // There are currently i groups of size 1 each.
        }
    }

    int GetNumOfComponents(void) const
    {
        return numOfComponents;
    }

    int GetSizeOfGroupContaining(int p)
    {
        return groupSizes[Find(p)];
    }

    int GetSize(void) const
    {
        return size;
    }

    /** Find which set 'p' belongs to. */
    int Find(int p)
    {
        // find the root of component p
        int root  = p;
        while(parentOf[root] != root)
            root = parentOf[root];

        // Now that the root of p is found, compress all the paths up to the root
        CompressPathsToRoot(p, root);

        return root;
    }

    /** Determine if elements 'p' and 'q' are in the same set. If they share a
     *  common root, they are.
     */
    bool Connected(int p, int q)
    {
        return(Find(p) == Find(q));
    }

    /** Unify the components or sets containing elements 'p' and 'q'. */
    void Unify(int p, int q)
    {
        int rootOfP = Find(p);
        int rootOfQ = Find(q);

        // if p and q are already in the same group, return.
        if(rootOfP == rootOfQ)
            return;

        // Merge the smaller group into the larger one
        if(GetSizeOfGroupContaining(rootOfP) >= GetSizeOfGroupContaining(rootOfQ))
        {
            groupSizes[rootOfP] += groupSizes[rootOfQ];
            parentOf[rootOfQ] = rootOfP;
        }
        else
        {
            groupSizes[rootOfQ] += groupSizes[rootOfP];
            parentOf[rootOfP] = rootOfQ;
        }
    }

private:
    /** Number of elements in the disjoint set., */
    int size = 0;
    /** Array to track the size of the various groups formed in the unifying process. */
    int *groupSizes = nullptr;
    /** parent of the ith element. If it points to itself, it is a root node.*/
    int *parentOf = nullptr;
    /** Tracks the number of components: single elements and/or groups formed among 
     * the elements of the  original disjoint set. */
    int numOfComponents = 0;

    /**
     * @brief Compress the paths leading to the root.
     * 
     *            +---+                            +---+
     *            | A |                            | A |
     *            +---+             >>             +---+
     *       ____/     \_____                 _____///\\\_____
     *  +---+                +---+       +---+     //  \\     +---+
     *  | B |                | C |       | B |    //    \\    | C |
     *  +---+                +---+       +---+   / |     |\   +---+
     *      \                 /                 |  |     | |
     *       +---+       +---+                +---+|     |+---+
     *       | E |       | F |                | E ||     || F |
     *       +---+       +---+                +---+|     |+---+
     *          \          /                       |     |
     *           +---+ +---+                      +---+ +---+
     *           | K | | L |                      | K | | L |
     *           +---+ +---+                      +---+ +---+
     */
    void CompressPathsToRoot(int &p, int &root)
    {
        // start at p, work your way to the root, attaching each parent element
        // directly to the root.
        while (p != root)
        {
            int parent = parentOf[p];
            parentOf[p] = root;
            p = parent;
        }
    }

};

#endif /* UNIONFIND_HPP_ */