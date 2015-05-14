#include "LKH.h"

/*
 * The ChooseInitialTour function generates a pseudo-random initial tour. 
 * The algorithm constructs a tour as follows. 
 *
 * First, a random node N is chosen.
 *
 * Then, as long as no all nodes have been chosen, choose the next node to 
 * follow N in the tour, NextN, and set N equal to NextN.
 *
 * NextN is chosen as follows:
 *  
 *  (A) If possible, choose NextN such that (N,NextN) is a fixed edge, or
 *      is common to two or more tours to be merged.
 *  (B) Otherwise, if possible, and Trial = 1, choose NextN such that 
 *      (N,NextN) is an edge of a given initial tour.
 *  (C) Otherwise, if possible, choose NextN so that (N,NextN) is a 
 *      candidate edge, the alpha-value of (N,NextN) is zero, and (N,NextN) 
 *      belongs to the current best or next best tour.
 *  (D) Otherwise, if possible, choose NextN such that (N,NextN) is a 
 *      candidate edge.
 *  (E) Otherwise, choose NextN at random among those nodes not already 
 *      chosen.
 *
 *  When more than one node may be chosen, the node is chosen at random 
 *  among the alternatives (a one-way list of nodes). 
 *
 *  The sequence of chosen nodes constitutes the initial tour.
 */

static int FixedOrCommonCandidates(Node * N);

void ChooseInitialTour()
{
    Node *N, *NextN, *FirstAlternative, *Last;
    Candidate *NN;
    int Alternatives, Count = 0, i;

    if (lkh.KickType > 0 && lkh.Kicks > 0 && lkh.Trial > 1) {
        for (Last = lkh.FirstNode; (N = Last->BestSuc) != lkh.FirstNode; Last = N)
            Follow(N, Last);
        for (i = 1; i <= lkh.Kicks; i++)
            KSwapKick(lkh.KickType);
        return;
    }
    if (lkh.Trial == 1 && (!lkh.FirstNode->InitialSuc || lkh.InitialTourFraction < 1)) {
        if (lkh.InitialTourAlgorithm == BORUVKA ||
            lkh.InitialTourAlgorithm == GREEDY ||
            lkh.InitialTourAlgorithm == MOORE ||
            lkh.InitialTourAlgorithm == NEAREST_NEIGHBOR ||
            lkh.InitialTourAlgorithm == QUICK_BORUVKA ||
            lkh.InitialTourAlgorithm == SIERPINSKI) {
            GainType Cost = lkh.InitialTourAlgorithm == MOORE ||
                lkh.InitialTourAlgorithm == SIERPINSKI ?
                SFCTour(lkh.InitialTourAlgorithm) : GreedyTour();
            if (lkh.MaxTrials == 0) {
                lkh.BetterCost = Cost;
                RecordBetterTour();
            }
            if (!lkh.FirstNode->InitialSuc)
                return;
        }
    }

Start:
    /* Mark all nodes as "not chosen" by setting their V field to zero */
    N = lkh.FirstNode;
    do
        N->V = 0;
    while ((N = N->Suc) != lkh.FirstNode);

    /* Choose lkh.FirstNode without two incident fixed or common candidate edges */
    do {
        if (FixedOrCommonCandidates(N) < 2)
            break;
    }
    while ((N = N->Suc) != lkh.FirstNode);
    lkh.FirstNode = N;

    /* Move nodes with two incident fixed or common candidate edges in 
       front of lkh.FirstNode */
    for (Last = lkh.FirstNode->Pred; N != Last; N = NextN) {
        NextN = N->Suc;
        if (FixedOrCommonCandidates(N) == 2)
            Follow(N, Last);
    }

    /* Mark lkh.FirstNode as chosen */
    lkh.FirstNode->V = 1;
    N = lkh.FirstNode;

    /* Loop as long as not all nodes have been chosen */
    while (N->Suc != lkh.FirstNode) {
        FirstAlternative = 0;
        Alternatives = 0;
        Count++;

        /* Case A */
        for (NN = N->CandidateSet; (NextN = NN->To); NN++) {
            if (!NextN->V && FixedOrCommon(N, NextN)) {
                Alternatives++;
                NextN->Next = FirstAlternative;
                FirstAlternative = NextN;
            }
        }
        if (Alternatives == 0 && lkh.FirstNode->InitialSuc && lkh.Trial == 1 &&
            Count <= lkh.InitialTourFraction * lkh.Dimension) {
            /* Case B */
            for (NN = N->CandidateSet; (NextN = NN->To); NN++) {
                if (!NextN->V && InInitialTour(N, NextN)) {
                    Alternatives++;
                    NextN->Next = FirstAlternative;
                    FirstAlternative = NextN;
                }
            }
        }
        if (Alternatives == 0 && lkh.Trial > 1 &&
                lkh.ProblemType != HCP && lkh.ProblemType != HPP) {
            /* Case C */
            for (NN = N->CandidateSet; (NextN = NN->To); NN++) {
                if (!NextN->V && FixedOrCommonCandidates(NextN) < 2 &&
                    NN->Alpha == 0 && (InBestTour(N, NextN) ||
                                       InNextBestTour(N, NextN))) {
                    Alternatives++;
                    NextN->Next = FirstAlternative;
                    FirstAlternative = NextN;
                }
            }
        }
        if (Alternatives == 0) {
            /* Case D */
            for (NN = N->CandidateSet; (NextN = NN->To); NN++) {
                if (!NextN->V && FixedOrCommonCandidates(NextN) < 2) {
                    Alternatives++;
                    NextN->Next = FirstAlternative;
                    FirstAlternative = NextN;
                }
            }
        }
        if (Alternatives == 0) {
            /* Case E (actually not really a random choice) */
            NextN = N->Suc;
            while ((FixedOrCommonCandidates(NextN) == 2 || Forbidden(N, NextN))
                   && NextN->Suc != lkh.FirstNode)
                NextN = NextN->Suc;
            if (FixedOrCommonCandidates(NextN) == 2 || Forbidden(N, NextN)) {
                lkh.FirstNode = lkh.FirstNode->Suc;
                goto Start;
            }
        } else {
            NextN = FirstAlternative;
            if (Alternatives > 1) {
                /* Select NextN at random among the alternatives */
                i = Random() % Alternatives;
                while (i--)
                    NextN = NextN->Next;
            }
        }
        /* Include NextN as the successor of N */
        Follow(NextN, N);
        N = NextN;
        N->V = 1;
    }
    if (Forbidden(N, N->Suc)) {
        lkh.FirstNode = lkh.FirstNode->Suc;
        goto Start;
    }
    if (lkh.MaxTrials == 0) {
        GainType Cost = 0;
        N = lkh.FirstNode;
        do
            Cost += lkh.C(N, N->Suc) - N->Pi - N->Suc->Pi;
        while ((N = N->Suc) != lkh.FirstNode);
        Cost /= lkh.Precision;
        if (Cost < lkh.BetterCost) {
            lkh.BetterCost = Cost;
            RecordBetterTour();
        }
    }
}

/* 
 * The FixedOrCommonCandidates function returns the number of fixed or
 * common candidate edges emanating from a given node, N.
 */

static int FixedOrCommonCandidates(Node * N)
{
    int Count = 0;
    Candidate *NN;

    if (N->FixedTo2)
        return 2;
    if (!N->FixedTo1 && lkh.MergeTourFiles < 2)
        return 0;
    for (NN = N->CandidateSet; NN->To; NN++)
        if (FixedOrCommon(N, NN->To))
            Count++;
    return Count;
}
