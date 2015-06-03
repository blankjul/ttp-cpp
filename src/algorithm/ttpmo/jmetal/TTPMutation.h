
#ifndef __TTP_MUTATION__
#define __TTP_MUTATION__

#include "operators/mutation/Mutation.h"
#include "core/Solution.h"
#include <math.h>
#include <float.h>
#include "util/PseudoRandom.h"
#include "encodings/variable/Binary.h"

/**
  * @class Mutation
  * @brief This class implements a polynomial mutation operator.
**/
class TTPMutation : public Mutation {

public:
  TTPMutation(map<string, void *> parameters);
  ~TTPMutation();
  void * execute(void *);

private:
  double mutationProbability_;
  void * doMutation(double probability, Solution * solution);

}; // BitFlipMutation

#endif
