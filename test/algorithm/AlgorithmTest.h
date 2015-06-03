#include "AbstractTest.h"


class AlgorithmTest : public AbstractTest {
public:


    TSP tsp = getTsp();
    TSP getTsp() {
        MapPtr mPtr = exampleMap();
        TSP tsp(mPtr);
        return tsp;
    }

    MOTTP getMOTTP() {
        ThiefMapPtr mPtr = exampleThiefMap();
        MOTTP ttp(mPtr, 3);
        return ttp;
    }
};

