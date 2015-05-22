#include "AbstractTest.h"




class ThiefMapTest : public AbstractTest {
public:
    ThiefMap tm = ThiefMap(5);

};



TEST_F(ThiefMapTest, ConstructObjectFromMap) {
    MapPtr m = make_shared<Map>(5);
    m->set(0,1,5);
    ThiefMap tm(m);
    EXPECT_EQ(tm[0][1], (*m)[0][1]);
}

TEST_F(ThiefMapTest, AddItemToFirstCity) {
    ASSERT_THROW(tm.insert(0, createItem(3, 3)), std::runtime_error);
}

TEST_F(ThiefMapTest, AddItemToCityOutOfBounds) {
    ASSERT_THROW(tm.insert(6, createItem(3, 3)), std::runtime_error);
}


TEST_F(ThiefMapTest, AddItemToACitySuccessfull) {
    tm.insert(1, createItem(3, 3));
    EXPECT_EQ(1, tm.getItemsAtCity(1).size());
}

TEST_F(ThiefMapTest, AddMultipleItemsToMultipleCitiesWithIterators) {
    vector<pair<int,ItemPtr>> items;
    for (int i = 0; i < 10; ++i) {
        items.push_back(make_pair<int,ItemPtr>(1, createItem(3, 3)));
    }
    tm.insert(items.begin(), items.end());
    EXPECT_EQ(10, tm.getItemsAtCity(1).size());
}

TEST_F(ThiefMapTest, InsertAndIterateOverManyItems) {
    vector<pair<int,ItemPtr>> items;
    for (int i = 0; i < 8; ++i) {
        items.push_back(make_pair<int,ItemPtr>((i / 2) + 1, createItem(3, 3)));
    }
    tm.insert(items.begin(), items.end());

    int counter = 0;
    for(ThiefMap::iterator it = tm.begin(); it != tm.end(); ++it) {
            EXPECT_EQ(items[counter++].second, *it);
    }
}

TEST_F(ThiefMapTest, CalculateTheTimeCorrectSpeed) {
    tm[0][1] = 10;
    EXPECT_EQ(50, tm.calcTime(0,1,0.2));
}

TEST_F(ThiefMapTest, CalculateTheTimeNoLinkBetweenCities) {
    EXPECT_EQ(numeric_limits<double>::infinity(), tm.calcTime(0,1,0.2));
}

TEST_F(ThiefMapTest, CalculateTheTimeOutOfBoundsException) {
    ASSERT_THROW(tm.calcTime(10,1,0.2), std::runtime_error);
}


TEST_F(ThiefMapTest, GetTheCityOfAnItem) {
    ItemPtr i = createItem(3, 3);
    tm.insert(1, i);
    EXPECT_EQ(1, tm.getCityOfItem(i));
}


TEST_F(ThiefMapTest, GetTheCityOfAnItemDoesNotExist) {
    ItemPtr i = createItem(3, 3);
    EXPECT_EQ(-1, tm.getCityOfItem(i));
}
