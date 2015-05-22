#include <iostream>
#include "problems/TravellingThiefProblemDeptr.h"
#include "gtest/gtest.h"




/*
TEST(TTPMO, TestCase1) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.addItems(items);


    std::vector<int> v = {0,2,1,3};
    Tour t(v);

    Knapsack k = ttpmo.convertVectorToKnapsack(std::vector<int> {0, 1, 0, 1, 0, 0});

    auto p = ttpmo.evaluateMO(t, k);

    EXPECT_NEAR(133.14, p.getTime(), 0.01);
    EXPECT_NEAR(1.694, p.getValue(), 0.1);



}


TEST(TTPMO, TestCaseG3) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,2,3};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertVectorToKnapsack(std::vector<int> {0, 0, 0, 0, 0, 0});


    auto p2 = ttpmo.evaluateMO(t2, k2);

    EXPECT_NEAR(20, p2.getTime(), 0.01);
    EXPECT_NEAR(0, p2.getValue(), 0.01);

}


TEST(TTPMO, TestCaseG2) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,3,2};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertVectorToKnapsack(std::vector<int> {0, 1, 0, 0, 0, 0});


    auto p2 = ttpmo.evaluateMO(t2, k2);


    EXPECT_NEAR(23.57, p2.getTime(), 0.01);
    EXPECT_NEAR(4, p2.getValue(), 1);

}



TEST(TTPMO, TestCaseG1) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,3,2};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertVectorToKnapsack(std::vector<int> {0, 1, 1, 0, 0, 0});


    auto p2 = ttpmo.evaluateMO(t2, k2);


    EXPECT_NEAR(30, p2.getTime(), 0.01);
    EXPECT_NEAR(7.2, p2.getValue(), 1);
}



TEST(TTPMO, TestCaseNoNegativeTime) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,2,3};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertVectorToKnapsack(std::vector<int> {0, 1, 0, 0, 1, 0});


    auto p2 = ttpmo.evaluateMO(t2, k2);

    EXPECT_TRUE(p2.getTime() > 0);

}
*/
