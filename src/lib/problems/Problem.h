

#ifndef TRAVELLING_THIEF_PROBLEM_PROBLEM_H
#define TRAVELLING_THIEF_PROBLEM_PROBLEM_H

namespace ttp {


   template <typename Input, typename Output>
   class Problem
   {

      virtual Output evaluate(Input&) = 0;


   };

}

#endif //TRAVELLING_THIEF_PROBLEM_PROBLEM_H
