#include "solver/tsp_exhaustive_solver.h"
#include "solver/ttp_exhaustive_solver.h"
#include "solver/tsp_greedy_solver.h"
#include "model/thief_map.h"
#include "problems/ttp.h"
#include "model/tour.h"
#include "gtest/gtest.h"

using namespace TTP;


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




TEST(TTPExhaustiveSolver, solve) {

    ThiefMap tm = ThiefMap(4);

    // set the weights
    tm.set(0,1,5);
    tm.set(0,2,6);
    tm.set(0,3,6);
    tm.set(1,2,5);
    tm.set(1,3,6);
    tm.set(2,3,4);


    tm.addItem(1, std::make_shared<Item>(2,2));
    tm.addItem(1, std::make_shared<Item>(3,3));
    tm.addItem(2, std::make_shared<Item>(10,3));
    tm.addItem(2, std::make_shared<Item>(4,1));
    tm.addItem(2, std::make_shared<Item>(4,1));
    tm.addItem(3, std::make_shared<Item>(2,2));


    std::vector<int> v = {0,2,1,3};
    TTP::Tour t(v);


    TTP::Knapsack k;
    k.add(tm.getItems(1)[0]);
    k.add(tm.getItems(2)[1]);


    TravellingThiefProblem ttp(tm, 3);

    TTPExhaustiveSolver s;
    s.solve(ttp);



    auto p = ttp.evaluate(t, k);
}
