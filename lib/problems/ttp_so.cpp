#include "ttp_so.h"


namespace TTP {


    double SingleObjectiveTravellingThiefProblem::evaluate(Tour &t, Knapsack &k) {


        // calculate the tour
        double elapsedTime = 0;
        vector<pair<ItemPtr,double>> pickedItems;

        calcTour(t,k,elapsedTime, pickedItems);

        // calculate the values of the knapsack when arrived
        double finalValue = 0;
        if (k.getWeight() <= maxWeight) {
            for (auto p : pickedItems) finalValue += p.first->getValue();
        }
        double result = finalValue - rentingRate * (elapsedTime);
        return result;

    }

    double SingleObjectiveTravellingThiefProblem::getRentingRate() const {
        return rentingRate;
    }

    void SingleObjectiveTravellingThiefProblem::setRentingRate(double rentingRate) {
        this->rentingRate = rentingRate;
    }
}
