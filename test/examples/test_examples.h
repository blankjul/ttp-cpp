

#ifndef TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H
#define TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H


#include "model/item.h"
#include "model/map.h"
#include <vector>



using namespace TTP;

MapPtr exampleMap();

vector<pair<ItemPtr,int>> exampleItemsLarge();

vector<pair<ItemPtr,int>> exampleItemsSmall();



#endif //TRAVELLING_THIEF_PROBLEM_TEST_EXAMPLES_H