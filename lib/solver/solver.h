
#ifndef TRAVELLING_THIEF_PROBLEM_SOLVER_H
#define TRAVELLING_THIEF_PROBLEM_SOLVER_H

#include <problems/ttp.h>
#include <problems/tsp.h>
#include <problems/knp.h>
#include "model/tour.h"
#include "model/knapsack.h"

using namespace std;


namespace ttp {

    class TSPSolver {

    public:
        virtual Tour solve(TravellingSalesmanProblem & tsp) = 0;
    };


    class KnapsackSolver {

    public:
        virtual Knapsack solve(KnapsackProblem & knp) = 0;
    };



    class TTPSOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(TravellingThiefProblem &ttp) = 0;
    };

    class TTPMOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(TravellingThiefProblem &ttp) = 0;
    };
}




#endif //TRAVELLING_THIEF_PROBLEM_SOLVER_H
