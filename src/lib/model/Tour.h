#ifndef TRAVELLING_THIEF_PROBLEM_TOUR_H
#define TRAVELLING_THIEF_PROBLEM_TOUR_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>


using namespace std;

namespace ttp {


    /*!
     * This class represents a tour that could be traveled by a salesman.
     *
     * Basically it is just a vector with integer values. But there are also some
     * additional functions like getting the symmetric tour or operator<< provided.
     *
     */
    class Tour {


        friend std::ostream & operator<<(std::ostream & s, Tour const & t);
        friend bool operator==( Tour const& lhs, Tour const& rhs) {
            return lhs.getVector() == rhs.getVector();
        }

    private:

        /*!< The vector that saves the order of the tour */
        vector<int> v;

    public:


        /**
         * Create a tour from a vector of integers.
         */
        Tour(const vector<int>& array) : v(array) {};

        /**
         * Return the city at the index of the tour.
         */
        int const& operator[](int) const;


        /**
         * Return how many cities are visited. (the home is only counting once)
         */
        int size() const;


        /**
         * Returns the symmetrical tour to this object. The starting city always stays the same.
         * e.g. [0,1,2,3] -> [0,3,2,1]
         */
        Tour getSymmetrical() const;


        //! return the vector representation
        const vector<int> &getVector() const;


        //! check if the tour is valid (only permuation and all cities are contained!
        bool isValid() const;



    };

    //! TourPtr for fast access
    typedef shared_ptr<Tour> TourPtr;



}

namespace std
{

    //! hash function for the tours.
    template <>
    struct hash<ttp::Tour>
    {
        size_t operator()(const ttp::Tour& t) const
        {
            std::size_t seed = 0;
            for(int i : t.getVector()) {
                const int value = i;
                seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

}


#endif //TRAVELLING_THIEF_PROBLEM_TOUR_H
