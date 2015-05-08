#ifndef TRAVELLING_THIEF_PROBLEM_TTPSO_H
#define TRAVELLING_THIEF_PROBLEM_TTPSO_H

#include "problems/ttp.h"


using namespace std;

namespace TTP {



    class SingleObjectiveTravellingThiefProblem : public TravellingThiefProblem {


    protected:

        /*!< Dropping rate of the items */
        double rentingRate;



    public:

        /*!< Default dropping rate per time unit of each item if nothing is specified */
        static constexpr double DEFAULT_RENTING_RATE = 0.9;

        SingleObjectiveTravellingThiefProblem(MapPtr &map, int maxWeight) : TravellingThiefProblem(map,maxWeight) {};

        double evaluate(Tour &t, Knapsack &k);



        /*
         * Setter and Getter
         */

        double getRentingRate() const ;
        void setRentingRate(double rentingRate);

    };



}


#endif //TRAVELLING_THIEF_PROBLEM_TTPSO_H
