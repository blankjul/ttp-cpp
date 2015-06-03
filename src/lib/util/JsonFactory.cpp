#include "JsonFactory.h"



Json::Value ttp::toJson(const ttp::Tour& t) {
    Json::Value object;
    for (int i : t.getVector()) object.append(i);
    return object;
}

Json::Value ttp::toJson(const ttp::Map& map) {
    Json::Value object;
    for (int i = 0; i < map.size(); ++i) {
        Json::Value row;
        for (int j = 0; j < map.size(); ++j) {
            row.append(map.get(i,j));
        }
        object.append(row);
    }
    return object;
}


Json::Value ttp::toJson(const ttp::ThiefMap& map) {
    Json::Value object;
    object["map"] = toJson( (ttp::Map) map);
    Json::Value jsonItems;
    Json::Value items;
    for (ThiefMap::const_iterator cit = map.begin(); cit != map.end(); ++cit) {
        Json::Value entry;
        entry["value"] = (*cit)->getValue();
        entry["weight"] = (*cit)->getWeight();
        entry["city"] = map.getCityOfItem(*cit);
        items.append(entry);
    }
    object["items"] = items;
    return object;
}
