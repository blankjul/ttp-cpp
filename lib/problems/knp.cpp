#include "knp.h"


namespace ttp {


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



    Knapsack KnapsackProblem::convertVectorToKnapsack(vector<int> b) {
        Knapsack k;
        if (b.size() != items.size()) return k;
        for (int i = 0; i < b.size(); ++i) {
            auto item = items[i];
            if (b[i] != 0) {
                k.add(item);
            }
        }
        return k;
    }


    vector<int> KnapsackProblem::convertKnapsackToVector(Knapsack &k) {
        vector<int> b(count());
        for (int i = 0; i < b.size(); ++i) {
            if (k.contains(items[i])) b[i] = 1;
        }
        return b;
    }

    double KnapsackProblem::getMaxWeight() const {
        return maxWeight;
    }

}
