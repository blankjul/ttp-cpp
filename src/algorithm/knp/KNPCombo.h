

#ifndef TRAVELLING_THIEF_PROBLEM_KNPCOMBO_H
#define TRAVELLING_THIEF_PROBLEM_KNPCOMBO_H

#include "KNPAlgorithm.h"



namespace ttp {

    class KNPCombo : public KNPAlgorithm {
    public:
        Knapsack solve(KnapsackProblem knp);
    };
}


#endif //TRAVELLING_THIEF_PROBLEM_KNPCOMBO_H
