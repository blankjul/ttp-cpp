#include "MOAD.h"
#include "jmetal/JMetalProblem.h"
#include "metaheuristics/moead/MOEAD.h"
#include "jmetal/TTPCrossover.h"
#include "jmetal/TTPMutation.h"



ttp::TTPOutputSet ttp::mo::MOAD::solve(ttp::MOTTP mottp) {

    JMetalProblem* p = new JMetalProblem(mottp);

    int populationSize_ = 500;
    int maxEvaluations_ = 500000;
    double mutationProbability_         = 1.0/p->getNumberOfVariables() ;
    double crossoverProbability_        = 0.9   ;
    double mutationDistributionIndex_   = 20.0  ;
    double crossoverDistributionIndex_  = 20.0  ;
    std::string dataDirectory = "../data";

    ::Algorithm * algorithm = new MOEAD(p);
    algorithm->setInputParameter("populationSize",&populationSize_);
    algorithm->setInputParameter("maxEvaluations",&maxEvaluations_);
    algorithm->setInputParameter("dataDirectory",&dataDirectory);


    // Mutation and Crossover for Real codification
    map<string, void *> parameters;

    double crossoverProbability = crossoverProbability_;
    double crossoverDistributionIndex = crossoverDistributionIndex_ ;
    parameters["probability"] =  &crossoverProbability;
    parameters["distributionIndex"] = &crossoverDistributionIndex;
    Operator  * crossover = new TTPCrossover(parameters);

    parameters.clear();
    double mutationProbability = mutationProbability_;
    double mutationDistributionIndex = mutationDistributionIndex_;
    parameters["probability"] = &mutationProbability;
    parameters["distributionIndex"] = &mutationDistributionIndex;
    Operator  * mutation = new TTPMutation(parameters);

    // Add the operators to the algorithm
    algorithm->addOperator("crossover",crossover);
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
