#ifndef TRAVELLING_THIEF_PROBLEM_ALGORITHM_H
#define TRAVELLING_THIEF_PROBLEM_ALGORITHM_H


namespace ttp {

    template <typename Problem, typename Result>
    class Algorithm {

    public:

        virtual Result solve(Problem p) = 0;

    };

}




#endif //TRAVELLING_THIEF_PROBLEM_ALGORITHM_H
