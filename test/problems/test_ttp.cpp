#include <iostream>
#include "problems/ttp.h"
#include "gtest/gtest.h"
#include <memory>


using namespace TTP;



TEST(ThiefMap, Evaluate) {

    Map tm = Map(4);


    // set the weights
    tm.set(0,1,5);
    tm.set(0,2,6);
    tm.set(0,3,6);
    tm.set(1,2,5);
    tm.set(1,3,6);
    tm.set(2,3,4);

    TravellingThiefProblem ttp(tm, 20);


    ttp.add(1, std::make_shared<Item>(2,2));
    ttp.add(1, std::make_shared<Item>(3,3));
    ttp.add(2, std::make_shared<Item>(10,3));
    ttp.add(2, std::make_shared<Item>(4,1));
    ttp.add(2, std::make_shared<Item>(4,1));
    ttp.add(3, std::make_shared<Item>(2,2));


    std::vector<int> v = {0,2,1,3};
    Tour t(v);


    Knapsack k;
    k.add(ttp.getItems(1)[0]);
    k.add(ttp.getItems(2)[1]);



    //auto p = ttp.evaluate(t, k);


    //EXPECT_NEAR(133.143, p.first, 0.1);
    //EXPECT_NEAR(1.694, p.second, 0.1);

}
