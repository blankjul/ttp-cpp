
#ifndef TRAVELLING_THIEF_PROBLEM_TSPSOEXHAUSTIVE_H
#define TRAVELLING_THIEF_PROBLEM_TSPSOEXHAUSTIVE_H

#include "TTPSOAlgorithm.h"



namespace ttp {

    class TTPSOExhaustive : public TTPSOAlgorithm{
    public:
        pair<Tour,Knapsack> solve(SOTTP);
    };

}


#endif //TRAVELLING_THIEF_PROBLEM_TSPSOEXHAUSTIVE_H
