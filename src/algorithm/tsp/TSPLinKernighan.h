#ifndef TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H
#define TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H

#include "TSPAlgorithm.h"



namespace ttp {

    class TSPLinKernighan : public TSPAlgorithm {
    public:
        Tour solve(TSP tsp);
    };

}







#endif //TRAVELLING_THIEF_PROBLEM_TSP_LIN_KERNIGHAN_H
