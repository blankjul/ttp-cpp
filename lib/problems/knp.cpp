#include "knp.h"


namespace TTP {


    const int KnapsackProblem::count() const {
        return items.size();
    }



    double KnapsackProblem::evaluate(Knapsack &k) {
        if (k.getWeight() > maxWeight) return 0;
        else return k.getValue();
    }



    vector<ItemPtr> KnapsackProblem::getItems() const {
        return items;
    }



    Knapsack KnapsackProblem::convertKnapsack(vector<bool> b) {
        Knapsack k;
        if (b.size() != items.size()) return k;
        for (int i = 0; i < b.size(); ++i) {
            auto item = items[i];
            if (b[i]) {
                k.add(item);
            }
        }
        return k;
    }

    double KnapsackProblem::getMaxWeight() const {
        return maxWeight;
    }

}
