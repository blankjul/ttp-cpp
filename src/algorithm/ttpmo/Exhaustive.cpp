#include "Exhaustive.h"
#include <algorithm>
#include "Util.h"

using namespace ttp;


TTPOutputSet mo::Exhaustive::solve(MOTTP ttp) {

    TTPOutputSet front;
    ThiefMapPtr m = ttp.getMap();

    // for all the possible tsp tours
    for (TourPtr t : allTours(m, true)) {

        for (KnapsackPtr k : allKnapsacks(m->getItems(), ttp.getMaxWeight())) {

            TTPInput input(*t,*k);
            TTPOutput p = ttp.evaluate(input);
            front.add(p);

        }
    }

    cout << front;

    return front;

}






