#include <iostream>
#include "problems/ttp_so.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include <problems/ttp_mo.h>


using namespace TTP;



TEST(TTPMO, TestCase) {

    Map m = Map(4);


    // set the weights
    m.set(0,1,5);
    m.set(0,2,6);
    m.set(0,3,6);
    m.set(1,2,5);
    m.set(1,3,6);
    m.set(2,3,4);

    MultiObjectiveTravellingThiefProblem ttpmo(m, 3);
    ttpmo.setDroppingRate(0.9);


    ttpmo.add(2, std::make_shared<Item>(10,3));
    ttpmo.add(2, std::make_shared<Item>(4,1));
    ttpmo.add(2, std::make_shared<Item>(4,1));

    ttpmo.add(1, std::make_shared<Item>(2,2));
    ttpmo.add(1, std::make_shared<Item>(3,3));

    ttpmo.add(3, std::make_shared<Item>(2,2));


    std::vector<int> v = {0,2,1,3};
    Tour t(v);

    Knapsack k = ttpmo.convertKnapsack(std::vector<bool> {false,true,false,true,false,false});


    auto p = ttpmo.evaluate(t, k);


    EXPECT_NEAR(133.14, p.first, 0.01);
    EXPECT_NEAR(1.694, p.second, 0.1);

}
