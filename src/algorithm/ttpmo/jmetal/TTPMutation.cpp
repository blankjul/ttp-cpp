#include "TTPMutation.h"
#include "encodings/variable/ArrayReal.h"
#include "JTour.h"


/**
 * Constructor
 * Creates a new instance of the polynomial mutation operator
 */
TTPMutation::TTPMutation(map<string, void *> parameters)
        : Mutation(parameters) {
    mutationProbability_ = 0.0;
    if (parameters["probability"] != NULL)
        mutationProbability_ = *(double *) parameters["probability"];
} // BitFlipMutation


/**
 * Destructor
 */
TTPMutation::~TTPMutation() { } // ~BitFlipMutation


/**
 * Perform the mutation operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void *TTPMutation::doMutation(double probability, Solution *solution) {
    int numberOfVariables = solution->getNumberOfVariables();

    Variable **variables = solution->getDecisionVariables();
    JTour *array = (JTour *) solution->getDecisionVariables()[0];
    Binary *bins = (Binary *) solution->getDecisionVariables()[1];



    for (int j = 0; j < bins->getNumberOfBits(); j++) {
        if (PseudoRandom::randDouble() <= mutationProbability_)
            bins->flip(j);
    }



    for (int j = 1; j < array->getLength(); j++) {
        if (PseudoRandom::randDouble() <= mutationProbability_) {
            int swapIndex = PseudoRandom::randInt(1, array->getLength() - 1);
            std::swap(array->v[j], array->v[swapIndex]);
        }
    }





} // doMutation



/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 * @throws JMException
 */
void *TTPMutation::execute(void *object) {
    Solution *solution = (Solution *) object;
    doMutation(mutationProbability_, solution);
    return solution;
} // execute
