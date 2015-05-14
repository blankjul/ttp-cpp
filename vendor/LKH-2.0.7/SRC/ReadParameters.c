#include "LKH.h"
#include "Genetic.h"

/*
 * The ReadParameters function reads the name of a parameter file from 
 * standard input and reads the problem parameters from this file.
 *
 * All entries of the parameter file are of the form <keyword >= <value> 
 * (or <keyword><whitespace><value>), where <keyword> denotes an alphanumeric
 * keyword and <value> denotes alphanumeric or numeric data. Keywords are not 
 * case sensitive. 
 *
 * The order of specifications in the file is arbitrary. The following 
 * specification is mandatory.
 *
 * PROBLEM_FILE = <string>
 * Specifies the name of the problem file.
 *
 * Additional control information may be supplied in the following format:
 *
 * ASCENT_CANDIDATES = <integer>
 * The number of candidate edges to be associated with each node during 
 * the ascent. The candidate set is complemented such that every candidate 
 * edge is associated with both its two end nodes.
 * Default: 50.
 *
 * BACKBONE_TRIALS = <integer>
 * The number of backbone trials in each run.
 * Default: 0.
 * 
 * BACKTRACKING = { YES | NO }
 * Specifies whether a backtracking K-opt move is to be used as the first 
 * move in a sequence of moves (where K = MOVE_TYPE). 
 * Default: NO.
 *
 * CANDIDATE_FILE = <string>
 * Specifies the name of a file to which the candidate sets are to be 
 * written. If, however, the file already exists, the candidate edges are 
 * read from the file. The first line of the file contains the number of
 * nodes. Each of the following lines contains a node number, the number of 
 * the dad of the node in the minimum spanning tree 
 * (0, if the node has no dad), the number of candidate edges emanating 
 * from the node, followed by the candidate edges. For each candidate edge 
 * its end node number and alpha-value are given.
 * It is possible to give more than one CANDIDATE_FILE specification. In this
 * case the given files are read and the union of their candidate edges is
 * used as candidate sets.
 *
 * CANDIDATE_SET_TYPE = { ALPHA | DELAUNAY [ PURE ] | NEAREST-NEIGHBOR | 
 *                        QUADRANT } 
 * Specifies the candidate set type. 
 * ALPHA is LKH's default type. It is applicable in general. 
 * The other four types can only be used for instances given by coordinates. 
 * The optional suffix PURE for the DELAUNAY type specifies that only 
 * edges of the Delaunay graph are used as candidates. 
 * Default: ALPHA.
 *
 * COMMENT <string>
 * A comment.
 *
 * # <string>
 * A comment.
 *
 * EOF
 * Terminates the input data. The entry is optional.
 *
 * EXCESS = <real>
 * The maximum alpha-value allowed for any candidate edge is set to 
 * EXCESS times the absolute value of the lower bound of a solution 
 * tour (determined by the ascent).
 * Default: value of 1.0/DIMENSION.
 *
 * EXTRA_CANDIDATES = <integer> [ SYMMETRIC ]
 * Number of extra candidate edges to be added to the candidate set
 * of each node. Their candidate set type may be specified after the
 * keyword EXTRA_CANDIDATE_SET_TYPE.
 * The integer may be followed by the keyword SYMMETRIC, signifying 
 * that these extra candidate edges is to be complemented such 
 * that each of them is associated with both its two end nodes. 
 * Default: 0
 *
 * EXTRA_CANDIDATE_SET_TYPE = { NEAREST-NEIGHBOR | QUADRANT } 
 * The candidate set type of extra candidate edges.
 * Default: QUADRANT                           
 *
 * GAIN23 = { YES | NO }
 * Specifies whether the Gain23 function is used.
 * Default: YES.
 *
 * GAIN_CRITERION = { YES | NO }
 * Specifies whether Lin and Kernighan's gain criterion is used.
 * Default: YES.
 *
 * INITIAL_PERIOD = <integer>
 * The length of the first period in the ascent.
 * Default: value of DIMENSION/2 (but at least 100). 
 *
 * INITIAL_STEP_SIZE = <integer>
 * The initial step size used in the ascent.
 * Default: 1.
 *
 * INITIAL_TOUR_ALGORITHM = { BORUVKA | GREEDY | MOORE | NEAREST-NEIGHBOR | 
 *                            QUICK-BORUVKA | SIERPINSKI | WALK }
 * Specifies the algorithm for obtaining an initial tour.
 * Default: WALK.
 *  
 * INITIAL_TOUR_FILE = <string>
 * Specifies the name of a file containing a tour to be used as the 
 * initial tour in the search. The tour is given by a list of integers 
 * giving the sequence in which the nodes are visited in the tour.
 * The tour is terminated by a -1.
 * See also INITIAL_TOUR_FRACTION.
 * 
 * INITIAL_TOUR_FRACTION = <real in [0;1]>
 * Specifies the fraction of the initial tour to be constructed by means 
 * of INITIAL_TOUR_FILE edges.
 * Default: 1.0  
 *
 * INPUT_TOUR_FILE = <string>
 * Specifies the name of a file containing a tour. The tour is used to 
 * limit the search (the last edge to be excluded in a non-gainful move 
 * must not belong to the tour). In addition, the Alpha field of its 
 * edges is set to zero. The tour is given by a list of integers giving 
 * the sequence in which the nodes are visited in the tour. The tour is 
 * terminated by a -1. 
 *
 * KICK_TYPE = <integer>
 * Specifies the value of K for a random K-swap kick. If KICK_TYPE is 
 * zero, then the LKH's special kicking strategy, WALK, is used.
 * Default: 0.
 *
 * KICKS = <integer>
 * Specifies the number of times to "kick" a tour found by Lin-Kernighan.
 * Each kick is a random K-swap-kick move. However, KICKS is zero, then 
 * LKH's special kicking strategy, WALK, is used.
 * Default: 1.
 *
 * MAX_BREADTH = <integer>
 * The maximum number of candidate edges considered at each level of 
 * the search for a move.
 * Default: INT_MAX. 
 *
 * MAX_CANDIDATES = <integer> [ SYMMETRIC ]
 * The maximum number of candidate edges to be associated with each node.
 * The integer may be followed by the keyword SYMMETRIC, signifying 
 * that the candidate set is to be complemented such that every candidate 
 * edge is associated with both its two end nodes. 
 * If MAX_CANDIDATES is zero the candidate sets are made up of the
 * edges represented in the CANDIDATE_FILEs, the INITIAL_TOUR_FILE, 
 * the INPUT_TOUR_FILE, the SUBPROBLEM_TOUR_FILE, and the MERGE_TOUR_FILEs.
 * Default: 5.
 *   
 * MAX_SWAPS = <integer>
 * Specifies the maximum number of swaps (flips) allowed in any search 
 * for a tour improvement.
 * Default: value of DIMENSION.
 *
 * MAX_TRIALS = <integer>
 * The maximum number of trials in each run.
 * Default: number of nodes (DIMENSION, given in the problem file).
 * 
 * MERGE_TOUR_FILE = <string>
 * Specifies the name of a tour to be merged. The edges of the tour are 
 * added to the candidate sets.
 * It is possible to give more than two MERGE_TOUR_FILE specifications. 
 *
 * MOVE_TYPE = <integer>
 * Specifies the sequential move type to be used as submove in Lin-Kernighan. 
 * A value K >= 2 signifies that a sequential K-opt move is used.
 * Default: 5.
 *
 * NONSEQUENTIAL_MOVE_TYPE = <integer>
 * Specifies the nonsequential move type to be used. A value K >= 4 
 * signifies that attempts are made to improve a tour by nonsequential 
 * k-opt moves where 4 <= k <= K. Note, however, that the effect depends
 * on the specifications of PATCHING_C and PATCHING_A. 
 * Default: value of (MOVE_TYPE + PATCHING_C + PATCHING_A - 1).
 *
 * OUTPUT_TOUR_FILE = <string>
 * Specifies the name of a file where the best tour is to be written.
 * Each time a trial has produced a new best tour, the tour is written 
 * to this file.  
 * The character '$' in the name has a special meaning. All occurrences
 * are replaced by the cost of the tour.      
 *
 * OPTIMUM = <integer>
 * Known optimal tour length. If STOP_AT_OPTIMUM is YES, a run will be 
 * terminated if the tour length becomes equal to this value.
 * Default: value of MINUS_INFINITY.
 *
 * PATCHING_A = <integer> [ RESTRICTED | EXTENDED ]
 * The maximum number of disjoint alternating cycles to be used for
 * patching. An attempt to patch cycles is made if the corresponding 
 * non-sequential move is gainful. 
 * The integer may be followed by the keyword RESTRICTED or EXTENDED.
 * The keyword RESTRICTED signifies that gainful moves are only
 * considered if all its inclusion edges are candidate edges.  
 * The keyword EXTENDED signifies that the non-sequential move need 
 * not be gainful if only all its inclusion edges are candidate edges.  
 * Default: 1.
 *     
 * PATCHING_C = <integer> [ RESTRICTED | EXTENDED ]
 * The maximum number of disjoint cycles to be patched in an attempt 
 * to find a feasible and gainful move. An attempt to patch cycles is 
 * made if the corresponding non-sequential move is gainful. 
 * The integer may be followed by the keyword RESTRICTED or EXTENDED.
 * The keyword RESTRICTED signifies that gainful moves are only
 * considered if all its inclusion edges are candidate edges.  
 * The keyword EXTENDED signifies that the non-sequential move need 
 * not be gainful if only all its inclusion edges are candidate edges. 
 * Default: 0.
 * 
 * PI_FILE = <string>
 * Specifies the name of a file to which penalties (Pi-values determined 
 * by the ascent) are to be written. If the file already exists, the 
 * penalties are read from the file, and the ascent is skipped. 
 * The first line of the file contains the number of nodes. Each of the 
 * following lines is of the form
 *       <integer> <integer>
 * where the first integer is a node number, and the second integer is 
 * the Pi-value associated with the node.
 * The file name "0" represents a file with all Pi-values equal to zero.
 *
 * POPULATION_SIZE = <integer>
 * Specifies the maximum size of the population in the genetic algorithm.
 * Default: 0.
 *
 * PRECISION = <integer>
 * The internal precision in the representation of transformed distances: 
 *    d[i][j] = PRECISION*c[i][j] + pi[i] + pi[j], 
 * where d[i][j], c[i][j], pi[i] and pi[j] are all integral. 
 * Default: 100 (which corresponds to 2 decimal places).
 *  
 * RESTRICTED_SEARCH = { YES | NO }
 * Specifies whether the following search pruning technique is used: 
 * The first edge to be broken in a move must not belong to the currently 
 * best solution tour. When no solution tour is known, it must not belong 
 * to the minimum spanning 1-tree.     
 * Default: YES. 
 * 
 * RUNS = <integer>
 * The total number of runs. 
 * Default: 10.
 *
 * SEED = <integer>
 * Specifies the initial seed for random number generation. If zero, the
 * seed is derived from the system clock.
 * Default: 1.
 *
 * STOP_AT_OPTIMUM = { YES | NO }
 * Specifies whether a run is stopped, if the tour length becomes equal 
 * to OPTIMUM.
 * Default: YES.
 * 
 * SUBGRADIENT = { YES | NO }
 * Specifies whether the Pi-values should be determined by subgradient 
 * optimization.
 * Default: YES.
 *
 * SUBPROBLEM_SIZE = <integer> [ DELAUNAY | KARP | K-CENTER | K-MEANS | MOORE |
 *                               ROHE | SIERPINSKI ] [ BORDERS ] [ COMPRESSED ] 
 * The number of nodes in a division of the original problem into subproblems.
 * The division is made according to the tour given by SUBPROBLEM_TOUR_FILE. 
 * The value 0 signifies that no division is made. 
 * By default the subproblems are determined by subdividing the tour into 
 * segments of equal size. However, the integer may be followed by DELAUNAY, 
 * KARP, K-CENTER, K-MEANS, MOORE, ROHE or SIERPINSKI. DELAUNAY specifies that 
 * the Delaunay partitioning scheme is used, KARP that Karp's partitioning 
 * scheme is used, K-CENTER that a partitioning scheme based on K-center 
 * clustering, K-MEANS that a partitioning scheme based on K-means clustering 
 * is used, ROHE that Rohe's random rectange partitining scheme is used, and 
 * MOORE or SIERPINSKI that a partitioning scheme based on either a Moore or 
 * Sierpinski space-filling curve is used.
 * The BORDERS specification signifies that the subproblems along the borders 
 * between subproblems are to be solved too.
 * The COMPRESSED specification signifies that each subproblem is compressed by 
 * removing from the problem all nodes with two incident subproblem tour edges 
 * that belong to all tours to be merged (at least two MERGE_TOUR_FILEs should 
 * be given).
 * Default: 0.
 *  
 * SUBPROBLEM_TOUR_FILE = <string>
 * Specifies the name of a file containing a tour to be used for dividing
 * the original problem into subproblems. The approximate number of nodes 
 * in each is * given by SUBPROBLEM_SIZE. 
 * The tour is given by a list of integers giving the sequence in which the 
 * nodes are visited in the tour. The tour is terminated by a -1
 *   
 * SUBSEQUENT_MOVE_TYPE = <integer>
 * Specifies the move type to be used for all moves following the first move 
 * in a sequence of moves. The value K >= 2 signifies that a K-opt move is to 
 * be used. The value 0 signifies that all moves are of the same type 
 * (K = MOVE_TYPE).
 * Default: 0.
 * 
 * SUBSEQUENT_PATCHING = { YES | NO }
 * Specifies whether patching is used for moves following the first move 
 * in a sequence of moves.
 * Default: YES.
 *
 * TIME_LIMIT = <real>
 * Specifies a time limit in seconds for each run.
 * Default: value of DBL_MAX. 
 *
 * TOUR_FILE = <string>
 * Specifies the name of a file where the best tour is to be written.
 * When a run has produced a new best tour, the tour is written to 
 * this file.
 * The character '$' in the name has a special meaning. All occurrences
 * are replaced by the cost of the tour. 
 *
 * TRACE_LEVEL = <integer>
 * Specifies the level of detail of the output given during the solution 
 * process. The value 0 signifies a minimum amount of output. The higher 
 * the value is the more information is given.
 * Default: 1. 
 *
 * List of abbreviations
 * ---------------------
 *
 * A string value may be abbreviated to the first few letters of the string, 
 * if that abbreviation is unambiguous.
 *
 *     Value        Abbreviation
 *     ALPHA             A
 *     BORDERS           B
 *     BORUVKA           B
 *     COMPRESSED        C
 *     DELAUNAY          D
 *     EXTENDED          E
 *     GREEDY            G
 *     KARP              KA
 *     K-CENTER          K-C
 *     K-MEANS           K-M
 *     MOORE             M
 *     NEAREST-NEIGHBOR  N
 *     NO                N
 *     PURE              P
 *     QUADRANT          Q
 *     QUICK-BORUVKA     Q
 *     RESTRICTED        R
 *     ROHE              R
 *     SIERPINSKI        S
 *     SYMMETRIC         S
 *     WALK              W
 *     YES               Y    
 */

