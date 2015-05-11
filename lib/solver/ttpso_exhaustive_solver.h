

#ifndef TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H

#include "solver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;


namespace ttp {

    class TTPSOExhaustiveSolver : public TTPSOSolver {

    public:


        pair<Tour,Knapsack> solve(TravellingThiefProblem &ttp) {

            MapPtr m = ttp.getMap();

            // create the start solution
            vector<int> v;
            for (int i = 0; i < m->count(); ++i) {
                v.push_back(i);
            }

            double bestTarget = numeric_limits<double>::min();
            std::vector<int> bestTour;


            // for all the possible tsp tours
            do {


                // create the start solution

                for (int i = 0; i < pow(2, ttp.sizeOfItems()); i++) {

                    std::vector<int> b;
                    for (int j = 0; j < ttp.sizeOfItems(); j++) {
                        bool tmp = i & (1 << j);
                        if (tmp) b.push_back(1);
                        else b.push_back(0);
                    }


                    // save if it's a new best tour
                    Tour t(v);
                    Knapsack k = ttp.convertKnapsack(b);
                    double targetValue = ttp.evaluateSO(t, k);

                    if (targetValue > bestTarget) {
                        bestTour = std::vector<int> (v);
                    }

                    /*
                    cout << t << " , ";
                    for (int j = 0; j < b.size(); ++j) cout << b[j] << ' ';
                    cout << targetValue << '\n';

                    */
                }


            } while (next_permutation(v.begin(), v.end()) && v[0] == 0);

            Tour t(bestTour);
            return make_pair(t,Knapsack());


        }

    };
}



#endif //TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H
