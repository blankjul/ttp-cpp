#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Hidden/LKH.h"
#include "Interface.h"



const char Delimiters[] = " :=\n\t\r\f\v\xef\xbb\xbf";
void CheckSpecificationPart(void);
char *Copy(char *S);
void CreateNodes(void);
void Read_DIMENSION(void);
void Read_DISPLAY_DATA_SECTION(void);
void Read_DISPLAY_DATA_TYPE(void);
void Read_EDGE_DATA_FORMAT(void);
void Read_EDGE_DATA_SECTION(void);
void Read_EDGE_WEIGHT_FORMAT(void);
void Read_EDGE_WEIGHT_SECTION(void);
void Read_EDGE_WEIGHT_TYPE(void);
void Read_FIXED_EDGES_SECTION(void);
void Read_NAME(void);
void Read_NODE_COORD_SECTION(void);
void Read_NODE_COORD_TYPE(void);
void Read_TOUR_SECTION(FILE ** File);
void Read_TYPE(void);
int TwoDWeightType(void);
int ThreeDWeightType(void);





int** ReadTSPFile(FILE* file)
{
    int i, K;
    char *Line, *Keyword;

    MaxMatrixDimension = 1000000;

    ProblemFile = file;

    FreeStructures();
    FirstNode = 0;
    WeightType = WeightFormat = ProblemType = -1;
    CoordType = NO_COORDS;
    Name = Copy("Unnamed");
    Type = EdgeWeightType = EdgeWeightFormat = 0;
    EdgeDataFormat = NodeCoordType = DisplayDataType = 0;
    Distance = 0;
    C = 0;
    c = 0;
    while ((Line = ReadLine(ProblemFile))) {
        if (!(Keyword = strtok(Line, Delimiters)))
            continue;
        for (i = 0; i < (int) strlen(Keyword); i++)
            Keyword[i] = (char) toupper(Keyword[i]);
        if (!strcmp(Keyword, "COMMENT"));
        else if (!strcmp(Keyword, "DEMAND_SECTION"))
            eprintf("Not implemented: %s", Keyword);
        else if (!strcmp(Keyword, "DEPOT_SECTION"))
            eprintf("Not implemented: %s", Keyword);
        else if (!strcmp(Keyword, "DIMENSION"))
            Read_DIMENSION();
        else if (!strcmp(Keyword, "DISPLAY_DATA_SECTION"))
            Read_DISPLAY_DATA_SECTION();
        else if (!strcmp(Keyword, "DISPLAY_DATA_TYPE"))
            Read_DISPLAY_DATA_TYPE();
        else if (!strcmp(Keyword, "EDGE_DATA_FORMAT"))
            Read_EDGE_DATA_FORMAT();
        else if (!strcmp(Keyword, "EDGE_DATA_SECTION"))
            Read_EDGE_DATA_SECTION();
        else if (!strcmp(Keyword, "EDGE_WEIGHT_FORMAT"))
            Read_EDGE_WEIGHT_FORMAT();
        else if (!strcmp(Keyword, "EDGE_WEIGHT_SECTION"))
            Read_EDGE_WEIGHT_SECTION();
        else if (!strcmp(Keyword, "EDGE_WEIGHT_TYPE"))
            Read_EDGE_WEIGHT_TYPE();
        else if (!strcmp(Keyword, "EOF"))
            break;
        else if (!strcmp(Keyword, "FIXED_EDGES_SECTION"))
            Read_FIXED_EDGES_SECTION();
        else if (!strcmp(Keyword, "NAME"))
            Read_NAME();
        else if (!strcmp(Keyword, "NODE_COORD_SECTION"))
            Read_NODE_COORD_SECTION();
        else if (!strcmp(Keyword, "NODE_COORD_TYPE"))
            Read_NODE_COORD_TYPE();
        else if (!strcmp(Keyword, "TOUR_SECTION"))
            Read_TOUR_SECTION(&ProblemFile);
        else if (!strcmp(Keyword, "TYPE"))
            Read_TYPE();
        else
            eprintf("Unknown keyword: %s", Keyword);
    }


    if (CostMatrix == 0 && Dimension <= MaxMatrixDimension && Distance != 0
        && Distance != Distance_1 && Distance != Distance_ATSP &&
        WeightType != GEO && WeightType != GEOM &&
        WeightType != GEO_MEEUS && WeightType != GEOM_MEEUS) {
        Node *Ni, *Nj;
        assert(CostMatrix =
               (int *) calloc((size_t) Dimension * (Dimension - 1) / 2,
                              sizeof(int)));
        Ni = FirstNode->Suc;
        do {
            Ni->C =
                &CostMatrix[(size_t) (Ni->Id - 1) * (Ni->Id - 2) / 2] - 1;
            if (ProblemType != HPP || Ni->Id < Dimension)
                for (Nj = FirstNode; Nj != Ni; Nj = Nj->Suc)
                    Ni->C[Nj->Id] = Fixed(Ni, Nj) ? 0 : Distance(Ni, Nj);
            else
                for (Nj = FirstNode; Nj != Ni; Nj = Nj->Suc)
                    Ni->C[Nj->Id] = 0;
        }
        while ((Ni = Ni->Suc) != FirstNode);
        WeightType = EXPLICIT;
        c = 0;
    }

    C = WeightType == EXPLICIT ? C_EXPLICIT : C_FUNCTION;
    D = WeightType == EXPLICIT ? D_EXPLICIT : D_FUNCTION;

    free(LastLine);
    LastLine = 0;


    int **data = malloc(Dimension * sizeof(int*));
    int x;
    for (x = 0; x < Dimension; x++) {
        data[x] = malloc(Dimension *  sizeof(int));
        //data[x] = calloc(0,Dimension *  sizeof(int));
    }


    Node *Ni, *Nj;
    Ni = FirstNode;

    int column = 0;
    do {
        int row = 0;
        if (Ni->C != 0) {
            for (Nj = FirstNode; Nj != Ni; Nj = Nj->Suc) {
                int value = Fixed(Ni, Nj) ? 0 : Distance(Ni, Nj);
                data[row][column] = value;
                data[column][row] = value;
                ++row;
            }
        }
        Ni = Ni->Suc;
        ++column;
    }
    while (Ni != FirstNode);

    dim = Dimension;

    return data;

}

