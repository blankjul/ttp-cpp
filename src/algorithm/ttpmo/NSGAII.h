
#ifndef TRAVELLING_THIEF_PROBLEM_TTPMONSGA
#define TRAVELLING_THIEF_PROBLEM_TTPMONSGA

#include "TTPMOAlgorithm.h"



namespace ttp {

    namespace mo {

    class NSGAII : public TTPMOAlgorithm{
    public:
        TTPOutputSet solve(MOTTP);
        int populationSize_ = 100;
        int maxEvaluations_ = 5000;
        double mutationProbability_         = 0.01;
        double crossoverProbability_        = 0.9   ;
        double mutationDistributionIndex_   = 20.0  ;
        double crossoverDistributionIndex_  = 20.0  ;

    };

    }

}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMONSGA
