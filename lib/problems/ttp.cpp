#include "ttp.h"
#include <cmath>
#include <iostream>

namespace ttp {


    TravellingThiefProblem::TravellingThiefProblem(MapPtr map, vector<ItemPtr> items, int maxWeight) : TravellingThiefProblem(map,maxWeight){
        int itemsPerCity = items.size() / map->count();
        for (int i = 0; i < items.size(); ++i) {
            int currentCity = i / itemsPerCity;
            add(items[i], currentCity);
        }
    }


    void TravellingThiefProblem::addItems(vector<pair<ItemPtr, int>> items) {
        for (int i = 0; i < items.size(); ++i) {
            add(items[i].first, items[i].second);
        }
    }


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

    Knapsack TravellingThiefProblem::convertKnapsack(vector<int> b) {
        Knapsack k;
        if (b.size() != items.size()) return k;
        for (int i = 0; i < b.size(); ++i) {
            auto item = items[i];
            if (b[i] != 0) {
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



    void TravellingThiefProblem::add(ItemPtr i, int city) {
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


    void TravellingThiefProblem::calcTour(Tour &t, Knapsack &k, double &currentTime , vector<pair<ItemPtr,double>> & pickedItems) {

        // initialize the values
        double currentSpeed = maxSpeed;
        double currentWeight = 0;

        // for all visited cities
        for (int i = 1; i < t.size(); ++i) {

            // when the thief arrives at the city -> add the elapsed time and observe the rent
            currentTime += m->get(t[i - 1], t[i]) / currentSpeed;

            // update the current knapsack weight by looking at new picked itemsMap
            vector<ItemPtr> availableItems = getItems(t[i]);
            for (ItemPtr item : availableItems) {
                if (k.contains(item)) {
                    currentWeight += item->getWeight();
                    auto p = make_pair(item, currentTime);
                    pickedItems.push_back(p);
                }
            }

            // update the velocity for the next run
            currentSpeed = max(minSpeed, maxSpeed - currentWeight * (maxSpeed - minSpeed) / maxWeight);

        }

        // go back to the starting point
        currentTime += m->get(t[t.size() - 1], t[0]) / currentSpeed;

    }


    int TravellingThiefProblem::sizeOfCities() {
        return m->count();
    }

    int TravellingThiefProblem::sizeOfItems() {
        return items.size();
    }

    const MapPtr& TravellingThiefProblem::getMap() const {
        return m;
    }


    vector<pair<ItemPtr, int>> TravellingThiefProblem::getItemList() {
        return getItemList();
    }


    double TravellingThiefProblem::evaluateSO(Tour &t, Knapsack &k, double rentingRate) {

        // calculate the tour
        double elapsedTime = 0;
        vector<pair<ItemPtr,double>> pickedItems;

        calcTour(t,k,elapsedTime, pickedItems);

        // calculate the values of the knapsack when arrived
        double finalValue = 0;
        if (k.getWeight() <= maxWeight) {
            for (auto p : pickedItems) finalValue += p.first->getValue();
        }
        double result = finalValue - rentingRate * (elapsedTime);
        return result;

    }


    pair<double, double> TravellingThiefProblem::evaluateMO(Tour &t, Knapsack &k, double droppingRate,
                                                          double droppingConstant) {
        // calculate the tour
        double elapsedTime = 0;
        vector<pair<ItemPtr, double>> pickedItems;

        calcTour(t, k, elapsedTime, pickedItems);

        // calculate the values of the knapsack when arrived
        double finalValue = 0;

        if (k.getWeight() <= maxWeight) {
            for (auto p : pickedItems) {
                double value = p.first->getValue();
                double pickedTime = elapsedTime - p.second;
                finalValue += value * pow(droppingRate, pickedTime / DEFAULT_DROPPING_CONSTANT);
            }
        }

        return pair<double, double>(elapsedTime, finalValue);
    }




    double TravellingThiefProblem::getRentingRate() const {
        return rentingRate;
    }

    void TravellingThiefProblem::setRentingRate(double rentingRate) {
        TravellingThiefProblem::rentingRate = rentingRate;
    }

    double TravellingThiefProblem::getDroppingRate() const {
        return droppingRate;
    }

    void TravellingThiefProblem::setDroppingRate(double droppingRate) {
        TravellingThiefProblem::droppingRate = droppingRate;
    }

    double TravellingThiefProblem::getDroppingConstant() const {
        return droppingConstant;
    }

    void TravellingThiefProblem::setDroppingConstant(double droppingConstant) {
        TravellingThiefProblem::droppingConstant = droppingConstant;
    }


    void TravellingThiefProblem::setItems(const vector<pair<ItemPtr, int>> &items) {
        TravellingThiefProblem::items = items;
    }
}
