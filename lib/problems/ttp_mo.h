#ifndef TRAVELLING_THIEF_PROBLEM_TTPMO_H
#define TRAVELLING_THIEF_PROBLEM_TTPMO_H

#include "problems/ttp.h"


using namespace std;

namespace TTP {





    class MultiObjectiveTravellingThiefProblem : public TravellingThiefProblem {


    protected:

        /*!< Dropping rate of the items */
        double droppingRate;


    public:

        /*!< Default constant for the exponent for the equation of the dropping rate */
        static constexpr double DEFAULT_DROPPING_CONSTANT = 10;

        /*!< Default dropping rate per time unit of each item if nothing is specified */
        static constexpr double DEFAULT_DROPPING_RATE = 0.9;


        MultiObjectiveTravellingThiefProblem(MapPtr &map, int maxWeight) : TravellingThiefProblem(map,maxWeight),
                          droppingRate(MultiObjectiveTravellingThiefProblem::DEFAULT_DROPPING_RATE){};

        pair<double,double> evaluate(Tour &t, Knapsack &k);


        /*
         * Setter and Getter
         */

        double  getDroppingRate() const;
        void  setDroppingRate(double droppingRate);


    };



}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMO_H
