#include "LKH.h"

/*
 * The ReadCandidates function attempts to read candidate edges from 
 * files. The candidate edges are added to the current candidate sets.
 *
 * The first line of the file contains the number of nodes.
 *
 * Each of the follwong lines contains a node number, the number of the
 * dad of the node in the minimum spanning tree (0, if the node has no dad), 
 * the number of candidate edges emanating from the node, followed by the 
 * candidate edges. For each candidate edge its end node number and 
 * alpha-value are given.
 *
 * The parameter MaxCandidates specifies the maximum number of candidate edges 
 * allowed for each node.
 *
 * If reading succeeds, the function returns 1; otherwise 0. 
 *
 * The function is called from the CreateCandidateSet function. 
 */

int ReadCandidates(int MaxCandidates)
{
    FILE *CandidateFile = 0;
    Node *From, *To;
    int Dimension, i, f, Id, Alpha, Count;

    if (lkh.CandidateFiles == 0 ||
        (lkh.CandidateFiles == 1 &&
         !(CandidateFile = fopen(lkh.CandidateFileName[0], "r"))))
        return 0;
    Dimension = lkh.ProblemType != ATSP ? lkh.DimensionSaved : 2 * lkh.DimensionSaved;
    for (f = 0; f < lkh.CandidateFiles; f++) {
        if (lkh.CandidateFiles >= 2 &&
            !(CandidateFile = fopen(lkh.CandidateFileName[f], "r")))
            eprintf("Cannot open CANDIDATE_FILE: \"%s\"",
                    lkh.CandidateFileName[f]);
        if (lkh.TraceLevel >= 1)
            printff("Reading CANDIDATE_FILE: \"%s\" ... ",
                    lkh.CandidateFileName[f]);
        fscanint(CandidateFile, &i);
        if (i != Dimension)
            eprintf("CANDIDATE_FILE \"%s\" does not match problem",
                    lkh.CandidateFileName[f]);
        while (fscanint(CandidateFile, &Id) == 1 && Id != -1) {
            assert(Id >= 1 && Id <= Dimension);
            From = &lkh.NodeSet[Id];
            fscanint(CandidateFile, &Id);
            assert(Id >= 0 && Id <= Dimension);
            if (Id > 0)
                From->Dad = &lkh.NodeSet[Id];
            assert(From != From->Dad);
            fscanint(CandidateFile, &Count);
            assert(Count >= 0 && Count < Dimension);
            if (!From->CandidateSet)
                assert(From->CandidateSet =
                       (Candidate *) calloc(Count + 1, sizeof(Candidate)));
            for (i = 0; i < Count; i++) {
                fscanint(CandidateFile, &Id);
                assert(Id >= 1 && Id <= Dimension);
                To = &lkh.NodeSet[Id];
                fscanint(CandidateFile, &Alpha);
                AddCandidate(From, To, lkh.D(From, To), Alpha);
            }
        }
        fclose(CandidateFile);
        if (lkh.TraceLevel >= 1)
            printff("done\n");
    }
    ResetCandidateSet();
    if (MaxCandidates > 0)
        TrimCandidateSet(MaxCandidates);
    return 1;
}
