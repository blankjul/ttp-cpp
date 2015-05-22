#include "solver/tsp_exhaustive_solver.h"
#include "solver/ttpmo_exhaustive_solver.h"
#include "solver/ttpso_exhaustive_solver.h"
#include "solver/tsp_lin_kernighan.h"
#include "gtest/gtest.h"
#include "experiments/generator.h"
#include "solver/knp_combo.h"

using namespace ttp;




/*


TEST(KNPComboSolver, solve2) {


    KnapsackProblem knp = ProblemFactory::createKNP(10000, 1000,ProblemFactory::KnapsackType::STRONGLY_CORRELATED, 10);
    KNPComboSolver knpsolver;
    knpsolver.solve(knp);

    //EXPECT_EQ(0, m.get(1,1));
}





TEST(TTPExhaustiveSolver, solveSO) {


    MapPtr m = exampleMap();
    TravellingThiefProblemDeptr ttps(m,3);
    vector<pair<ItemPtr, int>> items = exampleItemsLarge();
    ttps.setRentingRate(1);
    ttps.addItems(items);

    TTPSOExhaustiveSolver s;
    auto result = s.solve(ttps);

    std::vector<int> route {0,1,3,2};
    std::vector<int> pickingPlan {0, 1, 1, 0, 0, 0};

    EXPECT_EQ(route, result.first.getVector());
    EXPECT_EQ(pickingPlan, ttps.convertKnapsackToVector(result.second));

}



TEST(TTPExhaustiveSolver, solveMO) {

    MapPtr m = exampleMap();
    vector<pair<ItemPtr, int>> items = exampleItemsSmall();

    TravellingThiefProblemDeptr ttpmo(m, 3);
    ttpmo.setDroppingRate(0.9);
    ttpmo.addItems(items);

    TTPMOExhaustiveSolver s;
    s.solve(ttpmo);


}
*/