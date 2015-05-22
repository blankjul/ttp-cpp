#include "AbstractTest.h"


class AlgorithmTest : public AbstractTest {
public:


    TSP tsp = getTsp();
    TSP getTsp() {
        MapPtr mPtr = exampleMap();
        TSP tsp(mPtr);
        return tsp;
    }
};

