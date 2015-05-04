#ifndef TRAVELLING_THIEF_PROBLEM_KNAPSACK_H
#define TRAVELLING_THIEF_PROBLEM_KNAPSACK_H

#include "item.h"


using namespace std;

namespace TTP {

    class Knapsack {

    public:

        Knapsack(double w) : maxWeight(w){};

        bool add(Item i) {
            if (isOverloaded(i)) return false;
            else {
                items.push_back(i);
                currentWeight += i.getWeight();
                currentValue += i.getValue();
                return true;
            }
        }

        bool isOverloaded() const {
            return currentWeight > maxWeight;
        }

        bool isOverloaded(Item& i) const {
            return currentWeight + i.getWeight() > maxWeight;
        }

        int size() const {
            return items.size();
        }

        double getValue() const {
            return currentValue;
        }

        double getWeight() const {
            return currentWeight;
        }



    private:

        vector<Item> items;

        double maxWeight;

        double currentWeight;
        double currentValue;


    };
}


#endif //TRAVELLING_THIEF_PROBLEM_ITEM_H
