
#include "SMPSO.h"
#include "metaheuristics/smpso/SMPSO.h"
#include "jmetal/JMetalProblem.h"
#include "metaheuristics/nsgaII/NSGAII.h"
#include "experiments/settings/NSGAII_Settings.h"
#include "jmetal/TTPCrossover.h"
#include "jmetal/TTPMutation.h"


ttp::TTPOutputSet ttp::mo::SMPSO::solve(ttp::MOTTP mottp) {

    JMetalProblem* p = new JMetalProblem(mottp);

    ::Algorithm * algorithm = new ::SMPSO(p);

    double mutationProbability_       = 1.0/p->getNumberOfVariables() ;
    algorithm->setInputParameter("swarmSize", &swarmSize_);
    algorithm->setInputParameter("maxIterations", &maxIterations_);
    algorithm->setInputParameter("archiveSize", &archiveSize_);

    map<string, void *> parameters;

    double mutationProbability = mutationProbability_;
    double mutationDistributionIndex = mutationDistributionIndex_;
    parameters["probability"] = &mutationProbability;
    parameters["distributionIndex"] = &mutationDistributionIndex;
    Operator  * mutation = new TTPMutation(parameters);

    // Add the operators to the algorithm
    algorithm->addOperator("mutation",mutation);


    TTPOutputSet s;
    SolutionSet* result = algorithm->execute();
    for (int i = 0; i < result->size(); ++i) {
        Solution* entry = result->get(i);
        TTPOutput out(- entry->getObjective(0), entry->getObjective(1));
        s.add(out);
    }


    return s;
}
