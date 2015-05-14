#ifndef TRAVELLING_THIEF_PROBLEM_MAP_H
#define TRAVELLING_THIEF_PROBLEM_MAP_H

#include <vector>
#include <string>
#include <memory>
#include "tour.h"


using namespace std;

namespace ttp {


    /**
     * Definition for a matrix that is a vector of an vector.
     */
    typedef std::vector<std::vector<double>> Matrix;



    /*!
     * This class represents a map that contains cities and distances from one to each other.
     *
     * It saves the costs from one vertex or city to each other. The map is useful for getting symmetric access
     * to the costs or to evaluate the length of a specific tour.
     *
     */
    class Map {


    protected:

        double  **costs; /*!< Cost Matrix that saves the cost from one city to the other */

        const int n; /*!< Number of cities */

        bool symmetrical; /*!< If true it is always a symmetrical cost matrix! */



    public:



        /**
         * Creates a map that is symmetrical by default and provides n * n distances.
         *
         * Initial the matrix is like:
         *
         * [0   , -inf, -inf]
         * [-inf,    0, -inf]
         * [-inf, -inf,    0]
         *
         */
        Map(int numOfCities);

        /**
         * Creates a map that could also by asymmetrical -> ATSP.
         */
        Map(int numOfCities, bool symmetrical);


        /**
         * Return the costs if the salesman wants to travel from i to j.
         */
        double get(int i, int j) const;


        /**
         * Set the costs from i to j to the given value. Be aware of the symmetrical value!
         */
        bool set(int i, int j, double value);



        /**
         * Returns the number of cities.
         */
        int count() const;


        friend std::ostream & operator<<(std::ostream & s, Map const & t);



    };

    /**
     * Definition for using the shared pointer with ItemPtr
     */
    typedef std::shared_ptr<Map> MapPtr;


}


#endif //TRAVELLING_THIEF_PROBLEM_MAP_H
