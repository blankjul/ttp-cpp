

#ifndef TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H

#include "solver.h"
#include "problems/tsp.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ttp {

    class TSPExhaustiveSolver : public TSPSolver {

    public:


        Tour solve(TravellingSalesmanProblem & tsp) {


            // create the start solution
            vector<int> v;
            for (int i = 0; i < tsp.count(); ++i) {
                v.push_back(i);
            }

            double minCosts =  numeric_limits<double>::max();
            Tour* bestTour;

            do {

                Tour t(v);
                double costs = tsp.evaluate(t);

                if (costs < minCosts) {
                    bestTour = & t;
                }

                //cout << t << " -> " << costs <<'\n';

            } while ( next_permutation(v.begin(),v.end()) && v [0] == 0);


            return *bestTour;


        }

    };
}



#endif //TRAVELLING_THIEF_PROBLEM_TSPExhaustiveSolver_H
