#include "AbstractTest.h"
#include "../../src/experiment/Factory.h"

using namespace ttp;

class ExperimentTest : public AbstractTest {
};


TEST_F(ExperimentTest, TTP) {

    int n = 10;
    int numberOfItemsPerCity = 5;

    TSP tsp = ProblemFactory::createTSP(n);
    int numOfItems = numberOfItemsPerCity * (tsp.count() - 1);
    KnapsackProblem knp = ProblemFactory::createKNP(numOfItems, 1000,
                                                    ProblemFactory::KnapsackType::STRONGLY_CORRELATED,
                                                    100);

    MOTTP result = ProblemFactory::createTTP(tsp, knp, numberOfItemsPerCity);

    ThiefMapPtr map = result.getMap();
    for (int j = 1; j < map->size(); ++j) {
        EXPECT_EQ(numberOfItemsPerCity,map->getItemsAtCity(j).size());
    }

}

