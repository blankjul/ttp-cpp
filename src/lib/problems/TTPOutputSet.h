
#ifndef TRAVELLING_THIEF_PROBLEM_TTPSOLUTIONSET_H
#define TRAVELLING_THIEF_PROBLEM_TTPSOLUTIONSET_H

#include <iostream>
#include "TTPOutput.h"
#include <algorithm>

namespace ttp {



    class TTPOutputSet {


        friend std::ostream & operator<<(std::ostream &s, TTPOutputSet const & oset) {
            for(TTPOutput entry : oset) s << entry << endl;
            return s;
        }


    public:

        //! Define iterator for fast access to all items
        typedef vector<TTPOutput>::iterator iterator;
        typedef vector<TTPOutput>::const_iterator const_iterator;
        iterator begin() { return v.begin(); }
        const_iterator begin() const { return v.cbegin(); }
        iterator end() { return v.end(); }
        const_iterator end() const { return v.cend();}



        TTPOutputSet(){}


        void add(TTPOutput output) {
            if (isNonDominated(output)) {
                for (auto it : isDominatingIterators(output)) v.erase(it);
                v.push_back(output);
            }
        }


        bool isNonDominated(TTPOutput& other) {
            for (TTPOutput& o : v) if (o.isDominating(other)) return false;
            return true;
        }

        vector<TTPOutput> isDominating(TTPOutput& other) {
            vector<TTPOutput> result;
            for (auto it : isDominatingIterators(other)) result.push_back(*it);
            return result;
        }


        vector<iterator> isDominatingIterators(TTPOutput &other) {
            vector<iterator> result;
            for(iterator it = v.begin(); it != v.end(); ++it) {
                if (other.isDominating(*it) || other == *it) result.push_back(it);
            }
            return result;
        }


        const vector<TTPOutput> &getOutputs() const {
            return v;
        }

    private:

        vector<TTPOutput> v;


    };



}

#endif //TRAVELLING_THIEF_PROBLEM_TTPSOLUTION_H
