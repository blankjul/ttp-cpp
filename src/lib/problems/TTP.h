#ifndef TRAVELLING_THIEF_PROBLEM_TTP_H
#define TRAVELLING_THIEF_PROBLEM_TTP_H

#include <unordered_map>
#include "json/json.h"
#include "model/Item.h"
#include "model/ThiefMap.h"
#include "model/Knapsack.h"
#include "model/Tour.h"
#include "problems/Problem.h"
#include "problems/TTPOutput.h"
#include "problems/TTPInput.h"

using namespace std;

namespace ttp {



    /*!
     * This class represents the travelling thief problem which occurs in two different version.
     *
     * There is the single objective and the multi objective version which has different
     * target and evaluation functions.
     *
     */
    template <typename Input, typename Output>
    class TTP : public AbstractProblem<Input,Output> {


    protected:


        /*!< Minimal speed of the salesman */
        double minSpeed = 0.1;

        /*!< Maximal speed of the salesman */
        double maxSpeed = 1;

        /*!< Maximal weight of the knapsack */
        int maxWeight;

        /*!< The map that contains the cities and distances as well as the items */
        ThiefMapPtr map;



    public:

        //! initialize without values
        TTP() : map(nullptr), maxWeight(-1) {};

        //! Constructor for the classes that inherit from this one.
        TTP(ThiefMapPtr map, int maxWeight) : map(map), maxWeight(maxWeight) {};

        virtual Output evaluate(Input&) = 0;

        double getMinSpeed() const {
            return minSpeed;
        }

        void setMinSpeed(double minSpeed) {
            TTP::minSpeed = minSpeed;
        }

        double getMaxSpeed() const {
            return maxSpeed;
        }

        void setMaxSpeed(double maxSpeed) {
            TTP::maxSpeed = maxSpeed;
        }

        int getMaxWeight() const {
            return maxWeight;
        }

        void setMaxWeight(int maxWeight) {
            TTP::maxWeight = maxWeight;
        }

        const ThiefMapPtr &getMap() const {
            return map;
        }

        void setMap(const ThiefMapPtr &map) {
            TTP::map = map;
        }

        double calcTime(TTPInput input, vector<pair<ItemPtr,double>>* pickingTable = nullptr) {

            Knapsack k = input.getKnapsack();
            Tour t = input.getTour();

            if (!t.isValid()) {
                cout << t;
                throw runtime_error("The given tour is not valid!");
            }

            // initialize the values
            double currentTime = 0;
            double currentSpeed = maxSpeed;
            double currentWeight = 0;

            // for all visited cities
            for (int i = 1; i < t.size(); ++i) {

                // when the thief arrives at the city -> add the elapsed time and observe the rent
                currentTime += map->calcTime(t[i - 1], t[i], currentSpeed);

                // update the current knapsack weight by looking at new picked itemsMap
                vector<ItemPtr> availableItems = map->getItemsAtCity(t[i]);
                for (ItemPtr item : availableItems) {
                    if (k.contains(item)) {
                        currentWeight += item->getWeight();
                        if (pickingTable != nullptr) pickingTable->push_back(make_pair(item, currentTime));
                    }

                }

                // update the velocity for the next run
                currentSpeed = max(minSpeed, maxSpeed - currentWeight * (maxSpeed - minSpeed) / maxWeight);

            }

            // go back to the starting point
            currentTime += map->calcTime(t[t.size() - 1], t[0], currentSpeed);

            return currentTime;
        }



        Json::Value getJson() {
            Json::Value object;
            object["type"] = "ttp";
            object["numberOfCities"] = map->size();
            object["maxWeight"] = getMaxWeight();

            Json::Value matrix;
            for (int i = 0; i < map->size(); ++i) {
                Json::Value row;
                for (int j = 0; j < map->size(); ++j) {
                    row.append((*map)[i][j]);
                }
                matrix.append(row);
            }
            object["matrix"] = matrix;

            Json::Value items;
            for (auto it = map->begin(); it != map->end(); ++it) {
                Json::Value entry;
                entry["value"] = (*it)->getValue();
                entry["weight"] = (*it)->getWeight();
                entry["city"] = map->getCityOfItem(*it);
                items.append(entry);
            }
            object["items"] = items;
            return object;
        }



        void parseJson(Json::Value root) {

            std::string type = root.get("type", "unknown").asString();
            if (type != "ttp") throw std::runtime_error("Problem type has to be ttp!");

            int numOfCities = root.get("numberOfCities", -1).asInt();
            if (numOfCities < 0) throw std::runtime_error("Please define numberOfCities larger than zero!");
            map = ThiefMapPtr(numOfCities);

            maxWeight = root.get("maxWeight", -1).asInt();
            if (maxWeight < 0) throw std::runtime_error("Max Weight has to specified and larger than zero!");


            const Json::Value matrix = root["matrix"];
            for (int i = 0; i < matrix.size(); ++i) { // Iterates over the sequence elements.
                const Json::Value row = matrix[i];
                for (int j = 0; j < row.size(); ++j) {
                    map->set(i, j, row[j].asDouble());
                }
            }

            TTP ttp(map, maxWeight);

            const Json::Value items = root["items"];
            for (int i = 0; i < items.size(); ++i) { // Iterates over the sequence elements.
                const Json::Value item = items[i];
                ItemPtr ptr = make_shared<Item>(item["value"].asInt(), item["weight"].asInt());
                map->insert(item["city"].asInt(), ptr);
            }
        }


        TTP(std::istream &is) {

            Json::Value root;   // will contains the root value after parsing.
            Json::Reader reader;
            bool parsingSuccessful = reader.parse(is, root);
            if (!parsingSuccessful) {
                throw std::runtime_error("Could not read the JSON file!");
            }

            parseJson(root);

        }


        //! Converts the problem to json
        void toJson(std::ostream &s) {
            s << getJson();
        }







    };








}


#endif //TRAVELLING_THIEF_PROBLEM_TTP_H
