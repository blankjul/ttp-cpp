#include "LKH.h"
#include "Genetic.h"

/*
 * The PrintParameters function prints the problem parameters to 
 * standard output. 
*/

void PrintParameters()
{
    int i;

    printff("ASCENT_CANDIDATES = %d\n", lkh.AscentCandidates);
    printff("BACKBONE_TRIALS = %d\n", lkh.BackboneTrials);
    printff("BACKTRACKING = %s\n", lkh.Backtracking ? "YES" : "NO");
    if (lkh.CandidateFiles == 0)
        printff("# CANDIDATE_FILE =\n");
    else
        for (i = 0; i < lkh.CandidateFiles; i++)
            printff("CANDIDATE_FILE = %s\n", lkh.CandidateFileName[i]);
    printff("CANDIDATE_SET_TYPE = %s%s\n",
            lkh.CandidateSetType == ALPHA ? "ALPHA" :
            lkh.CandidateSetType == DELAUNAY ? "DELAUNAY" :
            lkh.CandidateSetType == NN ? "NEAREST-NEIGHBOR" :
            lkh.CandidateSetType == QUADRANT ? "QUADRANT" : "",
            lkh.DelaunayPure ? " PURE" : "");
    if (lkh.Excess >= 0)
        printff("EXCESS = %g\n", lkh.Excess);
    else
        printff("# EXCESS =\n");
    printff("EXTRA_CANDIDATES = %d %s\n",
            lkh.ExtraCandidates,
            lkh.ExtraCandidateSetSymmetric ? "SYMMETRIC" : "");
    printff("EXTRA_CANDIDATE_SET_TYPE = %s\n",
            lkh.ExtraCandidateSetType == NN ? "NEAREST-NEIGHBOR" :
            lkh.ExtraCandidateSetType == QUADRANT ? "QUADRANT" : "");
    printff("GAIN23 = %s\n", lkh.Gain23Used ? "YES" : "NO");
    printff("GAIN_CRITERION = %s\n", lkh.GainCriterionUsed ? "YES" : "NO");
    if (lkh.InitialPeriod >= 0)
        printff("INITIAL_PERIOD = %d\n", lkh.InitialPeriod);
    else
        printff("# INITIAL_PERIOD =\n");
    printff("INITIAL_STEP_SIZE = %d\n", lkh.InitialStepSize);
    printff("INITIAL_TOUR_ALGORITHM = %s\n",
            lkh.InitialTourAlgorithm == BORUVKA ? "BORUVKA" :
            lkh.InitialTourAlgorithm == GREEDY ? "GREEDY" :
            lkh.InitialTourAlgorithm == MOORE ? "MOORE" :
            lkh.InitialTourAlgorithm == NEAREST_NEIGHBOR ? "NEAREST-NEIGHBOR" :
            lkh.InitialTourAlgorithm ==
            QUICK_BORUVKA ? "QUICK-BORUVKA" :
            lkh.InitialTourAlgorithm == SIERPINSKI ? "SIERPINSKI" : "WALK");
    printff("%sINITIAL_TOUR_FILE = %s\n",
            lkh.InitialTourFileName ? "" : "# ",
            lkh.InitialTourFileName ? lkh.InitialTourFileName : "");
    printff("INITIAL_TOUR_FRACTION = %0.3f\n", lkh.InitialTourFraction);
    printff("%sINPUT_TOUR_FILE = %s\n",
            lkh.InputTourFileName ? "" : "# ",
            lkh.InputTourFileName ? lkh.InputTourFileName : "");
    printff("KICK_TYPE = %d\n", lkh.KickType);
    printff("KICKS = %d\n", lkh.Kicks);
    if (lkh.MaxBreadth == INT_MAX)
        printff("# MAX_BREADTH =\n");
    else
        printff("MAX_BREADTH = %d\n", lkh.MaxBreadth);
    printff("MAX_CANDIDATES = %d %s\n",
            lkh.MaxCandidates, lkh.CandidateSetSymmetric ? "SYMMETRIC" : "");
    if (lkh.MaxSwaps >= 0)
        printff("MAX_SWAPS = %d\n", lkh.MaxSwaps);
    else
        printff("# MAX_SWAPS =\n");
    if (lkh.MaxTrials >= 0)
        printff("MAX_TRIALS = %d\n", lkh.MaxTrials);
    else
        printff("# MAX_TRIALS =\n");
    if (lkh.MergeTourFiles == 0)
        printff("# MERGE_TOUR_FILE =\n");
    else
        for (i = 0; i < lkh.MergeTourFiles; i++)
            printff("MERGE_TOUR_FILE = %s\n", lkh.MergeTourFileName[i]);
    printff("MOVE_TYPE = %d\n", lkh.MoveType);
    printff("%sNONSEQUENTIAL_MOVE_TYPE = %d\n",
            lkh.PatchingA > 1 ? "" : "# ", lkh.NonsequentialMoveType);
    if (lkh.Optimum == MINUS_INFINITY)
        printff("# OPTIMUM =\n");
    else
        printff("OPTIMUM = " GainFormat "\n", lkh.Optimum);
    printff("%sOUTPUT_TOUR_FILE = %s\n",
            lkh.OutputTourFileName ? "" : "# ",
            lkh.OutputTourFileName ? lkh.OutputTourFileName : "");
    printff("PATCHING_A = %d %s\n", lkh.PatchingA,
            lkh.PatchingARestricted ? "RESTRICTED" :
            lkh.PatchingAExtended ? "EXTENDED" : "");
    printff("PATCHING_C = %d %s\n", lkh.PatchingC,
            lkh.PatchingCRestricted ? "RESTRICTED" :
            lkh.PatchingCExtended ? "EXTENDED" : "");
    printff("%sPI_FILE = %s\n",
            lkh.PiFileName ? "" : "# ", lkh.PiFileName ? lkh.PiFileName : "");
    if (lkh.MaxPopulationSize == 0)
        printff("# ");
    printff("POPULATION_SIZE = %d\n", lkh.MaxPopulationSize);
    printff("PRECISION = %d\n", lkh.Precision);
    printff("%sPROBLEM_FILE = %s\n",
            lkh.ProblemFileName ? "" : "# ",
            lkh.ProblemFileName ? lkh.ProblemFileName : "");
    printff("RESTRICTED_SEARCH = %s\n", lkh.RestrictedSearch ? "YES" : "NO");
    printff("RUNS = %d\n", lkh.Runs);
    printff("SEED = %u\n", lkh.Seed);
    printff("STOP_AT_OPTIMUM = %s\n", lkh.StopAtOptimum ? "YES" : "NO");
    printff("SUBGRADIENT = %s\n", lkh.Subgradient ? "YES" : "NO");
    if (lkh.SubproblemSize == 0)
        printff("# SUBPROBLEM_SIZE =\n");
    else
        printff("SUBPROBLEM_SIZE = %d%s%s%s\n", lkh.SubproblemSize,
                lkh.DelaunayPartitioning ? " DELAUNAY" :
                lkh.KarpPartitioning ? " KARP" :
                lkh.KCenterPartitioning ? " K-CENTER" :
                lkh.KMeansPartitioning ? " K-MEANS" :
                lkh.MoorePartitioning ? " MOORE" :
                lkh.RohePartitioning ? " ROHE" :
                lkh.SierpinskiPartitioning ? " SIERPINSKI" : "",
                lkh.SubproblemBorders ? " BORDERS" : "",
                lkh.SubproblemsCompressed ? " COMPRESSED" : "");
    printff("%sSUBPROBLEM_TOUR_FILE = %s\n",
            lkh.SubproblemTourFileName ? "" : "# ",
            lkh.SubproblemTourFileName ? lkh.SubproblemTourFileName : "");
    printff("SUBSEQUENT_MOVE_TYPE = %d\n",
            lkh.SubsequentMoveType == 0 ? lkh.MoveType : lkh.SubsequentMoveType);
    printff("SUBSEQUENT_PATCHING = %s\n",
            lkh.SubsequentPatching ? "YES" : "NO");
    if (lkh.TimeLimit == DBL_MAX)
        printff("# TIME_LIMIT =\n");
    else
        printff("TIME_LIMIT = %0.1f\n", lkh.TimeLimit);
    printff("%sTOUR_FILE = %s\n",
            lkh.TourFileName ? "" : "# ", lkh.TourFileName ? lkh.TourFileName : "");
    printff("TRACE_LEVEL = %d\n\n", lkh.TraceLevel);
}
