#include "LKH.h"

/*
 * The WritePenalties function writes node penalties (Pi-values)
 * to file PiFileName. 
 *
 * The first line of the file contains the number of nodes.
 *
 * Each of the following lines is of the form
 *       <integer> <integer>
 * where the first integer is a node number, and the second integer 
 * is the Pi-value associated with the node.
 *
 * The function is called from the CreateCandidateSet function. 
 */

void WritePenalties()
{
    Node *N;

    if (lkh.PiFileName == 0 || !(lkh.PiFile = fopen(lkh.PiFileName, "w")))
        return;
    if (lkh.TraceLevel >= 1)
        printff("Writing PI_FILE: \"%s\" ... ", lkh.PiFileName);
    fprintf(lkh.PiFile, "%d\n", lkh.Dimension);
    N = lkh.FirstNode;
    do
        fprintf(lkh.PiFile, "%d %d\n", N->Id, N->Pi);
    while ((N = N->Suc) != lkh.FirstNode);
    fprintf(lkh.PiFile, "-1\nEOF\n");
    fclose(lkh.PiFile);
    if (lkh.TraceLevel >= 1)
        printff("done\n", lkh.PiFileName);
}
