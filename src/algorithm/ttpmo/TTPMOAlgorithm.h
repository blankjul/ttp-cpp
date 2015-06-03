
#ifndef TRAVELLING_THIEF_PROBLEM_TTPMOAlgorithm_H
#define TRAVELLING_THIEF_PROBLEM_TTPMOAlgorithm_H

#include "Algorithm.h"
#include "problems/MOTTP.h"
#include "problems/TTPOutput.h"
#include "problems/TTPOutputSet.h"
#include <set>


namespace ttp {

    class TTPMOAlgorithm : public Algorithm<MOTTP, TTPOutputSet > {
    public:
        virtual TTPOutputSet solve(MOTTP) = 0;
    };

}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMOAlgorithm_H
