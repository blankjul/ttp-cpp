
#include "TSPExhaustive.h"
#include "Util.h"




Tour TSPExhaustive::solve(TSP tsp) {
    double minCosts =  numeric_limits<double>::max();
    TourPtr bestTour;

    for(TourPtr ptr : allTours(tsp.getMap(), true)) {
        double costs = tsp.evaluate(*ptr);
        if (costs < minCosts) {
            bestTour = ptr;
            minCosts = costs;
        }
    }
    return *bestTour;

}