int TwoDWeightType()
{
    return WeightType == EUC_2D || WeightType == MAX_2D ||
        WeightType == MAN_2D || WeightType == CEIL_2D ||
        WeightType == GEO || WeightType == GEOM ||
        WeightType == GEO_MEEUS || WeightType == GEOM_MEEUS ||
        WeightType == ATT ||
        (WeightType == SPECIAL && CoordType == TWOD_COORDS);
}



int ThreeDWeightType()
{
    return WeightType == EUC_3D || WeightType == MAX_3D ||
        WeightType == MAN_3D || WeightType == CEIL_3D ||
        WeightType == XRAY1 || WeightType == XRAY2 ||
        (WeightType == SPECIAL && CoordType == THREED_COORDS);
}

void CheckSpecificationPart()
{
    if (ProblemType == -1)
        eprintf("TYPE is missing");
    if (Dimension < 3)
        eprintf("DIMENSION < 3 or not specified");
    if (WeightType == -1 && ProblemType != ATSP && ProblemType != HCP)
        eprintf("EDGE_WEIGHT_TYPE is missing");
    if (WeightType == EXPLICIT && WeightFormat == -1)
        eprintf("EDGE_WEIGHT_FORMAT is missing");
    if (WeightType == EXPLICIT && WeightFormat == FUNCTION)
        eprintf("Conflicting EDGE_WEIGHT_TYPE and EDGE_WEIGHT_FORMAT");
    if (WeightType != EXPLICIT
        && (WeightType != SPECIAL || CoordType != NO_COORDS)
        && WeightType != -1 && WeightFormat != -1
        && WeightFormat != FUNCTION)
        eprintf("Conflicting EDGE_WEIGHT_TYPE and EDGE_WEIGHT_FORMAT");
    if (ProblemType == ATSP && WeightType != EXPLICIT && WeightType != -1)
        eprintf("Conflicting TYPE and EDGE_WEIGHT_TYPE");
    if (ProblemType == ATSP && WeightFormat != FULL_MATRIX)
        eprintf("Conflicting TYPE and EDGE_WEIGHT_FORMAT");
    if (CandidateSetType == DELAUNAY && !TwoDWeightType()
        && MaxCandidates > 0)
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for CANDIDATE_SET_TYPE = DELAUNAY");
    if (CandidateSetType == NN && !TwoDWeightType()
        && !ThreeDWeightType() && MaxCandidates > 0)
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for CANDIDATE_SET_TYPE = "
             "NEAREST-NEIGHBOR");
    if (CandidateSetType == QUADRANT && !TwoDWeightType()
        && !ThreeDWeightType() && MaxCandidates + ExtraCandidates > 0)
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for CANDIDATE_SET_TYPE = QUADRANT");
    if (ExtraCandidateSetType == NN && !TwoDWeightType()
        && !ThreeDWeightType() && ExtraCandidates > 0)
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for EXTRA_CANDIDATE_SET_TYPE = "
             "NEAREST-NEIGHBOR");
    if (ExtraCandidateSetType == QUADRANT && !TwoDWeightType()
        && !ThreeDWeightType()
        && ExtraCandidates > 0)
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for EXTRA_CANDIDATE_SET_TYPE = "
             "QUADRANT");
    if (InitialTourAlgorithm == QUICK_BORUVKA && !TwoDWeightType()
        && !ThreeDWeightType())
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for INITIAL_TOUR_ALGORITHM = "
             "QUICK-BORUVKA");
    if (InitialTourAlgorithm == SIERPINSKI && !TwoDWeightType())
        eprintf
            ("Illegal EDGE_WEIGHT_TYPE for INITIAL_TOUR_ALGORITHM = "
             "SIERPINSKI");
    if (DelaunayPartitioning && !TwoDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for DELAUNAY specification");
    if (KarpPartitioning && !TwoDWeightType() && !ThreeDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for KARP specification");
    if (KMeansPartitioning && !TwoDWeightType() && !ThreeDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for K-MEANS specification");
    if (MoorePartitioning && !TwoDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for MOORE specification");
    if (RohePartitioning && !TwoDWeightType() && !ThreeDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for ROHE specification");
    if (SierpinskiPartitioning && !TwoDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for SIERPINSKI specification");
    if (SubproblemBorders && !TwoDWeightType() && !ThreeDWeightType())
        eprintf("Illegal EDGE_WEIGHT_TYPE for BORDERS specification");
}

char *Copy(char *S)
{
    char *Buffer;

    if (!S || strlen(S) == 0)
        return 0;
    assert(Buffer = (char *) malloc(strlen(S) + 1));
    strcpy(Buffer, S);
    return Buffer;
}

void CreateNodes()
{
    Node *Prev = 0, *N = 0;
    int i;

    if (Dimension <= 0)
        eprintf("DIMENSION is not positive (or not specified)");
    if (ProblemType == ATSP)
        Dimension *= 2;
    else if (ProblemType == HPP) {
        Dimension++;
        if (Dimension > MaxMatrixDimension)
            eprintf("Dimension too large in HPP problem");
    }
    assert(NodeSet = (Node *) calloc(Dimension + 1, sizeof(Node)));
    for (i = 1; i <= Dimension; i++, Prev = N) {
        N = &NodeSet[i];
        if (i == 1)
            FirstNode = N;
        else
            Link(Prev, N);
        N->Id = i;
        if (MergeTourFiles >= 1)
            assert(N->MergeSuc =
                   (Node **) calloc(MergeTourFiles, sizeof(Node *)));
    }
    Link(N, FirstNode);
}

void Read_NAME()
{
    if (!(Name = Copy(strtok(0, Delimiters))))
        eprintf("NAME: string expected");
}

void Read_DIMENSION()
{
    char *Token = strtok(0, Delimiters);

    if (!Token || !sscanf(Token, "%d", &Dimension))
        eprintf("DIMENSION: integer expected");
    DimensionSaved = Dimension;
}

void Read_DISPLAY_DATA_SECTION()
{
    Node *N;
    int Id, i;

    CheckSpecificationPart();
    if (ProblemType == HPP)
        Dimension--;
    if (!DisplayDataType || strcmp(DisplayDataType, "TWOD_DISPLAY"))
        eprintf
            ("DISPLAY_DATA_SECTION conflicts with DISPLAY_DATA_TYPE: %s",
             DisplayDataType);
    if (!FirstNode)
        CreateNodes();
    N = FirstNode;
    do
        N->V = 0;
    while ((N = N->Suc) != FirstNode);
    N = FirstNode;
    for (i = 1; i <= Dimension; i++) {
        if (!fscanint(ProblemFile, &Id))
            eprintf("Missing nodes in DIPLAY_DATA_SECTION");
        if (Id <= 0 || Id > Dimension)
            eprintf("(DIPLAY_DATA_SECTION) Node number out of range: %d",
                    Id);
        N = &NodeSet[Id];
        if (N->V == 1)
            eprintf("(DIPLAY_DATA_SECTION) Node number occours twice: %d",
                    N->Id);
        N->V = 1;
        if (!fscanf(ProblemFile, "%lf", &N->X))
            eprintf("Missing X-coordinate in DIPLAY_DATA_SECTION");
        if (!fscanf(ProblemFile, "%lf", &N->Y))
            eprintf("Missing Y-coordinate in DIPLAY_DATA_SECTION");
    }
    N = FirstNode;
    do
        if (!N->V)
            break;
    while ((N = N->Suc) != FirstNode);
    if (!N->V)
        eprintf("(DIPLAY_DATA_SECTION) No coordinates given for node %d",
                N->Id);
    if (ProblemType == HPP)
        Dimension++;
}

void Read_DISPLAY_DATA_TYPE()
{
    unsigned int i;

    if (!(DisplayDataType = Copy(strtok(0, Delimiters))))
        eprintf("DISPLAY_DATA_TYPE: string expected");
    for (i = 0; i < strlen(DisplayDataType); i++)
        DisplayDataType[i] = (char) toupper(DisplayDataType[i]);
    if (strcmp(DisplayDataType, "COORD_DISPLAY") &&
        strcmp(DisplayDataType, "TWOD_DISPLAY") &&
        strcmp(DisplayDataType, "NO_DISPLAY"))
        eprintf("Unknown DISPLAY_DATA_TYPE: %s", DisplayDataType);
}

void Read_EDGE_DATA_FORMAT()
{
    unsigned int i;

    if (!(EdgeDataFormat = Copy(strtok(0, Delimiters))))
        eprintf("EDGE_DATA_FORMAT: string expected");
    for (i = 0; i < strlen(EdgeDataFormat); i++)
        EdgeDataFormat[i] = (char) toupper(EdgeDataFormat[i]);
    if (strcmp(EdgeDataFormat, "EDGE_LIST") &&
        strcmp(EdgeDataFormat, "ADJ_LIST"))
        eprintf("Unknown EDGE_DATA_FORMAT: %s", EdgeDataFormat);
    if (SubproblemTourFileName)
        eprintf("(EDGE_DATA_FORMAT)"
                " cannot be used together with SUBPROBLEM_TOUR_FILE");
}

void Read_EDGE_DATA_SECTION()
{
    Node *Ni, *Nj;
    int i, j;

    CheckSpecificationPart();
    if (!EdgeDataFormat)
        eprintf("Missing EDGE_DATA_FORMAT specification");
    if (!FirstNode)
        CreateNodes();
    if (ProblemType == HPP)
        Dimension--;
    if (!strcmp(EdgeDataFormat, "EDGE_LIST")) {
        if (!fscanint(ProblemFile, &i))
            i = -1;
        while (i != -1) {
            if (i <= 0
                || i > (ProblemType != ATSP ? Dimension : Dimension / 2))
                eprintf("(EDGE_DATA_SECTION) Node number out of range: %d",
                        i);
            fscanint(ProblemFile, &j);
            if (j <= 0
                || j > (ProblemType != ATSP ? Dimension : Dimension / 2))
                eprintf("(EDGE_DATA_SECTION) Node number out of range: %d",
                        j);
            if (i == j)
                eprintf("(EDGE_DATA_SECTION) Illgal edge: %d to %d", i, j);
            if (ProblemType == ATSP) {
                i += Dimension / 2;
                j += Dimension / 2;
            }
            Ni = &NodeSet[i];
            Nj = &NodeSet[j];
            if (!Ni->CandidateSet) {
                assert(Ni->CandidateSet =
                       (Candidate *) calloc(3, sizeof(Candidate)));
                Ni->CandidateSet[0].To = Nj;
                Ni->CandidateSet[0].Cost = 0;
                Ni->CandidateSet[0].Alpha = 0;
                Ni->V = 1;
            } else if (!IsCandidate(Ni, Nj)) {
                Ni->CandidateSet[Ni->V].To = Nj;
                Ni->CandidateSet[Ni->V].Cost = 0;
                Ni->CandidateSet[Ni->V].Alpha = Ni->V;
                assert(Ni->CandidateSet =
                       (Candidate *) realloc(Ni->CandidateSet,
                                             (++Ni->V +
                                              1) * sizeof(Candidate)));
                Ni->CandidateSet[Ni->V].To = 0;
            }
            if (ProblemType != ATSP) {
                if (!Nj->CandidateSet) {
                    assert(Nj->CandidateSet =
                           (Candidate *) calloc(3, sizeof(Candidate)));
                    Nj->CandidateSet[0].To = Ni;
                    Nj->CandidateSet[0].Cost = 0;
                    Nj->CandidateSet[0].Alpha = 0;
                    Nj->V = 1;
                } else if (ProblemType !=!IsCandidate(Nj, Ni)) {
                    Nj->CandidateSet[Nj->V].To = Ni;
                    Nj->CandidateSet[Nj->V].Cost = 0;
                    Nj->CandidateSet[Nj->V].Alpha = Nj->V;
                    assert(Nj->CandidateSet =
                           (Candidate *) realloc(Nj->CandidateSet,
                                                 (++Nj->V +
                                                  1) * sizeof(Candidate)));
                    Nj->CandidateSet[Nj->V].To = 0;
                }
            }
            if (!fscanint(ProblemFile, &i))
                i = -1;
        }
    } else if (!strcmp(EdgeDataFormat, "ADJ_LIST")) {
        Ni = FirstNode;
        do
            Ni->V = 0;
        while ((Ni = Ni->Suc) != FirstNode);
        if (!fscanint(ProblemFile, &i))
            i = -1;
        while (i != -1) {
            if (i <= 0
                || i > (ProblemType != ATSP ? Dimension : Dimension / 2))
                eprintf("(EDGE_DATA_SECTION) Node number out of range: %d",
                        i);
            if (ProblemType == ATSP)
                i += Dimension / 2;
            Ni = &NodeSet[i];
            fscanint(ProblemFile, &j);
            while (j != -1) {
                if (j <= 0
                    || j > (ProblemType !=
                            ATSP ? Dimension : Dimension / 2))
                    eprintf
                        ("(EDGE_DATA_SECTION) Node number out of range: %d",
                         j);
                if (i == j)
                    eprintf("(EDGE_DATA_SECTION) Illgal edge: %d to %d",
                            i, j);
                if (ProblemType == ATSP)
                    j += Dimension / 2;
                Nj = &NodeSet[j];
                if (!Ni->CandidateSet) {
                    assert(Ni->CandidateSet =
                           (Candidate *) calloc(3, sizeof(Candidate)));
                    Ni->CandidateSet[0].To = Nj;
                    Ni->CandidateSet[0].Cost = 0;
                    Ni->CandidateSet[0].Alpha = 0;
                    Ni->V = 1;
                } else if (!IsCandidate(Ni, Nj)) {
                    Ni->CandidateSet[Ni->V].To = Nj;
                    Ni->CandidateSet[Ni->V].Cost = 0;
                    Ni->CandidateSet[Ni->V].Alpha = Ni->V;
                    assert(Ni->CandidateSet =
                           (Candidate *) realloc(Ni->CandidateSet,
                                                 (++Ni->V +
                                                  1) * sizeof(Candidate)));
                    Ni->CandidateSet[Ni->V].To = 0;
                }
                if (ProblemType != ATSP) {
                    if (!Nj->CandidateSet) {
                        assert(Nj->CandidateSet =
                               (Candidate *) calloc(3, sizeof(Candidate)));
                        Nj->CandidateSet[0].To = Ni;
                        Nj->CandidateSet[0].Cost = 0;
                        Nj->CandidateSet[0].Alpha = 0;
                        Nj->V = 1;
                    } else if (!IsCandidate(Nj, Ni)) {
                        Nj->CandidateSet[Nj->V].To = Ni;
                        Nj->CandidateSet[Nj->V].Cost = 0;
                        Nj->CandidateSet[Nj->V].Alpha = Nj->V;
                        assert(Nj->CandidateSet =
                               (Candidate *) realloc(Nj->CandidateSet,
                                                     (++Nj->V +
                                                      1) * sizeof(Candidate)));
                        Nj->CandidateSet[Nj->V].To = 0;
                    }
                }
                if (!fscanint(ProblemFile, &j))
                    j = -1;
            }
            if (!fscanint(ProblemFile, &i))
                i = -1;
        }
    } else
        eprintf("(EDGE_DATA_SECTION) No EDGE_DATA_FORMAT specified");
    if (ProblemType == HPP)
        Dimension++;
    Distance = Distance_1;
}

void Read_EDGE_WEIGHT_FORMAT()
{
    unsigned int i;

    if (!(EdgeWeightFormat = Copy(strtok(0, Delimiters))))
        eprintf("EDGE_WEIGHT_FORMAT: string expected");
    for (i = 0; i < strlen(EdgeWeightFormat); i++)
        EdgeWeightFormat[i] = (char) toupper(EdgeWeightFormat[i]);
    if (!strcmp(EdgeWeightFormat, "FUNCTION"))
        WeightFormat = FUNCTION;
    else if (!strcmp(EdgeWeightFormat, "FULL_MATRIX"))
        WeightFormat = FULL_MATRIX;
    else if (!strcmp(EdgeWeightFormat, "UPPER_ROW"))
        WeightFormat = UPPER_ROW;
    else if (!strcmp(EdgeWeightFormat, "LOWER_ROW"))
        WeightFormat = LOWER_ROW;
    else if (!strcmp(EdgeWeightFormat, "UPPER_DIAG_ROW"))
        WeightFormat = UPPER_DIAG_ROW;
    else if (!strcmp(EdgeWeightFormat, "LOWER_DIAG_ROW"))
        WeightFormat = LOWER_DIAG_ROW;
    else if (!strcmp(EdgeWeightFormat, "UPPER_COL"))
        WeightFormat = UPPER_COL;
    else if (!strcmp(EdgeWeightFormat, "LOWER_COL"))
        WeightFormat = LOWER_COL;
    else if (!strcmp(EdgeWeightFormat, "UPPER_DIAG_COL"))
        WeightFormat = UPPER_DIAG_COL;
    else if (!strcmp(EdgeWeightFormat, "LOWER_DIAG_COL"))
        WeightFormat = LOWER_DIAG_COL;
    else
        eprintf("Unknown EDGE_WEIGHT_FORMAT: %s", EdgeWeightFormat);
}

void Read_EDGE_WEIGHT_SECTION()
{
    Node *Ni, *Nj;
    int i, j, n, W;

    CheckSpecificationPart();
    if (!FirstNode)
        CreateNodes();
    if (ProblemType != ATSP) {
        assert(CostMatrix =
               (int *) calloc((size_t) Dimension * (Dimension - 1) / 2,
                              sizeof(int)));
        Ni = FirstNode->Suc;
        do {
            Ni->C =
                &CostMatrix[(size_t) (Ni->Id - 1) * (Ni->Id - 2) / 2] - 1;
        }
        while ((Ni = Ni->Suc) != FirstNode);
    } else {
        n = Dimension / 2;
        assert(CostMatrix = (int *) calloc((size_t) n * n, sizeof(int)));
        for (Ni = FirstNode; Ni->Id <= n; Ni = Ni->Suc)
            Ni->C = &CostMatrix[(size_t) (Ni->Id - 1) * n] - 1;
    }
    if (ProblemType == HPP)
        Dimension--;
    switch (WeightFormat) {
    case FULL_MATRIX:
        if (ProblemType == ATSP) {
            n = Dimension / 2;
            for (i = 1; i <= n; i++) {
                Ni = &NodeSet[i];
                for (j = 1; j <= n; j++) {
                    if (!fscanint(ProblemFile, &W))
                        eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                    Ni->C[j] = W;
                    if (i != j && W > M)
                        M = W;
                }
                Nj = &NodeSet[i + n];
                if (!Ni->FixedTo1)
                    Ni->FixedTo1 = Nj;
                else if (!Ni->FixedTo2)
                    Ni->FixedTo2 = Nj;
                if (!Nj->FixedTo1)
                    Nj->FixedTo1 = Ni;
                else if (!Nj->FixedTo2)
                    Nj->FixedTo2 = Ni;
            }
            Distance = Distance_ATSP;
            WeightType = -1;
        } else
            for (i = 1, Ni = FirstNode; i <= Dimension; i++, Ni = Ni->Suc) {
                for (j = 1; j <= Dimension; j++) {
                    if (!fscanint(ProblemFile, &W))
                        eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                    if (j < i)
                        Ni->C[j] = W;
                }
            }
        break;
    case UPPER_ROW:
        for (i = 1, Ni = FirstNode; i < Dimension; i++, Ni = Ni->Suc) {
            for (j = i + 1, Nj = Ni->Suc; j <= Dimension;
                 j++, Nj = Nj->Suc) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                Nj->C[i] = W;
            }
        }
        break;
    case LOWER_ROW:
        for (i = 2, Ni = FirstNode->Suc; i <= Dimension; i++, Ni = Ni->Suc) {
            for (j = 1; j < i; j++) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                Ni->C[j] = W;
            }
        }
        break;
    case UPPER_DIAG_ROW:
        for (i = 1, Ni = FirstNode; i <= Dimension; i++, Ni = Ni->Suc) {
            for (j = i, Nj = Ni; j <= Dimension; j++, Nj = Nj->Suc) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                if (i != j)
                    Nj->C[i] = W;
            }
        }
        break;
    case LOWER_DIAG_ROW:
        for (i = 1, Ni = FirstNode; i <= Dimension; i++, Ni = Ni->Suc) {
            for (j = 1; j <= i; j++) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                if (j != i)
                    Ni->C[j] = W;
            }
        }
        break;
    case UPPER_COL:
        for (j = 2, Nj = FirstNode->Suc; j <= Dimension; j++, Nj = Nj->Suc) {
            for (i = 1; i < j; i++) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                Nj->C[i] = W;
            }
        }
        break;
    case LOWER_COL:
        for (j = 1, Nj = FirstNode; j < Dimension; j++, Nj = Nj->Suc) {
            for (i = j + 1, Ni = Nj->Suc; i <= Dimension;
                 i++, Ni = Ni->Suc) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                Ni->C[j] = W;
            }
        }
        break;
    case UPPER_DIAG_COL:
        for (j = 1, Nj = FirstNode; j <= Dimension; j++, Nj = Nj->Suc) {
            for (i = 1; i <= j; i++) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                if (i != j)
                    Nj->C[i] = W;
            }
        }
        break;
    case LOWER_DIAG_COL:
        for (j = 1, Nj = FirstNode; j <= Dimension; j++, Nj = Nj->Suc) {
            for (i = j, Ni = Nj; i <= Dimension; i++, Ni = Ni->Suc) {
                if (!fscanint(ProblemFile, &W))
                    eprintf("Missing weight in EDGE_WEIGHT_SECTION");
                if (i != j)
                    Ni->C[j] = W;
            }
        }
        break;
    }
    if (ProblemType == HPP)
        Dimension++;
}

