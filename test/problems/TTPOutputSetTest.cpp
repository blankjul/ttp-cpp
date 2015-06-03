
#include "AbstractTest.h"





class TTPOutputSetTest : public AbstractTest {
public:
    TTPOutputSet front;

    TTPOutputSet preFront = getFront();

    TTPOutputSet getFront() {
        TTPOutputSet front;
        front.add(TTPOutput(2,2));
        front.add(TTPOutput(4,4));
        front.add(TTPOutput(6,6));
        return front;
    }

    TTPOutput createOutput(double p, double v) {
        return TTPOutput(p,v);
    }
};


TEST_F(TTPOutputSetTest, addOutputThatIsNotDominated) {
    front.add(TTPOutput(3,4));
}


TEST_F(TTPOutputSetTest, isNonDominatedTrueBest) {
    TTPOutput o = createOutput(0,0);
    EXPECT_TRUE(preFront.isNonDominated(o));
}

TEST_F(TTPOutputSetTest, isNonDominatedTrueIndifferent) {
    TTPOutput o = createOutput(5,3);
    EXPECT_TRUE(preFront.isNonDominated(o));
}

TEST_F(TTPOutputSetTest, isNonDominatedFalse) {
    TTPOutput o = createOutput(2,3);
    EXPECT_FALSE(preFront.isNonDominated(o));
}


TEST_F(TTPOutputSetTest, isDominatingTrue) {
    TTPOutput o = createOutput(10,2);
    EXPECT_EQ(3, preFront.isDominating(o).size());
}