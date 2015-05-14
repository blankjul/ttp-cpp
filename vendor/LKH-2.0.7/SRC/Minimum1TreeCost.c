#include "LKH.h"

/*
 * The Minimum1TreeCost function returns the cost of a minimum 1-tree.
 *
 * The minimum 1-tre is found by determining the minimum spanning tree and 
 * then adding an edge corresponding to the second nearest neighbor of one 
 * of the leaves of the tree (any node which has degree 1). The leaf chosen
 * is the one that has the longest second nearest neighbor distance.
 *
 * The V-value of a node is its degree minus 2. Therefore, Norm being the 
 * sum of squares of all V-values, is a measure of a minimum 1-tree/s 
 * discrepancy from a tour. If Norm is zero, then the 1-tree constitutes a 
 * tour, and an optimal tour has been found.
 */

GainType Minimum1TreeCost(int Sparse)
{
    Node *N, *N1 = 0;
    GainType Sum = 0;
    int Max = INT_MIN;

    MinimumSpanningTree(Sparse);
    N = lkh.FirstNode;
    do {
        N->V = -2;
        Sum += N->Pi;
    }
    while ((N = N->Suc) != lkh.FirstNode);
    Sum *= -2;
    while ((N = N->Suc) != lkh.FirstNode) {
        N->V++;
        N->Dad->V++;
        Sum += N->Cost;
        N->Next = 0;
    }
    lkh.FirstNode->Dad = lkh.FirstNode->Suc;
    lkh.FirstNode->Cost = lkh.FirstNode->Suc->Cost;
    do {
        if (N->V == -1) {
            Connect(N, Max, Sparse);
            if (N->NextCost > Max) {
                N1 = N;
                Max = N->NextCost;
            }
        }
    }
    while ((N = N->Suc) != lkh.FirstNode);
    N1->Next->V++;
    N1->V++;
    Sum += N1->NextCost;
    lkh.Norm = 0;
    do
        lkh.Norm += N->V * N->V;
    while ((N = N->Suc) != lkh.FirstNode);
    if (N1 == lkh.FirstNode)
        N1->Suc->Dad = 0;
    else {
        lkh.FirstNode->Dad = 0;
        Precede(N1, lkh.FirstNode);
        lkh.FirstNode = N1;
    }
    if (lkh.Norm == 0) {
        for (N = lkh.FirstNode->Dad; N; N1 = N, N = N->Dad)
            Follow(N, N1);
        for (N = lkh.FirstNode->Suc; N != lkh.FirstNode; N = N->Suc)
            N->Dad = N->Pred;
        lkh.FirstNode->Suc->Dad = 0;
    }
    return Sum;
}
