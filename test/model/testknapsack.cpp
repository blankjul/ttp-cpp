#include <sys/types.h>
#include "model/knapsack.h"
#include "gtest/gtest.h"



TEST(KnapsackTest, addItem) {
    TTP::Knapsack k(5);
    k.add( TTP::Item(5,4));

    EXPECT_TRUE(k.add(TTP::Item(2,1)));
    EXPECT_EQ(7, k.getValue());
    EXPECT_EQ(5, k.getWeight());

}

