#include "model/tour.h"
#include "gtest/gtest.h"


/**
 * Check wether the tour is initialized correctly
 */
TEST(TourTest, Initialize) {
    std::vector<int> v = {0,2,1,3};
    ttp::Tour t(v);
    EXPECT_EQ(0, t[0]);
    EXPECT_EQ(3, t[3]);

}


/**
 * Check if call by reference is working.
 */
TEST(TourTest, CallByValue) {
    std::vector<int> v = {0,2,1,3};
    ttp::Tour t(v);

    // set the value to 2
    v[0] = 2;

    // but stays the same at the tour
    EXPECT_EQ(0, t[0]);

}


/**
 * Check if the symmetrical tour is correct.
 */
TEST(TourTest, GetSymmetrical) {
    std::vector<int> v = {0,2,1,3};
    ttp::Tour t(v);

    ttp::Tour sym = t.getSymmetrical();

    EXPECT_EQ(0, sym[0]);
    EXPECT_EQ(3, sym[1]);
    EXPECT_EQ(1, sym[2]);
    EXPECT_EQ(2, sym[3]);


}

