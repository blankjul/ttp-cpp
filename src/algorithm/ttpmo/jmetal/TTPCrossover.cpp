#include "operators/crossover/SinglePointCrossover.h"
#include "encodings/variable/ArrayReal.h"
#include "TTPCrossover.h"



TTPCrossover::TTPCrossover(map<string, void *> parameters)
        : Crossover(parameters) {
    crossoverProbability_ = 0.0;
    if (parameters["probability"] != NULL)
        crossoverProbability_ = *(double *) parameters["probability"];
} // TTPCrossover


Binary *crossBinary(double probability, Binary *bins1, Binary *bins2) {


    if (PseudoRandom::randDouble() < probability) {
        //1. Compute the total number of bits
        int totalNumberOfBits = bins1->getNumberOfBits();

        //2. Calculate the point to make the crossover
        int crossoverPoint = PseudoRandom::randInt(0, totalNumberOfBits - 1);

        //3. Compute the variable containing the crossoverPoint bit
        Binary *offspring = new Binary(totalNumberOfBits);
        for (int i = 0; i < crossoverPoint; ++i) {
            offspring->setIth(i, bins1->getIth(i));
        }
        for (int i = crossoverPoint; i < bins1->getNumberOfBits(); ++i) {
            offspring->setIth(i, bins2->getIth(i));
        }
        return offspring;
    }
    return bins1;

}

/**
 * Perform the crossover operation.
 * @param probability Crossover probability
 * @param parent1 The first parent
 * @param parent2 The second parent
 * @return An array containing the two offsprings
 **/
Solution **TTPCrossover::doCrossover(double probability, Solution *parent1, Solution *parent2) {


    /* create the two offsprings */
    Solution **offSpring = new Solution *[2];
    if (offSpring == NULL) {
        cout <<
        "Error grave: Impossible reserve memory for allocating new solutions when performing SinglePointCrossover " <<
        endl;
        exit(-1);
    }
    offSpring[0] = new Solution(parent1);
    offSpring[1] = new Solution(parent2);


    Variable **variables1 = offSpring[0]->getDecisionVariables();
    JTour *array1 = (JTour *) offSpring[0]->getDecisionVariables()[0];
    Binary *bins1 = (Binary *) offSpring[0]->getDecisionVariables()[1];
    Variable **variables2 = offSpring[1]->getDecisionVariables();
    JTour *array2 = (JTour *) offSpring[1]->getDecisionVariables()[0];
    Binary *bins2 = (Binary *) offSpring[1]->getDecisionVariables()[1];


    // do crossover with the bins
    if (PseudoRandom::randDouble() < probability) {
        //1. Compute the total number of bits
        int totalNumberOfBits = bins1->getNumberOfBits();

        //2. Calculate the point to make the crossover
        int crossoverPoint = PseudoRandom::randInt(0, totalNumberOfBits - 1);

        //3. Compute the variable containing the crossoverPoint bit
        for (int i = 0; i < crossoverPoint; ++i) {
            bins1->setIth(i, ((Binary *) parent1->getDecisionVariables()[1])->getIth(i));
            bins2->setIth(i, ((Binary *) parent2->getDecisionVariables()[1])->getIth(i));
        }
        for (int i = crossoverPoint; i < bins1->getNumberOfBits(); ++i) {
            bins1->setIth(i, ((Binary *) parent2->getDecisionVariables()[1])->getIth(i));
            bins2->setIth(i, ((Binary *) parent1->getDecisionVariables()[1])->getIth(i));
        }
    }


    int crossoverPoint = PseudoRandom::randInt(1, array1->getLength() - 1);
    offSpring[0]->getDecisionVariables()[0] = TTPCrossover::crossJTour(crossoverPoint, array1, array2);
    offSpring[1]->getDecisionVariables()[0] = TTPCrossover::crossJTour(crossoverPoint, array2, array1);

    return offSpring;
} // doCrossover



/**
 * Executes the operation
 * @param object An object containing an array of two parents
 * @return An object containing the offSprings
 */
void *TTPCrossover::execute(void *object) {
    Solution **parents = (Solution **) object;
    Solution **offSpring = (Solution **) doCrossover(crossoverProbability_, parents[0], parents[1]);
    return offSpring;
} // execute



