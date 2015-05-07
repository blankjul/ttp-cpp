#include <iostream>
#include "problems/ttp_so.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>


using namespace TTP;



TEST(TTPSO, Evaluate1) {

    Map m = Map(4);


    // set the weights
    m.set(0,1,5);
    m.set(0,2,6);
    m.set(0,3,6);
    m.set(1,2,5);
    m.set(1,3,6);
    m.set(2,3,4);

    SingleObjectiveTravellingThiefProblem ttpso(m, 3);
    ttpso.setRentingRate(1);


    ttpso.add(2, std::make_shared<Item>(100,3));
    ttpso.add(2, std::make_shared<Item>(40,1));
    ttpso.add(2, std::make_shared<Item>(40,1));

    ttpso.add(1, std::make_shared<Item>(20,2));
    ttpso.add(1, std::make_shared<Item>(30,3));

    ttpso.add(3, std::make_shared<Item>(20,2));


    std::vector<int> v = {0,2,1,3};
    Tour t(v);

    Knapsack k = ttpso.convertKnapsack(std::vector<bool> {false,true,false,true,false,false});


    double targetValue = ttpso.evaluate(t, k);


    EXPECT_NEAR(-73.14, targetValue, 0.01);

}



TEST(TTPSO, Evaluate2) {

    Map m = Map(4);


    // set the weights
    m.set(0,1,5);
    m.set(0,2,6);
    m.set(0,3,6);
    m.set(1,2,5);
    m.set(1,3,6);
    m.set(2,3,4);

    SingleObjectiveTravellingThiefProblem ttpso(m, 3);
    ttpso.setRentingRate(1);


    ttpso.add(2, std::make_shared<Item>(100,3));
    ttpso.add(2, std::make_shared<Item>(40,1));
    ttpso.add(2, std::make_shared<Item>(40,1));

    ttpso.add(1, std::make_shared<Item>(20,2));
    ttpso.add(1, std::make_shared<Item>(30,3));

    ttpso.add(3, std::make_shared<Item>(20,2));


    std::vector<int> v = {0,1,3,2};
    Tour t(v);

    Knapsack k = ttpso.convertKnapsack(std::vector<bool> {false,true,true,false,false,false});


    double targetValue = ttpso.evaluate(t, k);


    EXPECT_NEAR(50, targetValue, 0.01);

}
