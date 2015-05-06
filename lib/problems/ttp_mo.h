#ifndef TRAVELLING_THIEF_PROBLEM_TTPMO_H
#define TRAVELLING_THIEF_PROBLEM_TTPMO_H

#include "problems/ttp.h"


using namespace std;

namespace TTP {





    class MultiObjectiveTravellingThiefProblem : TravellingThiefProblem {


    public:

        /*!< Default constant for the exponent for the equation of the dropping rate */
        static constexpr double DEFAULT_DROPPING_CONSTANT = 10;


        MultiObjectiveTravellingThiefProblem(Map &map, int maxWeight) : TravellingThiefProblem(map,maxWeight) {};

        pair<double,double> evaluate(Tour &t, Knapsack &k);


    };



}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMO_H
