
#include "generator.h"
#include "model/map.h"
#include <iostream>
#include <iomanip>

extern "C"
{
#include "LKH.h"
}


namespace TTP {


    Map createMatrixFromTSPLIB(std::string pathToFile) {

        MaxMatrixDimension = 1000000;

        // set the filePtr
        char filePtr[1024];
        strncpy(filePtr, pathToFile.c_str(), sizeof(filePtr));
        filePtr[sizeof(filePtr) - 1] = 0;
        ProblemFileName = filePtr;

        ReadProblem();


        /*
         * Parse the faile and write the Map.
         */
        Map map(Dimension);

        Node *Ni, *Nj;
        Ni = FirstNode;

        int column = 0;

        do {
            int row = 0;
            if (Ni->C != 0) {
                for (Nj = FirstNode; Nj != Ni; Nj = Nj->Suc) {

                    int value = Fixed(Ni, Nj) ? 0 : Distance(Ni, Nj);

                    map.set(row,column,value);
                    ++row;
                }
            }

            Ni = Ni->Suc;
            ++column;
        }
        while (Ni != FirstNode);


        return map;


    }

}




