#include "TTPSolutionType.h"
#include "encodings/variable/ArrayReal.h"
#include "encodings/variable/Binary.h"
#include "JTour.h"


TTPSolutionType::TTPSolutionType(int cities, int items, Problem *problem) :
        SolutionType(problem), numOfCities(cities), numOfItems(items){
    this->problem = problem;
}


Variable **TTPSolutionType::createVariables() {
    int i;

    Variable **variables = new Variable*[2];
    if (variables ==  NULL) {
        cout << "Error grave: Impossible to reserve memory for variable type" << endl;
        exit(-1);
    }

    variables[0] = new JTour(numOfCities);
    variables[1] = new Binary(numOfItems);

    return variables;
}
