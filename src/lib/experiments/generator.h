#ifndef TRAVELLING_THIEF_PROBLEM_GENERATOR_H
#define TRAVELLING_THIEF_PROBLEM_GENERATOR_H

#include "problems/KnapsackProblem.h"
#include "problems/TravellingThiefProblemDeptr.h"
#include "model/Item.h"
#include "model/Map.h"
#include "problems/TSP.h"




namespace ttp {



    class ProblemFactory {




    public:


        /**
         * Enumeration for the Knapsack factory.
         */
        enum class KnapsackType{ UNCORRELATED = 1, WEAKLY_CORRELATED = 2, STRONGLY_CORRELATED = 3 };


        /**
         * Creates a TSP from a given TSPLIB file from Reinelt.
         */
        static TSP createTSPFromFile(string pathToFile);


        /**
         * Create a TSP Problem randomly with n cities on the map and creates the distance matrix
         * by calculating the euclidean distance between all the cities.
         *
         * \param n number of cities on the map
         * \param bounds of the map where the cities are placed
         * \param seed random seed for creating the same map twice.
         */
        static TSP createTSP(unsigned int n, unsigned int bound = 1000, unsigned int seed = time(NULL));


        /**
         *  Creates a KnapsackProblem.
         *
         *  \param numberOfItems number of items that are possible picked into the knapsack
         *  \param bounds maximal value of weight and value
         *  \param type enum of the type which determines the correlation
         *  \param seed for creating the same instance multiple times.
         *
         */
        static KnapsackProblem createKNP(unsigned int numberOfItems, unsigned int bounds, KnapsackType type, unsigned int seed = time(NULL) );



        /**
         *  Creates a TTP problem with the constrains of the sub problems
         *
         *  \param tsp that contains the map for the TTP
         *  \param knp all the items and the maxWeight are provided by this object
         *  \return one TTP
         *
         */
        //static TTP createTTP(TSP, KnapsackProblem, int itemsPerCity);




    };


}


#endif //TRAVELLING_THIEF_PROBLEM_GENERATOR_H
