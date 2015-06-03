#ifndef TRAVELLING_THIEF_PROBLEM_ABSTRACTTEST_H
#define TRAVELLING_THIEF_PROBLEM_ABSTRACTTEST_H


#include <algorithm>
#include <iostream>

#include "experiment/Generator.h"
#include "experiment/Factory.h"

#include "model/Item.h"
#include "model/Knapsack.h"
#include "model/Map.h"
#include "model/Tour.h"
#include "model/ThiefMap.h"

#include "problems/KnapsackProblem.h"
#include "problems/MOTTP.h"
#include "problems/SOTTP.h"
#include "problems/TTPOutput.h"
#include "problems/TSP.h"
#include "problems/TTP.h"
#include "problems/TTPOutputSet.h"

#include "tsp/TSPExhaustive.h"
#include "tsp/TSPAlgorithm.h"
#include "tsp/TSPLinKernighan.h"
#include "ttpmo/Exhaustive.h"



#include "gmock/gmock.h"
#include "gtest/gtest.h"





using namespace std;
using namespace ttp;
using namespace ::testing;


class AbstractTest : public ::testing::Test {
public:

    Tour createTour(vector<int> v) {
        return Tour(v);
    }

    MapPtr exampleMap() {
        MapPtr m = make_shared<Map>(4);
        m->set(0,1,5);
        m->set(0,2,6);
        m->set(0,3,6);
        m->set(1,2,5);
        m->set(1,3,6);
        m->set(2,3,4);
        return m;
    }

    ThiefMapPtr exampleThiefMap() {
        ThiefMapPtr mPtr =  make_shared<ThiefMap>(exampleMap());
        vector<pair<int,ItemPtr>> v = exampleItemsSmall();
        mPtr->insert(v.begin(), v.end());
        return mPtr;
    }

    vector<pair<int,ItemPtr>> exampleItemsLarge() {
        vector<pair<int,ItemPtr>> result;
        for(auto i : exampleItemsSmall()) {
            ItemPtr ptr = createItem(i.second->getValue() * 10, i.second->getWeight());
            result.push_back(make_pair(i.first, ptr));
        }
        return result;

    }

    vector<pair<int,ItemPtr>> exampleItemsSmall() {
        vector<pair<int,ItemPtr>> items;
        items.push_back(make_pair<int,ItemPtr>(2, createItem(10,3)));
        items.push_back(make_pair<int,ItemPtr>(2, createItem(4,1)));
        items.push_back(make_pair<int,ItemPtr>(2, createItem(4,1)));
        items.push_back(make_pair<int,ItemPtr>(1, createItem(2,2)));
        items.push_back(make_pair<int,ItemPtr>(2, createItem(3,3)));
        items.push_back(make_pair<int,ItemPtr>(3, createItem(2,2)));
        return items;
    }





};




#endif //TRAVELLING_THIEF_PROBLEM_ABSTRACTTEST_H
