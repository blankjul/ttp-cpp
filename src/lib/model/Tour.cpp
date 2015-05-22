#include "Tour.h"
#include <unordered_set>

namespace ttp {

    int const& Tour::operator[](int index) const
    {
        return v[index];
    }

    int Tour::size() const {
        return v.size();
    }


    std::ostream & operator<<(std::ostream & s, Tour const & t) {
        s << "[";
        for (int i = 0; i < t.v.size()-1; ++i)  s << t.v[i] << ",";
        s << t.v[t.size()-1] << "]";
        return s;
    }


    Tour Tour::getSymmetrical() const {
        std::vector<int> result;
        result.push_back(v[0]);
        for (int i = v.size()-1; i > 0; --i) {
            result.push_back(v[i]);
        }
        return Tour(result);
    }


    const vector<int> &Tour::getVector() const {
        return v;
    }


    bool Tour::isValid() const {
        // hash all the values
        unordered_set<int> hash;
        for (int i = 0; i < size(); ++i) {
            hash.insert(i);
        }
        // remove all values that are in the list
        for (int j = 0; j < size(); ++j) {
            hash.erase(v[j]);
        }
        return hash.empty();
    }
}