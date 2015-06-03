#include "ttpmo/jmetal/TTPCrossover.h"
#include "../../AbstractTest.h"


class CrossOverTest : public AbstractTest {
public:
    JTour t1 = JTour(vector<int>{5,7,1,3,6,4,2});
    JTour t2 = JTour(vector<int>{4,6,2,7,3,1,5});
};


TEST_F(CrossOverTest, Cross) {
    auto result = TTPCrossover::crossJTour(2, &t1, &t2, false);
    ASSERT_THAT(result->v, ElementsAre(4,6,2,3,7,5,1));
}

TEST_F(CrossOverTest, Cross2) {
    auto result = TTPCrossover::crossJTour(2, &t2, &t1, false);
    ASSERT_THAT(result->v, ElementsAre(5,7,1,6,3,2,4));
}

TEST_F(CrossOverTest, StepTheFirstAndItWorks) {
    auto result = TTPCrossover::crossJTour(2, &t1, &t2, true);
    ASSERT_THAT(result->v, ElementsAre(5,6,2,3,7,4,1));
}