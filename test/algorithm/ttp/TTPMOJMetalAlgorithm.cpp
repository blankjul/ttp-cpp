#include <algorithm/ttpmo/NSGAII.h>
#include <algorithm/ttpmo/MOAD.h>
#include <algorithm/ttpmo/SMPSO.h>
#include "algorithm/AlgorithmTest.h"





class TTPMOJMetalAlgorithmTest : public AlgorithmTest {
public:
    MOTTP ttp = getMOTTP();
};


TEST_F(TTPMOJMetalAlgorithmTest, NSGA) {
    ttp::mo::NSGAII nsga;
    nsga.populationSize_ = 10;
    nsga.maxEvaluations_ = 100;
    nsga.solve(ttp);
}

TEST_F(TTPMOJMetalAlgorithmTest, MOEAD) {
    ttp::mo::SMPSO smpso;
    //smpso.solve(ttp);
}




