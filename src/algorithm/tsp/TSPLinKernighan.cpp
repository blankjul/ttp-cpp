#include "TSPLinKernighan.h"
#include <algorithm>


extern "C"
{
#include "LKH.h"
#include "Genetic.h"
#include "Heap.h"
}


using namespace std;
using namespace ttp;




Tour TSPLinKernighan::solve(TSP tsp) {

    MapPtr map = tsp.getMap();
    int n = map->size();
    FILE* pf = tmpfile();

    if (pf) {

        fputs("NAME: TEMPORARY\n", pf);
        fputs("TYPE: TSP\n", pf);
        fputs("COMMENT: No Comment\n", pf);

        fputs("DIMENSION: ", pf);
        fputs(std::to_string(n).c_str(), pf);
        fputs("\n", pf);

        fputs("EDGE_WEIGHT_TYPE: EXPLICIT\n", pf);
        fputs("EDGE_WEIGHT_FORMAT: FULL_MATRIX\n", pf);
        fputs("DISPLAY_DATA_TYPE: TWOD_DISPLAY\n", pf);
        fputs("EDGE_WEIGHT_SECTION\n", pf);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int value = map->get(i,j);
                fputs(std::to_string(value).c_str(), pf);
                fputs(" ", pf);
            }
            fputs("\n", pf);
        }
        fputs("EOF\n", pf);

    }

    fflush (pf);
    fseek(pf, 0, SEEK_SET);


    /*
    if (verbose) {
        char *Line;
        while ((Line = ReadLine(pf))) {
            cout << Line << std::endl;
        }
        fseek(pf, 0, SEEK_SET);
    }
     */

    MaxMatrixDimension = 10000000;
    InitParameters();
    TraceLevel = 0;
    ReadProblemFromFile(pf);

    // search for the best tour
    findBest();

    fclose(pf);


    // HINT: increment all the indices because the lib is starting with index 1!
    // HINT: reorder that the tour is beginning with city 0!
    vector<int> result;
    vector<int> prefix;
    bool onlyPrefix = true;
    for (int j = 0; j < map->size(); ++j) {
        int value = BestTour[j] - 1;
        if (BestTour[j] == 1) onlyPrefix = false;
        if (onlyPrefix) prefix.push_back(value);
        else result.push_back(value);
    }
    std::move(prefix.begin(), prefix.end(), back_inserter(result));
    Tour t(result);

    return t;


}







