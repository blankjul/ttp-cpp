#include "AbstractTest.h"


using namespace ttp;
using namespace testing;

class MapTest : public AbstractTest {
public:
    Map m = Map(5);
};


TEST_F(MapTest, EmptyMapUnequalIndexIsInfinity) {
    EXPECT_EQ(std::numeric_limits<double>::max(), m.get(0,1));
}


TEST_F(MapTest, EmptyMapEqualIndexIsZero) {
    EXPECT_EQ(0, m.get(2,2));
}

TEST_F(MapTest, IndexOperator) {
    EXPECT_EQ(0, m[2][2]);
}


TEST_F(MapTest, SetValueWithEqualIndexNoChange) {
    m.set(1,1,6);
    EXPECT_EQ(0, m[1][1]);
}

TEST_F(MapTest, SetValueAndChange) {
    m.set(4,3,6);
    EXPECT_EQ(6, m[4][3]);
}


TEST_F(MapTest, GetValueOutOfBoundsException) {
    ASSERT_THROW(m.get(8,8), std::runtime_error);
}

TEST_F(MapTest, SetValueOutOfBoundsReturnFalse) {
    EXPECT_FALSE(m.set(5,5,6));
}

TEST_F(MapTest, SetValueWithIndex) {
    m[0][1] = 5;
    EXPECT_EQ(5, m.get(0,1));
}


TEST_F(MapTest, SetValuesSymetrical) {
    m.set(0,1,6);
    EXPECT_EQ(6, m.get(0,1));
    EXPECT_EQ(6, m.get(1,0));
}



