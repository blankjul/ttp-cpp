#include "LKH.h"

/*
 * The RecordBetterTour function is called by FindTour each time
 * the LinKernighan function has returned a better tour.
 *
 * The function records the tour in the BetterTour array and in the
 * BestSuc field of each node. Furthermore, for each node the previous 
 * value of BestSuc is saved in the NextBestSuc field.
 *
 * Recording a better tour in the BetterTour array when the problem is 
 * asymmetric requires special treatment since the number of nodes has
 * been doubled.  
 */

void RecordBetterTour()
{
    Node *N;
    int i = 0;

    N = lkh.FirstNode;
    do {
        if (lkh.ProblemType != ATSP)
            lkh.BetterTour[++i] = N->Id;
        else if (N->Id <= lkh.Dimension / 2) {
            i++;
            if (N->Suc->Id != N->Id + lkh.Dimension / 2)
                lkh.BetterTour[i] = N->Id;
            else
                lkh.BetterTour[lkh.Dimension / 2 - i + 1] = N->Id;
        }
        N->NextBestSuc = N->BestSuc;
        N->BestSuc = N->Suc;
    }
    while ((N = N->Suc) != lkh.FirstNode);
    lkh.BetterTour[0] = lkh.BetterTour[lkh.ProblemType != ATSP ? lkh.Dimension : lkh.Dimension / 2];
}
