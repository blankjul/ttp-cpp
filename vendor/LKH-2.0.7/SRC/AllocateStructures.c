#include "Segment.h"
#include "LKH.h"
#include "Heap.h"
#include "Sequence.h"

/*      
 * The AllocateStructures function allocates all necessary 
 * structures except nodes and candidates.
 */

#define Free(s) { free(s); s = 0; }

void AllocateStructures()
{
    int i, K;

    Free(lkh.Heap);
    Free(lkh.BestTour);
    Free(lkh.BetterTour);
    Free(lkh.HTable);
    Free(lkh.Rand);
    Free(lkh.CacheSig);
    Free(lkh.CacheVal);
    Free(T);
    Free(G);
    Free(t);
    Free(p);
    Free(q);
    Free(lkh.SwapStack);
    Free(tSaved);

    MakeHeap(lkh.Dimension);
    assert(lkh.BestTour = (int *) calloc(1 + lkh.Dimension, sizeof(int)));
    assert(lkh.BetterTour = (int *) calloc(1 + lkh.Dimension, sizeof(int)));
    assert(lkh.HTable = (HashTable *) malloc(sizeof(HashTable)));
    HashInitialize((HashTable *) lkh.HTable);
    SRandom(lkh.Seed);
    assert(lkh.Rand = (unsigned *)
           malloc((lkh.Dimension + 1) * sizeof(unsigned)));
    for (i = 1; i <= lkh.Dimension; i++)
        lkh.Rand[i] = Random();
    SRandom(lkh.Seed);
    if (lkh.WeightType != EXPLICIT) {
        for (i = 0; (1 << i) < (lkh.Dimension << 1); i++);
        i = 1 << i;
        assert(lkh.CacheSig = (int *) calloc(i, sizeof(int)));
        assert(lkh.CacheVal = (int *) calloc(i, sizeof(int)));
        lkh.CacheMask = i - 1;
    }
    AllocateSegments();
    K = lkh.MoveType;
    if (lkh.SubsequentMoveType > K)
        K = lkh.SubsequentMoveType;
    assert(T = (Node **) malloc((1 + 2 * K) * sizeof(Node *)));
    assert(G = (GainType *) malloc(2 * K * sizeof(GainType)));
    assert(t = (Node **) malloc(6 * K * sizeof(Node *)));
    assert(tSaved = (Node **) malloc((1 + 2 * K) * sizeof(Node *)));
    assert(p = (int *) malloc(6 * K * sizeof(int)));
    assert(q = (int *) malloc(6 * K * sizeof(int)));
    assert(incl = (int *) malloc(6 * K * sizeof(int)));
    assert(cycle = (int *) malloc(6 * K * sizeof(int)));
    assert(lkh.SwapStack =
           (SwapRecord *) malloc((lkh.MaxSwaps + 6 * K) * sizeof(SwapRecord)));
}

/*      
 * The AllocateSegments function allocates the segments of the two-level tree.
 */

void AllocateSegments()
{
    Segment *S = 0, *SPrev;
    SSegment *SS = 0, *SSPrev;
    int i;

    FreeSegments();
#ifdef THREE_LEVEL_TREE
    GroupSize = (int) pow((double) Dimension, 1.0 / 3.0);
#elif defined TWO_LEVEL_TREE
    lkh.GroupSize = (int) sqrt((double) lkh.Dimension);
#else
    GroupSize = Dimension;
#endif
    lkh.Groups = 0;
    for (i = lkh.Dimension, SPrev = 0; i > 0; i -= lkh.GroupSize, SPrev = S) {
        assert(S = (Segment *) malloc(sizeof(Segment)));
        S->Rank = ++lkh.Groups;
        if (!SPrev)
            lkh.FirstSegment = S;
        else
            SLink(SPrev, S);
    }
    SLink(S, lkh.FirstSegment);
#ifdef THREE_LEVEL_TREE
    SGroupSize = sqrt((double) Groups);
#else
    lkh.SGroupSize = lkh.Dimension;
#endif
    lkh.SGroups = 0;
    for (i = lkh.Groups, SSPrev = 0; i > 0; i -= lkh.SGroupSize, SSPrev = SS) {
        SS = (SSegment *) malloc(sizeof(SSegment));
        SS->Rank = ++lkh.SGroups;
        if (!SSPrev)
            lkh.FirstSSegment = SS;
        else
            SLink(SSPrev, SS);
    }
    SLink(SS, lkh.FirstSSegment);
}
