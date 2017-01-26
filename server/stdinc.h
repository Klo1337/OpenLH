#ifndef _stdinc_h
#define _stdinc_h

/*
 * Always include stdio.h and stdlib.h.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * NULL: value for null pointers, normally defined by stdio.h.
 */

#if !defined(NULL)
#define NULL 0L
#endif

/*
 * BYTE: name a handy chunk of bits.
 */

typedef unsigned char byte;

/*
 * PI, etc.  --  mathematical constants.
 */

#define PI         3.14159265358979323846
#define TWO_PI     6.28318530717958647693
#define FOUR_PI   12.56637061435917295385
#define HALF_PI    1.57079632679489661923
#define FRTHRD_PI  4.18879020478639098462

/*
 * STREQ: string-equality macro. STRNULL: test for empty string.
 * Note that string.h should be included if these are used.
 */

#define streq(x,y) (strcmp((x), (y)) == 0)
#define strnull(x) (strcmp((x), "") == 0)

/*
 * ABS: returns the absolute value of its argument.
 * MAX: returns the argument with the highest value.
 * MIN: returns the argument with the lowest value.
 */

#define ABS(x)   (((x)<0)?-(x):(x))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

#endif  /* ! _stdinc_h */

// #define DEBUG true
