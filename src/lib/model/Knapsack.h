#ifndef TRAVELLING_THIEF_PROBLEM_KNAPSACK_H
#define TRAVELLING_THIEF_PROBLEM_KNAPSACK_H

#include "Item.h"
#include <unordered_set>
#include <vector>



using namespace std;

namespace ttp {


    /*! This class represents the knapsack that could be filled with items.
     *
     * The pointer to items are saved in a set. The current weight und value
     * is provided by the class.
     *
     */
    class Knapsack {


    public:

        /**
         * Create an empty Knapsack without any items.
         */
        Knapsack() : weight(0), value(0) { };


        Knapsack(vector<ItemPtr> v) : Knapsack() {
            for (ItemPtr ptr : v) add(ptr);
        }

        template<typename ItemIterator>
        Knapsack(ItemIterator begin, ItemIterator end) : Knapsack() {
            for (ItemIterator it = begin; it != end; ++it) add(*it);
        }

        template<typename ItemIterator, typename BooleanIterator>
        Knapsack(ItemIterator ibegin, ItemIterator iend, BooleanIterator bbegin, BooleanIterator bend) : Knapsack() {
            fill(ibegin, iend, bbegin, bend);
        }

        /**
         * Add an item to the knapsack. Each item could only be once in a knapsack!
         */
        bool add(ItemPtr i);

        /**
         * Add an item to the knapsack.
         */
        bool remove(ItemPtr i);


        /**
         * Check wether an item is contained or not.
         */
        bool contains(ItemPtr i);

        /**
         * Returns the current number of items that are in the knapsack.
         */
        int size() const;


        /**
         * Returns the current value of all items -> Here is no renting rate considered.
         */
        double getValue() const;


        /**
         * Returns the current weight of all items.
         */
        double getWeight() const;


        /**
         * Returns all the items in the knapsack
         */
        const unordered_set<ItemPtr> &getItems() const;


        //! Picks items according to the input
        template<typename ItemIterator, typename BooleanIterator>
        void fill(ItemIterator ibegin, ItemIterator iend, BooleanIterator bbegin, BooleanIterator bend) {
            BooleanIterator bit = bbegin;
            ItemIterator iit = ibegin;
            for (; iit != iend && bit != bend; ++iit, ++bit) {
                if (*bit) add(*iit);
            }
            if (!(bit == bend && iit == iend)) throw runtime_error("Length error: different container sizes!");
        }

    private:


        unordered_set<ItemPtr> items;
        /*!< Set of all the items which were picked */

        double weight;
        /*!< current weight */

        double value; /*!< current value */


    };

    bool operator==( Knapsack const& lhs, Knapsack const& rhs);
    bool operator!=( Knapsack const& lhs, Knapsack const& rhs);
    std::ostream & operator<<(std::ostream &s, Knapsack const &k);




    //! TourPtr for fast access
    typedef shared_ptr<Knapsack> KnapsackPtr;

}


#endif //TRAVELLING_THIEF_PROBLEM_KNAPSACK_H
