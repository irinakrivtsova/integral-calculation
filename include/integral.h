#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <stdlib.h>
#include <math.h>

typedef double (*pfunc_t)(double);

double integral(pfunc_t f, double a, double b, double eps2);

#endif