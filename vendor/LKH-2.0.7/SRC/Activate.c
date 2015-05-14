#include "LKH.h"

/*
 * If a node is made "active", attempts are made to find an improving 
 * move with the node as anchor node, t1.
 *
 * The Active function makes a node active by inserting it into a 
 * queue of active nodes. FirstActive denotes the front node of 
 * the queue. LastActive denotes the rear. 
 *
 * The queue is implemented as a circular list in which the Next field 
 * of each Node references the successor node. 
 *
 * A node is member of the queue iff its Next != 0. The function has no 
 * effect if the node is already in the queue. 
 *
 * The function is called from the StoreTour function.  
*/

void Activate(Node * N)
{
    if (N->Next != 0)
        return;
    if (lkh.FirstActive == 0)
        lkh.FirstActive = lkh.LastActive = N;
    else
        lkh.LastActive = lkh.LastActive->Next = N;
    lkh.LastActive->Next = lkh.FirstActive;
}
