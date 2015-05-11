#include <iostream>
#include "problems/tsp.h"
#include "gtest/gtest.h"
#include <memory>
#include "examples/test_examples.h"


using namespace std;
using namespace ttp;


TEST(TSP, Evaluate1) {
    std::vector<int> v = {0,1,3,2};
    Tour t(v);

    Map m(4);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(2,3,4);
    m.set(1,3,5);

    MapPtr mPtr = std::make_shared<Map>(m);
    TravellingSalesmanProblem tsp(mPtr);

    EXPECT_EQ(14, tsp.evaluate(t));

}



TEST(TSP, Evaluate2) {

    MapPtr mPtr = exampleMap();

    TravellingSalesmanProblem tsp(mPtr);


    std::vector<int> v = {0,2,1,3};
    Tour t(v);
    double distance  = tsp.evaluate(t);

    EXPECT_EQ(23, distance);


}


TEST(TSP, Evaluate3) {

    MapPtr mPtr = exampleMap();

    std::vector<int> v = {0,1,2,3};
    Tour t(v);

    TravellingSalesmanProblem tsp(mPtr);

    double distance  = tsp.evaluate(t);

    EXPECT_EQ(20, distance);

}

