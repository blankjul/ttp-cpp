#include "map.h"
#include <limits>

using namespace TTP;

Map::Map(const int numOfCities) : n(numOfCities) {
    double noConnection =  numeric_limits<double>::max();
    for (int i = 0; i < n; ++i) {
        vector<double> v;
        for (int j = 0; j < n; ++j) {
            v.push_back(noConnection);
        }
        costs.push_back(v);
    }
}


const double Map::get(int i, int j) {
    if (i >= n or j >= n) return numeric_limits<double>::max();
    return costs[i][j];
}

bool Map::set(int i, int j, double value) {
    if (i >= n or j >= n) return false;
    else {
        costs[i][j] = value;
        costs[j][i] = value;
        return true;
    }
}

double Map::getCosts(Tour t) {
    double result = 0;
    for(int i=1; i < t.size(); i++)
    {
        result += costs[t[i-1]][t[i]];
    }
    result += costs[t[t.size() - 1]][0];
    return result;
}

int Map::size() {
    return n;
}