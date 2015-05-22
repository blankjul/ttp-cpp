#include "AbstractTest.h"


using namespace std;
using namespace ttp;


class TSPTest : public AbstractTest {
public:
    MapPtr mPtr = exampleMap();
    TSP tsp = getTsp();

    TSP getTsp() {
        MapPtr mPtr = exampleMap();
        TSP tsp(mPtr);
        return tsp;
    }

};


TEST_F(TSPTest, Evaluate1) {
    Tour t = createTour(vector<int> {0,1,3,2});
    EXPECT_EQ(21, tsp.evaluate(t));

}



TEST_F(TSPTest, Evaluate2) {
    Tour t = createTour(vector<int> {0,2,1,3});
    EXPECT_EQ(23, tsp.evaluate(t));


}


TEST_F(TSPTest, Evaluate3) {
    Tour t = createTour(vector<int> {0,1,2,1});
    EXPECT_EQ(20, tsp.evaluate(t));

}