void Read_EDGE_WEIGHT_TYPE()
{
    unsigned int i;

    if (!(EdgeWeightType = Copy(strtok(0, Delimiters))))
        eprintf("EDGE_WEIGHT_TYPE: string expected");
    for (i = 0; i < strlen(EdgeWeightType); i++)
        EdgeWeightType[i] = (char) toupper(EdgeWeightType[i]);
    if (!strcmp(EdgeWeightType, "ATT")) {
        WeightType = ATT;
        Distance = Distance_ATT;
        c = c_ATT;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "CEIL_2D")) {
        WeightType = CEIL_2D;
        Distance = Distance_CEIL_2D;
        c = c_CEIL_2D;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "CEIL_3D")) {
        WeightType = CEIL_3D;
        Distance = Distance_CEIL_3D;
        c = c_CEIL_3D;
        CoordType = THREED_COORDS;
    } else if (!strcmp(EdgeWeightType, "EUC_2D")) {
        WeightType = EUC_2D;
        Distance = Distance_EUC_2D;
        c = c_EUC_2D;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "EUC_3D")) {
        WeightType = EUC_3D;
        Distance = Distance_EUC_3D;
        c = c_EUC_3D;
        CoordType = THREED_COORDS;
    } else if (!strcmp(EdgeWeightType, "EXPLICIT")) {
        WeightType = EXPLICIT;
        Distance = Distance_EXPLICIT;
    } else if (!strcmp(EdgeWeightType, "MAN_2D")) {
        WeightType = MAN_2D;
        Distance = Distance_MAN_2D;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "MAN_3D")) {
        WeightType = MAN_3D;
        Distance = Distance_MAN_3D;
        CoordType = THREED_COORDS;
    } else if (!strcmp(EdgeWeightType, "MAX_2D")) {
        WeightType = MAX_2D;
        Distance = Distance_MAX_2D;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "MAX_3D")) {
        WeightType = MAX_3D;
        Distance = Distance_MAX_3D;
        CoordType = THREED_COORDS;
    } else if (!strcmp(EdgeWeightType, "GEO")) {
        WeightType = GEO;
        Distance = Distance_GEO;
        c = c_GEO;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "GEOM")) {
        WeightType = GEOM;
        Distance = Distance_GEOM;
        c = c_GEOM;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "GEO_MEEUS")) {
        WeightType = GEO_MEEUS;
        Distance = Distance_GEO_MEEUS;
        c = c_GEO_MEEUS;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "GEOM_MEEUS")) {
        WeightType = GEOM_MEEUS;
        Distance = Distance_GEOM_MEEUS;
        c = c_GEOM_MEEUS;
        CoordType = TWOD_COORDS;
    } else if (!strcmp(EdgeWeightType, "XRAY1")) {
        WeightType = XRAY1;
        Distance = Distance_XRAY1;
        CoordType = THREED_COORDS;
    } else if (!strcmp(EdgeWeightType, "XRAY2")) {
        WeightType = XRAY2;
        Distance = Distance_XRAY2;
        CoordType = THREED_COORDS;
    } else
        eprintf("Unknown EDGE_WEIGHT_TYPE: %s", EdgeWeightType);
}

