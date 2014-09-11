#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
#include <cstring>
using namespace std;

typedef unsigned char Byte;
typedef unsigned long ULong;
typedef unsigned short Word;

struct Edge {
    ULong uV1;
    ULong uV2;
};

class BitArray {

public:

        BitArray        (ULong pSizeInBits = 0);
        ~BitArray       ();
    bool EnsureCapacity (ULong pSizeInBits);
    void Destroy        (void);
    Word GetBit         (ULong pBit);
    void SetBit         (ULong pBit);
    void ResetBit       (ULong pBit);
    void ResetAllBits   ();

private:
    Byte *vArray;
    ULong vCapacityInBytes;
};

// Models an unweighted, undirected tree
class Graph {

public:
            Graph           (ULong pNumVertices);
            ~Graph          ();
    void    AddEdge         (ULong pV1, ULong pV2);
    ULong   LongestPath     ();

private:

    ULong    vNumVertices;
    vector<int> *vEdges;

    ULong   DepthFirstTraversal (ULong pSourceVertex, vector<Edge> &pVisitedEdges, BitArray &pLocalVisited);

    bool    IsEdgeVisited       (vector<Edge> &pVisited, ULong pV1, ULong pV2);
};


#define BITS_PER_BYTE       8

/*
 * Purpose: To initialize a bit array for use and set its initial size.
 */
BitArray::BitArray (ULong pSizeInBits)
{
    vArray           = NULL;
    vCapacityInBytes = 0;
    if (pSizeInBits > 0) EnsureCapacity (pSizeInBits);
}

BitArray::~BitArray ()
{
    delete vArray;
}

/*
 * Purpse: To set the max size of bit array.
 * Notes:
 *      1. Does not preserve or modify existing data.
 */
bool BitArray::EnsureCapacity (ULong pSizeInBits)
{
        ULong nbytes;

    // Expand array if needed
    nbytes = (pSizeInBits/BITS_PER_BYTE) + 1;
    if (nbytes > vCapacityInBytes) {
        // Release existing array and create new array.
        delete vArray;
        vArray = new Byte[pSizeInBits];
        vCapacityInBytes = nbytes;
        ResetAllBits ();
    }
    return true;
}

/*
 * Purpose: To release memory allocated for the bit array.
 */
void BitArray::Destroy (void)
{
    if (vArray) delete (vArray);
    vArray           = NULL;
    vCapacityInBytes = 0;
}

/*
 * Purpose: To check if a bit is set.
 */
Word BitArray::GetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = (1 << (pBit % BITS_PER_BYTE));
    return (vArray[byte] & mask) ? 1 : 0;
}

/*
 * Purpose: To set a bit.
 */
void BitArray::SetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = (1 << (pBit % BITS_PER_BYTE));
    vArray[byte] |= mask;
}

/*
 * Purpose: To reset a bit.
 */
void BitArray::ResetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = ~(1 << (pBit % BITS_PER_BYTE));
    vArray[byte] &= mask;
}

/**
 * Purpose: To reset all bits.
 */
void BitArray::ResetAllBits ()
{
    memset (vArray, 0, vCapacityInBytes);
}


Graph::Graph (ULong pNumVertices)
{
    assert (pNumVertices > 0);

    vNumVertices = pNumVertices;
    vEdges = new vector<int>[pNumVertices];
}

Graph::~Graph ()
{
    delete[] vEdges;
}

void Graph::AddEdge (ULong pV1, ULong pV2)
{
    assert ((pV1 < vNumVertices) && (pV2 < vNumVertices));

    // Undirected graph, so add two edges
    vEdges[pV1].push_back (pV2);
    vEdges[pV2].push_back (pV1);
}

bool Graph::IsEdgeVisited (vector<Edge> &pVisited, ULong pV1, ULong pV2)
{
        ULong t;
    if (pV1 > pV2) {
        t   = pV1;
        pV1 = pV2;
        pV2 = t;
    }

    for (vector<Edge>::iterator it = pVisited.begin (); it != pVisited.end (); it++) {
        if ((*it).uV1 == pV1 && (*it).uV2 == pV2) return true;
    }
    return false;
}


ULong Graph::DepthFirstTraversal (ULong pSourceVertex, vector<Edge> &pVisitedEdges, BitArray &pVisitedNodes)
{
        ULong max = 0;
        ULong l;

    assert (pSourceVertex < vNumVertices);

    for (vector<int>::iterator it = vEdges[pSourceVertex].begin (); it != vEdges[pSourceVertex].end (); it++) {
        if (!IsEdgeVisited (pVisitedEdges, pSourceVertex, *it)) {

                Edge e;
            if (pSourceVertex < *it) {
                e.uV1 = pSourceVertex;
                e.uV2 = *it;
            } else {
                e.uV1 = *it;
                e.uV2 = pSourceVertex;
            }

            pVisitedEdges.push_back (e);

            l = 1 + DepthFirstTraversal (*it, pVisitedEdges, pVisitedNodes);
            if (l > max) max = l;

            pVisitedEdges.pop_back ();
        }
    }

    pVisitedNodes.SetBit (pSourceVertex);
    return max;
}

ULong Graph::LongestPath ()
{
        ULong    l;
        ULong    max = 0;
        BitArray nvisited(vNumVertices);
        vector<Edge> evisited;

    for (ULong i = 0; i < vNumVertices; i++) {
        if (!nvisited.GetBit (i)) l = DepthFirstTraversal (i, evisited, nvisited);
        if (l > max) max = l;
    }
    return max;
}

int main ()
{
        Graph *graph;
        int  v1, v2;
        int  n;

/*        Graph g(4);
     g.AddEdge (0 , 1);

    g.AddEdge (1 , 2);
    g.AddEdge (1 , 3);

    assert (g.LongestPath () == 2); */

    cin >> n;
    graph = new Graph(n);

    for (int i = 0; i < n-1; i++) {
        cin >> v1 >> v2;
        assert ((v1 > 0) && (v2 > 0));
        graph->AddEdge (v1-1, v2-1);
    }

    cout << graph->LongestPath ();
    delete graph;
    return 0;
}
