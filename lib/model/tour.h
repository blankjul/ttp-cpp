#ifndef TRAVELLING_THIEF_PROBLEM_TOUR_H
#define TRAVELLING_THIEF_PROBLEM_TOUR_H

#include <vector>
#include <iostream>
#include <string>


using namespace std;

namespace TTP {

    class Tour {



    public:

        vector<int> v;

        Tour() {}
        Tour(vector<int>& v) : v(v) {};


        int const& operator[](int) const;

        int size() const;


        friend std::ostream & operator<<(std::ostream & s, Tour const & t) {
            s << "[";
            for (int i = 0; i < t.v.size()-1; ++i) {
                s << t.v[i] << ",";
            }
            s << t.v[t.size()-1] << "]";
            return s;
        }


    };
}


#endif //TRAVELLING_THIEF_PROBLEM_TOUR_H
