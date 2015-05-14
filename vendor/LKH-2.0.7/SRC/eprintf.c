#include "LKH.h"
#include <stdarg.h>

/* 
 * The eprintf function prints an error message and exits.
 */

void eprintf(const char *fmt, ...)
{
    va_list args;

    if (lkh.LastLine && *lkh.LastLine)
        fprintf(stderr, "\n%s\n", lkh.LastLine);
    fprintf(stderr, "\n*** Error ***\n");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}
