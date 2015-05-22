#include <fstream>
#include <limits>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "lkh_wrapper.h"


extern "C"
{
#include "LKH.h"
#include "Genetic.h"
#include "Heap.h"
#include "Interface.h"
}


namespace ttp {



    MapPtr LKHWrapper::createMap(std::string pathToFile) {


        TraceLevel = 0;
        if (verbose) cout << "READING " << pathToFile <<  std::endl;

        FILE* file = fopen(&(pathToFile[0]), "r");
        if (!file)
            throw std::runtime_error("File " + pathToFile + " does not exist");


        int** data = ReadTSPFile(file);


        /*
         * Parse the file and write the Map.
        */

        MapPtr map = make_shared<Map>(dim);


        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                if (i == j) map->set(i,j,0);
                else {
                    int value = data[i][j];
                    map->set(i,j,value);
                }
            }
        }
        return map;
    }




    int* LKHWrapper::calc(MapPtr map) {

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


        if (verbose) {
            char *Line;
            while ((Line = ReadLine(pf))) {
                cout << Line << std::endl;
            }
            fseek(pf, 0, SEEK_SET);
        }

        MaxMatrixDimension = 10000000;
        InitParameters();
        TraceLevel = 0;
        ReadProblemFromFile(pf);

        // search for the best tour
        findBest();

        fclose(pf);

        return BestTour;
    }


}