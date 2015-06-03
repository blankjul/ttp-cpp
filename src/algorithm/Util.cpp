#include "Util.h"
#include <stack>
#include <problems/TTPOutput.h>

using namespace ttp;






vector<vector<double>> ttp::convertTTPOutput(TTPOutputSet front)
{
    vector<vector<double>> result;
    for(TTPOutput& entry : front) {
        vector<double> toAdd {entry.getValue(), entry.getTime()};
        result.push_back(toAdd);
    }
    return result;
}



vector<TourPtr> ttp::allTours(MapPtr map, bool noSymmetrical) {

    vector<TourPtr> result;

    // create the start solution
    vector<int> v;
    for (int i = 0; i < map->size(); ++i) {
        v.push_back(i);
    }

    unordered_set<Tour> hash;

    do {

        // the current tour
        TourPtr ptr = make_shared<Tour>(v);

        // check if we do not need the tour because it's symmetrical
        if (noSymmetrical && hash.find(*ptr) != hash.end()) {
            continue;
        }

        // add symmetrical to the hash
        hash.insert(ptr->getSymmetrical());

        result.push_back(ptr);

    } while ( next_permutation(v.begin(),v.end()) && v [0] == 0);

    return result;

}




vector<KnapsackPtr> ttp::allKnapsacks(vector<ItemPtr> v) {
    vector<KnapsackPtr> result;

    for (int i = 0; i < pow(2, v.size()); i++) {

        std::vector<int> b;
        for (int j = 0; j < v.size(); j++) {
            bool tmp = i & (1 << j);
            if (tmp) b.push_back(1);
            else b.push_back(0);
        }

        KnapsackPtr k = make_shared<Knapsack>();
        k->fill(v.begin(), v.end(), b.begin(), b.end());

       result.push_back(k);
    }

    return result;
}


KnapsackPtr ttp::nextKnapsack(KnapsackPtr k, ItemPtr ptr) {
    unordered_set<ItemPtr> pickedItems = k->getItems();
    KnapsackPtr result = make_shared<Knapsack>(pickedItems.begin(), pickedItems.end());
    if (ptr != nullptr) result->add(ptr);
    return result;
}


vector<KnapsackPtr> ttp::allKnapsacks(vector<ItemPtr> items, int maxWeight) {

    // result and stack for saving the arguments
    vector<KnapsackPtr> result;
    stack<pair<KnapsackPtr,int>> s;

    // the root element
    KnapsackPtr ptr = make_shared<Knapsack>();

    auto root = make_pair(ptr, 0);
    s.push(root);

    while(!s.empty()) {

        // receive the top element
        pair<KnapsackPtr,int> p = s.top();
        s.pop();
        KnapsackPtr ptr = p.first;
        int depth = p.second;

        // prune the construction tree if the weight has exceeded
        if (ptr->getWeight() > maxWeight) continue;

        // if we reached the leaf of the construction tree
        if (depth == items.size()) {
            result.push_back(ptr);
        } else {

            // if we take an item
            KnapsackPtr ptrRight = nextKnapsack(ptr,items[depth]);
            s.push(make_pair(ptrRight, depth+1));

            // if we take NO item
            KnapsackPtr ptrLeft = nextKnapsack(ptr,nullptr);
            s.push(make_pair(ptrLeft, depth+1));

        }
    }

    return result;
}