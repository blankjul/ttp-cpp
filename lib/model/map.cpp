#include "map.h"
#include <limits>
#include <iomanip>

namespace TTP {

    Map::Map(int numOfCities) : Map(numOfCities, true) { }

    Map::Map(int numOfCities, bool symmetrical) : n(numOfCities), symmetrical(symmetrical) {
        double noConnection = numeric_limits<double>::max();
        for (int i = 0; i < n; ++i) {
            vector<double> v;
            for (int j = 0; j < n; ++j) {
                if (i == j) v.push_back(0);
                else v.push_back(noConnection);
            }
            costs.push_back(v);
        }
    }


    double Map::get(int i, int j) const {
        if (i >= n or j >= n) return numeric_limits<double>::max();
        return costs[i][j];
    }

    bool Map::set(int i, int j, double value) {
        if (i >= n or j >= n) return false;
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