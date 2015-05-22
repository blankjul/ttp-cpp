#ifndef TRAVELLING_THIEF_PROBLEM_TTPSO_H
#define TRAVELLING_THIEF_PROBLEM_TTPSO_H

#include <limits>
#include "problems/TTPInput.h"
#include "problems/TTP.h"
#include "model/Tour.h"


using namespace std;

namespace ttp {



    class SOTTP : public TTP<TTPInput,double> {


    protected:

        /*!< Renting rate for the picked items */
        double rentingRate = 1;


    public:

        SOTTP(const ThiefMapPtr &map, int maxWeight) :
                TTP(map,maxWeight) {}

        double evaluate(TTPInput& input) {
            double time = calcTime(input);

            Knapsack k = input.getKnapsack();
            double value = (k.getWeight() <= maxWeight) ? k.getValue() : - numeric_limits<double>::infinity();

            return value - rentingRate * time;
        }

        /*
         * Setter and Getter
         */
        double getRentingRate() const;
        void setRentingRate(double rentingRate);



    };


}


#endif //TRAVELLING_THIEF_PROBLEM_TTP_H
