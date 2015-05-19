#include "test_examples.h"
#include "experiments/generator.h"


using namespace ttp;

MapPtr exampleMap() {
    MapPtr m = make_shared<Map>(4);

    // set the weights
    m->set(0,1,5);
    m->set(0,2,6);
    m->set(0,3,6);
    m->set(1,2,5);
    m->set(1,3,6);
    m->set(2,3,4);
    return m;
}

vector<pair<ItemPtr,int>> exampleItemsLarge() {

    vector<pair<ItemPtr,int>> items;

    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(100,3),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(40,1),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(40,1),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(20,2),1));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(30,3),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(20,2),3));

    return items;

}

vector<pair<ItemPtr,int>> exampleItemsSmall() {

    vector<pair<ItemPtr,int>> items;

    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(10,3),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(4,1),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(4,1),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(2,2),1));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(3,3),2));
    items.push_back(make_pair<ItemPtr,int>(std::make_shared<Item>(2,2),3));

    return items;

}


TravellingSalesmanProblem berlin52() {
    return ProblemFactory::createTSPFromFile("../data/tsplib/berlin52.tsp");
}
