#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
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

