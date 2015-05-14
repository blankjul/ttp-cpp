#include <fstream>
#include <limits>
#include "lkh.h"



extern "C"
{
#include "LKH.h"
#include "Genetic.h"
#include "Heap.h"
}






namespace ttp {



    MapPtr LKHWrapper::createMap(std::string pathToFile) {

        ifstream file(pathToFile);
        if (!file) throw std::runtime_error("File " + pathToFile + " does not exist");

        //resetAllData();

        lkh.MaxMatrixDimension = numeric_limits<int>::max();

        // set the filePtr
        char filePtr[1024];
        strncpy(filePtr, pathToFile.c_str(), sizeof(filePtr));
        filePtr[sizeof(filePtr) - 1] = 0;
        lkh.ProblemFileName = filePtr;

        lkh.TraceLevel = 0;

        cout << "READING " << lkh.ProblemFileName << std::endl;


        ReadProblem();

        if (lkh.CostMatrix == 0) {
            throw std::runtime_error("Could not parse " + pathToFile + ". Wrong Format.");
        }

        /*
         * Parse the file and write the Map.
        */
        MapPtr map = make_shared<Map>(lkh.Dimension);

        Node *Ni, *Nj;
        Ni = lkh.FirstNode;

        int column = 0;



        do {
            int row = 0;
            if (Ni->C != 0) {
                for (Nj = lkh.FirstNode; Nj != Ni; Nj = Nj->Suc) {
                    int value = Fixed(Ni, Nj) ? 0 : lkh.Distance(Ni, Nj);
                    map->set(row, column, value);
                    ++row;

                }
            }
            Ni = Ni->Suc;
            ++column;
        }
        while (Ni != lkh.FirstNode);



        return map;

    }

