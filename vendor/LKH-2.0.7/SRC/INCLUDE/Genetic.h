#ifndef _GENETIC_H
#define _GENETIC_H

/*
 * This header specifies the interface for the genetic algorithm part of LKH.
 */




void AddToPopulation(GainType Cost);
void ApplyCrossover(int i, int j);
void FreePopulation();
int HasFitness(GainType Cost);
int LinearSelection(int Size, double Bias);
GainType MergeTourWithIndividual(int i);
void PrintPopulation();
void ReplaceIndividualWithTour(int i, GainType Cost);
int ReplacementIndividual(GainType Cost);

void ERXT();

#endif
