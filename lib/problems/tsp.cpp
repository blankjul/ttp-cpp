#include "tsp.h"
#include <cmath>

namespace ttp {


    double TravellingSalesmanProblem::evaluate(Tour &t) {
        double result = 0;
        for(int i=1; i < t.size(); i++)
        {
            result += m->get(t[i-1],t[i]);
        }
        result += m->get(t[t.size() - 1],t[0]);
        return result;
    }


    const MapPtr &TravellingSalesmanProblem::getMap() const {
        return m;
    }


    const int TravellingSalesmanProblem::count() const {
        return m->count();
    }
}
