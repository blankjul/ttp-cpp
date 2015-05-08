

#ifndef TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H

#include "solver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;


namespace TTP {

    class TTPSOExhaustiveSolver : public TTPSOSolver {

    public:


        pair<Tour,Knapsack> solve(SingleObjectiveTravellingThiefProblem &ttp) {

            MapPtr m = ttp.getMap();

            // create the start solution
            vector<int> v;
            for (int i = 0; i < m->count(); ++i) {
                v.push_back(i);
            }

            double minCosts =  numeric_limits<double>::max();
            Tour* bestTour;


            // for all the possible tsp tours
            do {

                // create a tour
                Tour t(v);


                // create the start solution
                std::vector<bool> b( ttp.sizeOfItems() , false );

                // for all possible array -> no order
                for (int i = 0; i < ttp.sizeOfItems(); ++i) {

                    // for each permutation
                    do {

                        // save if it's a new best tour
                        Knapsack k;
                        for (int j = 0; j < ttp.sizeOfItems(); ++j) {
                            if (b[j] == true) {
                                auto item = ttp.getItems()[j].first;
                                k.add(item);
                            }
                        }
                        //Knapsack k = ttp.convertKnapsack(b);


                        auto p = ttp.evaluate(t, k);

                        double costs = p;
                        if (costs < minCosts) {
                            bestTour = & t;
                        }

                        /*
                        cout << t << " , ";
                        for (size_t nIndex = 0; nIndex < b.size (); ++ nIndex)
                            cout << b [nIndex] << ' ';
                        cout << " -> " << fixed << p <<'\n';
                         */


                    } while ( next_permutation(b.begin(),b.end()));

                    b[i] = true;

                }



            } while ( next_permutation(v.begin(),v.end()) && v[0] == 0);


            return make_pair(*bestTour,Knapsack());


        }

    };
}



#endif //TRAVELLING_THIEF_PROBLEM_TTPSOExhaustiveSolver_H
