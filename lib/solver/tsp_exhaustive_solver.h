

#ifndef TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H

#include "solver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

namespace TTP {

    class TSPExhaustiveSolver : public TSPSolver {

    public:


        Tour solve(Map map) {

            // create the start solution
            vector<int> v;
            for (int i = 0; i < map.size(); ++i) {
                v.push_back(i);
            }

            double minCosts =  numeric_limits<double>::max();
            Tour bestTour;

            do {

                Tour t(v);
                double costs = map.getCosts(t);

                if (costs < minCosts) {
                    bestTour = t;
                }

                //cout << t << " -> " << costs <<'\n';

            } while ( next_permutation(v.begin(),v.end()) && v [0] == 0);


            return bestTour;


        }

    };
}



#endif //TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H
