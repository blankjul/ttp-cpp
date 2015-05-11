#include "item.h"


namespace ttp {

    const double Item::getWeight() const {
        return weight;
    }

    const double Item::getValue() const {
        return value;
    }


    std::ostream & operator<<(std::ostream &s, Item const &i) {
        s << "{value:" << i.getValue() << ",weight:" << i.getWeight() << "}";
        return s;
    }


}
