#include <iostream>
#include "problems/tsp.h"
#include "gtest/gtest.h"
#include <memory>

using namespace std;
using namespace TTP;


TEST(TSP, Evaluate1) {
    std::vector<int> v = {0,1,3,2};
    TTP::Tour t(v);

    TTP::Map m(4);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(2,3,4);
    m.set(1,3,5);

    MapPtr mPtr = std::make_shared<Map>(m);
    TTP::TravellingSalesmanProblem tsp(mPtr);

    EXPECT_EQ(14, tsp.evaluate(t));

}



TEST(TSP, Evaluate2) {

    Map m = Map(4);

    // set the weights
    m.set(0,1,5);
    m.set(0,2,6);
    m.set(0,3,6);
    m.set(1,2,5);
    m.set(1,3,6);
    m.set(2,3,4);


    auto mPtr = make_shared<Map>(m);
    TTP::TravellingSalesmanProblem tsp(mPtr);


    std::vector<int> v = {0,2,1,3};
    Tour t(v);
    double distance  = tsp.evaluate(t);

    EXPECT_EQ(23, distance);


}


TEST(TSP, Evaluate3) {

    Map m = Map(4);


    // set the weights
    m.set(0,1,5);
    m.set(0,2,6);
    m.set(0,3,6);
    m.set(1,2,5);
    m.set(1,3,6);
    m.set(2,3,4);

    std::vector<int> v = {0,1,2,3};
    Tour t(v);

    auto mPtr = make_shared<Map>(m);
    TTP::TravellingSalesmanProblem tsp(mPtr);

    double distance  = tsp.evaluate(t);

    EXPECT_EQ(20, distance);

}