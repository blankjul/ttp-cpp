#include "LKH.h"

/*
 * The CreateCandidateSet function determines for each node its set of incident
 * candidate edges.
 *
 * The Ascent function is called to determine a lower bound on the optimal tour 
 * using subgradient optimization. But only if the penalties (the Pi-values) is
 * not available on file. In the latter case, the penalties is read from the 
 * file, and the lower bound is computed from a minimum 1-tree.      
 *
 * The function GenerateCandidates is called to compute the Alpha-values and to 
 * associate to each node a set of incident candidate edges.  
 *
 * The CreateCandidateSet function itself is called from LKHmain.
 */

void CreateCandidateSet()
{
    GainType Cost, MaxAlpha, A;
    Node *Na;
    int CandidatesRead = 0, i;
    double EntryTime = GetTime();

    lkh.Norm = 9999;
    if (lkh.C == C_EXPLICIT) {
        Na = lkh.FirstNode;
        do {
            for (i = 1; i < Na->Id; i++)
                Na->C[i] *= lkh.Precision;
        }
        while ((Na = Na->Suc) != lkh.FirstNode);
    }
    if (lkh.Distance == Distance_1 ||
        (lkh.MaxTrials == 0 &&
         (lkh.FirstNode->InitialSuc || lkh.InitialTourAlgorithm == SIERPINSKI ||
                 lkh.InitialTourAlgorithm == MOORE))) {
        ReadCandidates(lkh.MaxCandidates);
        AddTourCandidates();
        if (lkh.ProblemType == HCP || lkh.ProblemType == HPP)
            Ascent();
        goto End_CreateCandidateSet;
    }
    if (lkh.TraceLevel >= 2)
        printff("Creating candidates ...\n");
    if (lkh.MaxCandidates > 0 &&
        (lkh.CandidateSetType == QUADRANT || lkh.CandidateSetType == NN)) {
        ReadPenalties();
        if (!(CandidatesRead = ReadCandidates(lkh.MaxCandidates)) &&
                lkh.MaxCandidates > 0) {
            if (lkh.CandidateSetType == QUADRANT)
                CreateQuadrantCandidateSet(lkh.MaxCandidates);
            else if (lkh.CandidateSetType == NN)
                CreateNearestNeighborCandidateSet(lkh.MaxCandidates);
        } else {
            AddTourCandidates();
            if (lkh.CandidateSetSymmetric)
                SymmetrizeCandidateSet();
        }
        goto End_CreateCandidateSet;
    }
    if (!ReadPenalties()) {
        /* No PiFile specified or available */
        Na = lkh.FirstNode;
        do
            Na->Pi = 0;
        while ((Na = Na->Suc) != lkh.FirstNode);
        CandidatesRead = ReadCandidates(lkh.MaxCandidates);
        Cost = Ascent();
        if (lkh.Subgradient && lkh.SubproblemSize == 0) {
            WritePenalties();
            lkh.PiFile = 0;
        }
    } else if ((CandidatesRead = ReadCandidates(lkh.MaxCandidates)) ||
            lkh.MaxCandidates == 0) {
        AddTourCandidates();
        if (lkh.CandidateSetSymmetric)
            SymmetrizeCandidateSet();
        goto End_CreateCandidateSet;
    } else {
        if (lkh.CandidateSetType != DELAUNAY && lkh.MaxCandidates > 0) {
            if (lkh.TraceLevel >= 2)
                printff("Computing lower bound ... ");
            Cost = Minimum1TreeCost(0);
            if (lkh.TraceLevel >= 2)
                printff("done\n");
        } else {
            CreateDelaunayCandidateSet();
            Na = lkh.FirstNode;
            do {
                Na->BestPi = Na->Pi;
                Na->Pi = 0;
            }
            while ((Na = Na->Suc) != lkh.FirstNode);
            if (lkh.TraceLevel >= 2)
                printff("Computing lower bound ... ");
            Cost = Minimum1TreeCost(1);
            if (lkh.TraceLevel >= 2)
                printff("done\n");
            Na = lkh.FirstNode;
            do {
                Na->Pi = Na->BestPi;
                Cost -= 2 * Na->Pi;
            }
            while ((Na = Na->Suc) != lkh.FirstNode);
        }
    }
    lkh.LowerBound = (double) Cost / lkh.Precision;
    if (lkh.TraceLevel >= 1) {
        printff("Lower bound = %0.1f", lkh.LowerBound);
        if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
            printff(", Gap = %0.2f%%",
                    100.0 * (lkh.Optimum - lkh.LowerBound) / lkh.Optimum);
        if (!lkh.PiFile)
            printff(", Ascent time = %0.2f sec.",
                    fabs(GetTime() - EntryTime));
        printff("\n");
    }
    MaxAlpha = (GainType) fabs(lkh.Excess * Cost);
    if ((A = lkh.Optimum * lkh.Precision - Cost) > 0 && A < MaxAlpha)
        MaxAlpha = A;
    if (lkh.CandidateSetType == DELAUNAY || lkh.MaxCandidates == 0)
        OrderCandidateSet(lkh.MaxCandidates, MaxAlpha, lkh.CandidateSetSymmetric);
    else
        GenerateCandidates(lkh.MaxCandidates, MaxAlpha, lkh.CandidateSetSymmetric);

  End_CreateCandidateSet:
    if (lkh.ExtraCandidates > 0) {
        AddExtraCandidates(lkh.ExtraCandidates,
                           lkh.ExtraCandidateSetType,
                           lkh.ExtraCandidateSetSymmetric);
        AddTourCandidates();
    }
    ResetCandidateSet();
    Na = lkh.FirstNode;
    do {
        if (!Na->CandidateSet || !Na->CandidateSet[0].To) {
            if (lkh.MaxCandidates == 0)
                eprintf("MAX_CANDIDATES = 0: Node %d has no candidates", 
                        Na->Id);
            else
                eprintf("Node %d has no candidates", Na->Id);
        }
    }
    while ((Na = Na->Suc) != lkh.FirstNode);
    if (!CandidatesRead && lkh.SubproblemSize == 0)
        WriteCandidates();
    if (lkh.C == C_EXPLICIT) {
        Na = lkh.FirstNode;
        do
            for (i = 1; i < Na->Id; i++)
                Na->C[i] += Na->Pi + lkh.NodeSet[i].Pi;
        while ((Na = Na->Suc) != lkh.FirstNode);
    }
    if (lkh.TraceLevel >= 1) {
        CandidateReport();
        printff("Preprocessing time = %0.2f sec.\n",
                fabs(GetTime() - EntryTime));
    }
}
