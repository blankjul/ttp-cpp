
#include "generator/generator.h"




int main(int argc, char* argv[]) {



    std::string pathToFile = argv[1];

    TTP::createMatrixFromTSPLIB(pathToFile);

    return 0;


  }
