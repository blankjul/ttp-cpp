#include "AbstractTest.h"
#include "Util.h"


class UtilTest : public AbstractTest {
public:
    MapPtr map = make_shared<Map>(4);
    vector<Tour> v;
    vector<Knapsack> k;
    vector<ItemPtr> items {createItem(1,1),createItem(1,1), createItem(1,1)};
    ItemPtr oneItem = createItem(1,1);

    KnapsackPtr knapsack = make_shared<Knapsack>();
    vector<ItemPtr> createItemsVector(int n) {
        vector<ItemPtr> items;
        for (int i = 0; i < n; ++i) {
            items.push_back(createItem(1,1));
        }
        return items;
    }

};



TEST_F(UtilTest, ConvertTTPOutputSetToVector) {
    TTPOutput out(5,4);
    TTPOutputSet front;
    front.add(out);
    EXPECT_THAT(convertTTPOutput(front), ElementsAre(vector<double>{5,4}));
}


TEST_F(UtilTest, GeneratorAllToursNonSymetrical) {
    for(TourPtr ptr : allTours(map, false)) v.push_back(*ptr);
    EXPECT_THAT(v, ElementsAre(
            createTour(vector<int>{0,1,2,3}),
            createTour(vector<int>{0,1,3,2}),
            createTour(vector<int>{0,2,1,3}),
            createTour(vector<int>{0,2,3,1}),
            createTour(vector<int>{0,3,1,2}),
            createTour(vector<int>{0,3,2,1})
    ));
}

TEST_F(UtilTest, GeneratorAllToursOnlySymetrical) {
    for(TourPtr ptr :  allTours(map, true)) v.push_back(*ptr);
    EXPECT_THAT(v, ElementsAre(
            createTour(vector<int>{0,1,2,3}),
            createTour(vector<int>{0,1,3,2}),
            createTour(vector<int>{0,2,1,3})
    ));
}


TEST_F(UtilTest, GeneratorAllKnapsacks) {
    vector<Knapsack> result;
    for(KnapsackPtr ptr :  allKnapsacks(items)) result.push_back(*ptr);
    EXPECT_THAT(result, UnorderedElementsAre(
           Knapsack(vector<ItemPtr>{}),
Knapsack(vector<ItemPtr>{items[0]}),
Knapsack(vector<ItemPtr>{items[1]}),
Knapsack(vector<ItemPtr>{items[2]}),
Knapsack(vector<ItemPtr>{items[0],items[1]}),
Knapsack(vector<ItemPtr>{items[0],items[2]}),
Knapsack(vector<ItemPtr>{items[1],items[2]}),
Knapsack(vector<ItemPtr>{items[0],items[1],items[2]})
    )
    );
}




TEST_F(UtilTest, GeneratorAllKnapsacksWithMaxWeight) {
    vector<Knapsack> result;
    for(KnapsackPtr ptr :  allKnapsacks(items,2)) result.push_back(*ptr);
    EXPECT_THAT(result, UnorderedElementsAre(
            Knapsack(vector<ItemPtr>{}),
            Knapsack(vector<ItemPtr>{items[0]}),
            Knapsack(vector<ItemPtr>{items[1]}),
            Knapsack(vector<ItemPtr>{items[2]}),
            Knapsack(vector<ItemPtr>{items[0],items[1]}),
            Knapsack(vector<ItemPtr>{items[0],items[2]}),
            Knapsack(vector<ItemPtr>{items[1],items[2]})
    )
    );
}

TEST_F(UtilTest, NextKnapsackPackNOItem) {
    KnapsackPtr result = nextKnapsack(knapsack,nullptr);
    EXPECT_EQ(0, result->size());
}

TEST_F(UtilTest, NextKnapsackPackItem) {
    KnapsackPtr result = nextKnapsack(knapsack,oneItem);
    EXPECT_EQ(1, result->size());
}

TEST_F(UtilTest, GeneratorAllKnapsacksWithMaxWeightLarge) {
    vector<ItemPtr> items = createItemsVector(10);
    vector<Knapsack> result;
    for(KnapsackPtr ptr :  allKnapsacks(items,5)) {
        result.push_back(*ptr);
    }
    // it is the binomial coefficient 0 out of 5 + 1 out of 5 ..... + 5 out of 5
    EXPECT_EQ(638, result.size());
}