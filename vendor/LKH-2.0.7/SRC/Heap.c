#include "LKH.h"
#include "Heap.h"





/*
 * A binary heap is used to implement a priority queue.
 *
 * A heap is useful in order to speed up the computations of minimum
 * spanning trees. The elements of the heap are the nodes, and the
 * priorities (ranks) are their associated costs (their minimum distance
 * to the current tree).
 */

static int HeapCount;    /* Its current number of elements */
static int HeapCapacity; /* Its capacity */

/*
 * The MakeHeap function creates an empty heap.
 */

void MakeHeap(int Size)
{
    assert(lkh.Heap = (Node **) malloc((Size + 1) * sizeof(Node *)));
    HeapCapacity = Size;
    HeapCount = 0;
}

/*
 * The HeapSiftUp function is called when the rank of a node is decreased,
 * or when a node is inserted into the heap.
 * The function moves the node forward in the heap (the foremost node
 * of the heap has the lowest rank).
 * When calling HeapSiftUp(N), node N must belong to the heap.
 */

void HeapSiftUp(Node * N)
{
    int Loc = N->Loc, Parent = Loc / 2;

    while (Parent && N->Rank < lkh.Heap[Parent]->Rank) {
        lkh.Heap[Loc] = lkh.Heap[Parent];
        lkh.Heap[Loc]->Loc = Loc;
        Loc = Parent;
        Parent /= 2;
    }
    lkh.Heap[Loc] = N;
    N->Loc = Loc;
}

/*
 * The HeapSiftDown function is called by the Heapify and HeapDeleteMin
 * functions. The function moves the node backwards in the heap
 * (the foremost node of the heap has the lowest rank).
 * When calling HeapSiftDown(N), node N must belong to the heap.
 */

void HeapSiftDown(Node * N)
{
    int Loc = N->Loc, Child;

    while (Loc <= HeapCount / 2) {
        Child = 2 * Loc;
        if (Child < HeapCount && lkh.Heap[Child + 1]->Rank < lkh.Heap[Child]->Rank)
            Child++;
        if (N->Rank <= lkh.Heap[Child]->Rank)
            break;
        lkh.Heap[Loc] = lkh.Heap[Child];
        lkh.Heap[Loc]->Loc = Loc;
        Loc = Child;
    }
    lkh.Heap[Loc] = N;
    N->Loc = Loc;
}

/*
 * The HeapDeleteMin function deletes the foremost node from the heap.
 * The function returns a pointer to the deleted node (0, if the heap
 * is empty).
 */

Node *HeapDeleteMin()
{
    Node *Remove;

    if (!HeapCount)
        return 0;
    Remove = lkh.Heap[1];
    lkh.Heap[1] = lkh.Heap[HeapCount--];
    lkh.Heap[1]->Loc = 1;
    HeapSiftDown(lkh.Heap[1]);
    Remove->Loc = 0;
    return Remove;
}

/*
 * The HeapInsert function inserts a node N into the heap.
 * When calling HeapInsert(N), node N must not belong to the heap.
 */

void HeapInsert(Node * N)
{
    HeapLazyInsert(N);
    HeapSiftUp(N);
}

/*
 * The HeapDelete function deletes a node N from the heap.
 */

void HeapDelete(Node * N)
{
    int Loc = N->Loc;
    if (!Loc)
        return;
    lkh.Heap[Loc] = lkh.Heap[HeapCount--];
    lkh.Heap[Loc]->Loc = Loc;
    if (lkh.Heap[Loc]->Rank > N->Rank)
        HeapSiftDown(lkh.Heap[Loc]);
    else
        HeapSiftUp(lkh.Heap[Loc]);
    N->Loc = 0;
}

/*
 * The HeapLazyInsert function inserts a node as the last node of the heap.
 * This may destroy the heap condition, but it can later be restored by
 * calling the Heapify function.
 * When calling HeapLazyInsert(N), node N must not belong to the heap.
 */

void HeapLazyInsert(Node * N)
{
    assert(HeapCount < HeapCapacity);
    lkh.Heap[++HeapCount] = N;
    N->Loc = HeapCount;
}

/*
 * The Heapify function constructs a heap from its nodes.
 */

void Heapify()
{
    int Loc;
    for (Loc = HeapCount / 2; Loc >= 1; Loc--)
        HeapSiftDown(lkh.Heap[Loc]);
}
