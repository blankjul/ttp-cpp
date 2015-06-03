#ifndef TRAVELLING_THIEF_PROBLEM_TTPMO_H
#define TRAVELLING_THIEF_PROBLEM_TTPMO_H

#include <limits>
#include <cmath>
#include "problems/TTPInput.h"
#include "problems/TTPOutput.h"
#include "problems/TTP.h"
#include "model/Tour.h"


using namespace std;

namespace ttp {


    class MOTTP : public TTP<TTPInput,TTPOutput> {


    protected:

        /*!< Dropping rate for the MOP */
        double droppingRate = 0.9;

        /*!< Dropping constant for the MOP */
        double droppingConstant = 10;


    public:

        MOTTP(const ThiefMapPtr &map, int maxWeight) :
                TTP(map,maxWeight) {}


        TTPOutput evaluate(TTPInput& input) {
            vector<pair<ItemPtr,double>> pickingTable;
            double time = calcTime(input, &pickingTable);


            double value = 0;
            if (input.getKnapsack().getWeight() > maxWeight) value = - numeric_limits<double>::infinity();
            else {
                for (auto pair : pickingTable) {
                    double itemValue = pair.first->getValue();
                    double pickedTime = time - pair.second;
                    value += itemValue * pow(droppingRate, pickedTime / droppingConstant);
                }
            }


            return TTPOutput(value,time);
        }

        /*
         * Setter and Getter
         */
        double getRentingRate() const;
        void setRentingRate(double rentingRate);



    };


}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMO_H
