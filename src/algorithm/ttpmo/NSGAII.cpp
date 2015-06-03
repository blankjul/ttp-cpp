

#include "jmetal/JMetalProblem.h"
#include "metaheuristics/nsgaII/NSGAII.h"
#include "experiments/settings/NSGAII_Settings.h"
#include "jmetal/TTPCrossover.h"
#include "jmetal/TTPMutation.h"
#include "NSGAII.h"


ttp::TTPOutputSet ttp::mo::NSGAII::solve(ttp::MOTTP mottp) {

    JMetalProblem* p = new JMetalProblem(mottp);

    ::Algorithm * algorithm = new ::NSGAII(p);
    algorithm->setInputParameter("populationSize",&populationSize_);
    algorithm->setInputParameter("maxEvaluations",&maxEvaluations_);

    // Mutation and Crossover for Real codification
    map<string, void *> parameters;



    double crossoverProbability = crossoverProbability_;
    double crossoverDistributionIndex = crossoverDistributionIndex_ ;
    parameters["probability"] =  &crossoverProbability;
    parameters["distributionIndex"] = &crossoverDistributionIndex;
    Operator  * crossover = new TTPCrossover(parameters);

    parameters.clear();
    double mutationProbability_       = 1.0/p->getNumberOfVariables() ;
    double mutationProbability = mutationProbability_;
    double mutationDistributionIndex = mutationDistributionIndex_;
    parameters["probability"] = &mutationProbability;
    parameters["distributionIndex"] = &mutationDistributionIndex;
    Operator  * mutation = new TTPMutation(parameters);

    // Selection Operator
    parameters.clear();
    Operator  * selection = new BinaryTournament2(parameters);

    // Add the operators to the algorithm
    algorithm->addOperator("crossover",crossover);
    algorithm->addOperator("mutation",mutation);
    algorithm->addOperator("selection",selection);

    //cout << "NGSAII algorithm initialized." << endl;


    TTPOutputSet s;
    SolutionSet* result = algorithm->execute();
    for (int i = 0; i < result->size(); ++i) {
        Solution* entry = result->get(i);
        TTPOutput out(- entry->getObjective(0), entry->getObjective(1));
        s.add(out);
    }

    return s;
}
