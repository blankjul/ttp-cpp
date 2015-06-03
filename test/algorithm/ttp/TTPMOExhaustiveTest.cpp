#include "algorithm/AlgorithmTest.h"



class TTPMOExhaustiveTest : public AlgorithmTest {
public:

    mo::Exhaustive algorithm;
};


TEST_F(TTPMOExhaustiveTest, ExhaustiveEvaluateExampleRouteAndFindBest) {
    MOTTP ttp = getMOTTP();
    algorithm.solve(ttp);
}

