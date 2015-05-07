#ifndef TRAVELLING_THIEF_PROBLEM_TTP_H
#define TRAVELLING_THIEF_PROBLEM_TTP_H

#include <unordered_map>
#include "model/item.h"
#include "model/map.h"
#include "model/knapsack.h"


using namespace std;

namespace TTP {



    /*!
     * This class represents the travelling thief problem which occurs in two different version.
     *
     * There is the single objective and the multi objective version which has different
     * target and evaluation functions.
     *
     */
    class TravellingThiefProblem {



    protected:

        /*!< Minimal speed of the salesman */
        double minSpeed;

        /*!< Maximal speed of the salesman */
        double maxSpeed;

        /*!< Maximal weight of the knapsack */
        int maxWeight;

        /*!< The map that contains the cities and distances */
        Map m;

        /*!< The mapping of cities and the item list */
        unordered_map<int, vector<ItemPtr>> itemsMap;

        /*!< List that knows the insertion order and could easily map each pointer to a city */
        vector<pair<ItemPtr, int>> items;



        /**
         * This is just a helper method for calculating the target. Since only the calculation
         * of the item values is different this calculates the time and collect the items picking time stamps.
         */
        void calcTour(Tour &t, Knapsack &k, double & currentTime , vector<pair<ItemPtr,double>> & pickedItems) ;



        /**
         * Constructor for the classes that inherit from this one.
         */
        TravellingThiefProblem(Map &map, int maxWeight) : minSpeed(TravellingThiefProblem::DEFAULT_MIN_SPEED),
                                                          maxSpeed(TravellingThiefProblem::DEFAULT_MAX_SPEED),
                                                          m(map),
                                                          maxWeight(maxWeight){}



    public:


        /*!< Default maximal speed or velocity of the thief */
        static constexpr double DEFAULT_MAX_SPEED = 1;

        /*!< Default minimal speed or velocity of the thief */
        static constexpr double DEFAULT_MIN_SPEED = 0.1;




        /**
         * Converts a boolean vector to a knapsack.
         */
        Knapsack convertKnapsack(vector<bool>);


        /**
         * Returns all items with mapping to the city.
         */
        const vector<pair<ItemPtr, int>> &getItems() const;


        /**
         * Returns all the items at the specific city.
         */
        vector< shared_ptr<Item> > getItems(int city);


        /**
         * Add an item to city. ATTENTION: One item could be added multiple times here.
         */
        void add(int city, ItemPtr i);




        /*
         * Setter and Getter
         */
        double getMinSpeed() const;
        void  setMinSpeed(double minSpeed);
        double  getMaxSpeed() const;
        void  setMaxSpeed(double maxSpeed);
        int  getMaxWeight() const;
        void  setMaxWeight(int maxWeight);


    };


}


#endif //TRAVELLING_THIEF_PROBLEM_TTP_H
