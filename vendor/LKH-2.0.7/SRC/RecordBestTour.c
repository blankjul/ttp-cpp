#include "LKH.h"

/*
 * The RecordBestTour function records the current best tour in the BestTour 
 * array. 
 *
 * The function is called by LKHmain each time a run has resulted in a
 * shorter tour. Thus, when the predetermined number of runs have been
 * completed, BestTour contains an array representation of the best tour
 * found.    
 */

void RecordBestTour()
{
    int i, Dim = lkh.ProblemType != ATSP ? lkh.Dimension : lkh.Dimension / 2;

    for (i = 0; i <= Dim; i++)
        lkh.BestTour[i] = lkh.BetterTour[i];
}
