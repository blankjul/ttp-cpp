#ifndef TRAVELLING_THIEF_PROBLEM_UTIL_H
#define TRAVELLING_THIEF_PROBLEM_UTIL_H

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include "model/Tour.h"
#include "model/Map.h"
#include <iterator>
#include <model/Knapsack.h>
#include <problems/TTPOutputSet.h>

using namespace std;


namespace ttp{


    vector<TourPtr> allTours(MapPtr map, bool noSymmetrical);

    vector<KnapsackPtr> allKnapsacks(vector<ItemPtr> v);

    vector<KnapsackPtr> allKnapsacks(vector<ItemPtr> v, int maxWeight);

    KnapsackPtr nextKnapsack(KnapsackPtr k, ItemPtr ptr);

    vector<vector<double>> convertTTPOutput(TTPOutputSet);

}



#endif //TRAVELLING_THIEF_PROBLEM_UTIL_H
