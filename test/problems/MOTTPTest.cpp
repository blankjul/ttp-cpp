#include "AbstractTest.h"






class MOTTPTest : public AbstractTest {
public:

    MOTTP ttp = getTTP();

    MOTTP getTTP() {
        ThiefMapPtr tm = make_shared<ThiefMap>(exampleMap());
        auto items = exampleItemsSmall();
        tm->insert(items.begin(), items.end());

        MOTTP ttp(tm, 3);
        return ttp;
    }
};



TEST_F(MOTTPTest, CalculateTimeForOneTourNoItemPicked) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,2,3}, vector<int> {0,0,0,0,0,0});
    EXPECT_EQ(TTPOutput(0,20), ttp.evaluate(input));
}


TEST_F(MOTTPTest, CalculateTimeForTourWithOneItem) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,3,2}, vector<int> {0,1,0,0,0,0});
    TTPOutput output = ttp.evaluate(input);
    EXPECT_NEAR(23.57, output.getTime(), 0.01);
    EXPECT_NEAR(3.65, output.getValue(), 0.01);
}


TEST_F(MOTTPTest, CalculateTimeForTourWithTwoItems) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,3,2}, vector<int> {0,1,1,0,0,0});
    TTPOutput output = ttp.evaluate(input);
    EXPECT_NEAR(30, output.getTime(), 0.01);
    EXPECT_NEAR(6.83, output.getValue(), 0.01);
}

