#ifndef TRAVELLING_THIEF_PROBLEM_TSPREEDY_H
#define TRAVELLING_THIEF_PROBLEM_TSPREEDY_H


#include "TSPAlgorithm.h"



using namespace std;


namespace ttp {

    class TSPGreedy : public TSPAlgorithm {
    public:
        Tour solve(TSP tsp);
    };

}







#endif //TRAVELLING_THIEF_PROBLEM_TSPREEDY_H
