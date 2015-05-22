#ifndef TRAVELLING_THIEF_PROBLEM_THIEFMAP_H
#define TRAVELLING_THIEF_PROBLEM_THIEFMAP_H

#include <unordered_map>
#include "Map.h"
#include "Item.h"
#include "model/Item.h"



namespace ttp{

    class ThiefMap : public Map {

    protected:

        /*!< The mapping of cities and the item list */
        unordered_map<int, vector<ItemPtr>> items;
        unordered_map<ItemPtr, int> itemsmap;
        vector<ItemPtr> itemslist;

    public:

        //! Define iterator for fast access to all items
        typedef vector<ItemPtr>::iterator iterator;
        typedef vector<ItemPtr>::const_iterator const_iterator;
        iterator begin() { return itemslist.begin(); }
        const_iterator begin() const { return itemslist.cbegin(); }
        iterator end() { return itemslist.end(); }
        const_iterator end() const { return itemslist.cend();}


        ThiefMap(MapPtr map);

        ThiefMap(int numOfCities);


        //! Adds an Item to the given city
        void insert(int, ItemPtr);


        //! Insert multiple elements with an iterator
        template <typename Iterator>
        void insert(Iterator begin, Iterator end) {
            for(Iterator current = begin; current != end; ++current) {
                insert(current->first, current->second);
            }
        };

        //! returns an vector of all items at that city
        vector<ItemPtr> getItemsAtCity(int);

        //! calculate the travelling time from i to j regarding the current speed
        double calcTime(int i, int j, double speed);

        //! returns the city where is item is located
        int getCityOfItem(ItemPtr ptr);



    };

    //! smart pointer for access
    typedef std::shared_ptr<ThiefMap> ThiefMapPtr;
}

#endif //TRAVELLING_THIEF_PROBLEM_THIEFMAP_H
