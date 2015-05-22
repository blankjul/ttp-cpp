
#ifndef TRAVELLING_THIEF_PROBLEM_SOLVER_H
#define TRAVELLING_THIEF_PROBLEM_SOLVER_H

#include "problems/TravellingThiefProblemDeptr.h"
#include "problems/TSP.h"
#include "problems/KnapsackProblem.h"
#include "model/Tour.h"
#include "model/Knapsack.h"

using namespace std;


namespace ttp {

    class TSPSolver {

    public:
        virtual Tour solve(TSP & tsp) = 0;
    };


    class KnapsackSolver {

    public:
        virtual Knapsack solve(KnapsackProblem & knp) = 0;
    };



    class TTPSOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(TravellingThiefProblemDeptr &ttp) = 0;
    };

    class TTPMOSolver {

    public:
        virtual pair<Tour,Knapsack> solve(TravellingThiefProblemDeptr &ttp) = 0;
    };
}




#endif //TRAVELLING_THIEF_PROBLEM_SOLVER_H
