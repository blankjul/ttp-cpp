
#ifndef TRAVELLING_THIEF_PROBLEM_SOLVER_H
#define TRAVELLING_THIEF_PROBLEM_SOLVER_H

#include "model/tour.h"
#include "model/map.h"
#include "model/knapsack.h"

using namespace std;


namespace TTP {

    class TSPSolver {

    public:
        virtual Tour solve(Map m) = 0;
    };


    class KnapsackSolver {

    public:
        virtual Knapsack solve(vector<Item>) = 0;
    };



    class TTPSolver {

    public:
        virtual pair<Tour,Knapsack> solve(Map m, vector<Item>) = 0;
    };
}




#endif //TRAVELLING_THIEF_PROBLEM_SOLVER_H
