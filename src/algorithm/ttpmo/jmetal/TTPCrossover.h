#ifndef __TTP_CROSSOVER__
#define __TTP_CROSSOVER__

#include "operators/crossover/Crossover.h"
#include "encodings/variable/Binary.h"
#include "core/Solution.h"
#include "JTour.h"
#include <math.h>
#include <algorithm>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class TTPCrossover : public Crossover {



public:
    static JTour* crossJTour(int point, JTour* p1, JTour* p2, bool stepFirst = true) {
        JTour* offspring = new JTour(p1);
        int index = (stepFirst) ? 1 : 0;
        for (; index <= point; ++index) {
            int swapIndex =  std::find(offspring->v.begin(), offspring->v.end(), p2->v[index]) - offspring->v.begin();
            int tmp = offspring->v[index];
            offspring->v[index] = offspring->v[swapIndex];
            offspring->v[swapIndex] = tmp;
        }
        return offspring;
    }


    TTPCrossover(map<string, void *> parameters);
    void *execute(void *);

private:

    double crossoverProbability_;
    Solution **doCrossover(double probability, Solution *parent1, Solution *parent2);
};

#endif