void Read_FIXED_EDGES_SECTION()
{
    Node *Ni, *Nj, *N, *NPrev = 0, *NNext;
    int i, j, Count = 0;

    CheckSpecificationPart();
    if (!FirstNode)
        CreateNodes();
    if (ProblemType == HPP)
        Dimension--;
    if (!fscanint(ProblemFile, &i))
        i = -1;
    while (i != -1) {
        if (i <= 0
            || i > (ProblemType != ATSP ? Dimension : Dimension / 2))
            eprintf("(FIXED_EDGES_SECTION) Node number out of range: %d",
                    i);
        fscanint(ProblemFile, &j);
        if (j <= 0
            || j > (ProblemType != ATSP ? Dimension : Dimension / 2))
            eprintf("(FIXED_EDGES_SECTION) Node number out of range: %d",
                    j);
        if (i == j)
            eprintf("(FIXED_EDGES_SECTION) Illgal edge: %d to %d", i, j);
        Ni = &NodeSet[i];
        Nj = &NodeSet[ProblemType == ATSP ? j + Dimension / 2 : j];
        if (!Ni->FixedTo1 || Ni->FixedTo1 == Nj)
            Ni->FixedTo1 = Nj;
        else if (!Ni->FixedTo2 || Ni->FixedTo2 == Nj)
            Ni->FixedTo2 = Nj;
        else
            eprintf("(FIXED_EDGES_SECTION) Illegal fix: %d to %d", i, j);
        if (!Nj->FixedTo1 || Nj->FixedTo1 == Ni)
            Nj->FixedTo1 = Ni;
        else if (!Nj->FixedTo2 || Nj->FixedTo2 == Ni)
            Nj->FixedTo2 = Ni;
        else
            eprintf("(FIXED_EDGES_SECTION) Illegal fix: %d to %d", i, j);
        /* Cycle check */
        N = Ni;
        Count = 0;
        do {
            NNext = N->FixedTo1 != NPrev ? N->FixedTo1 : N->FixedTo2;
            NPrev = N;
            Count++;
        } while ((N = NNext) && N != Ni);
        if (N == Ni && Count != Dimension)
            eprintf("(FIXED_EDGES_SECTION) Illegal fix: %d to %d", i, j);
        if (!fscanint(ProblemFile, &i))
            i = -1;
    }
    if (ProblemType == HPP)
        Dimension++;
}

