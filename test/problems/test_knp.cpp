#include <iostream>
#include "problems/knp.h"
#include "gtest/gtest.h"
#include <memory>

using namespace std;
using namespace TTP;


TEST(KNP, ConvertKnapsack) {

    vector<ItemPtr> items;

    auto i1 = std::make_shared<Item>(7,2);
    auto i2 = std::make_shared<Item>(7,2);

    items.push_back(i1);
    items.push_back(i2);

    KnapsackProblem knp(items, 10);

    auto result = knp.convertKnapsack(vector<bool> {true,false});

    EXPECT_TRUE(result.contains(i1));
    EXPECT_FALSE(result.contains(i2));

}



