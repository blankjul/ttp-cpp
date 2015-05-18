#include "LKH.h"


/*
 * This file contains the main function of the program.
 */

int main(int argc, char *argv[]) {


    /* Read the specification of the problem */
    if (argc >= 2)
        ParameterFileName = argv[1];

    ReadParameters();
    MaxMatrixDimension = 10000;
    ReadProblem();

    int result =  findBest();

    return result;

}

