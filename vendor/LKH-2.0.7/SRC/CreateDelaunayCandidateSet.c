#include "LKH.h"
#include "Delaunay.h"

/*
 * The CreateDelaunayCandidateSet function determines for each node its set 
 * of incident candidate edges. The edges are found by Delaunay triangulation. 
 *
 * The function is called from CreateCandidateSet.
 */

static int Level = 0;

void CreateDelaunayCandidateSet()
{
    Node *From, *To;
    point *u, *v;
    edge *e_start, *e;
    int d, i;

    if (lkh.TraceLevel >= 2)
        printff("Creating Delaunay candidate set ... ");
    if (Level == 0 && lkh.MaxCandidates == 0) {
        AddTourCandidates();
        From = lkh.FirstNode;
        do {
            if (!From->CandidateSet)
                eprintf("MAX_CANDIDATES = 0: No candidates");
        } while ((From = From->Suc) != lkh.FirstNode);
        if (lkh.TraceLevel >= 2)
            printff("done\n");
        return;
    }

    /* Find the Delaunay edges */
    delaunay(lkh.Dimension);

    /* Add the Delaunay edges to the candidate set */
    for (i = 0; i < lkh.Dimension; i++) {
        u = &p_array[i];
        From = &lkh.NodeSet[u->id];
        e_start = e = u->entry_pt;
        do {
            v = Other_point(e, u);
            if (u < v) {
                To = &lkh.NodeSet[v->id];
                d = lkh.D(From, To);
                AddCandidate(From, To, d, 1);
                AddCandidate(To, From, d, 1);
            }
        } while ((e = Next(e, u)) != e_start);
    }
    free_memory();
    if (Level == 0 &&
        (lkh.WeightType == GEO || lkh.WeightType == GEOM ||
         lkh.WeightType == GEO_MEEUS || lkh.WeightType == GEOM_MEEUS)) {
        if (lkh.TraceLevel >= 2)
            printff("done\n");
        From = lkh.FirstNode;
        while ((From = From->Suc) != lkh.FirstNode)
            if ((From->Y > 0) != (lkh.FirstNode->Y > 0))
                break;
        if (From != lkh.FirstNode) {
            /* Transform longitude (180 and -180 map to 0) */
            From = lkh.FirstNode;
            do {
                From->Zc = From->Y;
                if (lkh.WeightType == GEO || lkh.WeightType == GEO_MEEUS)
                    From->Y =
                        (int) From->Y + 5.0 * (From->Y -
                                               (int) From->Y) / 3.0;
                From->Y += From->Y > 0 ? -180 : 180;
                if (lkh.WeightType == GEO || lkh.WeightType == GEO_MEEUS)
                    From->Y =
                        (int) From->Y + 3.0 * (From->Y -
                                               (int) From->Y) / 5.0;
            } while ((From = From->Suc) != lkh.FirstNode);
            Level++;
            CreateDelaunayCandidateSet();
            Level--;
            From = lkh.FirstNode;
            do
                From->Y = From->Zc;
            while ((From = From->Suc) != lkh.FirstNode);
        }
    }
    if (Level == 0) {
        AddTourCandidates();
        /* Add quadrant neighbors if any node has less than two candidates. 
           That is, if it should happen that delaunay_edges fails. */
        From = lkh.FirstNode;
        do {
            if (From->CandidateSet == 0 ||
                From->CandidateSet[0].To == 0
                || From->CandidateSet[1].To == 0) {
                if (lkh.TraceLevel >= 2)
                    printff("*** Not complete ***\n");
                AddExtraCandidates(lkh.CoordType == THREED_COORDS ? 8 : 4,
                                   QUADRANT, 1);
                break;
            }
        } while ((From = From->Suc) != lkh.FirstNode);
        if (lkh.TraceLevel >= 2)
            printff("done\n");
    }
}
