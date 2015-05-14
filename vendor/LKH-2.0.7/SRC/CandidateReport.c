#include "LKH.h"

/*
 * The CandidateReport function prints the minimum, average and maximum
 * number of candidates associated with a node.
 */

void CandidateReport()
{
    int Min = INT_MAX, Max = 0, Fixed = 0, Count;
    GainType Sum = 0, Cost = 0;
    Node *N;
    Candidate *NN;

    N = lkh.FirstNode;
    do {
        Count = 0;
        if (N->CandidateSet)
            for (NN = N->CandidateSet; NN->To; NN++)
                Count++;
        if (Count > Max)
            Max = Count;
        if (Count < Min)
            Min = Count;
        Sum += Count;
        if (N->FixedTo1 && N->Id < N->FixedTo1->Id) {
            Fixed++;
            Cost += lkh.Distance != Distance_1 ? lkh.Distance(N, N->FixedTo1) : 0;
        }
        if (N->FixedTo2 && N->Id < N->FixedTo2->Id) {
            Fixed++;
            Cost += lkh.Distance != Distance_1 ? lkh.Distance(N, N->FixedTo2) : 0;
        }
    }
    while ((N = N->Suc) != lkh.FirstNode);
    printff("Cand.min = %d, Cand.avg = %0.1f, Cand.max = %d\n",
            Min, (double) Sum / lkh.Dimension, Max);
    if (Fixed > 0)
        printff("Edges.fixed = %d [Cost = " GainFormat "]\n", Fixed, Cost);
    if (lkh.MergeTourFiles >= 1) {
        Count = 0;
        N = lkh.FirstNode;
        do
            if (IsCommonEdge(N, N->MergeSuc[0]))
                Count++;
        while ((N = N->Suc) != lkh.FirstNode);
        printff("Edges.common = %d\n", Count);
    }
}
