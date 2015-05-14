#include "LKH.h"
#include "Genetic.h"

/*
 * The AddToPopulation function adds the current tour as an individual to 
 * the population. The fitness of the individual is set equal to the cost
 * of the tour. The population is kept sorted in increasing fitness order.
 */

void AddToPopulation(GainType Cost)
{
    int i, *P;
    Node *N;

    if (!lkh.Population) {
        assert(lkh.Population =
               (int **) malloc(lkh.MaxPopulationSize * sizeof(int *)));
        for (i = 0; i < lkh.MaxPopulationSize; i++)
            assert(lkh.Population[i] =
                   (int *) malloc((1 + lkh.Dimension) * sizeof(int)));
        assert(lkh.Fitness =
               (GainType *) malloc(lkh.MaxPopulationSize * sizeof(GainType)));
    }
    for (i = lkh.PopulationSize; i >= 1 && Cost < lkh.Fitness[i - 1]; i--) {
        lkh.Fitness[i] = lkh.Fitness[i - 1];
        P = lkh.Population[i];
        lkh.Population[i] = lkh.Population[i - 1];
        lkh.Population[i - 1] = P;
    }
    lkh.Fitness[i] = Cost;
    P = lkh.Population[i];
    N = lkh.FirstNode;
    i = 1;
    do
        P[i++] = N->Id;
    while ((N = N->Suc) != lkh.FirstNode);
    P[0] = P[lkh.Dimension];
    lkh.PopulationSize++;
}

/*
 * The ApplyCrossover function applies a specified crossover operator to two 
 * individuals.
 */

void ApplyCrossover(int i, int j)
{
    int *Pi, *Pj, k;

    Pi = lkh.Population[i];
    Pj = lkh.Population[j];
    for (k = 1; k <= lkh.Dimension; k++) {
        lkh.NodeSet[Pi[k - 1]].Suc = &lkh.NodeSet[Pi[k]];
        lkh.NodeSet[Pj[k - 1]].Next = &lkh.NodeSet[Pj[k]];
    }
    if (lkh.TraceLevel >= 1)
        printff("Crossover(%d,%d)\n", i + 1, j + 1);
    /* Apply the crossover operator */
    lkh.Crossover();
}

#define Free(s) { free(s); s = 0; }

/*
 * The FreePopulation function frees the memory space allocated to the 
 * population.
 */

void FreePopulation()
{
    if (lkh.Population) {
        int i;
        for (i = 0; i < lkh.MaxPopulationSize; i++)
            Free(lkh.Population[i]);
        Free(lkh.Population);
        Free(lkh.Fitness);
    }
    lkh.PopulationSize = 0;
}

/*
 * The HasFitness function returns 1 if the population contains an
 * individual with fitness equal to a given tour cost; otherwise 0.
 *
 * Since the population is sorted in fitness order the test may be
 * made by binary search.
 */

int HasFitness(GainType Cost)
{
    int Low = 0, High = lkh.PopulationSize - 1;
    while (Low < High) {
        int Mid = (Low + High) / 2;
        if (lkh.Fitness[Mid] < Cost)
            Low = Mid + 1;
        else
            High = Mid;
    }
    return High >= 0 && lkh.Fitness[High] == Cost;
}

/*
 * Random01 is an auxiliary function for computing a random double number
 * in the range [0;1).
 */

static double Random01()
{
    return ((double) Random()) / INT_MAX;
}

/*
 * The LinearSelection function is used to select an individual with 
 * random linear bias towards the best members of the population.
 * The parameter Bias is a number between 1.0 and 2.0.
 *
 * See
 *     Darrell Whitley,
 *     The GENITOR algorithm and selection pressure:
 *     Why rank-based allocation of reproductive trials is best. 
 *     Proceedings of the Third International Conference on Genetic Algorithms,
 *     1989.
 */

int LinearSelection(int Size, double Bias)
{
    return (int) (Size *
                  (Bias -
                   sqrt((Bias * Bias - 4 * (Bias - 1) * Random01()))) /
                  2 / (Bias - 1));
}

/*
 * The MergeTourWithIndividual function attempts to find a short tour by
 * merging the current tour with a specified inddividual of the population.
 * The merging algorithm is the iterative partial transcription algrithm
 * described by Mobius, Freisleben, Merz and Schreiber.
 */

