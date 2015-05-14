#include "LKH.h"
#include "Sequence.h"
#include "Genetic.h"

/*      
 * The FreeStructures function frees all allocated structures.
 */

#define Free(s) { free(s); s = 0; }

void FreeStructures()
{
    FreeCandidateSets();
    FreeSegments();
    if (lkh.NodeSet) {
        int i;
        for (i = 1; i <= lkh.Dimension; i++) {
            Node *N = &lkh.NodeSet[i];
            Free(N->MergeSuc);
            N->C = 0;
        }
        Free(lkh.NodeSet);
    }
    Free(lkh.CostMatrix);
    Free(lkh.BestTour);
    Free(lkh.BetterTour);
    Free(lkh.SwapStack);
    Free(lkh.HTable);
    Free(lkh.Rand);
    Free(lkh.CacheSig);
    Free(lkh.CacheVal);
    Free(lkh.Name);
    Free(lkh.Type);
    Free(lkh.EdgeWeightType);
    Free(lkh.EdgeWeightFormat);
    Free(lkh.EdgeDataFormat);
    Free(lkh.NodeCoordType);
    Free(lkh.DisplayDataType);
    Free(lkh.Heap);
    Free(t);
    Free(T);
    Free(tSaved);
    Free(p);
    Free(q);
    Free(incl);
    Free(cycle);
    Free(G);
    FreePopulation();
}

/*      
   The FreeSegments function frees the segments.
 */

void FreeSegments()
{
    if (lkh.FirstSegment) {
        Segment *S = lkh.FirstSegment, *SPrev;
        do {
            SPrev = S->Pred;
            Free(S);
        }
        while ((S = SPrev) != lkh.FirstSegment);
        lkh.FirstSegment = 0;
    }
    if (lkh.FirstSSegment) {
        SSegment *SS = lkh.FirstSSegment, *SSPrev;
        do {
            SSPrev = SS->Pred;
            Free(SS);
        }
        while ((SS = SSPrev) != lkh.FirstSSegment);
        lkh.FirstSSegment = 0;
    }
}

/*      
 * The FreeCandidateSets function frees the candidate sets.
 */

void FreeCandidateSets()
{
    Node *N = lkh.FirstNode;
    if (!N)
        return;
    do {
        Free(N->CandidateSet);
        Free(N->BackboneCandidateSet);
    }
    while ((N = N->Suc) != lkh.FirstNode);
}
