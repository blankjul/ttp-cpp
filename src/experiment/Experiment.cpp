#include <ttpmo/NSGAII.h>
#include <metaheuristics/nsgaII/NSGAII.h>
#include <ttpmo/MOAD.h>
#include <ttpmo/SMPSO.h>
#include "Factory.h"
#include "qualityIndicator/Hypervolume.h"
#include "qualityIndicator/Spread.h"
#include "qualityIndicator/InvertedGenerationalDistance.h"
#include "qualityIndicator/Epsilon.h"
#include "Algorithm.h"
#include "Util.h"

using namespace ttp;
using namespace ttp::mo;


void analyze(TTPOutputSet bestFront, TTPOutputSet front) {

    vector<vector<double>> solutionFront = convertTTPOutput(front);
    vector<vector<double>> trueFront = convertTTPOutput(bestFront);

    Hypervolume hv;
    double hvValue = hv.hypervolume(solutionFront, trueFront, trueFront[0].size());


    Spread spread;
    double spreadValue = spread.spread(solutionFront, trueFront, trueFront[0].size());

    InvertedGenerationalDistance igd;
    double igdValue = igd.invertedGenerationalDistance(solutionFront, trueFront, trueFront[0].size());


    Epsilon eps;
    double epsValue = eps.epsilon(solutionFront, trueFront, trueFront[0].size());


    cout << "hv: " << hvValue << endl;
    cout << "spread: " << spreadValue << endl;
    cout << "igd: " << igdValue << endl;
    cout << "eps: " << epsValue << endl;


}

int main(int argc, char **argv) {


    /*

    KnapsackProblem kn2p = ProblemFactory::createKNP(1000, 1000,
                                                    ProblemFactory::KnapsackType::STRONGLY_CORRELATED,100);

    ofstream strongFile;
    strongFile.open ("strong.csv");
    for (ItemPtr ptr : kn2p.getItems()) {
        strongFile << ptr->getWeight() << "," << ptr->getValue() << endl;
    }
    strongFile.close();

    KnapsackProblem kn3p = ProblemFactory::createKNP(1000, 1000,
                                                     ProblemFactory::KnapsackType::WEAKLY_CORRELATED,100);

    ofstream weakFile;
    strongFile.open ("weak.csv");
    for (ItemPtr ptr : kn3p.getItems()) {
        strongFile << ptr->getWeight() << "," << ptr->getValue() << endl;
    }
    strongFile.close();

    KnapsackProblem kn4p = ProblemFactory::createKNP(1000, 1000,
                                                     ProblemFactory::KnapsackType::UNCORRELATED,100);

    ofstream unFile;
    strongFile.open ("un.csv");
    for (ItemPtr ptr : kn4p.getItems()) {
        strongFile << ptr->getWeight() << "," << ptr->getValue() << endl;
    }
    strongFile.close();

*/




    Exhaustive exhaustive;

    vector<ttp::Algorithm<MOTTP, TTPOutputSet> *> algorithms;
    algorithms.push_back(new mo::NSGAII());



    vector<MOTTP> problems;


    vector<int> cities{5, 8};
    vector<int> numberOfItemsPerCityArray{1};

    long seed = 100;


    for (int n : cities) {

        // number of cities for the experiment and create tsp
        TSP tsp = ProblemFactory::createTSP(n, 100, seed);

        // for each number type
        for (int numberOfItemsPerCity : numberOfItemsPerCityArray) {

            // create knp with enough items -> first city has no items..
            int numOfItems = numberOfItemsPerCity * (tsp.count() - 1);
            KnapsackProblem knp = ProblemFactory::createKNP(numOfItems, 100,
                                                            ProblemFactory::KnapsackType::STRONGLY_CORRELATED,
                                                            seed);


            MOTTP ttp = ProblemFactory::createTTP(tsp, knp, numberOfItemsPerCity);

            cout << "------------------------------------------------\n";
            cout << "n: " << n << "  itemsPerCity " << numberOfItemsPerCity << endl;
            cout << "------------------------------------------------\n";
            TTPOutputSet bestFront = exhaustive.solve(ttp);


            for (ttp::Algorithm<MOTTP, TTPOutputSet> *algorithm : algorithms) {

                cout << "-----------------------\n";
                cout << (string) typeid(*algorithm).name() << endl;
                cout << "-----------------------\n";
                TTPOutputSet front = algorithm->solve(ttp);

                analyze(bestFront, front);

            }


        }

    }


};