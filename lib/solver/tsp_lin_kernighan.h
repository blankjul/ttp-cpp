

#ifndef TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H
#define TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H


#include "solver.h"



using namespace std;

namespace ttp {

    class TSPLinKernighanSolver : public TSPSolver {

    public:
        Tour solve(TravellingSalesmanProblem & tsp);





    };
}






#endif //TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H
