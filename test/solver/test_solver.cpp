#include "solver/tsp_exhaustive_solver.h"
#include "solver/ttpmo_exhaustive_solver.h"
#include "solver/ttpso_exhaustive_solver.h"
#include "solver/tsp_greedy_solver.h"
#include "problems/ttp_so.h"
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

    MapPtr m = make_shared<Map>(4);


    // set the weights
    m->set(0,1,5);
    m->set(0,2,6);
    m->set(0,3,6);
    m->set(1,2,5);
    m->set(1,3,6);
    m->set(2,3,4);



    MultiObjectiveTravellingThiefProblem ttp(m,3);


    ttp.add(2, std::make_shared<Item>(10,3));
    ttp.add(2, std::make_shared<Item>(4,1));
    ttp.add(2, std::make_shared<Item>(4,1));
    ttp.add(1, std::make_shared<Item>(2,2));
    ttp.add(1, std::make_shared<Item>(3,3));
    ttp.add(3, std::make_shared<Item>(2,2));


    TTPMOExhaustiveSolver s;
    s.solve(ttp);


    SingleObjectiveTravellingThiefProblem ttps(m,3);
    ttps.setRentingRate(1);

    ttps.add(2, std::make_shared<Item>(10,3));
    ttps.add(2, std::make_shared<Item>(4,1));
    ttps.add(2, std::make_shared<Item>(4,1));
    ttps.add(1, std::make_shared<Item>(2,2));
    ttps.add(1, std::make_shared<Item>(3,3));
    ttps.add(3, std::make_shared<Item>(2,2));

    TTPSOExhaustiveSolver s2;
    s2.solve(ttps);

}
