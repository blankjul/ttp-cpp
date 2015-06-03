

#include "ThiefMap.h"

using namespace ttp;


ThiefMap::ThiefMap(int numOfCities) : Map(numOfCities) {
    for (int i = 0; i < numOfCities; ++i) {
        auto p = make_pair(i, vector<ItemPtr>());
        items.insert(p);
    }
}

ThiefMap::ThiefMap(MapPtr map): ThiefMap(map->size()) {
    for (int i = 0; i < map->size(); ++i) {
        for (int j = 0; j < map->size(); ++j) {
            costs[i][j] = (*map)[i][j];
        }
    }
}


void ThiefMap::insert(int city, ItemPtr ptr) {
    if (city == 0) throw std::runtime_error("The first city does not have any item!");
    if (city >= size()) throw std::runtime_error("This city does not exist!");

    auto it = items.find(city);
    it->second.push_back(ptr);
    itemslist.push_back(ptr);
    itemsmap.insert(make_pair(ptr, city));
}




vector<ItemPtr> ThiefMap::getItemsAtCity(int city) const{
    auto it = items.find(city);
    if (it == items.end()) return vector<ItemPtr>();
    else return vector<ItemPtr>(it->second);
}

double ThiefMap::calcTime(int i, int j, double speed)const {
    return get(i,j) / speed;
}


int ThiefMap::getCityOfItem(ItemPtr ptr) const{
    auto it = itemsmap.find(ptr);
    if (it == itemsmap.end()) return -1;
    else return it->second;
}

int ThiefMap::itemSize() const {
    return itemslist.size();
}

const vector<ItemPtr> &ThiefMap::getItems() const {
    return itemslist;
}
