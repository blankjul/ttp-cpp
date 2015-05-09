#ifndef TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H

#include "solver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;

namespace TTP {

    class TTPMOExhaustiveSolver : public TTPMOSolver {

    public:


        pair<Tour, Knapsack> solve(MultiObjectiveTravellingThiefProblem &ttp) {

            MapPtr m = ttp.getMap();

            // create the start solution
            vector<int> v;
            for (int i = 0; i < m->count(); ++i) {
                v.push_back(i);
            }

            double minCosts = numeric_limits<double>::max();
            Tour *bestTour;


            // for all the possible tsp tours
            do {

                // create a tour
                Tour t(v);


                // create the start solution

                for (int i = 0; i < pow(2, ttp.sizeOfItems()); i++) {

                    std::vector<int> b;
                    for (int j = 0; j < ttp.sizeOfItems(); j++) {
                        bool tmp = i & (1 << j);
                        if (tmp) b.push_back(1);
                        else b.push_back(0);
                    }


                    // save if it's a new best tour
                    Knapsack k = ttp.convertKnapsack(b);
                    pair<double, double> p = ttp.evaluate(t, k);

                    double time = p.first;
                    double value = p.second;
                    if (time < minCosts) {
                        bestTour = &t;
                    }


                    cout << t << " , ";
                    for (int j = 0; j < b.size(); ++j) cout << b[j] << ' ';
                    cout << "[" << k.size() << "]" << " -> " << fixed << time << " , " << value << '\n';


                }


            } while (next_permutation(v.begin(), v.end()) && v[0] == 0);


            return make_pair(*bestTour, Knapsack());


        }

    };
}


#endif //TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H
