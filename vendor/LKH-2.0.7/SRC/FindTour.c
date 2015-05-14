#include "LKH.h"

/*
 * After the candidate set has been created the FindTour function is called 
 * a predetermined number of times (Runs). 
 *
 * FindTour performs a number of trials, where in each trial it attempts 
 * to improve a chosen initial tour using the modified Lin-Kernighan edge 
 * exchange heuristics. 
 *
 * Each time a better tour is found, the tour is recorded, and the candidates 
 * are reorderded by the AdjustCandidateSet function. Precedence is given to 
 * edges that are common to two currently best tours. The candidate set is 
 * extended with those tour edges that are not present in the current set. 
 * The original candidate set is re-established at exit from FindTour.  
 */

static void SwapCandidateSets();
static GainType OrdinalTourCost;

GainType FindTour()
{
    GainType Cost;
    Node *t;
    int i;
    double EntryTime = GetTime();

    t = lkh.FirstNode;
    do
        t->OldPred = t->OldSuc = t->NextBestSuc = t->BestSuc = 0;
    while ((t = t->Suc) != lkh.FirstNode);
    if (lkh.Run == 1 && lkh.Dimension == lkh.DimensionSaved) {
        OrdinalTourCost = 0;
        for (i = 1; i < lkh.Dimension; i++)
            OrdinalTourCost += lkh.C(&lkh.NodeSet[i], &lkh.NodeSet[i + 1])
                - lkh.NodeSet[i].Pi - lkh.NodeSet[i + 1].Pi;
        OrdinalTourCost += lkh.C(&lkh.NodeSet[lkh.Dimension], &lkh.NodeSet[1])
            - lkh.NodeSet[lkh.Dimension].Pi - lkh.NodeSet[1].Pi;
        OrdinalTourCost /= lkh.Precision;
    }
    lkh.BetterCost = PLUS_INFINITY;
    if (lkh.MaxTrials > 0)
        HashInitialize(lkh.HTable);
    else {
        lkh.Trial = 1;
        ChooseInitialTour();
    }

    for (lkh.Trial = 1; lkh.Trial <= lkh.MaxTrials; lkh.Trial++) {
        if (GetTime() - EntryTime >= lkh.TimeLimit) {
            if (lkh.TraceLevel >= 1)
                printff("*** Time limit exceeded ***\n");
            break;
        }
        /* Choose FirstNode at random */
        if (lkh.Dimension == lkh.DimensionSaved)
            lkh.FirstNode = &lkh.NodeSet[1 + Random() % lkh.Dimension];
        else
            for (i = Random() % lkh.Dimension; i > 0; i--)
                lkh.FirstNode = lkh.FirstNode->Suc;
        ChooseInitialTour();
        Cost = LinKernighan();
        if (lkh.FirstNode->BestSuc) {
            /* Merge tour with current best tour */
            t = lkh.FirstNode;
            while ((t = t->Next = t->BestSuc) != lkh.FirstNode);
            Cost = MergeWithTour();
        }
        if (lkh.Dimension == lkh.DimensionSaved && Cost >= OrdinalTourCost &&
                lkh.BetterCost > OrdinalTourCost) {
            /* Merge tour with ordinal tour */
            for (i = 1; i < lkh.Dimension; i++)
                lkh.NodeSet[i].Next = &lkh.NodeSet[i + 1];
            lkh.NodeSet[lkh.Dimension].Next = &lkh.NodeSet[1];
            Cost = MergeWithTour();
        }
        if (Cost < lkh.BetterCost) {
            if (lkh.TraceLevel >= 1) {
                printff("* %d: Cost = " GainFormat, lkh.Trial, Cost);
                if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                    printff(", Gap = %0.4f%%",
                            100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                printff(", Time = %0.2f sec. %s\n",
                        fabs(GetTime() - EntryTime),
                        Cost < lkh.Optimum ? "<" : Cost == lkh.Optimum ? "=" : "");
            }
            lkh.BetterCost = Cost;
            RecordBetterTour();
            if (lkh.Dimension == lkh.DimensionSaved && lkh.BetterCost < lkh.BestCost)
                WriteTour(lkh.OutputTourFileName, lkh.BetterTour, lkh.BetterCost);
            if (lkh.StopAtOptimum && lkh.BetterCost == lkh.Optimum)
                break;
            AdjustCandidateSet();
            HashInitialize(lkh.HTable);
            HashInsert(lkh.HTable, lkh.Hash, Cost);
        } else if (lkh.TraceLevel >= 2)
            printff("  %d: Cost = " GainFormat ", Time = %0.2f sec.\n",
                    lkh.Trial, Cost, fabs(GetTime() - EntryTime));
        /* Record backbones if wanted */
        if (lkh.Trial <= lkh.BackboneTrials && lkh.BackboneTrials < lkh.MaxTrials) {
            SwapCandidateSets();
            AdjustCandidateSet();
            if (lkh.Trial == lkh.BackboneTrials) {
                if (lkh.TraceLevel >= 1) {
                    printff("# %d: Backbone candidates ->\n", lkh.Trial);
                    CandidateReport();
                }
            } else
                SwapCandidateSets();
        }
    }
    if (lkh.BackboneTrials > 0 && lkh.BackboneTrials < lkh.MaxTrials) {
        if (lkh.Trial > lkh.BackboneTrials ||
            (lkh.Trial == lkh.BackboneTrials &&
             (!lkh.StopAtOptimum || lkh.BetterCost != lkh.Optimum)))
            SwapCandidateSets();
        t = lkh.FirstNode;
        do {
            free(t->BackboneCandidateSet);
            t->BackboneCandidateSet = 0;
        } while ((t = t->Suc) != lkh.FirstNode);
    }
    t = lkh.FirstNode;
    if (lkh.Norm == 0) {
        do
            t = t->BestSuc = t->Suc;
        while (t != lkh.FirstNode);
    }
    do
        (t->Suc = t->BestSuc)->Pred = t;
    while ((t = t->BestSuc) != lkh.FirstNode);
    if (lkh.Trial > lkh.MaxTrials)
        lkh.Trial = lkh.MaxTrials;
    ResetCandidateSet();
    return lkh.BetterCost;
}

/*
 * The SwapCandidateSets function swaps the normal and backbone candidate sets.
 */

static void SwapCandidateSets()
{
    Node *t = lkh.FirstNode;
    do {
        Candidate *Temp = t->CandidateSet;
        t->CandidateSet = t->BackboneCandidateSet;
        t->BackboneCandidateSet = Temp;
    } while ((t = t->Suc) != lkh.FirstNode);
}