static char Delimiters[] = "= \n\t\r\f\v\xef\xbb\xbf";
static char *GetFileName(char *Line);
static char *ReadYesOrNo(int *V);
#undef max
static size_t max(size_t a, size_t b);



void InitParameters() {


    lkh.ProblemFileName = lkh.PiFileName = lkh.InputTourFileName =
    lkh.OutputTourFileName = lkh.TourFileName = 0;
    lkh.CandidateFiles = lkh.MergeTourFiles = 0;
    lkh.AscentCandidates = 50;
    lkh.BackboneTrials = 0;
    lkh.Backtracking = 0;
    lkh.CandidateSetSymmetric = 0;
    lkh.CandidateSetType = ALPHA;
    lkh.Crossover = ERXT;
    lkh.DelaunayPartitioning = 0;
    lkh.DelaunayPure = 0;
    lkh.Excess = -1;
    lkh.ExtraCandidates = 0;
    lkh.ExtraCandidateSetSymmetric = 0;
    lkh.ExtraCandidateSetType = QUADRANT;
    lkh.Gain23Used = 1;
    lkh.GainCriterionUsed = 1;
    lkh.InitialPeriod = -1;
    lkh.InitialStepSize = 0;
    lkh.InitialTourAlgorithm = WALK;
    lkh.InitialTourFraction = 1.0;
    lkh.KarpPartitioning = 0;
    lkh.KCenterPartitioning = 0;
    lkh.KMeansPartitioning = 0;
    lkh.Kicks = 1;
    lkh.KickType = 0;
    lkh.MaxBreadth = INT_MAX;
    lkh.MaxCandidates = 5;
    lkh.MaxPopulationSize = 0;
    lkh.MaxSwaps = -1;
    lkh.MaxTrials = -1;
    lkh.MoorePartitioning = 0;
    lkh.MoveType = 5;
    lkh.NonsequentialMoveType = -1;
    lkh.Optimum = MINUS_INFINITY;
    lkh.PatchingA = 3;
    lkh.PatchingC = 2;
    lkh.PatchingAExtended = 0;
    lkh.PatchingARestricted = 0;
    lkh.PatchingCExtended = 0;
    lkh.PatchingCRestricted = 0;
    lkh.Precision = 100;
    lkh.RestrictedSearch = 1;
    lkh.RohePartitioning = 0;
    lkh.Runs = 10;
    lkh.Seed = 1;
    lkh.SierpinskiPartitioning = 0;
    lkh.StopAtOptimum = 1;
    lkh.Subgradient = 1;
    lkh.SubproblemBorders = 0;
    lkh.SubproblemsCompressed = 0;
    lkh.SubproblemSize = 0;
    lkh.SubsequentMoveType = 0;
    lkh.SubsequentPatching = 1;
    lkh.TimeLimit = DBL_MAX;
    lkh.TraceLevel = 1;
}



