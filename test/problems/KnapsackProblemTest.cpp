#include "AbstractTest.h"



class KnapsackProblemTest : public AbstractTest {
};


TEST_F(KnapsackProblemTest, ConvertKnapsack) {

    vector<ItemPtr> items;

    auto i1 = std::make_shared<Item>(7,2);
    auto i2 = std::make_shared<Item>(7,2);

    items.push_back(i1);
    items.push_back(i2);

    KnapsackProblem knp(items, 10);

    auto result = knp.convertVectorToKnapsack(vector<int> {1,0});

    EXPECT_TRUE(result.contains(i1));
    EXPECT_FALSE(result.contains(i2));

}



TEST_F(KnapsackProblemTest, Evaluate1) {
    auto items = exampleItemsLarge();
    KnapsackProblem knp(items.begin(), items.end(), 3);
    Knapsack k;
    k.add(items[0].second);
    EXPECT_EQ(100, knp.evaluate(k));
}
