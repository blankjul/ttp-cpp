#include <iostream>
#include "problems/ttp.h"
#include "gtest/gtest.h"
#include "examples/test_examples.h"



using namespace ttp;




TEST(TTPMO, TestCase1) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblem ttpmo(m, 3);
    ttpmo.addItems(items);


    std::vector<int> v = {0,2,1,3};
    Tour t(v);

    Knapsack k = ttpmo.convertKnapsack(std::vector<int> {0,1,0,1,0,0});

    auto p = ttpmo.evaluateMO(t, k);

    EXPECT_NEAR(133.14, p.first, 0.01);
    EXPECT_NEAR(1.694, p.second, 0.1);



}


TEST(TTPMO, TestCaseG3) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblem ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,2,3};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertKnapsack(std::vector<int> {0,0,0,0,0,0});


    auto p2 = ttpmo.evaluateMO(t2, k2);

    EXPECT_NEAR(20, p2.first, 0.01);
    EXPECT_NEAR(0, p2.second, 0.01);

}


TEST(TTPMO, TestCaseG2) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblem ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,3,2};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertKnapsack(std::vector<int> {0,1,0,0,0,0});


    auto p2 = ttpmo.evaluateMO(t2, k2);


    EXPECT_NEAR(23.57, p2.first, 0.01);
    EXPECT_NEAR(4, p2.second, 1);

}



TEST(TTPMO, TestCaseG1) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblem ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,3,2};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertKnapsack(std::vector<int> {0,1,1,0,0,0});


    auto p2 = ttpmo.evaluateMO(t2, k2);


    EXPECT_NEAR(30, p2.first, 0.01);
    EXPECT_NEAR(7.2, p2.second, 1);
}



TEST(TTPMO, TestCaseNoNegativeTime) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    TravellingThiefProblem ttpmo(m, 3);
    ttpmo.addItems(items);

    std::vector<int> v2 = {0,1,2,3};
    Tour t2(v2);

    Knapsack k2 = ttpmo.convertKnapsack(std::vector<int> {0,1,0,0,1,0});


    auto p2 = ttpmo.evaluateMO(t2, k2);

    EXPECT_TRUE(p2.first > 0);

}

