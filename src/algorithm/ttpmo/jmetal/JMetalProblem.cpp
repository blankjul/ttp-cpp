#include "JMetalProblem.h"
#include "TTPSolutionType.h"
#include "encodings/variable/Binary.h"
#include "encodings/variable/ArrayReal.h"
#include "model/Item.h"
#include "JTour.h"
#include <algorithm>




JMetalProblem::JMetalProblem(ttp::MOTTP &mottp) : mottp(mottp){
    numberOfVariables_ = 2;
    numberOfObjectives_ = 2;
    numberOfConstraints_ = 0;
    problemName_ = "TTP";

    ttp::ThiefMapPtr map = mottp.getMap();
    solutionType_ = new TTPSolutionType(map->size(), map->itemSize(), this);

}


/**
 * Destructor
 */
JMetalProblem::~JMetalProblem() {
} // ~JMetalAdapter


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void JMetalProblem::evaluate(Solution *solution) {

    Variable **variables = solution->getDecisionVariables();

    JTour *array = (JTour *) solution->getDecisionVariables()[0];
    Binary *bins = (Binary *) solution->getDecisionVariables()[1];

    ttp::Knapsack knp;
    const vector<ttp::ItemPtr> items = mottp.getMap()->getItems();
    for (int i = 0; i < bins->getNumberOfBits(); ++i) {
        if (bins->getIth(i)) knp.add(items[i]);
    }

    ttp::Tour tour = ttp::Tour(array->v);

    ttp::TTPInput input(tour, knp);
    ttp::TTPOutput out = mottp.evaluate(input);

    //cout << out << "   -  > " << <<endl;


    solution->setObjective(0, - out.getValue());
    solution->setObjective(1, out.getTime());


} // evaluate
