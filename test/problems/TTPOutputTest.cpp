
#include "AbstractTest.h"



class TTPOutputTest : public AbstractTest {
};


TEST_F(TTPOutputTest, isDominatedTrue) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(10,4);
    EXPECT_TRUE(sol2.isDominatedBy(sol1));
}

TEST_F(TTPOutputTest, isDominatedFalseCauseEqual) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(12,4);
    EXPECT_FALSE(sol2.isDominatedBy(sol1));
}

TEST_F(TTPOutputTest, isDominatedFalseCauseWorse) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(12,3);
    EXPECT_FALSE(sol2.isDominatedBy(sol1));
}

TEST_F(TTPOutputTest, isEqualTrue) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(12,4);
    EXPECT_TRUE(sol1 == sol2);
}

TEST_F(TTPOutputTest, isEqualFalse) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(12,5);
    EXPECT_FALSE(sol1 == sol2);
}

TEST_F(TTPOutputTest, isIndifferent) {
    // time, value
    TTPOutput sol1(12,4);
    TTPOutput sol2(11,3);
    EXPECT_TRUE(sol1.isIndifferentTo(sol2));
    EXPECT_TRUE(sol2.isIndifferentTo(sol1));
}




