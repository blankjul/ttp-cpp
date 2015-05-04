#include "tour.h"

using namespace TTP;

int const& Tour::operator[](int index) const
{
    return v[index];
}

int Tour::size() const {
    return v.size();
}


