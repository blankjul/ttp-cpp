#ifndef TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H
#define TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H

#include "TSPAlgorithm.h"



namespace ttp {

    class TSPExhaustive : public TSPAlgorithm {
    public:


        Tour solve(TSP tsp) {

            // create the start solution
            vector<int> v;
            for (int i = 0; i < tsp.count(); ++i) {
                v.push_back(i);
            }

            double minCosts =  numeric_limits<double>::max();
            std::vector<int> bestTour;

            do {

                Tour t(v);
                double costs = tsp.evaluate(t);

                if (costs < minCosts) {
                    bestTour = v;
                }

            } while ( next_permutation(v.begin(),v.end()) && v [0] == 0);


            Tour result(bestTour);

            return result;
        }


    };

}




#endif //TRAVELLING_THIEF_PROBLEM_TSPEXHAUSTIVE_H
