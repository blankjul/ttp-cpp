#include "ttp_mo.h"
#include <cmath>

namespace TTP {

    pair<double, double> MultiObjectiveTravellingThiefProblem::evaluate(Tour &t, Knapsack &k) {


        // calculate the tour
        double elapsedTime = 0;
        vector<pair<ItemPtr,double>> pickedItems;

        calcTour(t,k,elapsedTime, pickedItems);

        // calculate the values of the knapsack when arrived
        double finalValue = 0;
        if (k.getWeight() <= maxWeight) {
            for (auto p : pickedItems) {
                double value = p.first->getValue();
                double time = elapsedTime - p.second;
                finalValue += p.first->getValue() * pow(droppingRate, time / DEFAULT_DROPPING_CONSTANT);
            }
        }

        return pair<double, double>(elapsedTime, finalValue);
    }

    double  MultiObjectiveTravellingThiefProblem::getDroppingRate() const {
        return droppingRate;
    }

    void  MultiObjectiveTravellingThiefProblem::setDroppingRate(double droppingRate) {
        droppingRate = droppingRate;
    }



}
