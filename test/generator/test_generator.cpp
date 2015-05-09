
#include "gtest/gtest.h"
#include <sstream>
#include <iostream>
#include <generator/generator.h>
#include <model/map.h>
#include <model/item.h>
#include <iostream>
#include <model/knapsack.h>


/**
 * Test if exeception is thrown when file does not exist
 */
TEST(GeneratorTest, TSPFileDoesNotExist) {
    ASSERT_THROW(TTP::ProblemFactory::createTSP("nofile"), std::runtime_error);
}

/**
 * Test what happends when the format is wrong
 */
TEST(GeneratorTest, TSPWrongInputFormat) {
    ASSERT_THROW(TTP::ProblemFactory::createTSP("README.md"), std::runtime_error);
}

/**
 * Test if we itemsCount is negative
 */
TEST(GeneratorTest, KNPCountItemsNegative) {
    ASSERT_THROW(TTP::ProblemFactory::createKNP(-1, 1000, TTP::ProblemFactory::KnapsackType::UNCORRELATED,1), std::runtime_error);
}


/**
 * Test if uppper bound is negative
 */
TEST(GeneratorTest, KNPUperBoundNegative) {
    ASSERT_THROW(TTP::ProblemFactory::createKNP(1, -1, TTP::ProblemFactory::KnapsackType::UNCORRELATED,1), std::runtime_error);
}

/**
 * Test if we create multiple ttps
 */
TEST(GeneratorTest, KNPMultipleCreating) {
   auto list = TTP::ProblemFactory::createMultipleKNP(100, 1000, TTP::ProblemFactory::KnapsackType::UNCORRELATED, 10);EXPECT_EQ(10, list.size());
}


/**
 * Example test case that compares the pisinger create with this result.
 */
TEST(GeneratorTest, ExampleCase) {
    TTP::KnapsackProblem knp = TTP::ProblemFactory::createKNP(10, 1000, TTP::ProblemFactory::KnapsackType::UNCORRELATED, 10, 200);

    // just compare the first three instances
    auto list = knp.getItems();

    /*
    INPUT:
    n = 10
    r = 1000
    t = 1
    i = 200
    S = 10

    OUPUT:
    1   681   604
    2   563   165
    3   975   154
    4   695   871
    5   120   560
    6   484    91
    7    83   832
    8   375   747
    9    96   746
    10   921   845
     */

    EXPECT_EQ(681, list[0]->getValue());
    EXPECT_EQ(604, list[0]->getWeight());

    EXPECT_EQ(563, list[1]->getValue());
    EXPECT_EQ(165, list[1]->getWeight());


}



/**
 * Test for loading a tsp file
 */
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



