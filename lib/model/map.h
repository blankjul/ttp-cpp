#ifndef TRAVELLING_THIEF_PROBLEM_MAP_H
#define TRAVELLING_THIEF_PROBLEM_MAP_H

#include <vector>
#include <string>
#include "tour.h"

using namespace std;

namespace TTP {

    class Map {


    protected:

        vector<vector<double>> costs;

        const int n;



    public:

        Map(const int numOfCities);

        const double get(int i, int j);

        bool set(int i, int j, double value);

        double getCosts(Tour t);

        int size();



    };


}


#endif //TRAVELLING_THIEF_PROBLEM_MAP_H
