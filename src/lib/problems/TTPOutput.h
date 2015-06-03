
#ifndef TRAVELLING_THIEF_PROBLEM_TTPSOLUTION_H
#define TRAVELLING_THIEF_PROBLEM_TTPSOLUTION_H

#include <iostream>

namespace ttp {


    /**
     * This is the solution object returned by an evaluation of the TTP problem.
     *
     * The aim is to provide for the MOP algorithm correct implement of >, < and == to
     * order the objects correctly.
     */
    class TTPOutput {


        friend bool operator==( TTPOutput const &left, TTPOutput const &right ) {
            return left.value == right.value && left.time == right.time;
        }

        friend bool operator!=( TTPOutput const &left, TTPOutput const &right ) {
            return !operator==(left,right);
        }

        friend bool operator<( TTPOutput const &left, TTPOutput const &right ) {
            return left.isDominatedBy(right);
        }

        friend std::ostream & operator<<(std::ostream &s, TTPOutput const &sol) {
            //cout.precision(15);
            s << fixed << "{time:" << sol.getTime() << ",value:" << sol.getValue() << "}";
            return s;
        }

    public:


        TTPOutput(double value, double time) : time(time), value(value) {}


        double getTime() const {
            return time;
        }

        double getValue() const {
            return value;
        }


        bool isDominatedBy(TTPOutput other) const {
            return other.time <= time && other.value >= value && *this != other;
        }


        bool isDominating(TTPOutput other) const {
            return time <=  other.getTime() && value >=  other.getValue() && *this != other;
        }


        bool isIndifferentTo(TTPOutput other) const {
            return isDominatedBy(other) == false && isDominating(other) == false;
        }



    private:

        double time;

        double value;

    };




}



#endif //TRAVELLING_THIEF_PROBLEM_TTPSOLUTION_H
