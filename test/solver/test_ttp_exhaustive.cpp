
#include "solver/ttpmo_exhaustive_solver.h"
#include "gtest/gtest.h"
#include "experiments/generator.h"
using namespace ttp;

/*
TEST(TTPExhaustiveSolver, DISABLE_examplePareto) {
    MapPtr m = exampleMap();
    vector<pair<int, ItemPtr>> items = exampleItemsSmall();

    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.setDroppingRate(0.9);
    ttpmo.addItems(items);

    TTPMOExhaustiveSolver s;

    s.solve(ttpmo);

}
*/