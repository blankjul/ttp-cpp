#ifndef __JMetalAdapter__
#define __JMetalAdapter__

#include "core/Solution.h"
#include "core/Problem.h"
#include "problems/MOTTP.h"



using namespace std;


class JMetalProblem : public Problem {

private:

    ttp::MOTTP mottp;
   
public:
	JMetalProblem(ttp::MOTTP &mottp);
	~JMetalProblem();
	void evaluate(Solution *solution);
  
};

#endif /* __JMetalAdapter__ */
