#ifndef ROOT_H
#define ROOT_H

typedef double (*pfunc_t)(double);

extern int iterations;

double root(pfunc_t f, pfunc_t g, pfunc_t fd, pfunc_t gd, double a, double b, double eps1);

#endif