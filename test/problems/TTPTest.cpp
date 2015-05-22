#include "AbstractTest.h"




// the mocking class because TTP is normal abstract
class MockTTP : public TTP<double,double> {
public:
    MockTTP(ThiefMapPtr map, int maxWeight) : TTP(map,maxWeight){};
    double evaluate(double &d) {
        return d;
    }

};


class TTPTest : public AbstractTest {
public:

    MockTTP ttp = getTTP();

    MockTTP getTTP() {
        ThiefMapPtr tm = make_shared<ThiefMap>(exampleMap());
        auto items = exampleItemsSmall();
        tm->insert(items.begin(), items.end());
        MockTTP ttp(tm, 3);
        return ttp;
    }
};



TEST_F(TTPTest, CalculateTimeForOneTourNoItemPicked) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,2,3}, vector<int> {0,0,0,0,0,0});
    EXPECT_NEAR(20, ttp.calcTime(input), 0.01);
}


TEST_F(TTPTest, CalculateTimeForTourWithOneItem) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,3,2}, vector<int> {0,1,0,0,0,0});
    EXPECT_NEAR(23.57, ttp.calcTime(input), 0.01);
}


TEST_F(TTPTest, CalculateTimeForTourWithTwoItems) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,1,3,2}, vector<int> {0,1,1,0,0,0});
    EXPECT_NEAR(30, ttp.calcTime(input), 0.01);
}

TEST_F(TTPTest, CalculateTimeAndPickingTable) {
    vector<pair<ItemPtr,double>> pickingTable;
    ThiefMapPtr ptr = ttp.getMap();
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,2,1,3}, vector<int> {0,1,0,1,0,0});
    ttp.calcTime(input, &pickingTable);

    // dirty but round for is equal and elementsare!
    pickingTable[1].second = round(pickingTable[1].second);
    pair<ItemPtr,double> i1 = make_pair(ptr->getItemsAtCity(2)[1], 6);
    pair<ItemPtr,double> i2 = make_pair(ptr->getItemsAtCity(1)[0], 13);

    EXPECT_THAT(pickingTable, ElementsAre(i1,i2));

}


TEST_F(TTPTest, CalculateTimeForNotValidTour) {
    TTPInput input = TTPInput::create(ttp.getMap(), vector<int> {0,3,3,2}, vector<int> {0,1,1,0,0,0});
    ASSERT_THROW(ttp.calcTime(input), runtime_error);
}





