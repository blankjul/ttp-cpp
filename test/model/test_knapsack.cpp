#include "model/knapsack.h"
#include "gtest/gtest.h"
#include "model/item.h"


using namespace TTP;


/**
 * Checks if add item does work.
 */
TEST(KnapsackTest, addItem) {
    TTP::Knapsack k;

    auto i1 = std::make_shared<Item>(2,1);
    auto i2 = std::make_shared<Item>(5,4);

    k.add(i1);
    k.add(i2);

    EXPECT_EQ(7, k.getValue());
    EXPECT_EQ(5, k.getWeight());

}


/**
 * Check if contains works correctly
 */
TEST(KnapsackTest, Contains) {
    TTP::Knapsack k;
    auto i1 = std::make_shared<Item>(5,4);
    k.add(i1);
    EXPECT_TRUE(k.contains(i1));
}


/**
 * Test if remove if not exists.
 */
TEST(KnapsackTest, RemoveNotExists) {
    TTP::Knapsack k;
    auto i1 = std::make_shared<Item>(5,4);
    k.remove(i1);
    EXPECT_EQ(0, k.getValue());
}


/**
 * Test if remove if not exists.
 */
TEST(KnapsackTest, AddIfExists) {
    TTP::Knapsack k;
    auto i1 = std::make_shared<Item>(5,4);
    k.add(i1);
    EXPECT_EQ(5, k.getValue());
    k.add(i1);
    EXPECT_EQ(5, k.getValue());
}