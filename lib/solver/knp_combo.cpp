
#include "knp_combo.h"

extern "C"
{
#include "combo.h"
}


using namespace std;




    ttp::Knapsack ttp::KNPComboSolver::solve(ttp::KnapsackProblem &knp) {



        std::vector<ItemPtr> items = knp.getItems();
        long sum = 0;
        vector<item> combo_items;


        for (int j = 0; j < items.size() ; ++j) {

            ItemPtr ptr = items[j];

            // create the new item
            item i;
            i.p = ptr->getValue();
            i.w = ptr->getWeight();
            i.x = 0;
            i.i = j;
            combo_items.push_back(i);

            sum += i.w;
        }

        //cout << "----------------\n";

        if (sum <= knp.getMaxWeight()) cout << "damn you are stupid. pick all items! \n" << knp.getMaxWeight() << "\n" << sum;


        item *f = &(*combo_items.begin());
        item *l = &(*combo_items.end());



        combo(f,l, knp.getMaxWeight(),1, 100,  true, true);


        Knapsack pack;

        vector<int> result;
        for (item i : combo_items) {

            // yeah we take this one!
            if (i.x) {

                // get int of the item
                int index = i.i;
                ItemPtr ptr = items[index];

                //cout << "[" << i.i << "] w:" << i.w << "," << "v:" << i.p << "  ->  " << *ptr << "\n";

                // pick that item
                pack.add(ptr);

            }
        }


        for (auto b :  knp.convertKnapsackToVector(pack)) {
            //cout << b;
        }



        return pack;

    }





