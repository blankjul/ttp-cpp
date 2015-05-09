#include "solver/tsp_exhaustive_solver.h"
#include "solver/ttpmo_exhaustive_solver.h"
#include "solver/ttpso_exhaustive_solver.h"
#include "solver/tsp_greedy_solver.h"
#include "problems/ttp_so.h"
#include "model/tour.h"
#include "gtest/gtest.h"
#include "examples/test_examples.h"


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



TEST(TTPExhaustiveSolver, solveSO) {

    MapPtr m = exampleMap();


    SingleObjectiveTravellingThiefProblem ttps(m,3);
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();
    ttps.setRentingRate(1);
    ttps.addItems(items);


    TTPSOExhaustiveSolver s2;
    s2.solve(ttps);

}

TEST(TTPExhaustiveSolver, solveMO) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();

    MultiObjectiveTravellingThiefProblem ttpmo(m, 3);
    ttpmo.setDroppingRate(0.9);
    ttpmo.addItems(items);

    TTPMOExhaustiveSolver s;
    s.solve(ttpmo);


}
