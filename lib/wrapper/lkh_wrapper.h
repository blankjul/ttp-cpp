#ifndef TRAVELLING_THIEF_PROBLEM_LKH_H
#define TRAVELLING_THIEF_PROBLEM_LKH_H


#include "model/map.h"

struct LKH;


namespace ttp {

    class LKHWrapper {

    public:


        MapPtr createMap(std::string);

        int *calc(MapPtr map);

        bool verbose = false;

    };

}

#endif