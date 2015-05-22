#include <iostream>
#include "problems/TravellingThiefProblemDeptr.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>




/*
TEST(TTPSO, Evaluate1) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsLarge();

    TravellingThiefProblemDeptr ttpso(m, 3);
    ttpso.addItems(items);


    std::vector<int> v = {0,2,1,3};
    Tour t(v);

    Knapsack k = ttpso.convertVectorToKnapsack(std::vector<int> {0, 1, 0, 1, 0, 0});


    double targetValue = ttpso.evaluateSO(t, k, 1);


    EXPECT_NEAR(-73.14, targetValue, 0.01);

}



TEST(TTPSO, Evaluate2) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsLarge();

    TravellingThiefProblemDeptr ttpso(m, 3);
    ttpso.addItems(items);



    std::vector<int> v = {0,1,3,2};
    Tour t(v);

    Knapsack k = ttpso.convertVectorToKnapsack(std::vector<int> {0, 1, 1, 0, 0, 0});


    double targetValue = ttpso.evaluateSO(t, k, 1);


    EXPECT_NEAR(50, targetValue, 0.01);

}
*/