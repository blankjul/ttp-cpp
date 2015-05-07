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


    void TravellingThiefProblem::calcTour(Tour &t, Knapsack &k, double & currentTime , vector<pair<ItemPtr,double>> & pickedItems) {

        // initialize the values
        double currentSpeed = maxSpeed;
        double currentWeight = 0;

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

    }
}
