#include "LKH.h"

/*
 * The SolveSFCSubproblems function attempts to improve a given tour 
 * by means of partitioning based on a space-filling curve, either a 
 * Sierpinski curve or a Moore curve. If an improvement is found, 
 * the new tour is written to TourFile.
 * 
 * The tour is divided into segments of equal size. Each segment 
 * constitutes a subproblem to be solved by the LinKernighan function. 
 * 
 * The original tour is given by the SubproblemSuc references of the nodes. 
 * The size of each segment is SubproblemSize.
 *
 * The function runs in two rounds. In the first round the first segment 
 * starts at FirstNode. In the second round the middle of this segment is 
 * used as a starting point for the first segment. 
 */

void SolveSFCSubproblems()
{
    Node *FirstNodeSaved, *N;
    int CurrentSubproblem, Subproblems, Round, i;
    GainType GlobalBestCost, OldGlobalBestCost;
    Node **Suc;
    double EntryTime = GetTime();

    SFCTour(lkh.SierpinskiPartitioning ? SIERPINSKI : MOORE);
    assert(Suc = (Node **) malloc((1 + lkh.Dimension) * sizeof(Node *)));
    N = lkh.FirstNode;
    do
        Suc[N->Id] = N->Suc;
    while ((N = N->Suc) != lkh.FirstNode);
    AllocateStructures();
    Subproblems = (int) ceil((double) lkh.Dimension / lkh.SubproblemSize);
    ReadPenalties();
    lkh.FirstNode = &lkh.NodeSet[Random() % lkh.Dimension + 1];

    /* Compute upper bound for the original problem */
    GlobalBestCost = 0;
    N = FirstNodeSaved = lkh.FirstNode;
    do {
        if (!Fixed(N, N->SubproblemSuc))
            GlobalBestCost += lkh.Distance(N, N->SubproblemSuc);
        N->Subproblem = 0;
    }
    while ((N = N->SubproblemSuc) != lkh.FirstNode);
    for (Round = 1; Round <= 2; Round++) {
        if (Round == 2 && Subproblems == 1)
            break;
        if (lkh.TraceLevel >= 1) {
            if (Round == 2 || lkh.TraceLevel >= 2)
                printff("\n");
            printff
                ("*** %s partitioning *** [Round %d of %d, Cost = "
                 GainFormat "]\n",
                 lkh.SierpinskiPartitioning ? "Sierpinski" : "Moore",
                 Round, Subproblems > 1 ? 2 : 1, GlobalBestCost);
        }
        lkh.FirstNode = FirstNodeSaved;
        if (Round == 2)
            for (i = lkh.SubproblemSize / 2; i > 0; i--)
                lkh.FirstNode = Suc[lkh.FirstNode->Id];
        for (CurrentSubproblem = 1;
             CurrentSubproblem <= Subproblems; CurrentSubproblem++) {
            for (i = 0, N = lkh.FirstNode; i < lkh.SubproblemSize;
                 i++, N = Suc[N->Id]) {
                N->Subproblem =
                    (Round - 1) * Subproblems + CurrentSubproblem;
                N->FixedTo1Saved = N->FixedTo2Saved = 0;
                N->SubBestPred = N->SubBestSuc = 0;
            }
            OldGlobalBestCost = GlobalBestCost;
            SolveSubproblem((Round - 1) * Subproblems + CurrentSubproblem,
                            Subproblems, &GlobalBestCost);
            if (lkh.SubproblemsCompressed
                && GlobalBestCost == OldGlobalBestCost)
                SolveCompressedSubproblem((Round - 1) * Subproblems +
                                          CurrentSubproblem, Subproblems,
                                          &GlobalBestCost);
            lkh.FirstNode = N;
        }
    }
    free(Suc);
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
