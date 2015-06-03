#include "algorithm/AlgorithmTest.h"



class TSPExhaustiveTest : public AlgorithmTest {
public:
    TSPExhaustive algorithm;
    TSPLinKernighan lkh;
};


TEST_F(TSPExhaustiveTest, ExhaustiveEvaluateExampleRouteAndFindBest) {
    EXPECT_EQ(createTour(vector<int> {0,1,2,3}), algorithm.solve(tsp));
}


TEST_F(TSPExhaustiveTest, LKHEvaluateExampleRouteAndFindBest) {
    EXPECT_EQ(createTour(vector<int> {0,3,2,1}), lkh.solve(tsp));
}