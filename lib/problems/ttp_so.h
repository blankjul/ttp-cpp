#ifndef TRAVELLING_THIEF_PROBLEM_TTPSO_H
#define TRAVELLING_THIEF_PROBLEM_TTPSO_H

#include "problems/ttp.h"


using namespace std;

namespace TTP {




    class SingleObjectiveTravellingThiefProblem : TravellingThiefProblem {


    public:

        SingleObjectiveTravellingThiefProblem(Map &map, int maxWeight) : TravellingThiefProblem(map,maxWeight) {};

        double evaluate(Tour &t, Knapsack &k);


    };



}


#endif //TRAVELLING_THIEF_PROBLEM_TTPSO_H
