#include "LKH.h"

/* 
 * The Ascent function computes a lower bound on the optimal tour length 
 * using subgradient optimization. The function also transforms the original 
 * problem into a problem in which the Alpha-values reflect the likelihood 
 * of edges being optimal.
 *
 * The function attempts to find penalties (Pi-values) that maximizes the 
 * lower bound L(T(Pi)) - 2*PiSum, where L(T(Pi)) denotes the length of the 
 * minimum spanning 1-tree computed from the transformed distances, and PiSum 
 * denotes the sum of Pi-values. If C(i,j) denotes the length of an edge 
 * (i,j), then the transformed distance D(i,j) of an edge is 
 * C(i,j) + Pi(i) + Pi(j).
 *
 * The Minimum1TreeCost function is used to compute the cost of a minimum 
 * 1-tree.The Generatecandidates function is called in order to generate 
 * candidate sets. Minimum 1-trees are then computed in the corresponding 
 * sparse graph.         
 */

GainType Ascent()
{
    Node *t;
    GainType BestW, W, W0, Alpha, MaxAlpha = INT_MAX;
    int T, Period, P, InitialPhase, BestNorm;

  Start:
    /* Initialize Pi and BestPi */
    t = lkh.FirstNode;
    do
        t->Pi = t->BestPi = 0;
    while ((t = t->Suc) != lkh.FirstNode);
    if (lkh.CandidateSetType == DELAUNAY)
        CreateDelaunayCandidateSet();
    else
        AddTourCandidates();

    /* Compute the cost of a minimum 1-tree */
    W = Minimum1TreeCost(lkh.CandidateSetType == DELAUNAY
                         || lkh.MaxCandidates == 0);

    /* Return this cost 
       if either
       (1) subgradient optimization is not wanted, or
       (2) the norm of the tree (its deviation from a tour) is zero
           (in that case the true optimum has been found).
     */
    if (!lkh.Subgradient || !lkh.Norm)
        return W;

    if (lkh.Optimum != MINUS_INFINITY && (Alpha = lkh.Optimum * lkh.Precision - W) > 0)
        MaxAlpha = Alpha;
    if (lkh.MaxCandidates > 0) {
        /* Generate symmetric candididate sets for all nodes */
        if (lkh.CandidateSetType != DELAUNAY)
            GenerateCandidates(lkh.AscentCandidates, MaxAlpha, 1);
        else {
            OrderCandidateSet(lkh.AscentCandidates, MaxAlpha, 1);
            W = Minimum1TreeCost(1);
            if (!lkh.Norm || W / lkh.Precision == lkh.Optimum)
                return W;
        }
    }
    if (lkh.ExtraCandidates > 0)
        AddExtraCandidates(lkh.ExtraCandidates, lkh.ExtraCandidateSetType,
                           lkh.ExtraCandidateSetSymmetric);
    if (lkh.TraceLevel >= 2) {
        CandidateReport();
        printff("Subgradient optimization ...\n");
    }

    /* Set LastV of every node to V (the node's degree in the 1-tree) */
    t = lkh.FirstNode;
    do
        t->LastV = t->V;
    while ((t = t->Suc) != lkh.FirstNode);

    BestW = W0 = W;
    BestNorm = lkh.Norm;
    InitialPhase = 1;
    /* Perform subradient optimization with decreasing period length 
       and decreasing step size */
    for (Period = lkh.InitialPeriod, T = lkh.InitialStepSize * lkh.Precision;
         Period > 0 && T > 0 && lkh.Norm != 0; Period /= 2, T /= 2) {
        /* Period and step size are halved at each iteration */
        if (lkh.TraceLevel >= 2)
            printff
                ("  T = %d, Period = %d, BestW = %0.1f, Norm = %d\n",
                 T, Period, (double) BestW / lkh.Precision, lkh.Norm);
        for (P = 1; T && P <= Period && lkh.Norm != 0; P++) {
            /* Adjust the Pi-values */
            t = lkh.FirstNode;
            do {
                if (t->V != 0) {
                    t->Pi += T * (7 * t->V + 3 * t->LastV) / 10;
                    if (t->Pi > INT_MAX / 4)
                        t->Pi = INT_MAX / 4;
                    else if (t->Pi < -INT_MAX / 4)
                        t->Pi = -INT_MAX / 4;
                }
                t->LastV = t->V;
            }
            while ((t = t->Suc) != lkh.FirstNode);
            /* Compute a minimum 1-tree in the sparse graph */
            W = Minimum1TreeCost(1);
            /* Test if an improvement has been found */
            if (W > BestW || (W == BestW && lkh.Norm < BestNorm)) {
                /* If the lower bound becomes greater than twice its
                   initial value it is taken as a sign that the graph might be
                   too sparse */
                if (W - W0 > (W0 >= 0 ? W0 : -W0) && lkh.AscentCandidates > 0
                    && lkh.AscentCandidates < lkh.Dimension) {
                    W = Minimum1TreeCost(lkh.CandidateSetType == DELAUNAY
                                         || lkh.MaxCandidates == 0);
                    if (W < W0) {
                        /* Double the number of candidate edges 
                           and start all over again */
                        if (lkh.TraceLevel >= 2)
                            printff("Warning: AscentCandidates doubled\n");
                        if ((lkh.AscentCandidates *= 2) > lkh.Dimension)
                            lkh.AscentCandidates = lkh.Dimension;
                        goto Start;
                    }
                    W0 = W;
                }
                BestW = W;
                BestNorm = lkh.Norm;
                /* Update the BestPi-values */
                t = lkh.FirstNode;
                do
                    t->BestPi = t->Pi;
                while ((t = t->Suc) != lkh.FirstNode);
                if (lkh.TraceLevel >= 2)
                    printff
                        ("* T = %d, Period = %d, P = %d, BestW = %0.1f, Norm = %d\n",
                         T, Period, P, (double) BestW / lkh.Precision, lkh.Norm);
                /* If in the initial phase, the step size is doubled */
                if (InitialPhase && T * sqrt((double) lkh.Norm) > 0)
                    T *= 2;
                /* If the improvement was found at the last iteration of the 
                   current period, then double the period */
                if (lkh.CandidateSetType != DELAUNAY && P == Period
                    && (Period *= 2) > lkh.InitialPeriod)
                    Period = lkh.InitialPeriod;
            } else {
                if (lkh.TraceLevel >= 3)
                    printff
                        ("  T = %d, Period = %d, P = %d, W = %0.1f, Norm = %d\n",
                         T, Period, P, (double) W / lkh.Precision, lkh.Norm);
                if (InitialPhase && P > Period / 2) {
                    /* Conclude the initial phase */
                    InitialPhase = 0;
                    P = 0;
                    T = 3 * T / 4;
                }
            }
        }
    }

    t = lkh.FirstNode;
    do {
        t->Pi = t->BestPi;
        t->BestPi = 0;
    } while ((t = t->Suc) != lkh.FirstNode);

    /* Compute a minimum 1-tree */
    W = BestW = Minimum1TreeCost(lkh.CandidateSetType == DELAUNAY
                                 || lkh.MaxCandidates == 0);

    if (lkh.MaxCandidates > 0) {
        FreeCandidateSets();
        if (lkh.CandidateSetType == DELAUNAY)
            CreateDelaunayCandidateSet();
    } else {
        Candidate *Nt;
        t = lkh.FirstNode;
        do {
            for (Nt = t->CandidateSet; Nt && Nt->To; Nt++)
                Nt->Cost += t->Pi + Nt->To->Pi;
        }
        while ((t = t->Suc) != lkh.FirstNode);
    }
    if (lkh.TraceLevel >= 2)
        printff("Ascent: BestW = %0.1f, Norm = %d\n",
                (double) BestW / lkh.Precision, lkh.Norm);
    return W;
}
