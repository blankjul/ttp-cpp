

#ifndef TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H
#define TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H


#include "model/item.h"
#include "model/map.h"
#include <vector>
#include <problems/tsp.h>


using namespace ttp;

MapPtr exampleMap();

vector<pair<ItemPtr,int>> exampleItemsLarge();

vector<pair<ItemPtr,int>> exampleItemsSmall();

TravellingSalesmanProblem berlin52();



#endif //TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H