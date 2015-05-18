#include "solver/tsp_lin_kernighan.h"
#include "solver/tsp_exhaustive_solver.h"
#include "examples/test_examples.h"
#include "gtest/gtest.h"

#include "generator/generator.h"
using namespace ttp;



TEST(TSPLinKernighanSolver, Bier127) {
    //TravellingSalesmanProblem tsp = ProblemFactory::createTSPFromFile("../test/generator/berlin4.tsp");

    TravellingSalesmanProblem tsp = ProblemFactory::createTSPFromFile("../data/tsplib/bier127.tsp");
    //TravellingSalesmanProblem tsp = ProblemFactory::createTSP(20);

    TSPLinKernighanSolver s;

    s.solve(tsp);

    //EXPECT_EQ(0, m.get(1,1));
}




TEST(TSP, EvaluateTTPRoute) {

    MapPtr mPtr = exampleMap();
    TravellingSalesmanProblem tsp(mPtr);
    TSPExhaustiveSolver s;
    s.solve(tsp);
    Tour result = s.solve(tsp);
    std::vector<int> v = {0,3,2,1};
    EXPECT_EQ(v, result.getVector());
}


TEST(TSPLinKernighanSolver, berlin52) {
    TravellingSalesmanProblem tsp = ProblemFactory::createTSPFromFile("../data/tsplib/berlin52.tsp");
    TravellingSalesmanProblem tsp2 = ProblemFactory::createTSPFromFile("../data/tsplib/bayg29.tsp");
    TravellingSalesmanProblem tsp3 = ProblemFactory::createTSPFromFile("../data/tsplib/bays29.tsp");

    TSPLinKernighanSolver s;
    s.solve(tsp);
    s.solve(tsp2);
    s.solve(tsp3);

    //s.solve(tsp);


Tour t = s.solve(tsp);
    s.solve(tsp);
    s.solve(tsp);
    s.solve(tsp);

    s.solve(tsp);
cout << t<< endl;

cout << tsp.evaluate(t);

    //EXPECT_EQ(0, m.get(1,1));
}
