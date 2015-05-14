#ifndef TRAVELLING_THIEF_PROBLEM_KNP_H
#define TRAVELLING_THIEF_PROBLEM_KNP_H


#include <vector>
#include "model/item.h"
#include "model/knapsack.h"


using namespace std;



namespace ttp {



    /*!
     * This class represents the knapsack problem. A knapsack should be filled with items which has a profit and
     * a weight value. The knapsack has a maximum weight which is the constraint for maxmizing the overall value
     * of the knapsack.
     */
    class KnapsackProblem {


    private:

        vector<ItemPtr> items;  /*!< all items that could be picked into the knapsack */

        double maxWeight;


    public:

        /**
         * Create a Knapsack problem with items.
         */
        KnapsackProblem(vector<ItemPtr> & items, double maxWeight) : items(items), maxWeight(maxWeight) {};


        /**
         * Evaluate the current picking plan for the knapsack.
         */
        double evaluate(Knapsack & k);



        /**
         * Returns all available items.
         */
        vector<ItemPtr> getItems() const;



        /**
         * Returns the number of items that are available.
         */
        const int count() const;


        /**
         * Returns the maximal weight
         */
        double getMaxWeight() const;

        /**
         * Converts a int vector to a knapsack.
         */
        Knapsack convertVectorToKnapsack(vector<int>);

        /**
         * Converts a knapsack to an int vector.
         */
        vector<int> convertKnapsackToVector(Knapsack &k);




    };


}


#endif //TRAVELLING_THIEF_PROBLEM_KNP_H
