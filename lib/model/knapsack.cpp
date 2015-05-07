#include "knapsack.h"

namespace TTP {


    bool Knapsack::add(ItemPtr i) {
        if (items.find(i) != items.end()) return false;
        weight += i->getWeight();
        value += i->getValue();
        items.insert(i);
        return true;
    }

    int Knapsack::size() const {
        return items.size();
    }

    double Knapsack::getValue() const {
        return value;
    }

    double Knapsack::getWeight() const {
        return weight;
    }

    bool Knapsack::contains(ItemPtr i) {
        return items.find(i) != items.end();
    }


    bool Knapsack::remove(ItemPtr i) {
        if (items.find(i) == items.end()) return false;
        weight -= i->getWeight();
        value -= i->getValue();
        items.erase(i);
        return true;
    }
}




