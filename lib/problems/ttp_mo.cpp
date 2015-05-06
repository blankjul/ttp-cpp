#include "ttp_mo.h"
#include <cmath>

namespace TTP {

    pair<double, double> MultiObjectiveTravellingThiefProblem::evaluate(Tour &t, Knapsack &k) {

        // initialize the values
        double currentSpeed = maxSpeed;
        double currentTime = 0;
        double currentWeight = 0;

        // save the picked item and the time when it is picked
        vector<pair<ItemPtr, double>> pickedItems;

        // for all visited cities
        for (int i = 1; i < t.size(); ++i) {

            // when the thief arrives at the city -> add the elapsed time and observe the rent
            currentTime += m.get(t[i - 1], t[i]) / currentSpeed;

            // update the current knapsack weight by looking at new picked itemsMap
            vector<ItemPtr> availableItems = getItems(t[i]);
            for (ItemPtr i : availableItems) {
                if (k.contains(i)) {
                    currentWeight += i->getWeight();
                    auto p = make_pair(i, currentTime);
                    pickedItems.push_back(p);
                }
            }

            // update the velocity for the next run
            currentSpeed = maxSpeed - currentWeight * (maxSpeed - minSpeed) / maxWeight;

        }

        // go back to the starting point
        currentTime += m.get(t[t.size() - 1], t[0]) / currentSpeed;


        // calculate the values of the knapsack when arrived
        double finalValue = 0;
        for (auto p : pickedItems) {
            double value = p.first->getValue();
            double time = currentTime - p.second;
            finalValue += p.first->getValue() * pow(droppingRate, time / DEFAULT_DROPPING_CONSTANT);
        }

        return pair<double, double>(currentTime, finalValue);
    }



}
