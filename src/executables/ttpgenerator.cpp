#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include "experiments/generator.h"
#include <fstream>
#include <cursesm.h>
#include "algorithm"
#include "problems/TravellingThiefProblemDeptr.h"


using namespace ttp;
using namespace std;

int main(int argc, char **argv) {

    // Wrap everything in a try block for catching exceptions.
    try {


        TCLAP::CmdLine cmd("The ttpgenerator is used to create Test Cases for the Travelling Thief Problem.", ' ',
                           "0.1");


        TCLAP::UnlabeledValueArg<std::string> argFilePath("tspFile", "Please insert the Path to a .tsp file from the \
                TSPLIB from Reinelt.", true, "", "file.tsp");
        cmd.add(argFilePath);

        TCLAP::UnlabeledValueArg<int> argItemsCount("itemsPerCity", "How many items each of the cities \
                should have", true, 1, "itemsPerCity");
        cmd.add(argItemsCount);

        TCLAP::UnlabeledValueArg<int> argUpperBound("range", "Weight/Value Range [0,x] of the items", true, 1000,
                                                    "upperBound");
        cmd.add(argUpperBound);

        TCLAP::UnlabeledValueArg<int> argItemsType("itemType",
                                                   "items type: 1=uncorr., 2=weakly corr., 3=strongly corr., 4=subset sum",
                                                   true, 1000, "itemsType");
        cmd.add(argItemsType);

        TCLAP::UnlabeledValueArg<int> argCapacity("maxCapacityFactor",
                                                  "For the TTP instance there are 10 different Capacity values.", true,
                                                  1, "maxCapacityFactor");
        cmd.add(argCapacity);


        TCLAP::ValueArg<long> argRandomSeed("s", "seed", "Random seed to create the items.", false, -1, "random seed");
        cmd.add(argRandomSeed);


        // Parse the argv array.
        cmd.parse(argc, argv);


        // parse all the values
        std::string filePath = argFilePath.getValue();
        int itemPerCity = argItemsCount.getValue();
        int range = argUpperBound.getValue();
        ProblemFactory::KnapsackType type = static_cast<ProblemFactory::KnapsackType>(argItemsType.getValue());
        int c = argCapacity.getValue();

        // parse optional argument
        long seed = argRandomSeed.getValue();
        if (seed == -1) seed = time(NULL);

        TSP tsp = ProblemFactory::createTSPFromFile(filePath);
        KnapsackProblem knp = ProblemFactory::createKNP(itemPerCity * tsp.count(), range, type, seed);



    } catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
    catch (std::runtime_error &e)  // catch any exceptions
    { std::cerr << "ERROR: " << e.what() << std::endl; }
}