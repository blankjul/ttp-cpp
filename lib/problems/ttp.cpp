#include "ttp.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "json/json.h"


namespace ttp {


    TravellingThiefProblem::TravellingThiefProblem(MapPtr map, vector<ItemPtr> items, int itemsPerCity, int maxWeight)
            : TravellingThiefProblem(map, maxWeight) {

        if (items.size() < (map->count() - 1) * itemsPerCity)
            throw std::runtime_error("The items are not enough to fill all the cities according to itemsPerCity!");

        int counter = 0;
        for (int j = 1; j < map->count(); ++j) {
            for (int i = 0; i < itemsPerCity; ++i) {
                add(items[counter++], j);
            }
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

    Knapsack TravellingThiefProblem::convertVectorToKnapsack(vector<int> b) {
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


    vector<int> TravellingThiefProblem::convertKnapsackToVector(Knapsack &k) {
        vector<int> b(sizeOfItems());
        for (int i = 0; i < b.size(); ++i) {
            if (k.contains(items[i].first)) b[i] = 1;
        }
        return b;
    }

    const vector<pair<ItemPtr, int>> &TravellingThiefProblem::getItems() const {
        return items;
    }


    vector<shared_ptr<Item> > TravellingThiefProblem::getItems(int city) {
        auto it = itemsMap.find(city);
        if (it == itemsMap.end()) return vector<ItemPtr>();
        else return vector<ItemPtr>(it->second);
    }


    void TravellingThiefProblem::add(ItemPtr i, int city) {

        if (city == 0) throw std::runtime_error("The first city does not have any item!");

        auto it = itemsMap.find(city);

        if (it == itemsMap.end()) {
            // create vector with one element
            vector<ItemPtr> v;
            v.push_back(i);

            // add the current city
            pair<int, vector<ItemPtr> > pair(city, v);
            itemsMap.insert(pair);

        } else {
            it->second.push_back(i);
        }
        items.push_back(make_pair(i, city));
    }


    void TravellingThiefProblem::calcTour(Tour &t, Knapsack &k, double &currentTime,
                                          vector<pair<ItemPtr, double>> &pickedItems) {

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

    const MapPtr &TravellingThiefProblem::getMap() const {
        return m;
    }


    vector<pair<ItemPtr, int>> TravellingThiefProblem::getItemList() {
        return getItemList();
    }


    double TravellingThiefProblem::evaluateSO(Tour &t, Knapsack &k, double rentingRate) {

        // calculate the tour
        double elapsedTime = 0;
        vector<pair<ItemPtr, double>> pickedItems;

        calcTour(t, k, elapsedTime, pickedItems);

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


    void TravellingThiefProblem::toJson(std::ostream &s) {
        s << "{\n\"type\": \"ttp\", \n";
        s << "\"numberOfCities\": " << m->count() << ", \n";
        s << "\"maxWeight\": " << getMaxWeight() << ", \n";
        s << "\"droppingRate\": " << getDroppingRate() << ", \n";
        s << "\"droppingConstant\": " << getDroppingConstant() << ", \n";
        s << "\"rentingRate\": " << getRentingRate() << ", \n";

        // print the distance matrixs
        s << "\"matrix\": [\n";
        for (int i = 0; i < m->count(); ++i) {
            s << "[";
            for (int j = 0; j < m->count(); ++j) {
                int value = m->get(i, j);
                s << value;
                if (j != m->count() - 1) s << ",";
            }
            s << "]";
            if (i != m->count() - 1) s << ",";
            s << "\n";
        }
        s << "]\n";

        s << ", \n \"items\": [\n";
        vector<pair<ItemPtr, int>> l = getItems();
        for (int i = 0; i < l.size(); ++i) {
            ItemPtr ptr = l[i].first;
            int city = l[i].second;
            s << "[" << ptr->getValue() << "," << ptr->getWeight() << "," << city << "]";
            if (i != l.size() - 1) s << ",";
        }

        s << "]\n";
        s << "}\n";
    }


    TravellingThiefProblem TravellingThiefProblem::fromJson(std::istream &is) {

        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(is, root);
        if (!parsingSuccessful) {
            throw std::runtime_error("Could not read the JSON file!");
        }

        std::string type = root.get("type", "unknown").asString();
        if (type != "ttp") throw std::runtime_error("Problem type has to be ttp!");

        int numOfCities = root.get("numberOfCities", -1).asInt();
        if (numOfCities < 0) throw std::runtime_error("Please define numberOfCities larger than zero!");

        int maxWeight = root.get("maxWeight", -1).asInt();
        if (maxWeight < 0) throw std::runtime_error("Max Weight has to specified and larger than zero!");

        double droppingRate = root.get("droppingRate", -1).asDouble();
        if (droppingRate < 0 || droppingRate > 1) throw std::runtime_error("No droppingRate between [0,1] found!");

        double droppingConstant = root.get("droppingConstant", 0).asDouble();
        if (droppingRate < 0) throw std::runtime_error("No droppingConstant larger than zero was found.");

        double rentingRate = root.get("rentingRate", -1).asDouble();
        if (rentingRate < 0 || rentingRate > 1) throw std::runtime_error("No rentingRate between [0,1] found!");


        MapPtr m = make_shared<Map>(numOfCities);

        const Json::Value matrix = root["matrix"];
        for (int i = 0; i < matrix.size(); ++i) { // Iterates over the sequence elements.
            const Json::Value row = matrix[i];
            for (int j = 0; j < row.size(); ++j) {
                m->set(i, j, row[j].asDouble());
            }
        }

        TravellingThiefProblem ttp(m, maxWeight);

        const Json::Value items = root["items"];
        for (int i = 0; i < items.size(); ++i) { // Iterates over the sequence elements.
            const Json::Value item = items[i];
            ItemPtr ptr = make_shared<Item>(item[0].asInt(), item[1].asInt());
            ttp.add(ptr, item[2].asInt());
        }

        return ttp;

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
