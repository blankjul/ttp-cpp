#ifndef TRAVELLING_THIEF_PROBLEM_JSONPARSER_H
#define TRAVELLING_THIEF_PROBLEM_JSONPARSER_H

#include "model/ThiefMap.h"
#include "model/Tour.h"
#include "model/Map.h"
#include "json/json.h"

namespace ttp {

    Json::Value parseTour(std::istream &is);


}

#endif //TRAVELLING_THIEF_PROBLEM_JSONPARSER_H
