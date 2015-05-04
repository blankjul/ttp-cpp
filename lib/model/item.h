#ifndef TRAVELLING_THIEF_PROBLEM_ITEM_H
#define TRAVELLING_THIEF_PROBLEM_ITEM_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace TTP {

    class Item {

    public:

        Item(const double v, const double w) : value(v), weight(w), name("NoName"){}
        Item(const double v, const double w, const string n) : value(v), weight(w), name(n) {}


        double getWeight() const {return weight;}

        double getValue() const {return value;}

        string getName() const {return name;}

        friend std::ostream & operator<<(std::ostream & s, Item const & i) {
            s << "[ " << i.name << ", weight: " << i.weight << " , value: " << i.value << " ]";
            return s;
        }


    private:

        string name;
        double value;
        double weight;


    };
}


#endif //TRAVELLING_THIEF_PROBLEM_ITEM_H
