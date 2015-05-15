#ifndef TRAVELLING_THIEF_PROBLEM_TTP_H
#define TRAVELLING_THIEF_PROBLEM_TTP_H

#include <unordered_map>
#include "model/item.h"
#include "model/map.h"
#include "model/knapsack.h"



using namespace std;

namespace ttp {



    /*!
     * This class represents the travelling thief problem which occurs in two different version.
     *
     * There is the single objective and the multi objective version which has different
     * target and evaluation functions.
     *
     */
    class TravellingThiefProblem {



    protected:

        /*!< Minimal speed of the salesman */
        double minSpeed;

        /*!< Maximal speed of the salesman */
        double maxSpeed;

        /*!< Maximal weight of the knapsack */
        int maxWeight;

        /*!< The map that contains the cities and distances */
        MapPtr m;

        /*!< Renting rate for the SO */
        double rentingRate;

        /*!< Dropping rate for the MOP */
        double droppingRate;

        /*!< Dropping constant for the MOP */
        double droppingConstant;


        /*!< The mapping of cities and the item list */
        unordered_map<int, vector<ItemPtr>> itemsMap;

        /*!< List that knows the insertion order and could easily map each pointer to a city */
        vector<pair<ItemPtr, int>> items;



        /**
         * This is just a helper method for calculating the target. Since only the calculation
         * of the item values is different this calculates the time and collect the items picking time stamps.
         */
        void calcTour(Tour &t, Knapsack &k, double & currentTime , vector<pair<ItemPtr,double>> & pickedItems) ;



    public:


        /*!< Default maximal speed or velocity of the thief */
        static constexpr double DEFAULT_MAX_SPEED = 1;

        /*!< Default minimal speed or velocity of the thief */
        static constexpr double DEFAULT_MIN_SPEED = 0.1;

        /*!< SOP Default dropping rate per time unit of each item if nothing is specified */
        static constexpr double DEFAULT_RENTING_RATE = 1;

        /*!< MOP Default dropping rate per time unit of each item if nothing is specified */
        static constexpr double DEFAULT_DROPPING_RATE = 0.9;

        /*!< MOP Default constant for the exponent for the equation of the dropping rate */
        static constexpr double DEFAULT_DROPPING_CONSTANT = 10;


        /**
         * Constructor for the classes that inherit from this one.
         */
        TravellingThiefProblem(MapPtr map, int maxWeight) : minSpeed(TravellingThiefProblem::DEFAULT_MIN_SPEED),
                                                          maxSpeed(TravellingThiefProblem::DEFAULT_MAX_SPEED),
                                                            droppingRate(TravellingThiefProblem::DEFAULT_DROPPING_RATE),
                                                            droppingConstant(TravellingThiefProblem::DEFAULT_DROPPING_CONSTANT),
                                                            rentingRate(TravellingThiefProblem::DEFAULT_RENTING_RATE),
                                                          m(map),
                                                          maxWeight(maxWeight){}


        /**
         * Constructor for the classes that inherit from this one.
         *
         * The items are distributed to the cities automatically.
         */
        TravellingThiefProblem(MapPtr map, vector<ItemPtr>, int itemsPerCity, int maxWeight);

        /**
         * Add multpile items to this problem
         */
        void addItems(vector<pair<ItemPtr,int>>);

        /**
         * Converts a int vector to a knapsack.
         */
        Knapsack convertVectorToKnapsack(vector<int>);

        /**
         * Converts a knapsack to an int vector.
         */
        vector<int> convertKnapsackToVector(Knapsack &k);


        /**
         * Returns all items with mapping to the city.
         */
        const vector<pair<ItemPtr, int>> &getItems() const;


        /**
         * Returns all the items at the specific city.
         */
        vector<ItemPtr > getItems(int city);


        /**
         * Add an item to city. ATTENTION: One item could be added multiple times here.
         */
        void add(ItemPtr i, int city);


        /**
         * Returns the number of cities to visit
         */
        int sizeOfCities();

        /**
         * Returns the number of items to pick
         */
        int sizeOfItems();


        /**
         * Returns the Map where the thief travels on
         */
        const MapPtr &getMap() const;



        /**
         * Returns the value for the single objective problem.
         * \param t the tour of the thief.
         * \param k the items that are picked by the thief
         * \param rentingRate for the single objective value
         * \return value - R * time
         */
        double evaluateSO(Tour &t, Knapsack &k, double rentingRate = DEFAULT_RENTING_RATE);



        /**
         * Returns the value for the multi objective problem.
         *
         * \param t the tour of the thief.
         * \param k the items that are picked by the thief
         * \param droppingRate of the items
         * \param droppingConstant constant for calculate the drop
         * \return <time,value> as a MOP result
         */
        pair<double, double> evaluateMO(Tour &t, Knapsack &k, double droppingRate = DEFAULT_DROPPING_RATE, double droppingConstant = DEFAULT_DROPPING_CONSTANT);


        /**
         * fills the stream with a json representation of this object.
         */
        void toJson(std::ostream &s);

        /**
         * fills the stream with a json representation of this object.
         */
        static TravellingThiefProblem fromJson(std::istream &s);


        /*
         * Setter and Getter
         */
        double getMinSpeed() const;
        void  setMinSpeed(double minSpeed);
        double  getMaxSpeed() const;
        void  setMaxSpeed(double maxSpeed);
        int  getMaxWeight() const;
        void  setMaxWeight(int maxWeight);
        double getRentingRate() const;
        void setRentingRate(double rentingRate);
        double getDroppingRate() const;
        void setDroppingRate(double droppingRate);
        double getDroppingConstant() const;
        void setDroppingConstant(double droppingConstant);
        void setItems(const vector<pair<ItemPtr, int>> &items);
        vector<pair<ItemPtr, int>> getItemList();


    };


}


#endif //TRAVELLING_THIEF_PROBLEM_TTP_H