void Read_NODE_COORD_SECTION()
{
    Node *N;
    int Id, i;

    CheckSpecificationPart();
    if (CoordType != TWOD_COORDS && CoordType != THREED_COORDS)
        eprintf("NODE_COORD_SECTION conflicts with NODE_COORD_TYPE: %s",
                NodeCoordType);
    if (!FirstNode)
        CreateNodes();
    N = FirstNode;
    if (ProblemType == HPP)
        Dimension--;
    for (i = 1; i <= Dimension; i++) {
        if (!fscanint(ProblemFile, &Id))
            eprintf("Missing nodes in NODE_COORD_SECTION");
        if (Id <= 0 || Id > Dimension)
            eprintf("(NODE_COORD_SECTION) Node number out of range: %d",
                    Id);
        N = &NodeSet[Id];
        if (N->V == 1)
            eprintf("(NODE_COORD_SECTION) Node number occours twice: %d",
                    N->Id);
        N->V = 1;
        if (!fscanf(ProblemFile, "%lf", &N->X))
            eprintf("Missing X-coordinate in NODE_COORD_SECTION");
        if (!fscanf(ProblemFile, "%lf", &N->Y))
            eprintf("Missing Y-coordinate in NODE_COORD_SECTION");
        if (CoordType == THREED_COORDS
            && !fscanf(ProblemFile, "%lf", &N->Z))
            eprintf("Missing Z-coordinate in NODE_COORD_SECTION");
        if (Name && !strcmp(Name, "d657")) {
            N->X = (float) N->X;
            N->Y = (float) N->Y;
        }
    }
    N = FirstNode;
    do
        if (!N->V && N->Id <= Dimension)
            break;
    while ((N = N->Suc) != FirstNode);
    if (!N->V)
        eprintf("(NODE_COORD_SECTION) No coordinates given for node %d",
                N->Id);
    if (ProblemType == HPP)
        Dimension++;
}

