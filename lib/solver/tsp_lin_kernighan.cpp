#include "tsp_lin_kernighan.h"
#include "wrapper/lkh_wrapper.h"


using namespace std;

namespace ttp {


    Tour TSPLinKernighanSolver::solve(TravellingSalesmanProblem &tsp) {

        MapPtr m = tsp.getMap();

        LKHWrapper lkh;
        int* ptr = lkh.calc(tsp.getMap());


        vector<int> result;
        for (int j = 0; j < m->count(); ++j) {
            result.push_back(ptr[j] - 1);
        }
        Tour t(result);

        return t;


    }








}