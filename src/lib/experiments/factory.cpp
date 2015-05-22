

#include "factory.h"
#include "generator.h"
#include "problems/TravellingThiefProblemDeptr.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace ttp;


void ExperimentFactory::create() {

    vector<int> cities {5,10,20,50,100};

    vector<int> numberOfItemsPerCity{1,2,5,10};


    long seed = 1;


    for (int i = 0; i < cities.size(); ++i) {

        // number of cities for the experiment and create tsp
        int n = cities[i];
        TSP tsp = ProblemFactory::createTSP(n, seed);

        // for each number type
        for (int j = 0; j < numberOfItemsPerCity.size(); ++j) {

            // create knp with enough items -> first city has no items..
            int numOfItems = numberOfItemsPerCity[j] * (tsp.count() -  1);
            KnapsackProblem knp = ProblemFactory::createKNP(numOfItems, 1000, ProblemFactory::KnapsackType::STRONGLY_CORRELATED, seed);

            // create ttp and print the json to file
            TravellingThiefProblemDeptr ttp(tsp.getMap(), knp.getItems(), numberOfItemsPerCity[j], knp.getMaxWeight());

            std::stringstream ss;
            ss << "../data/ttp_n" << n << "_i" <<  numberOfItemsPerCity[j] << ".ttp";
            const std::string name = ss.str();

            ofstream jsonFile (name);

            ttp.toJson(jsonFile);


        }



    }







}