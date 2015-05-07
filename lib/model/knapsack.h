#ifndef TRAVELLING_THIEF_PROBLEM_KNAPSACK_H
#define TRAVELLING_THIEF_PROBLEM_KNAPSACK_H

#include "item.h"
#include <unordered_set>



using namespace std;

namespace TTP {


    /*! This class represents the knapsack that could be filled with items.
     *
     * The pointer to items are saved in a set. The current weight und value
     * is provided by the class.
     *
     */
    class Knapsack {

    public:

        /**
         * Create an empty Knapsack without any items.
         */
        Knapsack() : weight(0), value(0) {};

        /**
         * Add an item to the knapsack. Each item could only be once in a knapsack!
         */
        bool add(ItemPtr i);

        /**
         * Add an item to the knapsack.
         */
        bool remove(ItemPtr i);


        /**
         * Check wether an item is contained or not.
         */
        bool contains(ItemPtr i);

        /**
         * Returns the current number of items that are in the knapsack.
         */
        int size() const;


        /**
         * Returns the current value of all items -> Here is no renting rate considered.
         */
        double getValue() const;


        /**
         * Returns the current weight of all items.
         */
        double getWeight() const;

    private:


        unordered_set<ItemPtr> items; /*!< Set of all the items which were picked */

        double weight; /*!< current weight */

        double value; /*!< current value */


    };
}


#endif //TRAVELLING_THIEF_PROBLEM_KNAPSACK_H
