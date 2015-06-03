#ifndef __TTP_SOLUTION_TYPE__
#define __TTP_SOLUTION_TYPE__

#include "core/SolutionType.h"
#include "encodings/variable/Real.h"
#include <string>


class TTPSolutionType : public SolutionType {
private:

    Problem* problem;
    int numOfCities;
    int numOfItems;
public:
    TTPSolutionType(int cities, int items, Problem *problem);
    Variable **createVariables();

};

#endif