void Read_NODE_COORD_TYPE()
{
    unsigned int i;

    if (!(NodeCoordType = Copy(strtok(0, Delimiters))))
        eprintf("NODE_COORD_TYPE: string expected");
    for (i = 0; i < strlen(NodeCoordType); i++)
        NodeCoordType[i] = (char) toupper(NodeCoordType[i]);
    if (!strcmp(NodeCoordType, "TWOD_COORDS"))
        CoordType = TWOD_COORDS;
    else if (!strcmp(NodeCoordType, "THREED_COORDS"))
        CoordType = THREED_COORDS;
    else if (!strcmp(NodeCoordType, "NO_COORDS"))
        CoordType = NO_COORDS;
    else
        eprintf("Unknown NODE_COORD_TYPE: %s", NodeCoordType);
}

void Read_TOUR_SECTION(FILE ** File)
{
    Node *First = 0, *Last = 0, *N, *Na;
    int i, k;

    if (TraceLevel >= 1) {
        printff("Reading ");
        if (File == &InitialTourFile)
            printff("INITIAL_TOUR_FILE: \"%s\" ... ", InitialTourFileName);
        else if (File == &InputTourFile)
            printff("INPUT_TOUR_FILE: \"%s\" ... ", InputTourFileName);
        else if (File == &SubproblemTourFile)
            printff("SUBPROBLEM_TOUR_FILE: \"%s\" ... ",
                    SubproblemTourFileName);
        else
            for (i = 0; i < MergeTourFiles; i++)
                if (File == &MergeTourFile[i])
                    printff("MERGE_TOUR_FILE: \"%s\" ... ",
                            MergeTourFileName[i]);
    }
    if (!FirstNode)
        CreateNodes();
    N = FirstNode;
    do
        N->V = 0;
    while ((N = N->Suc) != FirstNode);
    if (ProblemType == HPP)
        Dimension--;
    if (ProblemType == ATSP)
        Dimension /= 2;
    if (!fscanint(*File, &i))
        i = -1;
    for (k = 0; k <= Dimension && i != -1; k++) {
        if (i <= 0 || i > Dimension)
            eprintf("(TOUR_SECTION) Node number out of range: %d", i);
        N = &NodeSet[i];
        if (N->V == 1 && k != Dimension)
            eprintf("(TOUR_SECTION) Node number occours twice: %d", N->Id);
        N->V = 1;
        if (k == 0)
            First = Last = N;
        else {
            if (ProblemType == ATSP) {
                Na = N + Dimension;
                Na->V = 1;
            } else
                Na = 0;
            if (File == &InitialTourFile) {
                if (!Na)
                    Last->InitialSuc = N;
                else {
                    Last->InitialSuc = Na;
                    Na->InitialSuc = N;
                }
            } else if (File == &InputTourFile) {
                if (!Na)
                    Last->InputSuc = N;
                else {
                    Last->InputSuc = Na;
                    Na->InputSuc = N;
                }
            } else if (File == &SubproblemTourFile) {
                if (!Na)
                    (Last->SubproblemSuc = N)->SubproblemPred = Last;
                else {
                    (Last->SubproblemSuc = Na)->SubproblemPred = Last;
                    (Na->SubproblemSuc = N)->SubproblemPred = Na;
                }
            } else {
                for (i = 0; i < MergeTourFiles; i++) {
                    if (File == &MergeTourFile[i]) {
                        if (!Na)
                            Last->MergeSuc[i] = N;
                        else {
                            Last->MergeSuc[i] = Na;
                            Na->MergeSuc[i] = N;
                        }
                    }
                }
            }
            Last = N;
        }
        if (k < Dimension)
            fscanint(*File, &i);
        if (k == Dimension - 1)
            i = First->Id;
    }
    N = FirstNode;
    do
        if (!N->V)
            eprintf("(TOUR_SECTION) Node is missing: %d", N->Id);
    while ((N = N->Suc) != FirstNode);
    if (File == &SubproblemTourFile) {
        do {
            if (N->FixedTo1 &&
                N->SubproblemPred != N->FixedTo1
                && N->SubproblemSuc != N->FixedTo1)
                eprintf("Fixed edge (%d, %d) "
                        "does not belong to subproblem tour", N->Id,
                        N->FixedTo1->Id);
            if (N->FixedTo2 && N->SubproblemPred != N->FixedTo2
                && N->SubproblemSuc != N->FixedTo2)
                eprintf("Fixed edge (%d, %d) "
                        "does not belong to subproblem tour", N->Id,
                        N->FixedTo2->Id);
        } while ((N = N->Suc) != FirstNode);
    }
    if (ProblemType == HPP)
        Dimension++;
    if (ProblemType == ATSP)
        Dimension *= 2;
    if (TraceLevel >= 1)
        printff("done\n");
}

