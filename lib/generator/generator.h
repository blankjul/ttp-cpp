#ifndef TRAVELLING_THIEF_PROBLEM_GENERATOR_H
#define TRAVELLING_THIEF_PROBLEM_GENERATOR_H

#include <problems/knp.h>
#include <problems/ttp.h>
#include "model/item.h"
#include "model/map.h"
#include "problems/tsp.h"




namespace ttp {



    class ProblemFactory {




    public:


        /**
         * Enumeration for specifing the Knapsack factory.
         */
        enum class KnapsackType{ UNCORRELATED=1, WEAKLY_CORRELATED=2, STRONLY_CORRELATED=3, SUBSET_SUM=4};


        /**
         * Creates a TravellingSalesmanProblem from a given TSPLIB file from Reinelt.
         */
        static TravellingSalesmanProblem createTSP(string pathToFile);


        /**
         *  Creates a KnapsackProblem from several parameters.
         *
         *  \param numberOfItems number of items that are possible picked into the knapsack
         *  \param upperBound maximal value of weight and value
         *  \param type enum of the type which determines the correlation
         *  \param capacityFactor Factor of the capacity. Low Factor = Small knapsack; High Factor = Huge knapsack
         *  \param randomSeed Random seed for creating the same instance multiple times
         *
         */
        static KnapsackProblem createKNP(int numberOfItems, int upperBound, KnapsackType type, int capacityFactor, long randomSeed = time(NULL) );



        /**
         *  Creates a multiple knapsack problems. All have exactly the same items but different maxWeights!
         *  The value capacityFactorRange determines the number of problems.
         *  If there is a random seed defined you will always have the same knapsack combination!
         *
         *  \param numberOfItems number of items that are possible picked into the knapsack
         *  \param upperBound maximal value of weight and value
         *  \param type enum of the type which determines the correlation
         *  \param capacityFactorRange There are several Problems created with always the same items but different maxWeights.
         *                       This value also determines the size of the result vector.
         *  \param randomSeed Random seed for creating the same instance multiple times
         *
         */
        static vector<KnapsackProblem> createMultipleKNP(int numberOfItems, int upperBound, KnapsackType type, int capacityFactorRange , long randomSeed = time(NULL) );


        /**
         *  Creates a TTP problem with the constrains of the sub problems
         *
         *  \param tsp that contains the map for the TTP
         *  \param knp all the items and the maxWeight are provided by this object
         *  \return one TTP
         *
         */
        static TravellingThiefProblem createTTP(TravellingSalesmanProblem, KnapsackProblem);


        /**
         *  Creates Muliple TTP problems by using a TTP and multiple KNPs
         *
         *  \param tsp that contains the map for the TTP
         *  \param knps with the same items but different maxWeights!
         *  \return multiple TTPs
         *
         */
        static vector<TravellingThiefProblem> createMultipleTTP(TravellingSalesmanProblem tsp, vector<KnapsackProblem> knps);


    private:


        static pair<vector<ItemPtr>,long> createRandomItems(int, int, KnapsackType, long);



    };


}


#endif //TRAVELLING_THIEF_PROBLEM_GENERATOR_H
