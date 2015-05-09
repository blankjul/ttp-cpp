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

    const unordered_set<ItemPtr> &Knapsack::getItems() const {
        return items;
    }


    std::ostream & operator<<(std::ostream & s, Knapsack const &k) {
        s << "Knapsack[size:" << k.size() << ",weight:" << k.getWeight() << ",value:" << k.getValue() << "]\n";
        auto items = k.getItems();
        unordered_set<::std::shared_ptr<::TTP::Item>>::const_iterator it = items.begin();
        int counter = 0;
        for(; it != items.end(); ++it) {
            s << counter++ << *it << "\n";
        }
    }


}