void Read_TYPE()
{
    unsigned int i;

    if (!(Type = Copy(strtok(0, Delimiters))))
        eprintf("TYPE: string expected");
    for (i = 0; i < strlen(Type); i++)
        Type[i] = (char) toupper(Type[i]);
    if (!strcmp(Type, "TSP"))
        ProblemType = TSP;
    else if (!strcmp(Type, "ATSP"))
        ProblemType = ATSP;
    else if (!strcmp(Type, "SOP")) {
        ProblemType = SOP;
        eprintf("TYPE: Type not implemented: %s", Type);
    } else if (!strcmp(Type, "HCP"))
        ProblemType = HCP;
    else if (!strcmp(Type, "CVRP")) {
        ProblemType = CVRP;
        eprintf("TYPE: Type not implemented: %s", Type);
    } else if (!strcmp(Type, "TOUR")) {
        ProblemType = TOUR;
        eprintf("TYPE: Type not implemented: %s", Type);
    } else if (!strcmp(Type, "HPP"))
        ProblemType = HPP;
    else
        eprintf("Unknown TYPE: %s", Type);
}

/*
   The ReadTour function reads a tour from a file.

   The format is as follows: 

   OPTIMUM = <real>
   Known optimal tour length. A run will be terminated as soon as a tour 
   length less than or equal to optimum is achieved.
   Default: MINUS_INFINITY.

   TOUR_SECTION :
   A tour is specified in this section. The tour is given by a list of integers
   giving the sequence in which the nodes are visited in the tour. The tour is
   terminated by a -1. 

   EOF
   Terminates the input data. The entry is optional.

   Other keywords in TSPLIB format may be included in the file, but they are 
   ignored.
*/

