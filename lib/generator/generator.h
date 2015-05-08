#ifndef TRAVELLING_THIEF_PROBLEM_GENERATOR_H
#define TRAVELLING_THIEF_PROBLEM_GENERATOR_H

#include <problems/knp.h>
#include <problems/ttp.h>
#include "model/item.h"
#include "model/map.h"
#include "problems/tsp.h"


namespace TTP {


    class ProblemFactory {


    public:

        /**
         * Creates a TravellingSalesmanProblem from a given TSPLIB file from Reinelt.
         */
        static TravellingSalesmanProblem createTSP(string pathToFile);


        /**
         *  Creates a KnapsackProblem from several parameters.
         *
         *  numberOfItems: number of items that are possible picked into the knapsack
         *  upperBound: maximal value of weight and value
         *  type:   1=uncorrelated,
         *          2=weakly correlated.,
         *          3=strongly correlated.,
         *          4=subset sum
         *  capacityFactor: Factor of the capacity. Low Factor = Small knapsack; High Factor = Huge knapsack
         *  randomSeed: Random seed for creating the same instance multiple times
         *
         */
        static KnapsackProblem createKNP(int numberOfItems, int upperBound, int type, int capacityFactor, long randomSeed = time(NULL) );



        /**
         *  Creates a KnapsackProblem from several parameters.
         *
         *  numberOfItems: number of items that are possible picked into the knapsack
         *  upperBound: maximal value of weight and value
         *  type:   1=uncorrelated,
         *          2=weakly correlated.,
         *          3=strongly correlated.,
         *          4=subset sum
         *  capacityFactorRange: There are several Problems created with always the same items but different maxWeights.
         *                       This value also determines the size of the result vector.
         *  randomSeed: Random seed for creating the same instance multiple times
         *
         */
        static vector<KnapsackProblem> createMultipleKNP(int numberOfItems, int upperBound, int capacityFactorRange, int type, long randomSeed = time(NULL) );


        /**
         *  Creates a KnapsackProblem from several parameters.
         *
         *  pathToFile: Path to the TSP File.
         *  numberOfItems: number of items that are possible picked into the knapsack
         *  upperBound: maximal value of weight and value
         *  type:   1=uncorrelated,
         *          2=weakly correlated.,
         *          3=strongly correlated.,
         *          4=subset sum
         *  capacityFactor: Factor of the capacity. Low Factor = Small knapsack; High Factor = Huge knapsack
         *  randomSeed: Random seed for creating the same instance multiple times
         *
         */
        static TravellingThiefProblem createTTP(string pathToFile, int numberOfItems, int upperBound, int type, int capacityFactor, long randomSeed = time(NULL) );


        /**
         *  Creates a KnapsackProblem from several parameters.
         *
         *  pathToFile: Path to the TSP File.
         *  numberOfItems: item per city
         *  upperBound: maximal value of weight and value
         *  type:   1=uncorrelated,
         *          2=weakly correlated.,
         *          3=strongly correlated.,
         *          4=subset sum
         *  capacityFactorRange: There are several Problems created with always the same items but different maxWeights.
         *                       This value also determines the size of the result vector.
         *  randomSeed: Random seed for creating the same instance multiple times
         *
         */
        static vector<TravellingThiefProblem> createMultipleTTP(string pathToFile, int numberOfItems, int upperBound, int type, int capacityFactorRange, long randomSeed = time(NULL) );


    private:


        static pair<vector<ItemPtr>,long> createRandomItems(int, int, int, long);



    };


}


#endif //TRAVELLING_THIEF_PROBLEM_GENERATOR_H
