#include "solver/tsp_exhaustive_solver.h"
#include "solver/tsp_greedy_solver.h"
#include "model/map.h"
#include "model/tour.h"
#include "gtest/gtest.h"




TEST(TSPExhaustiveSolver, solve) {
    TTP::Map m(4);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(2,3,4);
    m.set(1,3,5);
    TTP::TSPExhaustiveSolver s;

    //TTP::Tour t = s.solve(m);

    //EXPECT_EQ(0, m.get(1,1));
}



TEST(TSPGreedySolver, solve) {
    TTP::Map m(100);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(2,3,4);
    m.set(1,3,5);
    TTP::TSPGreedySolver s;

    TTP::Tour t = s.solve(m);

    //EXPECT_EQ(0, m.get(1,1));
}
