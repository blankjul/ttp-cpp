
#ifndef TRAVELLING_THIEF_PROBLEM_TSPSOALGORITHM_H
#define TRAVELLING_THIEF_PROBLEM_TSPSOALGORITHM_H

#include "Algorithm.h"
#include "problems/SOTTP.h"


using namespace std;
using namespace ttp;


namespace ttp {

    class TTPSOAlgorithm : public Algorithm<SOTTP,pair<Tour,Knapsack>>{
    public:
        virtual pair<Tour,Knapsack> solve(SOTTP){};
    };

}


#endif //TRAVELLING_THIEF_PROBLEM_TSPSOALGORITHM_H
