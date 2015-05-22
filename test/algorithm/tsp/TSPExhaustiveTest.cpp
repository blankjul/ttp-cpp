#include "algorithm/AlgorithmTest.h"



class TSPTest : public AlgorithmTest {
public:
    TSPExhaustive algorithm;
};


TEST_F(TSPTest, ExhaustiveEvaluateExampleRouteAndFindBest) {
    EXPECT_EQ(createTour(vector<int> {0,3,2,1}), algorithm.solve(tsp));
}
