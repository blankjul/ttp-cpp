#include "model/tour.h"
#include "gtest/gtest.h"


TEST(TourTest, Index) {
    std::vector<int> v = {0,2,1,3};
    TTP::Tour m(v);
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(3, v[3]);
}

