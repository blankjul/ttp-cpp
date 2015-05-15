#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include "generator/generator.h"
#include <fstream>
#include "solver/solver.h"
#include "solver/ttpmo_exhaustive_solver.h"


using namespace ttp;
using namespace std;

int main(int argc, char **argv) {

    // Wrap everything in a try block for catching exceptions.
    try {


        TCLAP::CmdLine cmd("The ttpgenerator is used to create Test Cases for the Travelling Thief Problem.", ' ',
                           "0.1");


        TCLAP::UnlabeledValueArg<std::string> argFilePath("ttpFile",
                                                          "Please insert the Path to a .ttp in the json format.", true,
                                                          "", "file.ttp");
        cmd.add(argFilePath);

        TCLAP::UnlabeledValueArg<std::string> argAlgorithm("algorithm",
                                                           "Please determine which algorithm should be used to solve the problem.",
                                                           false, "exhaustive", "algorithm");
        cmd.add(argAlgorithm);


        // Parse the argv array.
        cmd.parse(argc, argv);


        std::string filePath = argFilePath.getValue();
        std::string algorithm = argAlgorithm.getValue();

        ifstream jsonFile (filePath);

        TravellingThiefProblem ttp = TravellingThiefProblem::fromJson(jsonFile);


        shared_ptr<TTPMOSolver> s = NULL;


        if (algorithm == "exhaustive") {
            s = make_shared<TTPMOExhaustiveSolver>();
        }

        if (s == NULL) throw runtime_error("Algorithm not found.");

        s->solve(ttp);


    } catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
    catch (std::runtime_error &e)  // catch any exceptions
    { std::cerr << "ERROR: " << e.what() << std::endl; }


}