void ReadParameters()
{
    InitParameters();

    char *Line, *Keyword, *Token, *Name;
    unsigned int i;

    if (lkh.ParameterFileName) {
        if (!(lkh.ParameterFile = fopen(lkh.ParameterFileName, "r")))
            eprintf("Cannot open PARAMETER_FILE: \"%s\"",
                    lkh.ParameterFileName);
        printff("PARAMETER_FILE = %s\n", lkh.ParameterFileName);
    } else {
        while (1) {
            printff("PARAMETER_FILE = ");
            if (!(lkh.ParameterFileName = GetFileName(ReadLine(stdin)))) {
                do {
                    printff("PROBLEM_FILE = ");
                    lkh.ProblemFileName = GetFileName(ReadLine(stdin));
                } while (!lkh.ProblemFileName);
                return;
            } else if (!(lkh.ParameterFile = fopen(lkh.ParameterFileName, "r")))
                printff("Cannot open \"%s\". Please try again.\n",
                        lkh.ParameterFileName);
            else
                break;
        }
    }
    while ((Line = ReadLine(lkh.ParameterFile))) {
        if (!(Keyword = strtok(Line, Delimiters)))
            continue;
        if (Keyword[0] == '#')
            continue;
        for (i = 0; i < strlen(Keyword); i++)
            Keyword[i] = (char) toupper(Keyword[i]);
        if (!strcmp(Keyword, "ASCENT_CANDIDATES")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.AscentCandidates))
                eprintf("ASCENT_CANDIDATES: integer expected");
            if (lkh.AscentCandidates < 2)
                eprintf("ASCENT_CANDIDATES: >= 2 expected");
        } else if (!strcmp(Keyword, "BACKBONE_TRIALS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.BackboneTrials))
                eprintf("BACKBONE_TRIALS: integer expected");
            if (lkh.BackboneTrials < 0)
                eprintf("BACKBONE_TRIALS: non-negative integer expected");
        } else if (!strcmp(Keyword, "BACKTRACKING")) {
            if (!ReadYesOrNo(&lkh.Backtracking))
                eprintf("BACKTRACKING: YES or NO expected");
        } else if (!strcmp(Keyword, "CANDIDATE_FILE")) {
            if (!(Name = GetFileName(0)))
                eprintf("CANDIDATE_FILE: string expected");
            if (lkh.CandidateFiles == 0) {
                assert(lkh.CandidateFileName =
                       (char **) malloc(sizeof(char *)));
                lkh.CandidateFileName[lkh.CandidateFiles++] = Name;
            } else {
                int i;
                for (i = 0; i < lkh.CandidateFiles; i++)
                    if (!strcmp(Name, lkh.CandidateFileName[i]))
                        break;
                if (i == lkh.CandidateFiles) {
                    assert(lkh.CandidateFileName =
                           (char **) realloc(lkh.CandidateFileName,
                                             (lkh.CandidateFiles +
                                              1) * sizeof(char *)));
                    lkh.CandidateFileName[lkh.CandidateFiles++] = Name;
                }
            }
        } else if (!strcmp(Keyword, "CANDIDATE_SET_TYPE")) {
            if (!(Token = strtok(0, Delimiters)))
                eprintf("%s", "CANDIDATE_SET_TYPE: "
                        "ALPHA, DELAUNAY, NEAREST-NEIGHBOR, "
                        "or QUADRANT expected");
            for (i = 0; i < strlen(Token); i++)
                Token[i] = (char) toupper(Token[i]);
            if (!strncmp(Token, "ALPHA", strlen(Token)))
                lkh.CandidateSetType = ALPHA;
            else if (!strncmp(Token, "DELAUNAY", strlen(Token))) {
                lkh.CandidateSetType = DELAUNAY;
            } else if (!strncmp(Token, "NEAREST-NEIGHBOR", strlen(Token)))
                lkh.CandidateSetType = NN;
            else if (!strncmp(Token, "QUADRANT", strlen(Token)))
                lkh.CandidateSetType = QUADRANT;
            else
                eprintf("%s", "CANDIDATE_SET_TYPE: "
                        "ALPHA, DELAUNAY, NEAREST-NEIGHBOR, "
                        "or QUADRANT expected");
            if (lkh.CandidateSetType == DELAUNAY) {
                if ((Token = strtok(0, Delimiters))) {
                    for (i = 0; i < strlen(Token); i++)
                        Token[i] = (char) toupper(Token[i]);
                    if (strncmp(Token, "PURE", strlen(Token)))
                        eprintf("%s", "CANDIDATE_SET_TYPE (DELAUNAY): "
                                "PURE or no token expected");
                    lkh.DelaunayPure = 1;
                }
            }
        } else if (!strcmp(Keyword, "COMMENT"))
            continue;
        else if (!strcmp(Keyword, "EOF"))
            break;
        else if (!strcmp(Keyword, "EXCESS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%lf", &lkh.Excess))
                eprintf("EXCESS: real expected");
            if (lkh.Excess < 0)
                eprintf("EXCESS: non-negeative real expected");
        } else if (!strcmp(Keyword, "EXTRA_CANDIDATES")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.ExtraCandidates))
                eprintf("EXTRA_CANDIDATES: integer expected");
            if (lkh.ExtraCandidates < 0)
                eprintf("EXTRA_CANDIDATES: non-negative integer expected");
            if ((Token = strtok(0, Delimiters))) {
                for (i = 0; i < strlen(Token); i++)
                    Token[i] = (char) toupper(Token[i]);
                if (strncmp(Token, "SYMMETRIC", strlen(Token)))
                    eprintf
                        ("(EXTRA_CANDIDATES) Illegal SYMMETRIC specification");
                lkh.ExtraCandidateSetSymmetric = 1;
            }
        } else if (!strcmp(Keyword, "EXTRA_CANDIDATE_SET_TYPE")) {
            if (!(Token = strtok(0, Delimiters)))
                eprintf("%s", "EXTRA_CANDIDATE_SET_TYPE: "
                        "NEAREST-NEIGHBOR, or QUADRANT expected");
            for (i = 0; i < strlen(Token); i++)
                Token[i] = (char) toupper(Token[i]);
            if (!strncmp(Token, "NEAREST-NEIGHBOR", strlen(Token)))
                lkh.ExtraCandidateSetType = NN;
            else if (!strncmp(Token, "QUADRANT", strlen(Token)))
                lkh.ExtraCandidateSetType = QUADRANT;
            else
                eprintf("%s", "EXTRA_CANDIDATE_SET_TYPE: "
                        "NEAREST-NEIGHBOR or QUADRANT expected");
        } else if (!strcmp(Keyword, "GAIN23")) {
            if (!ReadYesOrNo(&lkh.Gain23Used))
                eprintf("GAIN23: YES or NO expected");
        } else if (!strcmp(Keyword, "GAIN_CRITERION")) {
            if (!ReadYesOrNo(&lkh.GainCriterionUsed))
                eprintf("GAIN_CRITERION: YES or NO expected");
        } else if (!strcmp(Keyword, "INITIAL_PERIOD")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.InitialPeriod))
                eprintf("INITIAL_PERIOD: integer expected");
            if (lkh.InitialPeriod < 0)
                eprintf("INITIAL_PERIOD: non-negative integer expected");
        } else if (!strcmp(Keyword, "INITIAL_STEP_SIZE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.InitialStepSize))
                eprintf("INITIAL_STEP_SIZE: integer expected");
            if (lkh.InitialStepSize <= 0)
                eprintf("INITIAL_STEP_SIZE: positive integer expected");
        } else if (!strcmp(Keyword, "INITIAL_TOUR_ALGORITHM")) {
            if (!(Token = strtok(0, Delimiters)))
                eprintf("INITIAL_TOUR_ALGORITHM: "
                        "BORUVKA, GREEDY, MOORE, NEAREST-NEIGHBOR,\n"
                        "QUICK-BORUVKA, SIERPINSKI, or WALK expected");
            for (i = 0; i < strlen(Token); i++)
                Token[i] = (char) toupper(Token[i]);
            if (!strncmp(Token, "BORUVKA", strlen(Token)))
                lkh.InitialTourAlgorithm = BORUVKA;
            else if (!strncmp(Token, "GREEDY", strlen(Token)))
                lkh.InitialTourAlgorithm = GREEDY;
            else if (!strncmp(Token, "MOORE", strlen(Token)))
                lkh.InitialTourAlgorithm = MOORE;
            else if (!strncmp(Token, "NEAREST-NEIGHBOR", strlen(Token)))
                lkh.InitialTourAlgorithm = NEAREST_NEIGHBOR;
            else if (!strncmp(Token, "QUICK-BORUVKA", strlen(Token)))
                lkh.InitialTourAlgorithm = QUICK_BORUVKA;
            else if (!strncmp(Token, "SIERPINSKI", strlen(Token)))
                lkh.InitialTourAlgorithm = SIERPINSKI;
            else if (!strncmp(Token, "WALK", strlen(Token)))
                lkh.InitialTourAlgorithm = WALK;
            else
                eprintf("INITIAL_TOUR_ALGORITHM: "
                        "BORUVKA, GREEDY, MOORE, NEAREST-NEIGHBOR,\n"
                        "QUICK-BORUVKA, SIERPINSKI or WALK expected");
        } else if (!strcmp(Keyword, "INITIAL_TOUR_FILE")) {
            if (!(lkh.InitialTourFileName = GetFileName(0)))
                eprintf("INITIAL_TOUR_FILE: string expected");
        } else if (!strcmp(Keyword, "INITIAL_TOUR_FRACTION")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%lf", &lkh.InitialTourFraction))
                eprintf("INITIAL_TOUR_FRACTION: real expected");
            if (lkh.InitialTourFraction < 0 || lkh.InitialTourFraction > 1)
                eprintf("INITIAL_TOUR_FRACTION: >= 0 or <= 1 expected");
        } else if (!strcmp(Keyword, "INPUT_TOUR_FILE")) {
            if (!(lkh.InputTourFileName = GetFileName(0)))
                eprintf("INPUT_TOUR_FILE: string expected");
        } else if (!strcmp(Keyword, "KICK_TYPE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.KickType))
                eprintf("KICK_TYPE: integer expected");
            if (lkh.KickType != 0 && lkh.KickType < 4)
                eprintf("KICK_TYPE: integer >= 4 expected");
        } else if (!strcmp(Keyword, "KICKS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.Kicks))
                eprintf("KICKS: integer expected");
            if (lkh.Kicks < 0)
                eprintf("KICKS: non-negative integer expected");
        } else if (!strcmp(Keyword, "MAX_BREADTH")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MaxBreadth))
                eprintf("MAX_BREADTH: integer expected");
            if (lkh.MaxBreadth < 0)
                eprintf("MAX_BREADTH: non-negative integer expected");
        } else if (!strcmp(Keyword, "MAX_CANDIDATES")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MaxCandidates))
                eprintf("MAX_CANDIDATES: integer expected");
            if (lkh.MaxCandidates < 0)
                eprintf("MAX_CANDIDATES: non-negative integer expected");
            if ((Token = strtok(0, Delimiters))) {
                for (i = 0; i < strlen(Token); i++)
                    Token[i] = (char) toupper(Token[i]);
                if (!strncmp(Token, "SYMMETRIC", strlen(Token)))
                    lkh.CandidateSetSymmetric = 1;
                else
                    eprintf
                        ("(MAX_CANDIDATES) Illegal SYMMETRIC specification");
            }
        } else if (!strcmp(Keyword, "MAX_SWAPS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MaxSwaps))
                eprintf("MAX_SWAPS: integer expected");
            if (lkh.MaxSwaps < 0)
                eprintf("MAX_SWAPS: non-negative integer expected");
        } else if (!strcmp(Keyword, "MAX_TRIALS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MaxTrials))
                eprintf("MAX_TRIALS: integer expected");
            if (lkh.MaxTrials < 0)
                eprintf("MAX_TRIALS: non-negative integer expected");
        } else if (!strcmp(Keyword, "MERGE_TOUR_FILE")) {
            if (!(Name = GetFileName(0)))
                eprintf("MERGE_TOUR_FILE: string expected");
            if (lkh.MergeTourFiles == 0) {
                assert(lkh.MergeTourFileName =
                       (char **) malloc(sizeof(char *)));
                lkh.MergeTourFileName[lkh.MergeTourFiles++] = Name;
            } else {
                int i;
                for (i = 0; i < lkh.MergeTourFiles; i++)
                    if (!strcmp(Name, lkh.MergeTourFileName[i]))
                        break;
                if (i == lkh.MergeTourFiles) {
                    assert(lkh.MergeTourFileName =
                           (char **) realloc(lkh.MergeTourFileName,
                                             (lkh.MergeTourFiles +
                                              1) * sizeof(char *)));
                    lkh.MergeTourFileName[lkh.MergeTourFiles++] = Name;
                }
            }
        } else if (!strcmp(Keyword, "MOVE_TYPE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MoveType))
                eprintf("MOVE_TYPE: integer expected");
            if (lkh.MoveType < 2)
                eprintf("MOVE_TYPE: >= 2 expected");
        } else if (!strcmp(Keyword, "NONSEQUENTIAL_MOVE_TYPE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.NonsequentialMoveType))
                eprintf("NONSEQUENTIAL_MOVE_TYPE: integer expected");
            if (lkh.NonsequentialMoveType < 4)
                eprintf("NONSEQUENTIAL_MOVE_TYPE: >= 4 expected");
        } else if (!strcmp(Keyword, "OPTIMUM")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, GainInputFormat, &lkh.Optimum))
                eprintf("OPTIMUM: integer expected");
        } else if (!strcmp(Keyword, "OUTPUT_TOUR_FILE")) {
            if (!(lkh.OutputTourFileName = GetFileName(0)))
                eprintf("OUTPUT_TOUR_FILE: string expected");
        } else if (!strcmp(Keyword, "PATCHING_A")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.PatchingA))
                eprintf("PATCHING_A: integer expected");
            if (lkh.PatchingA < 0)
                eprintf("PATCHING_A: non-negative integer expected");
            if ((Token = strtok(0, Delimiters))) {
                for (i = 0; i < strlen(Token); i++)
                    Token[i] = (char) toupper(Token[i]);
                if (!strncmp(Token, "RESTRICTED", strlen(Token)))
                    lkh.PatchingARestricted = 1;
                else if (!strncmp(Token, "EXTENDED", strlen(Token)))
                    lkh.PatchingAExtended = 1;
                else
                    eprintf("%s", "(PATCHING_A) "
                            "Illegal RESTRICTED or EXTENDED specification");
            }
        } else if (!strcmp(Keyword, "PATCHING_C")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.PatchingC))
                eprintf("PATCHING_C: integer expected");
            if (lkh.PatchingC < 0)
                eprintf("PATCHING_C: non-negative integer expected");
            if ((Token = strtok(0, Delimiters))) {
                for (i = 0; i < strlen(Token); i++)
                    Token[i] = (char) toupper(Token[i]);
                if (!strncmp(Token, "RESTRICTED", strlen(Token)))
                    lkh.PatchingCRestricted = 1;
                else if (!strncmp(Token, "EXTENDED", strlen(Token)))
                    lkh.PatchingCExtended = 1;
                else
                    eprintf("%s", "(PATCHING_C) ",
                            "Illegal RESTRICTED or EXTENDED specification");
            }
        } else if (!strcmp(Keyword, "PI_FILE")) {
            if (!(lkh.PiFileName = GetFileName(0)))
                eprintf("PI_FILE: string expected");
        } else if (!strcmp(Keyword, "POPULATION_SIZE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.MaxPopulationSize))
                eprintf("POPULATION_SIZE: integer expected");
        } else if (!strcmp(Keyword, "PRECISION")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.Precision))
                eprintf("PRECISION: integer expected");
        } else if (!strcmp(Keyword, "PROBLEM_FILE")) {
            if (!(lkh.ProblemFileName = GetFileName(0)))
                eprintf("PROBLEM_FILE: string expected");
        } else if (!strcmp(Keyword, "RESTRICTED_SEARCH")) {
            if (!ReadYesOrNo(&lkh.RestrictedSearch))
                eprintf("RESTRICTED_SEARCH: YES or NO expected");
        } else if (!strcmp(Keyword, "RUNS")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.Runs))
                eprintf("RUNS: integer expected");
            if (lkh.Runs <= 0)
                eprintf("RUNS: positive integer expected");
        } else if (!strcmp(Keyword, "SEED")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%u", &lkh.Seed))
                eprintf("SEED: integer expected");
        } else if (!strcmp(Keyword, "STOP_AT_OPTIMUM")) {
            if (!ReadYesOrNo(&lkh.StopAtOptimum))
                eprintf("STOP_AT_OPTIMUM: YES or NO expected");
        } else if (!strcmp(Keyword, "SUBGRADIENT")) {
            if (!ReadYesOrNo(&lkh.Subgradient))
                eprintf("SUBGRADIENT: YES or NO expected");
        } else if (!strcmp(Keyword, "SUBPROBLEM_TOUR_FILE")) {
            if (!(lkh.SubproblemTourFileName = GetFileName(0)))
                eprintf("SUBPROBLEM_TOUR_FILE: string expected");
        } else if (!strcmp(Keyword, "SUBPROBLEM_SIZE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.SubproblemSize))
                eprintf("SUBPROBLEM_SIZE: integer expected");
            if (lkh.SubproblemSize < 3)
                eprintf("SUBPROBLEM_SIZE: >= 3 expected");
            if ((Token = strtok(0, Delimiters))) {
                for (i = 0; i < strlen(Token); i++)
                    Token[i] = (char) toupper(Token[i]);
                if (!strncmp(Token, "DELAUNAY", strlen(Token)))
                    lkh.DelaunayPartitioning = 1;
                else if (!strncmp(Token, "KARP", max(strlen(Token), 2)))
                    lkh.KarpPartitioning = 1;
                else if (!strncmp(Token, "K-CENTER", max(strlen(Token), 3)))
                    lkh.KCenterPartitioning = 1;
                else if (!strncmp(Token, "K-MEANS", max(strlen(Token), 3)))
                    lkh.KMeansPartitioning = 1;
                else if (!strncmp(Token, "MOORE", strlen(Token)))
                    lkh.MoorePartitioning = 1;
                else if (!strncmp(Token, "ROHE", strlen(Token)))
                    lkh.RohePartitioning = 1;
                else if (!strncmp(Token, "SIERPINSKI", strlen(Token)))
                    lkh.SierpinskiPartitioning = 1;
                else if (!strncmp(Token, "BORDERS", strlen(Token)))
                    lkh.SubproblemBorders = 1;
                else if (!strncmp(Token, "COMPRESSED", strlen(Token)))
                    lkh.SubproblemsCompressed = 1;
                else
                    eprintf
                        ("(SUBPROBLEM_SIZE) Illegal DELAUNAY, KARP, K-CENTER, "
                         "K-MEANS, MOORE, ROHE,\n SIERPINSKI, "
                         "BORDERS or COMPRESSED specification");
                while ((Token = strtok(0, Delimiters))) {
                    for (i = 0; i < strlen(Token); i++)
                        Token[i] = (char) toupper(Token[i]);
                    if (!strncmp(Token, "BORDERS", strlen(Token)))
                        lkh.SubproblemBorders = 1;
                    else if (!strncmp(Token, "COMPRESSED", strlen(Token)))
                        lkh.SubproblemsCompressed = 1;
                    else
                        eprintf
                            ("(SUBPROBLEM_SIZE) Illegal BORDERS or "
                             "COMPRESSED specification");
                }
            }
        } else if (!strcmp(Keyword, "SUBSEQUENT_MOVE_TYPE")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.SubsequentMoveType))
                eprintf("SUBSEQUENT_MOVE_TYPE: integer expected");
            if (lkh.SubsequentMoveType != 0 && lkh.SubsequentMoveType < 2)
                eprintf("SUBSEQUENT_MOVE_TYPE: 0 or >= 2 expected");
        } else if (!strcmp(Keyword, "SUBSEQUENT_PATCHING")) {
            if (!ReadYesOrNo(&lkh.SubsequentPatching))
                eprintf("SUBSEQUENT_PATCHING: YES or NO expected");
        } else if (!strcmp(Keyword, "TIME_LIMIT")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%lf", &lkh.TimeLimit))
                eprintf("TIME_LIMIT: real expected");
            if (lkh.TimeLimit < 0)
                eprintf("TIME_LIMIT: >= 0 expected");
        } else if (!strcmp(Keyword, "TOUR_FILE")) {
            if (!(lkh.TourFileName = GetFileName(0)))
                eprintf("TOUR_FILE: string expected");
        } else if (!strcmp(Keyword, "TRACE_LEVEL")) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &lkh.TraceLevel))
                eprintf("TRACE_LEVEL: integer expected");
        } else
            eprintf("Unknown keyword: %s", Keyword);
        if ((Token = strtok(0, Delimiters)) && Token[0] != '#')
            eprintf("Junk at end of line: %s", Token);
    }
    if (!lkh.ProblemFileName)
        eprintf("Problem file name is missing");
    if (lkh.SubproblemSize == 0 && lkh.SubproblemTourFileName != 0)
        eprintf("SUBPROBLEM_SIZE specification is missing");
    if (lkh.SubproblemSize > 0 && lkh.SubproblemTourFileName == 0)
        eprintf("SUBPROBLEM_TOUR_FILE specification is missing");
    fclose(lkh.ParameterFile);
    free(lkh.LastLine);
    lkh.LastLine = 0;
}

static char *GetFileName(char *Line)
{
    char *Rest = strtok(Line, "\n\t\r\f"), *t;

    if (!Rest)
        return 0;
    while (isspace(*Rest))
        Rest++;
    if (!Line) {
        if (*Rest == '=')
            Rest++;
    }
    while (isspace(*Rest))
        Rest++;
    for (t = Rest + strlen(Rest) - 1; isspace(*t); t--)
        *t = '\0';
    if (!strlen(Rest))
        return 0;
    assert(t = (char *) malloc(strlen(Rest) + 1));
    strcpy(t, Rest);
    return t;
}

static char *ReadYesOrNo(int *V)
{
    char *Token = strtok(0, Delimiters);

    if (Token) {
        unsigned int i;
        for (i = 0; i < strlen(Token); i++)
            Token[i] = (char) toupper(Token[i]);
        if (!strncmp(Token, "YES", strlen(Token)))
            *V = 1;
        else if (!strncmp(Token, "NO", strlen(Token)))
            *V = 0;
        else
            Token = 0;
    }
    return Token;
}

static size_t max(size_t a, size_t b)
{
    return a > b ? a : b;
}
