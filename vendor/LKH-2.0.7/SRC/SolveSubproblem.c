#include "LKH.h"
#include "Genetic.h"

/* 
 * The SolveSubproblem solves a given subproblem. The subproblem is 
 * identified by the parameter CurrentSuproblem and contains all 
 * nodes with Subproblem equal to CurrentSubproblem.   
 *  
 * The parameter Subproblems specifies the number of subproblems.
 * The parameter GlobalBestCost references the current best cost of the 
 * whole problem.
 *
 * If the subproblem is too small (Dimension <= 3), the function returns 0;
 * otherwise 1. 
 */

int
SolveSubproblem(int CurrentSubproblem, int Subproblems,
                GainType * GlobalBestCost)
{
    Node *FirstNodeSaved = lkh.FirstNode, *N, *Next, *Last = 0;
    GainType OptimumSaved = lkh.Optimum, Cost, Improvement, GlobalCost;
    double LastTime, Time, ExcessSaved = lkh.Excess;
    int NewDimension = 0, OldDimension = 0, Number, i, InitialTourEdges = 0,
        AscentCandidatesSaved = lkh.AscentCandidates,
        InitialPeriodSaved = lkh.InitialPeriod, MaxTrialsSaved = lkh.MaxTrials;

    lkh.BestCost = PLUS_INFINITY;
    lkh.FirstNode = 0;
    N = FirstNodeSaved;
    do {
        if (N->Subproblem == CurrentSubproblem) {
            if (lkh.SubproblemsCompressed &&
                (((N->SubproblemPred == N->SubBestPred ||
                   FixedOrCommon(N, N->SubproblemPred) ||
                   (N->SubBestPred &&
                    (N->FixedTo1Saved == N->SubBestPred ||
                     N->FixedTo2Saved == N->SubBestPred))) &&
                  (N->SubproblemSuc == N->SubBestSuc ||
                   FixedOrCommon(N, N->SubproblemSuc) ||
                   (N->SubBestSuc &&
                    (N->FixedTo1Saved == N->SubBestSuc ||
                     N->FixedTo2Saved == N->SubBestSuc)))) ||
                 ((N->SubproblemPred == N->SubBestSuc ||
                   FixedOrCommon(N, N->SubproblemPred) ||
                   (N->SubBestSuc &&
                    (N->FixedTo1Saved == N->SubBestSuc ||
                     N->FixedTo2Saved == N->SubBestSuc))) &&
                  (N->SubproblemSuc == N->SubBestPred ||
                   FixedOrCommon(N, N->SubproblemSuc) ||
                   (N->SubBestPred &&
                    (N->FixedTo1Saved == N->SubBestPred ||
                     N->FixedTo2Saved == N->SubBestPred))))))
                N->Subproblem = -CurrentSubproblem;
            else {
                if (!lkh.FirstNode)
                    lkh.FirstNode = N;
                NewDimension++;
            }
            N->Head = N->Tail = 0;
            if (N->SubBestSuc)
                OldDimension++;
        }
        N->SubBestPred = N->SubBestSuc = 0;
        N->FixedTo1Saved = N->FixedTo1;
        N->FixedTo2Saved = N->FixedTo2;
    } while ((N = N->SubproblemSuc) != FirstNodeSaved);
    if ((Number = CurrentSubproblem % Subproblems) == 0)
        Number = Subproblems;
    if (NewDimension <= 3 || NewDimension == OldDimension) {
        if (lkh.TraceLevel >= 1 && NewDimension <= 3)
            printff
                ("\nSubproblem %d of %d: Dimension = %d (too small)\n",
                 Number, Subproblems, NewDimension);
        lkh.FirstNode = FirstNodeSaved;
        return 0;
    }
    if (lkh.AscentCandidates > NewDimension - 1)
        lkh.AscentCandidates = NewDimension - 1;
    if (lkh.InitialPeriod < 0) {
        lkh.InitialPeriod = NewDimension / 2;
        if (lkh.InitialPeriod < 100)
            lkh.InitialPeriod = 100;
    }
    if (lkh.Excess < 0)
        lkh.Excess = 1.0 / NewDimension;
    if (lkh.MaxTrials == -1)
        lkh.MaxTrials = NewDimension;
    N = lkh.FirstNode;
    do {
        Next = N->SubproblemSuc;
        if (N->Subproblem == CurrentSubproblem) {
            N->Pred = N->Suc = N;
            if (N != lkh.FirstNode)
                Follow(N, Last);
            Last = N;
        } else if (Next->Subproblem == CurrentSubproblem
                   && !Fixed(Last, Next)) {
            if (!Last->FixedTo1
                || Last->FixedTo1->Subproblem != CurrentSubproblem)
                Last->FixedTo1 = Next;
            else
                Last->FixedTo2 = Next;
            if (!Next->FixedTo1
                || Next->FixedTo1->Subproblem != CurrentSubproblem)
                Next->FixedTo1 = Last;
            else
                Next->FixedTo2 = Last;
            if (lkh.C == C_EXPLICIT) {
                if (Last->Id > Next->Id)
                    Last->C[Next->Id] = 0;
                else
                    Next->C[Last->Id] = 0;
            }
        }
    }
    while ((N = Next) != lkh.FirstNode);

    lkh.Dimension = NewDimension;
    AllocateSegments();
    InitializeStatistics();
    if (lkh.CacheSig)
        for (i = 0; i <= lkh.CacheMask; i++)
            lkh.CacheSig[i] = 0;
    OptimumSaved = lkh.Optimum;
    lkh.Optimum = 0;
    N = lkh.FirstNode;
    do {
        if (N->SubproblemSuc == N->InitialSuc ||
            N->SubproblemPred == N->InitialSuc)
            InitialTourEdges++;
        if (!Fixed(N, N->Suc))
            lkh.Optimum += lkh.Distance(N, N->Suc);
        if (N->FixedTo1 && N->Subproblem != N->FixedTo1->Subproblem)
            eprintf("Illegal fixed edge (%d,%d)", N->Id, N->FixedTo1->Id);
        if (N->FixedTo2 && N->Subproblem != N->FixedTo2->Subproblem)
            eprintf("Illegal fixed edge (%d,%d)", N->Id, N->FixedTo2->Id);
    }
    while ((N = N->Suc) != lkh.FirstNode);
    if (lkh.TraceLevel >= 1)
        printff
            ("\nSubproblem %d of %d: Dimension = %d, Upper bound = "
             GainFormat "\n", Number, Subproblems, lkh.Dimension, lkh.Optimum);
    FreeCandidateSets();
    CreateCandidateSet();

    for (lkh.Run = 1; lkh.Run <= lkh.Runs; lkh.Run++) {
        LastTime = GetTime();
        Cost = lkh.Norm != 0 ? FindTour() : lkh.Optimum;
        /* Merge with subproblem tour */
        Last = 0;
        N = lkh.FirstNode;
        do {
            if (N->Subproblem == CurrentSubproblem) {
                if (Last)
                    Last->Next = N;
                Last = N;
            }
        }
        while ((N = N->SubproblemSuc) != lkh.FirstNode);
        Last->Next = lkh.FirstNode;
        Cost = MergeWithTour();
        if (lkh.MaxPopulationSize > 1) {
            /* Genetic algorithm */
            for (i = 0; i < lkh.PopulationSize; i++)
                Cost = MergeTourWithIndividual(i);
            if (!HasFitness(Cost)) {
                if (lkh.PopulationSize < lkh.MaxPopulationSize) {
                    AddToPopulation(Cost);
                    if (lkh.TraceLevel >= 1)
                        PrintPopulation();
                } else if (Cost < lkh.Fitness[lkh.PopulationSize - 1]) {
                    ReplaceIndividualWithTour(lkh.PopulationSize - 1, Cost);
                    if (lkh.TraceLevel >= 1)
                        PrintPopulation();
                }
            }
        }
        if (Cost < lkh.BestCost) {
            N = lkh.FirstNode;
            do {
                N->SubBestPred = N->Pred;
                N->SubBestSuc = N->Suc;
            } while ((N = N->Suc) != lkh.FirstNode);
            lkh.BestCost = Cost;
        }
        if (Cost < lkh.Optimum || (Cost != lkh.Optimum && lkh.OutputTourFileName)) {
            Improvement = lkh.Optimum - Cost;
            if (Improvement > 0) {
                lkh.BestCost = GlobalCost = *GlobalBestCost -= Improvement;
                lkh.Optimum = Cost;
            } else
                GlobalCost = *GlobalBestCost - Improvement;
            N = lkh.FirstNode;
            do
                N->Mark = 0;
            while ((N = N->SubproblemSuc) != lkh.FirstNode);
            do {
                N->Mark = N;
                if (!N->SubproblemSuc->Mark &&
                    (N->Subproblem != CurrentSubproblem ||
                     N->SubproblemSuc->Subproblem != CurrentSubproblem))
                    N->BestSuc = N->SubproblemSuc;
                else if (!N->SubproblemPred->Mark &&
                         (N->Subproblem != CurrentSubproblem ||
                          N->SubproblemPred->Subproblem !=
                          CurrentSubproblem))
                    N->BestSuc = N->SubproblemPred;
                else if (!N->Suc->Mark)
                    N->BestSuc = N->Suc;
                else if (!N->Pred->Mark)
                    N->BestSuc = N->Pred;
                else
                    N->BestSuc = lkh.FirstNode;
            }
            while ((N = N->BestSuc) != lkh.FirstNode);
            lkh.Dimension = lkh.ProblemType != ATSP ? lkh.DimensionSaved :
                2 * lkh.DimensionSaved;
            i = 0;
            do {
                if (lkh.ProblemType != ATSP)
                    lkh.BetterTour[++i] = N->Id;
                else if (N->Id <= lkh.Dimension / 2) {
                    i++;
                    if (N->BestSuc->Id != N->Id + lkh.Dimension / 2)
                        lkh.BetterTour[i] = N->Id;
                    else
                        lkh.BetterTour[lkh.Dimension / 2 - i + 1] = N->Id;
                }
            }
            while ((N = N->BestSuc) != lkh.FirstNode);
            lkh.BetterTour[0] =
                    lkh.BetterTour[lkh.ProblemType !=
                           ATSP ? lkh.Dimension : lkh.Dimension / 2];
            WriteTour(lkh.OutputTourFileName, lkh.BetterTour, GlobalCost);
            if (Improvement > 0) {
                do
                    if (N->Subproblem != CurrentSubproblem)
                        break;
                while ((N = N->SubproblemPred) != lkh.FirstNode);
                if (N->SubproblemSuc == N->BestSuc) {
                    N = lkh.FirstNode;
                    do {
                        N->BestSuc->SubproblemPred = N;
                        N = N->SubproblemSuc = N->BestSuc;
                    }
                    while (N != lkh.FirstNode);
                } else {
                    N = lkh.FirstNode;
                    do
                        (N->SubproblemPred = N->BestSuc)->SubproblemSuc =
                            N;
                    while ((N = N->BestSuc) != lkh.FirstNode);
                }
                RecordBestTour();
                WriteTour(lkh.TourFileName, lkh.BestTour, GlobalCost);
            }
            lkh.Dimension = NewDimension;
            if (lkh.TraceLevel >= 1) {
                printff("*** %d: Cost = " GainFormat, Number, GlobalCost);
                if (OptimumSaved != MINUS_INFINITY && OptimumSaved != 0)
                    printff(", Gap = %0.4f%%",
                            100.0 * (GlobalCost -
                                     OptimumSaved) / OptimumSaved);
                printff(", Time = %0.2f sec. %s\n",
                        fabs(GetTime() - LastTime),
                        GlobalCost < OptimumSaved ? "<" : GlobalCost ==
                        OptimumSaved ? "=" : "");
            }
        }

        Time = fabs(GetTime() - LastTime);
        UpdateStatistics(Cost, Time);
        if (lkh.TraceLevel >= 1 && Cost != PLUS_INFINITY)
            printff("Run %d: Cost = " GainFormat ", Time = %0.2f sec.\n\n",
                    lkh.Run, Cost, Time);
        if (lkh.PopulationSize >= 2 &&
            (lkh.PopulationSize == lkh.MaxPopulationSize
             || lkh.Run >= 2 * lkh.MaxPopulationSize) && lkh.Run < lkh.Runs) {
            Node *N;
            int Parent1, Parent2;
            Parent1 = LinearSelection(lkh.PopulationSize, 1.25);
            do
                Parent2 = LinearSelection(lkh.PopulationSize, 1.25);
            while (Parent1 == Parent2);
            ApplyCrossover(Parent1, Parent2);
            N = lkh.FirstNode;
            do {
                int d = lkh.C(N, N->Suc);
                AddCandidate(N, N->Suc, d, INT_MAX);
                AddCandidate(N->Suc, N, d, INT_MAX);
                N = N->InitialSuc = N->Suc;
            }
            while (N != lkh.FirstNode);
        }
        SRandom(++lkh.Seed);
        if (lkh.Norm == 0)
            break;
    }

    if (lkh.TraceLevel >= 1)
        PrintStatistics();

    if (lkh.C == C_EXPLICIT) {
        N = lkh.FirstNode;
        do {
            for (i = 1; i < N->Id; i++) {
                N->C[i] -= N->Pi + lkh.NodeSet[i].Pi;
                N->C[i] /= lkh.Precision;
            }
            if (N->FixedTo1 && N->FixedTo1 != N->FixedTo1Saved) {
                if (N->Id > N->FixedTo1->Id)
                    N->C[N->FixedTo1->Id] = lkh.Distance(N, N->FixedTo1);
                else
                    N->FixedTo1->C[N->Id] = lkh.Distance(N, N->FixedTo1);
            }
            if (N->FixedTo2 && N->FixedTo2 != N->FixedTo2Saved) {
                if (N->Id > N->FixedTo2->Id)
                    N->C[N->FixedTo2->Id] = lkh.Distance(N, N->FixedTo2);
                else
                    N->FixedTo2->C[N->Id] = lkh.Distance(N, N->FixedTo2);
            }
        }
        while ((N = N->Suc) != lkh.FirstNode);
    }

    FreeSegments();
    FreeCandidateSets();
    FreePopulation();
    if (InitialTourEdges == lkh.Dimension) {
        do
            N->InitialSuc = N->SubproblemSuc;
        while ((N = N->SubproblemSuc) != lkh.FirstNode);
    } else {
        do
            N->InitialSuc = 0;
        while ((N = N->SubproblemSuc) != lkh.FirstNode);
    }
    lkh.Dimension = lkh.ProblemType != ATSP ? lkh.DimensionSaved : 2 * lkh.DimensionSaved;
    N = lkh.FirstNode = FirstNodeSaved;
    do {
        N->Suc = N->BestSuc = N->SubproblemSuc;
        N->Suc->Pred = N;
        Next = N->FixedTo1;
        N->FixedTo1 = N->FixedTo1Saved;
        N->FixedTo1Saved = Next;
        Next = N->FixedTo2;
        N->FixedTo2 = N->FixedTo2Saved;
        N->FixedTo2Saved = Next;
    }
    while ((N = N->Suc) != lkh.FirstNode);
    lkh.Optimum = OptimumSaved;
    lkh.Excess = ExcessSaved;
    lkh.AscentCandidates = AscentCandidatesSaved;
    lkh.InitialPeriod = InitialPeriodSaved;
    lkh.MaxTrials = MaxTrialsSaved;
    return 1;
}
