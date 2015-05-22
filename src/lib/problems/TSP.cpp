#include "TSP.h"
#include <cmath>

using namespace ttp;


double TSP::evaluate(Tour& t) {
    double result = 0;
    for(int i=1; i < t.size(); i++)
    {
        result += m->get(t[i-1],t[i]);
    }
    result += m->get(t[t.size() - 1],t[0]);
    return result;
}


const MapPtr&TSP::getMap() const {
    return m;
}


const int TSP::count() const {
    return m->size();
}

