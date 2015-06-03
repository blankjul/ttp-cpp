#include "AbstractTest.h"


class SOTTPTest : public AbstractTest {
public:

    SOTTP ttp = getTTP();

    SOTTP getTTP() {
        ThiefMapPtr tm = make_shared<ThiefMap>(exampleMap());
        auto items = exampleItemsLarge();
        tm->insert(items.begin(), items.end());
        SOTTP ttp(tm, 3);
        return ttp;
    }
};



TEST_F(SOTTPTest, CalculateTargetValue) {
    SOTTP ttp = getTTP();
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int>{0,2,1,3}, vector<int>{0,1,0,1,0,0});
    EXPECT_NEAR(-73.14, ttp.evaluate(input), 0.01);
}

TEST_F(SOTTPTest, CalculateTargetValueWeightToHigh) {
    SOTTP ttp = getTTP();
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int>{0,2,1,3}, vector<int>{0,1,0,1,1,0});
    EXPECT_EQ(- numeric_limits<double>::infinity(), ttp.evaluate(input));
}