void ReadTourMy(char *FileName, FILE ** File)
{
    char *Line, *Keyword, *Token;
    unsigned int i;
    int Done = 0;

    if (!(*File = fopen(FileName, "r")))
        eprintf("Cannot open tour file: \"%s\"", FileName);
    while ((Line = ReadLine(*File))) {
        if (!(Keyword = strtok(Line, Delimiters)))
            continue;
        for (i = 0; i < strlen(Keyword); i++)
            Keyword[i] = (char) toupper(Keyword[i]);
        if (!strcmp(Keyword, "COMMENT") ||
            !strcmp(Keyword, "DEMAND_SECTION") ||
            !strcmp(Keyword, "DEPOT_SECTION") ||
            !strcmp(Keyword, "DISPLAY_DATA_SECTION") ||
            !strcmp(Keyword, "DISPLAY_DATA_TYPE") ||
            !strcmp(Keyword, "EDGE_DATA_FORMAT") ||
            !strcmp(Keyword, "EDGE_DATA_SECTION") ||
            !strcmp(Keyword, "EDGE_WEIGHT_FORMAT") ||
            !strcmp(Keyword, "EDGE_WEIGHT_SECTION") ||
            !strcmp(Keyword, "EDGE_WEIGHT_TYPE") ||
            !strcmp(Keyword, "FIXED_EDGES_SECTION") ||
            !strcmp(Keyword, "NAME") ||
            !strcmp(Keyword, "NODE_COORD_SECTION") ||
            !strcmp(Keyword, "NODE_COORD_TYPE")
            || !strcmp(Keyword, "TYPE"));
        else if (strcmp(Keyword, "OPTIMUM") == 0) {
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, GainInputFormat, &Optimum))
                eprintf("[%s] (OPTIMUM): integer expected", FileName);
        } else if (strcmp(Keyword, "DIMENSION") == 0) {
            int Dim = 0;
            if (!(Token = strtok(0, Delimiters)) ||
                !sscanf(Token, "%d", &Dim))
                eprintf("[%s] (DIMENSION): integer expected", FileName);
            if (Dim != DimensionSaved)
                eprintf
                    ("[%s] (DIMENSION): does not match problem dimension",
                     FileName);
        } else if (!strcmp(Keyword, "TOUR_SECTION")) {
            Read_TOUR_SECTION(File);
            Done = 1;
        } else if (!strcmp(Keyword, "EOF"))
            break;
        else
            eprintf("[%s] Unknown Keyword: %s", FileName, Keyword);
    }
    if (!Done)
        eprintf("Missing TOUR_SECTION in tour file: \"%s\"", FileName);
    fclose(*File);
}