GainType MergeTourWithIndividual(int i)
{
    int *Pi, k;

    assert(i >= 0 && i < lkh.PopulationSize);
    Pi = lkh.Population[i];
    for (k = 1; k <= lkh.Dimension; k++)
        lkh.NodeSet[Pi[k - 1]].Next = &lkh.NodeSet[Pi[k]];
    return MergeWithTour();
}

/*
 * The PrintPopulation function prints the cost and gap to optimum for
 * each individual of the population.
 */

void PrintPopulation()
{
    int i;
    printff("Population:\n");
    for (i = 0; i < lkh.PopulationSize; i++) {
        printff("%3d: " GainFormat, i + 1, lkh.Fitness[i]);
        if (lkh.Optimum != MINUS_INFINITY && lkh.Optimum != 0)
            printff(", Gap = %0.4f%%",
                    100.0 * (lkh.Fitness[i] - lkh.Optimum) / lkh.Optimum);
        printff("\n");
    }
}

/*
 * The ReplaceIndividualWithTour function replaces a given individual in 
 * the population by an indidual that represents the current tour.
 * The population is kept sorted in increasing fitness order.
 */

void ReplaceIndividualWithTour(int i, GainType Cost)
{
    int j, *P;
    Node *N;

    assert(i >= 0 && i < lkh.PopulationSize);
    lkh.Fitness[i] = Cost;
    P = lkh.Population[i];
    N = lkh.FirstNode;
    for (j = 1; j <= lkh.Dimension; j++) {
        P[j] = N->Id;
        N = N->Suc;
    }
    P[0] = P[lkh.Dimension];
    while (i >= 1 && Cost < lkh.Fitness[i - 1]) {
        lkh.Fitness[i] = lkh.Fitness[i - 1];
        lkh.Population[i] = lkh.Population[i - 1];
        i--;
    }
    lkh.Fitness[i] = Cost;
    lkh.Population[i] = P;
    while (i < lkh.PopulationSize - 1 && Cost > lkh.Fitness[i + 1]) {
        lkh.Fitness[i] = lkh.Fitness[i + 1];
        lkh.Population[i] = lkh.Population[i + 1];
        i++;
    }
    lkh.Fitness[i] = Cost;
    lkh.Population[i] = P;
}

/* 
 * The DistanceToIndividual returns the number of different edges between 
 * the tour (given by OldSuc) and individual i. 
 */

static int DistanceToIndividual(int i) { 
    int Count = 0, j, *P = lkh.Population[i];
    Node *N;
    
    for (j = 0; j < lkh.Dimension; j++) {
        N = &lkh.NodeSet[P[j]];
        (N->Next = &lkh.NodeSet[P[j + 1]])->Prev = N;
    }
    N = lkh.FirstNode;
    do
        if (N->OldSuc != N->Next && N->OldSuc != N->Prev)
            Count++;
    while ((N = N->OldSuc) != lkh.FirstNode);
    return Count;
}

/*
 * The ReplacementIndividual function returns the individual to be 
 * replaced with the current tour. The function implements the 
 * replacement strategy (CD/RW) proposed in
 *
 *      M. Lozano, F. Herrera, and J. R. Cano,
 *      Replacement strategies to preserve useful diversity in
 *      steady-state genetic algorithms.
 *      Information Sciences 178 (2008) 4421–4433.
 */

int ReplacementIndividual(GainType Cost) {
    int i, j, d, *P;
    int MinDist = INT_MAX, CMin = lkh.PopulationSize - 1;
    Node *N = lkh.FirstNode;
    while ((N = N->OldSuc = N->Suc) != lkh.FirstNode);
    for (i = lkh.PopulationSize - 1; i >= 0 && lkh.Fitness[i] > Cost; i--) {
        if ((d = DistanceToIndividual(i)) < MinDist) {
            CMin = i;
            MinDist = d;
        }
    }
    if (CMin == lkh.PopulationSize - 1)
        return CMin;
    P = lkh.Population[CMin];
    for (j = 0; j < lkh.Dimension; j++)
        lkh.NodeSet[P[j]].OldSuc = &lkh.NodeSet[P[j + 1]];
    for (i = 0; i < lkh.PopulationSize; i++)
        if (i != CMin && (d = DistanceToIndividual(i)) < MinDist)
            return lkh.PopulationSize - 1;
    return CMin;
}
