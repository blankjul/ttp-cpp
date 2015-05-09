
#ifndef TRAVELLING_THIEF_PROBLEM_SOLVER_H
#define TRAVELLING_THIEF_PROBLEM_SOLVER_H

#include <problems/ttp.h>
#include <problems/ttp_so.h>
#include <problems/ttp_mo.h>
#include <problems/tsp.h>
#include <problems/knp.h>
#include "model/tour.h"
#include "model/knapsack.h"

using namespace std;


namespace TTP {

    class TSPSolver {

    public:
        virtual Tour solve(TravellingSalesmanProblem & tsp) = 0;
    };


    class KnapsackSolver {

    public:
        virtual Knapsack solve(KnapsackProblem & tsp) = 0;
    };



    class TTPSOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(SingleObjectiveTravellingThiefProblem &ttp) = 0;
    };

    class TTPMOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(MultiObjectiveTravellingThiefProblem &ttp) = 0;
    };
}




#endif //TRAVELLING_THIEF_PROBLEM_SOLVER_H
