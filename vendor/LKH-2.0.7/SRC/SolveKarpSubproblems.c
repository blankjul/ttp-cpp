#include "LKH.h"
#include "GeoConversion.h"

/*
 * The SolveKarpSubproblems function attempts to improve a given tour 
 * by means of Karp's partitioning scheme. 
 *
 * The overall region containing the nodes is subdivided into rectangles
 * with SubproblemSize nodes in each rectangle. Each rectangle together 
 * with the given tour induces a subproblem consisting of all nodes inside 
 * the rectangle, and with edges fixed between nodes that are connected 
 * by tour segments whose interior points are outside the rectangle.  
 *  
 * If an improvement is found, the new tour is written to TourFile. 
 * The original tour is given by the SubproblemSuc references of the nodes.
 */

static void KarpPartition(int start, int end);
static void CalculateSubproblems(int start, int end);

static Node **KDTree;
static GainType GlobalBestCost, OldGlobalBestCost;
static int CurrentSubproblem, Subproblems;

void SolveKarpSubproblems()
{
    Node *N;
    double EntryTime = GetTime();

    AllocateStructures();
    ReadPenalties();

    /* Compute upper bound for the original problem */
    GlobalBestCost = 0;
    N = lkh.FirstNode;
    do {
        if (!Fixed(N, N->SubproblemSuc))
            GlobalBestCost += lkh.Distance(N, N->SubproblemSuc);
        N->Subproblem = 0;
    }
    while ((N = N->SubproblemSuc) != lkh.FirstNode);
    if (lkh.TraceLevel >= 1) {
        if (lkh.TraceLevel >= 2)
            printff("\n");
        printff("*** Karp partitioning *** [Cost = " GainFormat "]\n",
                GlobalBestCost);
    }
    if (lkh.WeightType == GEO || lkh.WeightType == GEOM ||
            lkh.WeightType == GEO_MEEUS || lkh.WeightType == GEOM_MEEUS) {
        N = lkh.FirstNode;
        do {
            N->Xc = N->X;
            N->Yc = N->Y;
            N->Zc = N->Z;
            if (lkh.WeightType == GEO || lkh.WeightType == GEO_MEEUS)
                GEO2XYZ(N->Xc, N->Yc, &N->X, &N->Y, &N->Z);
            else
                GEOM2XYZ(N->Xc, N->Yc, &N->X, &N->Y, &N->Z);
        } while ((N = N->SubproblemSuc) != lkh.FirstNode);
        lkh.CoordType = THREED_COORDS;
    }
    KDTree = BuildKDTree(lkh.SubproblemSize);
    if (lkh.WeightType == GEO || lkh.WeightType == GEOM ||
            lkh.WeightType == GEO_MEEUS || lkh.WeightType == GEOM_MEEUS) {
        N = lkh.FirstNode;
        do {
            N->X = N->Xc;
            N->Y = N->Yc;
            N->Z = N->Zc;
        } while ((N = N->SubproblemSuc) != lkh.FirstNode);
        lkh.CoordType = TWOD_COORDS;
    }

    Subproblems = 0;
    CalculateSubproblems(0, lkh.Dimension - 1);
    CurrentSubproblem = 0;
    KarpPartition(0, lkh.Dimension - 1);
    free(KDTree);
    printff("\nCost = " GainFormat, GlobalBestCost);
    if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
        printff(", Gap = %0.4f%%",
                100.0 * (GlobalBestCost - lkh.Optimum) / lkh.Optimum);
    printff(", Time = %0.2f sec. %s\n", fabs(GetTime() - EntryTime),
            GlobalBestCost < lkh.Optimum ? "<" : GlobalBestCost ==
                                                     lkh.Optimum ? "=" : "");
    if (lkh.SubproblemBorders && Subproblems > 1)
        SolveSubproblemBorderProblems(Subproblems, &GlobalBestCost);
}

/*
 * The KarpPartition function subidivides the overall region into 
 * rectangles and attempts to solve the induced subproblems. 
 */

static void KarpPartition(int start, int end)
{
    if (end - start + 1 <= lkh.SubproblemSize) {
        int i;
        CurrentSubproblem++;
        for (i = start; i <= end; i++)
            KDTree[i]->Subproblem = CurrentSubproblem;
        OldGlobalBestCost = GlobalBestCost;
        SolveSubproblem(CurrentSubproblem, Subproblems, &GlobalBestCost);
        if (lkh.SubproblemsCompressed && GlobalBestCost == OldGlobalBestCost)
            SolveCompressedSubproblem(CurrentSubproblem, Subproblems,
                                      &GlobalBestCost);
    } else {
        int mid = (start + end) / 2;
        KarpPartition(start, mid);
        KarpPartition(mid + 1, end);
    }
}

/*
 * The CalculateSubproblems function is used to calculate the number of 
 * subproblems (Subproblems) created by the Karpartition function.
 */

static void CalculateSubproblems(int start, int end)
{
    if (end - start + 1 <= lkh.SubproblemSize)
        Subproblems++;
    else {
        int mid = (start + end) / 2;
        CalculateSubproblems(start, mid);
        CalculateSubproblems(mid + 1, end);
    }
}
