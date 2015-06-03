#include "AbstractTest.h"



class TourTest : public AbstractTest {
};



TEST_F(TourTest, InitializeTourAndOrderIsCorrect) {
    Tour t = createTour(vector<int> {0,2,1,3});
    EXPECT_THAT(t.getVector(), ElementsAre(0,2,1,3));
}



TEST_F(TourTest, TestCallByValueCallingFunction) {
    std::vector<int> v = {0,2,1,3};
    ttp::Tour t(v);
    v[0] = 2;

    EXPECT_THAT(t.getVector(), ElementsAre(0,2,1,3));
    EXPECT_THAT(v, ElementsAre(2,2,1,3));
}



TEST_F(TourTest, GetSymmetrical) {
    Tour t = createTour(vector<int> {0,2,1,3});
    EXPECT_THAT(t.getSymmetrical().getVector(), ElementsAre(0,3,1,2));
}

TEST_F(TourTest, IsValidTrue) {
    Tour t = createTour(vector<int> {0,1,2,3});
    EXPECT_TRUE(t.isValid());
}

TEST_F(TourTest, IsValidFalseCauseSameElementTwice) {
    Tour t = createTour(vector<int> {0,2,2,3});
    EXPECT_FALSE(t.isValid());
}

TEST_F(TourTest, IsValidFalseCauseWrongStartIndex) {
    Tour t = createTour(vector<int> {1,2,3,4});
    EXPECT_FALSE(t.isValid());
}


TEST_F(TourTest, SameHashValue) {
    unordered_set<Tour> s;
    s.insert(createTour(vector<int> {0,1,2,3}));
    s.insert(createTour(vector<int> {0,1,2,3}));
    EXPECT_EQ(1, s.size());
}

TEST_F(TourTest, DifferentHashValues) {
    unordered_set<Tour> s;
    s.insert(createTour(vector<int> {0,1,2,3}));
    s.insert(createTour(vector<int> {1,0,2,3}));
    EXPECT_EQ(2, s.size());
}