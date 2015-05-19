#include "map.h"
#include <limits>
#include <iomanip>

namespace ttp {

    Map::Map(int numOfCities) : Map(numOfCities, true) { }

    Map::Map(int numOfCities, bool symmetrical) : n(numOfCities), symmetrical(symmetrical) {
        costs = (double **)malloc(n * sizeof(double *));
        for(int i = 0; i < n; ++i) {
            costs[i] = (double *)malloc(n * sizeof(double));
            for(int j = 0; j < n; ++j) {
                if (i == j) costs[i][j] = 0;
                else costs[i][j] = numeric_limits<double>::max();
            }
        }
    }


    double Map::get(int i, int j) const {
        if (i >= n or j >= n) return numeric_limits<double>::max();
        return costs[i][j];
    }

    bool Map::set(int i, int j, double value) {
        // there is no distance between the city itself
        if (i == j ) return false;
        // out of bounds
        else if (i >= n or j >= n) return false;
        else {
            costs[i][j] = value;
            if (symmetrical) costs[j][i] = value;
            return true;
        }
    }


    int Map::count() const {
        return n;
    }

    std::ostream &operator<<(std::ostream &s, Map const &m) {
        s.precision(2);
        for (int i = 0; i < m.count(); ++i) {
            for (int j = 0; j < m.count(); ++j) {
                int value = m.get(i, j);
                s << setfill(' ') << setw(6) <<  value << " ";
            }
            s << '\n';
        }
        return s;
    }


}