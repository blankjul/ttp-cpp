#include "Segment.h"
#include "LKH.h"
#include "Hashing.h"
#include "Sequence.h"

/*
 * The LinKernighan function seeks to improve a tour by sequential 
 * and non-sequential edge exchanges.
 *
 * The function returns the cost of the resulting tour. 
 */

GainType LinKernighan()
{
    Node *t1, *t2, *SUCt1;
    GainType Gain, G0, Cost;
    int X2, i, it = 0;
    Candidate *Nt1;
    Segment *S;
    SSegment *SS;
    double EntryTime = GetTime();

    lkh.Reversed = 0;
    S = lkh.FirstSegment;
    i = 0;
    do {
        S->Size = 0;
        S->Rank = ++i;
        S->Reversed = 0;
        S->First = S->Last = 0;
    }
    while ((S = S->Suc) != lkh.FirstSegment);
    SS = lkh.FirstSSegment;
    i = 0;
    do {
        SS->Size = 0;
        SS->Rank = ++i;
        SS->Reversed = 0;
        SS->First = SS->Last = 0;
    }
    while ((SS = SS->Suc) != lkh.FirstSSegment);

    lkh.FirstActive = lkh.LastActive = 0;
    lkh.Swaps = 0;

    /* Compute the cost of the initial tour, Cost.
       Compute the corresponding hash value, Hash.
       Initialize the segment list.
       Make all nodes "active" (so that they can be used as t1). */
    Cost = 0;
    lkh.Hash = 0;
    i = 0;
    t1 = lkh.FirstNode;
    do {
        t2 = t1->OldSuc = t1->Suc;
        t1->OldPred = t1->Pred;
        t1->Rank = ++i;
        Cost += (t1->SucCost = t2->PredCost = lkh.C(t1, t2)) - t1->Pi - t2->Pi;
        lkh.Hash ^= lkh.Rand[t1->Id] * lkh.Rand[t2->Id];
        t1->Cost = INT_MAX;
        for (Nt1 = t1->CandidateSet; (t2 = Nt1->To); Nt1++)
            if (t2 != t1->Pred && t2 != t1->Suc && Nt1->Cost < t1->Cost)
                t1->Cost = Nt1->Cost;
        t1->Parent = S;
        S->Size++;
        if (S->Size == 1)
            S->First = t1;
        S->Last = t1;
        if (SS->Size == 0)
            SS->First = S;
        S->Parent = SS;
        SS->Last = S;
        if (S->Size == lkh.GroupSize) {
            S = S->Suc;
            SS->Size++;
            if (SS->Size == lkh.SGroupSize)
                SS = SS->Suc;
        }
        t1->OldPredExcluded = t1->OldSucExcluded = 0;
        t1->Next = 0;
        if (lkh.KickType == 0 || lkh.Kicks == 0 ||
            !InBestTour(t1, t1->Pred) || !InBestTour(t1, t1->Suc))
            Activate(t1);
    }
    while ((t1 = t1->Suc) != lkh.FirstNode);
    if (S->Size < lkh.GroupSize)
        SS->Size++;
    Cost /= lkh.Precision;
    if (lkh.TraceLevel >= 3 || (lkh.TraceLevel == 2 && Cost < lkh.BetterCost)) {
        printff("Cost = " GainFormat, Cost);
        if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
            printff(", Gap = %0.4f%%", 100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
        printff(", Time = %0.2f sec. %s\n", fabs(GetTime() - EntryTime),
                Cost < lkh.Optimum ? "<" : Cost == lkh.Optimum ? "=" : "");
    }
    lkh.PredSucCostAvailable = 1;

    /* Loop as long as improvements are found */
    do {
        /* Choose t1 as the first "active" node */
        while ((t1 = RemoveFirstActive())) {
            /* t1 is now "passive" */
            SUCt1 = SUC(t1);
            if ((lkh.TraceLevel >= 3 || (lkh.TraceLevel == 2 && lkh.Trial == 1)) &&
                ++it % (lkh.Dimension >= 100000 ? 10000 :
                        lkh.Dimension >= 10000 ? 1000 : 100) == 0)
                printff("#%d: Time = %0.2f sec.\n",
                        it, fabs(GetTime() - EntryTime));
            /* Choose t2 as one of t1's two neighbors on the tour */
            for (X2 = 1; X2 <= 2; X2++) {
                t2 = X2 == 1 ? PRED(t1) : SUCt1;
                if (FixedOrCommon(t1, t2) ||
                    (lkh.RestrictedSearch && Near(t1, t2) &&
                     (lkh.Trial == 1 ||
                      (lkh.Trial > lkh.BackboneTrials &&
                       (lkh.KickType == 0 || lkh.Kicks == 0)))))
                    continue;
                G0 = lkh.C(t1, t2);
                /* Try to find a tour-improving chain of moves */
                do
                    t2 = lkh.Swaps == 0 ? lkh.BestMove(t1, t2, &G0, &Gain) :
                         lkh.BestSubsequentMove(t1, t2, &G0, &Gain);
                while (t2);
                if (Gain > 0) {
                    /* An improvement has been found */
                    assert(Gain % lkh.Precision == 0);
                    Cost -= Gain / lkh.Precision;
                    if (lkh.TraceLevel >= 3 ||
                        (lkh.TraceLevel == 2 && Cost < lkh.BetterCost)) {
                        printff("Cost = " GainFormat, Cost);
                        if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                            printff(", Gap = %0.4f%%",
                                    100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                        printff(", Time = %0.2f sec. %s\n",
                                fabs(GetTime() - EntryTime),
                                Cost < lkh.Optimum ? "<" : Cost ==
                                                                   lkh.Optimum ? "=" : "");
                    }
                    StoreTour();
                    if (HashSearch(lkh.HTable, lkh.Hash, Cost))
                        goto End_LinKernighan;
                    /* Make t1 "active" again */
                    Activate(t1);
                    break;
                }
                RestoreTour();
            }
        }
        if (HashSearch(lkh.HTable, lkh.Hash, Cost))
            goto End_LinKernighan;
        HashInsert(lkh.HTable, lkh.Hash, Cost);
        /* Try to find improvements using non-sequential 4/5-opt moves */
        Gain = 0;
        if (lkh.Gain23Used && (Gain = Gain23()) > 0) {
            /* An improvement has been found */
            assert(Gain % lkh.Precision == 0);
            Cost -= Gain / lkh.Precision;
            StoreTour();
            if (lkh.TraceLevel >= 3 || (lkh.TraceLevel == 2 && Cost < lkh.BetterCost)) {
                printff("Cost = " GainFormat, Cost);
                if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                    printff(", Gap = %0.4f%%",
                            100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                printff(", Time = %0.2f sec. + %s\n",
                        fabs(GetTime() - EntryTime),
                        Cost < lkh.Optimum ? "<" : Cost == lkh.Optimum ? "=" : "");
            }
            if (HashSearch(lkh.HTable, lkh.Hash, Cost))
                goto End_LinKernighan;
        }
    }
    while (Gain > 0);

  End_LinKernighan:
  lkh.PredSucCostAvailable = 0;
    NormalizeNodeList();
    NormalizeSegmentList();
    return Cost;
}
