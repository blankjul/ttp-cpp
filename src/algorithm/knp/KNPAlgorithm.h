
#ifndef TRAVELLING_THIEF_PROBLEM_KNPALGORITHM_H
#define TRAVELLING_THIEF_PROBLEM_KNPALGORITHM_H

#include <iostream>
#include <vector>
#include "Algorithm.h"
#include <problems/KnapsackProblem.h>
#include <model/Knapsack.h>


namespace ttp {

    class KNPAlgorithm : public Algorithm<KnapsackProblem,Knapsack>{
    public:
        virtual Knapsack solve(KnapsackProblem){};

    };


}


#endif //TRAVELLING_THIEF_PROBLEM_KNPALGORITHM_H
