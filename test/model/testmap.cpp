#include "model/map.h"
#include "model/tour.h"
#include "gtest/gtest.h"


TEST(MapTest, Initialize) {
    TTP::Map m(2);
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(1,1));
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(2,2));
}


TEST(MapTest, Set) {
    TTP::Map m(2);

    // set value in index
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(1,1));
    m.set(1,1,6);
    EXPECT_EQ(6, m.get(1,1));

    // set value out of bounds
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(2,2));
    m.set(2,2,6);
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(2,2));

}

TEST(MapTest, Symetrical) {
    TTP::Map m(2);

    m.set(0,1,6);
    EXPECT_EQ(6, m.get(0,1));
    EXPECT_EQ(6, m.get(1,0));

}

TEST(TourTest, Costs) {
    std::vector<int> v = {0,1,3,2};
    TTP::Tour t(v);

    TTP::Map m(4);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(2,3,4);
    m.set(1,3,5);

    EXPECT_EQ(14, m.getCosts(t));

}


