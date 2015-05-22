#ifndef TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H
#define TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H

#include "solver.h"
#include "problems/TTP.h"
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>


using namespace std;

namespace ttp {

    class TTPMOExhaustiveSolver : public TTPMOSolver {

    public:


        pair<Tour, Knapsack> solve(TravellingThiefProblemDeptr &ttp) {

            set<TTPOutput> front;

            MapPtr m = ttp.getMap();

            // create the start solution
            vector<int> v;
            for (int i = 0; i < m->size(); ++i) {
                v.push_back(i);
            }

            double minCosts = numeric_limits<double>::max();
            std::vector<int> bestTour;
            std::vector<int> bestPickingPlan;


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
                    Knapsack k = ttp.convertVectorToKnapsack(b);
                    TTPOutput p = ttp.evaluateMO(t, k);

                    double time = p.getTime();
                    double value = p.getValue();

                    if (time < minCosts) {
                        bestTour = std::vector<int> (v);
                        bestPickingPlan = b;
                        minCosts = time;
                    }


                    // check if this solution belongs to the pareto front
                    bool isDominated = false;
                    vector<TTPOutput> isDominating;
                    for (TTPOutput entry : front) {
                        if (p.isDominating(entry)) isDominating.push_back(entry);
                        if (p.isDominatedBy(entry)) isDominated = true;
                    }

                    if (!isDominated) {
                        front.insert(p);
                        for (auto entry : isDominating) {
                            front.erase(entry);
                        }
                    }


                }


            } while (next_permutation(v.begin(), v.end()) && v[0] == 0);


            Tour t(bestTour);
            Knapsack k = ttp.convertVectorToKnapsack(bestPickingPlan);


            cout << "result:\n";
            for (TTPOutput entry : front) {
                cout << entry << endl;
            }
            cout << "end\n";


            return make_pair(t,k);


        }

    };
}





#endif //TRAVELLING_THIEF_PROBLEM_TTPMOExhaustiveSolver_H
