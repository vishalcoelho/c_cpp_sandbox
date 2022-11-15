#include <assert.h>
#include <iostream>

#include "unionfind.hpp"
#include "../utils/utils.hpp"

static void testUFInitCorrect(UnionFind &uf);
static void testKruskalsAlgorithm(UnionFind &uf);

int main(void)
{
    printStartOfTest();
    try
    {
        UnionFind uf(-1);
    }
    catch (const std::length_error &e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }

    UnionFind uf(10);
    testUFInitCorrect(uf);
    UnionFind uf2(5);
    testKruskalsAlgorithm(uf2);
    printEndOfTest();
    return 0;
}

static void testUFInitCorrect(UnionFind &uf)
{
    assert(10 == uf.GetNumOfComponents());
    printPass(__FUNCTION__);
}

/*
 * Note: I have not assigned weight to the edges nor have i chosen the unify operations
 * to give the quickest path. This is not a true min spanning tree.
 * 
 * Im using the sequence of unify operations to stress test the class.
 * 
 *          +---+          Union Opertions                     +---+                                     +---+
 *          | A |          ---------------                     | A |                                     | A |
 *          +---+           A, B  -> new group G1              +---+                                     +---+
 *         /  |  \          C, F  -> new group G2             /     \                                   / | | \
 *        /   |   \         A, E  -> add to G1               /       \                                 /  | |  \
 *       /    |    \        A, C  -> unify G1 and G2        /         \                               /   | |   \
 *  +---+    /      +---+                              +---+           +---+                     +---+    | |    +---+
 *  | B | --|       | C |  >> Min Spanning Tree >>     | B |           | C |   >> Path      >>   | B |   /   \   | C |
 *  +---+   \       +---+                              +---+           +---+     Compression     +---+  /     \  +---+
 *      \   |\       /                                     \            /                               |      |
 *       \  | \     \                                       \          /                                |      |
 *        \ |  \   /                                         \        /                                 |      |
 *       +---+  +---+                                       +---+  +---+                              +---+  +---+
 *       | E |  | F |                                       | E |  | F |                              | E |  | F |
 *       +---+  +---+                                       +---+  +---+                              +---+  +---+
 */
static void testKruskalsAlgorithm(UnionFind &uf)
{
    // Start of with the following bijection
    // A -> 0
    // B -> 1
    // C -> 2
    // D -> 3
    // E -> 4
    enum
    {
        NODE_A = 0,
        NODE_B = 1,
        NODE_C = 2,
        NODE_D = 3,
        NODE_E = 4,
    };

    uf.Unify(NODE_A, NODE_B);
    assert(NODE_A == uf.Find(NODE_B));
    assert(NODE_A == uf.Find(NODE_A));
    uf.Unify(NODE_C, NODE_E);
    assert(NODE_C == uf.Find(NODE_E));
    assert(NODE_C == uf.Find(NODE_E));
    assert(false == uf.Connected(NODE_A, NODE_C));
    uf.Unify(NODE_A, NODE_D);
    assert(NODE_A == uf.Find(NODE_B));
    assert(NODE_A == uf.Find(NODE_D));
    assert(NODE_A == uf.Find(NODE_A));
    uf.Unify(NODE_A, NODE_C);
    assert(NODE_A == uf.Find(NODE_B));
    assert(NODE_A == uf.Find(NODE_C));
    assert(NODE_A == uf.Find(NODE_D));
    assert(NODE_A == uf.Find(NODE_E));
    assert(NODE_A == uf.Find(NODE_A));
    assert(true == uf.Connected(NODE_A, NODE_C));
    printPass(__FUNCTION__);
}