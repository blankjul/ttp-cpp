

#ifndef TRAVELLING_THIEF_PROBLEM_KNP_COMBO_H
#define TRAVELLING_THIEF_PROBLEM_KNP_COMBO_H


#include "solver.h"


using namespace std;

namespace ttp {

    class KNPComboSolver : public KnapsackSolver {

    public:

        Knapsack solve(KnapsackProblem & knp);

    };
}






#endif //TRAVELLING_THIEF_PROBLEM_KNP_COMBO_H
