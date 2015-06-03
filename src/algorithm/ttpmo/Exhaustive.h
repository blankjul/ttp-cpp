
#ifndef TRAVELLING_THIEF_PROBLEM_TSPMOEXHAUSTIVE_H
#define TRAVELLING_THIEF_PROBLEM_TSPMOEXHAUSTIVE_H

#include "TTPMOAlgorithm.h"



namespace ttp {

    namespace mo {

        class Exhaustive : public TTPMOAlgorithm {
        public:
            TTPOutputSet solve(MOTTP);
        };
    }

}


#endif //TRAVELLING_THIEF_PROBLEM_TSPMOEXHAUSTIVE_H
