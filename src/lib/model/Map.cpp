#include "Map.h"
#include <limits>
#include <iomanip>

using namespace ttp;

Map::Map(int numOfCities) : Map(numOfCities, true) { }

Map::Map(int numOfCities, bool symmetrical) : symmetrical(symmetrical), costs(numOfCities) {
    for(int i = 0; i < size(); ++i) {
        costs[i] = vector<double>(numOfCities);
        for(int j = 0; j < size(); ++j) {
            if (i == j) costs[i][j] = 0;
            else costs[i][j] = numeric_limits<double>::max();
        }
    }
}


double Map::get(int i, int j) const {
    if (i >= size() || j >= size()) throw runtime_error("Out of bounds when asking for costs of the map.");
    else return costs[i][j];
}


bool Map::set(int i, int j, double value) {
    // there is no distance between the city itself
    if (i == j ) return false;
    else if (i >= size() || j >= size()) return false;
    else {
        costs[i][j] = value;
        if (symmetrical) costs[j][i] = value;
        return true;
    }
}


int Map::size() const {
    return costs.size();
}


std::ostream &operator<<(std::ostream &s, Map const &m) {
    s.precision(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            int value = m.get(i, j);
            s << setfill(' ') << setw(6) <<  value << " ";
        }
        s << '\n';
    }
    return s;
}

vector<double>& Map::operator[]( int index) {
    return costs[index];
}


