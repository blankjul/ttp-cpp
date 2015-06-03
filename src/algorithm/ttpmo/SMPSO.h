
#ifndef TRAVELLING_THIEF_PROBLEM_TTPSMPSO
#define TRAVELLING_THIEF_PROBLEM_TTPSMPSO

#include "TTPMOAlgorithm.h"



namespace ttp {

    namespace mo {

    class SMPSO : public TTPMOAlgorithm{
    public:
        TTPOutputSet solve(MOTTP);
        int swarmSize_                 = 100 ;
        int maxIterations_             = 250 ;
        int archiveSize_               = 100 ;
        double mutationDistributionIndex_ = 20.0 ;
        double mutationProbability_       = 0.01;
    };

    }

}


#endif //TRAVELLING_THIEF_PROBLEM_TTPSMPSO
