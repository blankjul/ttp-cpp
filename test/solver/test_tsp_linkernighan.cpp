#include "solver/tsp_lin_kernighan.h"
#include "solver/tsp_exhaustive_solver.h"
#include "gtest/gtest.h"
#include "experiments/generator.h"
using namespace ttp;


/*


TEST(TSPLinKernighanSolver, Bier127) {
    //TSP tsp = ExperimentFactory::createTSPFromFile("../test/generator/berlin4.tsp");

    TSP tsp = ProblemFactory::createTSPFromFile("../data/tsplib/bier127.tsp");
    //TSP tsp = ExperimentFactory::createTSP(20);

    TSPLinKernighanSolver s;

    s.solve(tsp);

    //EXPECT_EQ(0, m.get(1,1));
}




TEST(TSP, EvaluateTTPRoute) {

    MapPtr mPtr = exampleMap();
    TSP tsp(mPtr);
    TSPExhaustiveSolver s;
    s.solve(tsp);
    Tour result = s.solve(tsp);
    std::vector<int> v = {0,3,2,1};
    EXPECT_EQ(v, result.getVector());
}


TEST(TSPLinKernighanSolver, berlin52) {
    TSP tsp = ProblemFactory::createTSPFromFile("../data/tsplib/berlin52.tsp");


    TSPLinKernighanSolver s;
    s.solve(tsp);



Tour t = s.solve(tsp);

cout << t<< endl;

cout << tsp.evaluate(t);

    //EXPECT_EQ(0, m.get(1,1));
}
*/