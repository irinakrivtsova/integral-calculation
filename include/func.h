#ifndef FUNC_H
#define FUNC_H

typedef double (*pfunc_t)(double);

double func1(double x);
double func2(double x);
double func3(double x);

double der1(double x);
double der2(double x);
double der3(double x);

extern int iterations;

double root(pfunc_t f, pfunc_tg, pfunc_t fd, pfunc_t gd, double a, double b, double eps1);

double integral(pfunc_t f, double a, double b, double eps2);

#endif