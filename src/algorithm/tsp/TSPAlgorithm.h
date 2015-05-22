
#ifndef TRAVELLING_THIEF_PROBLEM_TSPALGORITHM_H
#define TRAVELLING_THIEF_PROBLEM_TSPALGORITHM_H

#include "Algorithm.h"
#include "problems/TSP.h"



namespace ttp {

    class TSPAlgorithm : public Algorithm<TSP,Tour>{
    public:
        virtual Tour solve(TSP){};

    };

}


#endif //TRAVELLING_THIEF_PROBLEM_TSPALGORITHM_H
