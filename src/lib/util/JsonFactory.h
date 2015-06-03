#ifndef TRAVELLING_THIEF_PROBLEM_JSONFACTORY_H
#define TRAVELLING_THIEF_PROBLEM_JSONFACTORY_H

#include "model/ThiefMap.h"
#include "model/Tour.h"
#include "model/Map.h"
#include "json/json.h"

namespace ttp {


    Json::Value toJson(const ttp::Tour& t);
    Json::Value toJson(const ttp::Map& m);
    Json::Value toJson(const ttp::ThiefMap& m);


}


#endif //TRAVELLING_THIEF_PROBLEM_JSONFACTORY_H
