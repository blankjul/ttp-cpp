
#include "gtest/gtest.h"
#include <sstream>
#include <iostream>
#include <generator/generator.h>
#include <model/map.h>

TEST(GeneratorTest, TSPLIBBerlin) {


    TTP::Map m = TTP::createMatrixFromTSPLIB("/home/julesy/Workspace/travelling-thief-problem/bin/berlin4.tsp");

    TTP::Map expected(4);
    expected.set(0,1,666);
    expected.set(0,2,281);
    expected.set(0,3,396);

    expected.set(1,2,649);
    expected.set(1,3,1047);

    expected.set(2,3,604);

    for (int i = 0; i < m.count(); ++i) {
        for (int j = 0; j < m.count(); ++j) {
            EXPECT_EQ(expected.get(i,j), m.get(i,j));
        }
    }

    std::cout << m;



}

TEST(GeneratorTest, TSPLIBBerlin2) {


    TTP::Map m = TTP::createMatrixFromTSPLIB("/home/julesy/Workspace/travelling-thief-problem/bin/berlin52.tsp");



    //std::cout << m;



}


