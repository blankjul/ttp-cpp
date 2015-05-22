#include "AbstractTest.h"

using namespace ttp;

class KnapsackTest : public AbstractTest {
public:
    Knapsack k;

};


TEST_F(KnapsackTest, AddItemAndCheckWeightAndValue) {
    k.add(createItem(2,1));
    k.add(createItem(5,4));

    EXPECT_EQ(7, k.getValue());
    EXPECT_EQ(5, k.getWeight());
}


TEST_F(KnapsackTest, AddItemAndCheckWetherItsContained) {
    ItemPtr i = createItem(5,4);
    k.add(i);
    EXPECT_TRUE(k.contains(i));
}



TEST_F(KnapsackTest, RemoveItemAndItDoesNotExist) {
    auto i = std::make_shared<Item>(5,4);
    k.remove(i);
    EXPECT_EQ(0, k.getValue());
}



TEST_F(KnapsackTest, AddTwoTimesButNothingChanges) {
    auto i = std::make_shared<Item>(5,4);
    k.add(i);
    EXPECT_EQ(5, k.getValue());
    k.add(i);
    EXPECT_EQ(5, k.getValue());
}

TEST_F(KnapsackTest, PickItemsEmptyKnapsack) {
    vector<bool> b(3,false);
    vector<ItemPtr> items (3,createItem(1,1));
    k.fill(items.begin(), items.end(), b.begin(), b.end());
    EXPECT_EQ(0, k.size());
}

TEST_F(KnapsackTest, PickItemsPickOne) {
    vector<bool> b{true,false,false};
    vector<ItemPtr> items (3,createItem(1,1));
    k.fill(items.begin(), items.end(), b.begin(), b.end());
    EXPECT_EQ(1, k.size());
}

TEST_F(KnapsackTest, PickItemsDifferentLength) {
    vector<bool> b{true, false};
    vector<ItemPtr> items(3, createItem(1, 1));
    ASSERT_THROW(k.fill(items.begin(), items.end(), b.begin(), b.end()), std::runtime_error);
}

TEST_F(KnapsackTest, PickItemsPickOneWithIntVectorAsInput) {
    vector<int> b{1,0,0};
    vector<ItemPtr> items (3,createItem(1,1));
    k.fill(items.begin(), items.end(), b.begin(), b.end());
    EXPECT_EQ(1, k.size());
}

