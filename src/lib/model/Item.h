#ifndef TRAVELLING_THIEF_PROBLEM_ITEM_H
#define TRAVELLING_THIEF_PROBLEM_ITEM_H

#include <string>
#include <iostream>
#include <memory>


namespace ttp {




    /*! This class represents an item that has a weight and a value. */
    class Item {

        friend std::ostream & operator<<(std::ostream &, Item const &);

    public:

        /**
         * Construct an item with a constant value and weight.
         */
        Item(const double v, const double w) : value(v), weight(w) { }

        /**
         * Returns the weight of the item.
         */
        const double getWeight() const;


        /**
         * Returns the value of the item
         */
        const double getValue() const;



    private:

        const double value;

        const double weight;


    };

    /**
     * Definition for using the shared pointer with ItemPtr
     */
    typedef std::shared_ptr<Item> ItemPtr;


    //! Create an ItemPtr quickly.
    static ItemPtr createItem(const double v, const double w) {
        ItemPtr ptr = std::make_shared<Item>(v,w);
        return ptr;
    }

}


#endif //TRAVELLING_THIEF_PROBLEM_ITEM_H
