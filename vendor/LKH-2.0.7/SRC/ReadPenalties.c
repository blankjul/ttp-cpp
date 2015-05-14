#include "LKH.h"

/*
 * The ReadPenalties function attempts to read node penalties (Pi-values)
 * from file. 
 *
 * The first line of the file contains the number of nodes.
 *
 * Each of the following lines is of the form
 *       <integer> <integer>
 * where the first integer is a node number, and the second integer 
 * is the Pi-value associated with the node.
 *
 * If reading succeeds, the function returns 1; otherwise 0.
 *
 * The function is called from the CreateCandidateSet function. 
 */

int ReadPenalties()
{
    int i, Id;
    Node *Na, *Nb = 0;
    static int PenaltiesRead = 0;

    if (lkh.PiFileName == 0)
        return 0;
    if (PenaltiesRead || strcmp(lkh.PiFileName, "0") == 0)
        return PenaltiesRead = 1;
    if (!(lkh.PiFile = fopen(lkh.PiFileName, "r")))
        return 0;
    if (lkh.TraceLevel >= 1)
        printff("Reading PI_FILE: \"%s\" ... ", lkh.PiFileName);
    fscanint(lkh.PiFile, &i);
    if (i != lkh.Dimension)
        eprintf("PI_FILE \"%s\" does not match problem", lkh.PiFileName);
    fscanint(lkh.PiFile, &Id);
    assert(Id >= 1 && Id <= lkh.Dimension);
    lkh.FirstNode = Na = &lkh.NodeSet[Id];
    fscanint(lkh.PiFile, &Na->Pi);
    for (i = 2; i <= lkh.Dimension; i++) {
        fscanint(lkh.PiFile, &Id);
        assert(Id >= 1 && Id <= lkh.Dimension);
        Nb = &lkh.NodeSet[Id];
        fscanint(lkh.PiFile, &Nb->Pi);
        Nb->Pred = Na;
        Na->Suc = Nb;
        Na = Nb;
    }
    lkh.FirstNode->Pred = Nb;
    Nb->Suc = lkh.FirstNode;
    fclose(lkh.PiFile);
    if (lkh.TraceLevel >= 1)
        printff("done\n");
    return PenaltiesRead = 1;
}
