#include "LKH.h"

/* 
 * The SymmetrizeCandidateSet function complement the candidate set such 
 * that every candidate edge is associated with both its two end nodes. 
*/

void SymmetrizeCandidateSet()
{
    Node *From, *To;
    Candidate *NFrom;

    From = lkh.FirstNode;
    do {
        for (NFrom = From->CandidateSet; NFrom && (To = NFrom->To); NFrom++)
            AddCandidate(To, From, NFrom->Cost, NFrom->Alpha);
    }
    while ((From = From->Suc) != lkh.FirstNode);
    ResetCandidateSet();
}
