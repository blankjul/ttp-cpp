#include "TTPSOExhaustive.h"
#include "Util.h"
#include <algorithm>




pair<Tour, Knapsack> TTPSOExhaustive::solve(SOTTP ttp) {

    ThiefMapPtr m = ttp.getMap();

    double bestTarget = numeric_limits<double>::min();
    TourPtr bestTour;
    KnapsackPtr bestKnapsack;


    // for all the possible tsp tours
    for (TourPtr t : allTours(m, true)) {

        for (KnapsackPtr k : allKnapsacks(m->getItems())) {

            TTPInput input(*t, *k);
            double targetValue = ttp.evaluate(input);

            if (targetValue > bestTarget) {
                bestTour = t;
                bestKnapsack = k;
                bestTarget = targetValue;
            }

        }
    }


    return make_pair(*bestTour, *bestKnapsack);

}






