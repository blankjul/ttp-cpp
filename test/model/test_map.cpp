#include "model/map.h"
#include "model/tour.h"
#include "gtest/gtest.h"


TEST(MapTest, Initialize) {
    TTP::Map m(2);
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(0,1));
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(2,2));
}


TEST(MapTest, Set) {
    TTP::Map m(2);

    // set value in index
    EXPECT_EQ(0, m.get(1,1));
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



