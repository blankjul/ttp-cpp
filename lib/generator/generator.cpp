
#include "generator.h"
#include "model/map.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <algorithm>
#include "wrapper/lkh.h"



namespace ttp {



    TravellingSalesmanProblem ProblemFactory::createTSP(std::string pathToFile) {
        LKHWrapper lkh;
        MapPtr map = lkh.createMap(pathToFile);
        TravellingSalesmanProblem tsp(map);
        return tsp;
    }


    KnapsackProblem ProblemFactory::createKNP(int numberOfItems, int upperBound, KnapsackType type, int capacityFactor,
                                              long randomSeed) {


        auto result = createRandomItems(numberOfItems, upperBound, type, randomSeed);

        float rndm = rand()/(float)RAND_MAX;
        long c = (rndm * result.second) / (capacityFactor + 1);
        if (c <= upperBound) c = upperBound + 1;

        KnapsackProblem knp(result.first, c);
        return knp;
    }


    vector<KnapsackProblem> ProblemFactory::createMultipleKNP(int numberOfItems, int upperBound, KnapsackType type,
                                                              int capacityFactorRange,  long randomSeed) {

        vector<KnapsackProblem> knps;

        auto result = createRandomItems(numberOfItems, upperBound, type, randomSeed);



        for (int j = 1; j <= capacityFactorRange; ++j) {
            float rndm = rand()/(float)RAND_MAX;
            long c = (rndm * (double) result.second) / (j + 1);
            if (c <= upperBound) c = upperBound + 1;
            KnapsackProblem knp(result.first, c);
            knps.push_back(knp);
        }
        return knps;
    }



    pair<vector<ItemPtr>,long> ProblemFactory::createRandomItems(int numberOfItems, int upperBound, KnapsackType type, long randomSeed) {


        if (numberOfItems <= 0) throw std::runtime_error("The number of items has to be higher than 0.");
        if (upperBound <= 0) throw std::runtime_error("The upper bound of weight and value has to be higher than 0.");


        vector<ItemPtr> items;

        srand(randomSeed);
        int r1 = upperBound /10;

        long sum = 0;

        for (int i = 0; i < numberOfItems; ++i) {

            double weight = (rand() % upperBound) + 1;
            double value;

            switch (type) {
                case KnapsackType::UNCORRELATED: value = (rand() % upperBound) + 1;
                    break;
                case KnapsackType::WEAKLY_CORRELATED: value = (rand() % (2*r1+1)) + weight - r1;
                    if (value <= 0) value = 1;
                    break;
                case KnapsackType::STRONLY_CORRELATED: value = weight + 10;
                    break;
                case KnapsackType::SUBSET_SUM: value = weight;
                    break;
            }
            sum += weight;
            ItemPtr iPtr = make_shared<Item>(value, weight);
            items.push_back(iPtr);

        }
        auto result = make_pair(items,sum);
        return result;

    }



    TravellingThiefProblem ProblemFactory::createTTP(TravellingSalesmanProblem tsp, KnapsackProblem knp) {
        TravellingThiefProblem ttp(tsp.getMap(), knp.getItems(), knp.getMaxWeight());
        return ttp;
    }




    vector<TravellingThiefProblem> ProblemFactory::createMultipleTTP(TravellingSalesmanProblem tsp, vector<KnapsackProblem> knps) {
        vector<TravellingThiefProblem> result;
        for (int i = 0; i < knps.size(); ++i) {
            TravellingThiefProblem ttp(tsp.getMap(), knps[i].getItems(), knps[i].getMaxWeight());
        }
        return result;
    }





}




