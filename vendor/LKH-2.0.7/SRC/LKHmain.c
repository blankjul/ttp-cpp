#include "LKH.h"
#include "Genetic.h"

/*
 * This file contains the executables function of the program.
 */



int main(int argc, char *argv[])
{



    /* Read the specification of the problem */
    if (argc >= 2)
        lkh.ParameterFileName = argv[1];
    ReadParameters();
    lkh.MaxMatrixDimension = 10000;
    ReadProblem();

    return calc();


}




int calc() {

    GainType Cost, OldOptimum;
    double Time, LastTime = GetTime();

    if (lkh.SubproblemSize > 0) {
        if (lkh.DelaunayPartitioning)
            SolveDelaunaySubproblems();
        else if (lkh.KarpPartitioning)
            SolveKarpSubproblems();
        else if (lkh.KCenterPartitioning)
            SolveKCenterSubproblems();
        else if (lkh.KMeansPartitioning)
            SolveKMeansSubproblems();
        else if (lkh.RohePartitioning)
            SolveRoheSubproblems();
        else if (lkh.MoorePartitioning || lkh.SierpinskiPartitioning)
            SolveSFCSubproblems();
        else
            SolveTourSegmentSubproblems();
        return EXIT_SUCCESS;
    }
    AllocateStructures();
    CreateCandidateSet();
    InitializeStatistics();

    if (lkh.Norm != 0)
        lkh.BestCost = PLUS_INFINITY;
    else {
        /* The ascent has solved the problem! */
        lkh.Optimum = lkh.BestCost = (GainType) lkh.LowerBound;
        UpdateStatistics(lkh.Optimum, GetTime() - LastTime);
        RecordBetterTour();
        RecordBestTour();
        WriteTour(lkh.OutputTourFileName, lkh.BestTour, lkh.BestCost);
        WriteTour(lkh.TourFileName, lkh.BestTour, lkh.BestCost);
        lkh.Runs = 0;
    }

    /* Find a specified number (Runs) of local optima */
    for (lkh.Run = 1; lkh.Run <= lkh.Runs; lkh.Run++) {
        LastTime = GetTime();
        Cost = FindTour();      /* using the Lin-Kernighan heuristic */
        if (lkh.MaxPopulationSize > 1) {
            /* Genetic algorithm */
            int i;
            for (i = 0; i < lkh.PopulationSize; i++) {
                GainType OldCost = Cost;
                Cost = MergeTourWithIndividual(i);
                if (lkh.TraceLevel >= 1 && Cost < OldCost) {
                    printff("  Merged with %d: Cost = " GainFormat, i + 1,
                            Cost);
                    if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                        printff(", Gap = %0.4f%%",
                                100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                    printff("\n");
                }
            }
            if (!HasFitness(Cost)) {
                if (lkh.PopulationSize < lkh.MaxPopulationSize) {
                    AddToPopulation(Cost);
                    if (lkh.TraceLevel >= 1)
                        PrintPopulation();
                } else if (Cost < lkh.Fitness[lkh.PopulationSize - 1]) {
                    i = ReplacementIndividual(Cost);
                    ReplaceIndividualWithTour(i, Cost);
                    if (lkh.TraceLevel >= 1)
                        PrintPopulation();
                }
            }
        } else if (lkh.Run > 1)
            Cost = MergeBetterTourWithBestTour();
        if (Cost < lkh.BestCost) {
            lkh.BestCost = Cost;
            RecordBetterTour();
            RecordBestTour();
            WriteTour(lkh.OutputTourFileName, lkh.BestTour, lkh.BestCost);
            WriteTour(lkh.TourFileName, lkh.BestTour, lkh.BestCost);
        }
        OldOptimum = lkh.Optimum;
        if (Cost < lkh.Optimum) {
            if (lkh.FirstNode->InputSuc) {
                Node *N = lkh.FirstNode;
                while ((N = N->InputSuc = N->Suc) != lkh.FirstNode);
            }
            lkh.Optimum = Cost;
            printff("*** New optimum = " GainFormat " ***\n\n", lkh.Optimum);
        }
        Time = fabs(GetTime() - LastTime);
        UpdateStatistics(Cost, Time);
        if (lkh.TraceLevel >= 1 && Cost != PLUS_INFINITY) {
            printff("Run %d: Cost = " GainFormat, lkh.Run, Cost);
            if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                printff(", Gap = %0.4f%%",
                        100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
            printff(", Time = %0.2f sec. %s\n\n", Time,
                    Cost < lkh.Optimum ? "<" : Cost == lkh.Optimum ? "=" : "");
        }
        if (lkh.StopAtOptimum && Cost == OldOptimum && lkh.MaxPopulationSize >= 1) {
            lkh.Runs = lkh.Run;
            break;
        }
        if (lkh.PopulationSize >= 2 &&
            (lkh.PopulationSize == lkh.MaxPopulationSize ||
                    lkh.Run >= 2 * lkh.MaxPopulationSize) && lkh.Run < lkh.Runs) {
            Node *N;
            int Parent1, Parent2;
            Parent1 = LinearSelection(lkh.PopulationSize, 1.25);
            do
                Parent2 = LinearSelection(lkh.PopulationSize, 1.25);
            while (Parent2 == Parent1);
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
    }
    PrintStatistics();
    return EXIT_SUCCESS;
}