    int* LKHWrapper::calc(MapPtr map) {

        //resetAllData();

        InitParameters();
        lkh.TraceLevel = 0;

        int i, K;
        lkh.ProblemType = TSP;
        lkh.WeightFormat = FULL_MATRIX;
        lkh.WeightType = EXPLICIT;
        lkh.C = lkh.WeightType == EXPLICIT ? C_EXPLICIT : C_FUNCTION;
        lkh.D = lkh.WeightType == EXPLICIT ? D_EXPLICIT : D_FUNCTION;
        lkh.Dimension = map->count();



        Node *Prev = 0, *N = 0;
        if (lkh.Dimension <= 0) eprintf("DIMENSION is not positive (or not specified)");

        assert(lkh.NodeSet = (Node *) calloc(lkh.Dimension + 1, sizeof(Node)));
        for (int i = 1; i <= lkh.Dimension; i++, Prev = N) {
            N = &lkh.NodeSet[i];
            if (i == 1)
                lkh.FirstNode = N;
            else
            Link(Prev, N);
            N->Id = i;
        }
        Link(N, lkh.FirstNode);



        Node *Ni, *Nj;
        assert(lkh.CostMatrix =
                       (int *) calloc((size_t) lkh.Dimension * (lkh.Dimension - 1) / 2,
                                      sizeof(int)));
        Ni = lkh.FirstNode->Suc;
        do {
            Ni->C =
                    &lkh.CostMatrix[(size_t) (Ni->Id - 1) * (Ni->Id - 2) / 2] - 1;
            if (lkh.ProblemType != HPP || Ni->Id < lkh.Dimension)
                for (Nj = lkh.FirstNode; Nj != Ni; Nj = Nj->Suc) {
                    Ni->C[Nj->Id] = Fixed(Ni, Nj) ? 0 : map->get(Ni->Id - 1, Nj->Id - 1);
                }
            else
                for (Nj = lkh.FirstNode; Nj != Ni; Nj = Nj->Suc) {
                    Ni->C[Nj->Id] = 0;
                }
        }
        while ((Ni = Ni->Suc) != lkh.FirstNode);
        lkh.WeightType = EXPLICIT;
        lkh.c = 0;



        lkh.Swaps = 0;


        /* Adjust parameters */
        if (lkh.Seed == 0)
            lkh.Seed = (unsigned) time(0);
        if (lkh.Precision == 0)
            lkh.Precision = 100;
        if (lkh.InitialStepSize == 0)
            lkh.InitialStepSize = 1;
        if (lkh.MaxSwaps < 0)
            lkh.MaxSwaps = lkh.Dimension;
        if (lkh.KickType > lkh.Dimension / 2)
            lkh.KickType = lkh.Dimension / 2;
        if (lkh.Runs == 0)
            lkh.Runs = 10;
        if (lkh.MaxCandidates > lkh.Dimension - 1)
            lkh.MaxCandidates = lkh.Dimension - 1;
        if (lkh.ExtraCandidates > lkh.Dimension - 1)
            lkh.ExtraCandidates = lkh.Dimension - 1;
        if (lkh.SubproblemSize >= lkh.Dimension)
            lkh.SubproblemSize = lkh.Dimension;
        else if (lkh.SubproblemSize == 0) {
            if (lkh.AscentCandidates > lkh.Dimension - 1)
                lkh.AscentCandidates = lkh.Dimension - 1;
            if (lkh.InitialPeriod < 0) {
                lkh.InitialPeriod = lkh.Dimension / 2;
                if (lkh.InitialPeriod < 100)
                    lkh.InitialPeriod = 100;
            }
            if (lkh.Excess < 0)
                lkh.Excess = 1.0 / lkh.Dimension;
            if (lkh.MaxTrials == -1)
                lkh.MaxTrials = lkh.Dimension;
            MakeHeap(lkh.Dimension);
        }

        if (lkh.SubsequentMoveType == 0)
            lkh.SubsequentMoveType = lkh.MoveType;
        K = lkh.MoveType >= lkh.SubsequentMoveType
            || !lkh.SubsequentPatching ? lkh.MoveType : lkh.SubsequentMoveType;
        if (lkh.PatchingC > K)
            lkh.PatchingC = K;
        if (lkh.PatchingA > 1 && lkh.PatchingA >= lkh.PatchingC)
            lkh.PatchingA = lkh.PatchingC > 2 ? lkh.PatchingC - 1 : 1;
        if (lkh.NonsequentialMoveType == -1 ||
            lkh.NonsequentialMoveType > K + lkh.PatchingC + lkh.PatchingA - 1)
            lkh.NonsequentialMoveType = K + lkh.PatchingC + lkh.PatchingA - 1;
        if (lkh.PatchingC >= 1 && lkh.NonsequentialMoveType >= 4) {
            lkh.BestMove = lkh.BestSubsequentMove = BestKOptMove;
            if (!lkh.SubsequentPatching && lkh.SubsequentMoveType <= 5) {
                MoveFunction BestOptMove[] =
                        { 0, 0, Best2OptMove, Best3OptMove,
                          Best4OptMove, Best5OptMove
                        };
                lkh.BestSubsequentMove = BestOptMove[lkh.SubsequentMoveType];
            }
        } else {
            MoveFunction BestOptMove[] = { 0, 0, Best2OptMove, Best3OptMove,
                                           Best4OptMove, Best5OptMove
            };
            lkh.BestMove = lkh.MoveType <= 5 ? BestOptMove[lkh.MoveType] : BestKOptMove;
            lkh.BestSubsequentMove = lkh.SubsequentMoveType <= 5 ?
                                     BestOptMove[lkh.SubsequentMoveType] : BestKOptMove;
        }
        if (lkh.ProblemType == HCP || lkh.ProblemType == HPP)
            lkh.MaxCandidates = 0;
        if (lkh.TraceLevel >= 1) {
            //printff("done\n");
            //PrintParameters();
        }


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
                    /*
                    if (lkh.TraceLevel >= 1 && Cost < OldCost) {
                        printff("  Merged with %d: Cost = " GainFormat, i + 1,
                                Cost);
                        if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                            printff(", Gap = %0.4f%%",
                                    100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                        printff("\n");
                    }
                     */
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
                //printff("*** New optimum = " GainFormat " ***\n\n", lkh.Optimum);
            }
            Time = fabs(GetTime() - LastTime);
            UpdateStatistics(Cost, Time);
            /*
            if (lkh.TraceLevel >= 1 && Cost != PLUS_INFINITY) {
                printff("Run %d: Cost = " GainFormat, lkh.Run, Cost);
                if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
                    printff(", Gap = %0.4f%%", 100.0 * (Cost - lkh.Optimum) / lkh.Optimum);
                printff(", Time = %0.2f sec. %s\n\n", Time,
                        Cost < lkh.Optimum ? "<" : Cost == lkh.Optimum ? "=" : "");
            }
             */
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

        return lkh.BestTour;
    }


}