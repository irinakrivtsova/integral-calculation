#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double (*pfunc_t)(double);

double func1(double x);
double func2(double x);
double func3(double x);

double der1(double x);
double der2(double x);
double der3(double x);

extern int iterations;

double root(pfunc_t f, pfunc_t g, pfunc_t fd, pfunc_t gd, double a, double b, double eps1);

double integral(pfunc_t f, double a, double b, double eps2);

#endif