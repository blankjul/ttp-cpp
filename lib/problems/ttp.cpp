#include "ttp.h"

namespace TTP {


    double TravellingThiefProblem::getMinSpeed() const {
        return minSpeed;
    }

    void  TravellingThiefProblem::setMinSpeed(double minSpeed) {
        TravellingThiefProblem::minSpeed = minSpeed;
    }

    double  TravellingThiefProblem::getMaxSpeed() const {
        return maxSpeed;
    }

    void  TravellingThiefProblem::setMaxSpeed(double maxSpeed) {
        TravellingThiefProblem::maxSpeed = maxSpeed;
    }

    double  TravellingThiefProblem::getDroppingRate() const {
        return droppingRate;
    }

    void  TravellingThiefProblem::setDroppingRate(double droppingRate) {
        TravellingThiefProblem::droppingRate = droppingRate;
    }

    int  TravellingThiefProblem::getMaxWeight() const {
        return maxWeight;
    }

    void  TravellingThiefProblem::setMaxWeight(int maxWeight) {
        TravellingThiefProblem::maxWeight = maxWeight;
    }

    Knapsack TravellingThiefProblem::convertKnapsack(vector<bool> b) {
        Knapsack k;
        if (b.size() != items.size()) return k;
        for (int i = 0; i < b.size(); ++i) {
            auto item = items[i];
            if (b[i]) {
                k.add(item.first);
            }
        }
        return k;
    }

    const vector<pair<ItemPtr, int>> & TravellingThiefProblem::getItems() const {
        return items;
    }


    vector<shared_ptr<Item> > TravellingThiefProblem::getItems(int city) {
        auto it = itemsMap.find(city);
        if (it == itemsMap.end()) return vector<ItemPtr>();
        else return vector<ItemPtr>(it->second);
    }



    void TravellingThiefProblem::add(int city, ItemPtr i) {
        auto it = itemsMap.find(city);

        if (it == itemsMap.end()) {
            // create vector with one element
            vector<ItemPtr> v;
            v.push_back(i);

            // add the current city
            pair< int, vector<ItemPtr> > pair (city,v);
            itemsMap.insert(pair);

        } else {
            it->second.push_back(i);
        }
        items.push_back(make_pair(i, city));
    }
}
