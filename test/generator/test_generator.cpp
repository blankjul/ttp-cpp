
#include "gtest/gtest.h"
#include <sstream>
#include <iostream>
#include <generator/generator.h>
#include <model/map.h>



TEST(GeneratorTest, FileDoesNotExist) {
    ASSERT_THROW(TTP::ProblemFactory::createTSP("nofile"), std::runtime_error);
}


TEST(GeneratorTest, WrongInputFormat) {
    ASSERT_THROW(TTP::ProblemFactory::createTSP("README.md"), std::runtime_error);
}


TEST(GeneratorTest, TSPLIBBerlin) {
    TTP::TravellingSalesmanProblem tsp = TTP::ProblemFactory::createTSP("test/generator/berlin4.tsp");

    TTP::MapPtr m = tsp.getMap();

    TTP::Map expected(4);
    expected.set(0,1,666);
    expected.set(0,2,281);
    expected.set(0,3,396);

    expected.set(1,2,649);
    expected.set(1,3,1047);

    expected.set(2,3,604);

    for (int i = 0; i < m->count(); ++i) {
        for (int j = 0; j < m->count(); ++j)
        {
            EXPECT_EQ(expected.get(i,j), m->get(i,j));
        }
    }



}



