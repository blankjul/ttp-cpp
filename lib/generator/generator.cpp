
#include "generator.h"
#include "model/map.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <algorithm>

extern "C"
{
#include "LKH.h"
}



namespace TTP {





    TravellingSalesmanProblem ProblemFactory::createTSP(std::string pathToFile) {

        MaxMatrixDimension =  numeric_limits<int>::max();


        ifstream file(pathToFile);
        if(!file) throw std::runtime_error("File " + pathToFile + " does not exist");

        // set the filePtr
        char filePtr[1024];
        strncpy(filePtr, pathToFile.c_str(), sizeof(filePtr));
        filePtr[sizeof(filePtr) - 1] = 0;
        ProblemFileName = filePtr;

        TraceLevel = 0;

        ReadProblem();

        if (CostMatrix == 0) throw std::runtime_error("Eror while parsing " + pathToFile + ". Wrong Format.");

        /*
         * Parse the file and write the Map.
         */
        MapPtr map = make_shared<Map>(Dimension);

        Node *Ni, *Nj;
        Ni = FirstNode;

        int column = 0;

        do {
            int row = 0;
            if (Ni->C != 0) {
                for (Nj = FirstNode; Nj != Ni; Nj = Nj->Suc) {

                    int value = Fixed(Ni, Nj) ? 0 : Distance(Ni, Nj);

                    map->set(row,column,value);
                    ++row;
                }
            }

            Ni = Ni->Suc;
            ++column;
        }
        while (Ni != FirstNode);

        TravellingSalesmanProblem tsp(map);
        return tsp;

    }


    KnapsackProblem ProblemFactory::createKNP(int numberOfItems, int upperBound, int type, int capacityFactor,
                                              long randomSeed) {

        auto result = createRandomItems(numberOfItems, upperBound, type, randomSeed);

        long c = (randomSeed * (double) result.second) / (capacityFactor + 1);
        if (c <= upperBound) c = upperBound + 1;

        TTP::KnapsackProblem knp(result.first, c);
        return knp;
    }


    vector<KnapsackProblem> ProblemFactory::createMultipleKNP(int numberOfItems, int upperBound,
                                                              int capacityFactorRange, int type, long randomSeed) {

        vector<KnapsackProblem> knps;

        auto result = createRandomItems(numberOfItems, upperBound, type, randomSeed);

        for (int j = 1; j <= capacityFactorRange; ++j) {
            long c = (randomSeed * (double) result.second) / (j + 1);
            if (c <= upperBound) c = upperBound + 1;
            TTP::KnapsackProblem knp(result.first, c);
            knps.push_back(knp);
        }
        return knps;
    }



    pair<vector<ItemPtr>,long> ProblemFactory::createRandomItems(int numberOfItems, int upperBound, int type, long randomSeed = time(NULL)) {

        vector<ItemPtr> items;

        srand(randomSeed);
        int r1 = upperBound /10;

        long sum = 0;

        for (int i = 0; i < numberOfItems; ++i) {

            double weight = (rand() % upperBound) + 1;
            double value;

            switch (type) {
                case 1: value = (rand() % upperBound) + 1;
                    break;
                case 2: value = (rand() % (2*r1+1)) + weight - r1;
                    if (value <= 0) value = 1;
                    break;
                case 3: value = weight + 10;
                    break;
                case 4: value = weight;
                    break;
            }
            sum += weight;
            ItemPtr iPtr = make_shared<Item>(value, weight);
            items.push_back(iPtr);

        }
        auto result = make_pair(items,sum);
        return result;

    }


    TravellingThiefProblem ProblemFactory::createTTP(string pathToFile, int itemPerCity, int upperBound, int type,
                                                     int capacityFactor, long randomSeed) {
        TravellingSalesmanProblem tsp = ProblemFactory::createTSP(pathToFile);
        KnapsackProblem knp = ProblemFactory::createKNP(itemPerCity*tsp.count(), upperBound, type, capacityFactor, randomSeed);
        TravellingThiefProblem ttp(tsp.getMap(), knp.getItems(), knp.getMaxWeight());

        return ttp;
    }


    vector<TravellingThiefProblem> ProblemFactory::createMultipleTTP(string pathToFile, int itemPerCity, int upperBound, int type,
                                                             int capacityFactor, long randomSeed) {
        vector<TravellingThiefProblem> result;
        TravellingSalesmanProblem tsp = ProblemFactory::createTSP(pathToFile);
        vector<KnapsackProblem> knps = ProblemFactory::createMultipleKNP(itemPerCity*tsp.count(), upperBound, type, capacityFactor, randomSeed);

        for (int i = 0; i < knps.size(); ++i) {
            TravellingThiefProblem ttp(tsp.getMap(), knps[i].getItems(), knps[i].getMaxWeight());
        }

        return result;

    }
}




