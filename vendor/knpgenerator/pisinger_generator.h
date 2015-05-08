



/* ======================================================================
	     GENERATOR.c, David Pisinger   april 1994
   ====================================================================== */

/* This is the C-code corresponding to the paper:
 *
 *   D. Pisinger
 *   Core problems in Knapsack Algorithms
 *   Operations Research (accepted for publication)
 *
 * Further details on the project can also be found in
 *
 *   D. Pisinger
 *   Algorithms for Knapsack Problems
 *   Report 95/1, DIKU, University of Copenhagen
 *   Universitetsparken 1
 *   DK-2100 Copenhagen
 *
 * The current code generates randomly generated instances and
 * writes them to a file. Different capacities are considered to
 * ensure proper testing.
 *
 * The code has been tested on a hp9000/735, and conforms with the
 * ANSI-C standard apart from some of the timing routines (which may
 * be removed). To compile the code use:
 *
 *   cc -Aa -O -o generator generator.c -lm
 * 
 * The code is run by issuing the command
 *
 *   generator n r type i S
 *
 * where n: number of items, 
 *       r: range of coefficients, 
 *       type: 1=uncorr., 2=weakly corr., 3=strongly corr., 4=subset sum
 *       i: instance no
         S: number of tests in series (typically 1000)
 * output will be written to the file "test.in".
 *
 * Please do not re-distribute. A new copy can be obtained by contacting
 * the author at the adress below. Errors and questions are refered to:
 *
 *   David Pisinger, associate professor
 *   DIKU, University of Copenhagen,
 *   Universitetsparken 1,
 *   DK-2100 Copenhagen.
 *   e-mail: pisinger@diku.dk
 *   fax: +45 35 32 14 01
 */


#ifndef KNAPSACK_GENERATOR
#define KNAPSACK_GENERATOR

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <values.h>
#include <string.h>
#include <malloc.h>


/* ======================================================================
				     macros
   ====================================================================== */

//#define srand(x)     srand48x(x)
#define randm(x)     (lrand48x() % (x))
#define NO(f,i)      ((int) ((i+1)-f))
#define TRUE  1
#define FALSE 0


/* ======================================================================
				 type declarations
   ====================================================================== */

typedef int   boolean; /* boolean variables */
typedef short itype;   /* item profits and weights */
typedef long  stype;   /* sum of pofit or weight */

/* item */
typedef struct {
  itype   p;     /* profit */
  itype   w;     /* weight */
  boolean x;     /* solution variable */
} item;


/* =======================================================================
                                random
   ======================================================================= */

/* to generate the same instances as at HP9000 - UNIX, */
/* here follows C-versions of SRAND48, and LRAND48.  */

unsigned long _h48, _l48;

void srand48x(long s);

long lrand48x(void);

/* ======================================================================
                                 error
   ====================================================================== */

void error(char *str, ...);


/* ======================================================================
				  palloc
   ====================================================================== */

void pfree(void *p);


void * palloc(size_t no, size_t each);


/* ======================================================================
                                showitems
   ====================================================================== */

void showitems(item *f, item *l, stype c);


/* ======================================================================
				maketest
   ====================================================================== */

stype maketest(item *f, item *l, int r, int type, int v, int S);

#endif //KNAPSACK_GENERATOR


