#include "tsp_lin_kernighan.h"
#include "wrapper/lkh_wrapper.h"
#include <algorithm>



using namespace std;

namespace ttp {


    Tour TSPLinKernighanSolver::solve(TSP &tsp) {

        MapPtr m = tsp.getMap();



        LKHWrapper lkh;
        int* ptr = lkh.calc(tsp.getMap());





        // HINT: increment all the indices because the lib is starting with index 1!
        // HINT: reorder that the tour is beginning with city 0!
        vector<int> result;
        vector<int> prefix;
        bool onlyPrefix = true;
        for (int j = 0; j < m->size(); ++j) {
            int value = ptr[j] - 1;
            if (ptr[j] == 1) onlyPrefix = false;
            if (onlyPrefix) prefix.push_back(value);
            else result.push_back(value);
        }
        std::move(prefix.begin(), prefix.end(), back_inserter(result));
        Tour t(result);

        return t;


    }








}