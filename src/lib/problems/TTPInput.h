
#ifndef TRAVELLING_THIEF_PROBLEM_TTPINPUT_H
#define TRAVELLING_THIEF_PROBLEM_TTPINPUT_H

#include "model/Tour.h"
#include "model/Knapsack.h"
#include "model/ThiefMap.h"



namespace ttp {


    class TTPInput {



    public:


        TTPInput(Tour& t, Knapsack& k) : tour(t), knapsack(k) {}


        const Tour &getTour() const {
            return tour;
        }

        void setTour(const Tour &tour) {
            this->tour = tour;
        }

        const Knapsack &getKnapsack() const {
            return knapsack;
        }

        void setKnapsack(const Knapsack &knapsack) {
            this->knapsack = knapsack;
        }

        TTPInput static create(ThiefMapPtr ptr, vector<int> v, vector<int> p) {
            Knapsack k(ptr->begin(), ptr->end(), p.begin(), p.end());
            Tour t(v);
            TTPInput input(t,k);
            return input;
        }



    private:

        Tour tour;

        Knapsack knapsack;

    };





}

#endif //TRAVELLING_THIEF_PROBLEM_TTPINPUT_H
