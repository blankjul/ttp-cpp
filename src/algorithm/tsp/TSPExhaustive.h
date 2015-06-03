#ifndef TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H
#define TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H

#include "TSPAlgorithm.h"




namespace ttp {

    class TSPExhaustive : public TSPAlgorithm {
    public:
        Tour solve(TSP tsp);
    };

}




#endif //TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H
