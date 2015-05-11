#ifndef TRAVELLING_THIEF_PROBLEM_TSP_H
#define TRAVELLING_THIEF_PROBLEM_TSP_H

#include "model/map.h"


using namespace std;

namespace ttp {



    /*!
     * This class represents the travelling salesman problem. The shortest tour of a map that contains
     * each city only once should be found.
     */
    class TravellingSalesmanProblem {


    private:

        MapPtr m;  /*!< The map that contains the cities and distances */


    public:

        /**
         * Create a TSP on a specific map
         */
        TravellingSalesmanProblem(MapPtr &m) : m(m) {};


        /**
         * Evaluate a tour on this TSP.
         */
        double evaluate(Tour &t);


        /**
         * Returns the map of the TSP.
         */
        const MapPtr &getMap() const;


        /**
         * Returns the number of cities that are involved.
         */
        const int count() const;
    };


}


#endif //TRAVELLING_THIEF_PROBLEM_TSP_H
