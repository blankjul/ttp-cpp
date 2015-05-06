
#ifndef TRAVELLING_THIEF_PROBLEM_SOLVER_H
#define TRAVELLING_THIEF_PROBLEM_SOLVER_H

#include <problems/ttp.h>
#include <problems/tsp.h>
#include "model/tour.h"
#include "model/thief_map.h"
#include "model/knapsack.h"

using namespace std;


namespace TTP {

    class TSPSolver {

    public:
        virtual Tour solve(TravellingSalesmanProblem & tsp) = 0;
    };


    class KnapsackSolver {

    public:
        virtual Knapsack solve(vector<Item>&) = 0;
    };



    class TTPSolver {

    public:
        virtual pair<Tour,Knapsack> solve(TravellingThiefProblem &ttp) = 0;
    };
}




#endif //TRAVELLING_THIEF_PROBLEM_SOLVER_H
