#include "root.h"

#if defined(DIVIDING_METHOD) && defined(TANGENT_METHOD)
#error "Only one root method must be defined"
#endif

#if !defined(DIVIDING_METHOD) && !defined(TANGENT_METHOD)
#error "Root method is not defined. Use -DDIVIDING_METHOD or -DTANGENT_METHOD"
#endif

int iterations;

double root(pfunc_t f, pfunc_t g, pfunc_t fd, pfunc_t gd, double a, double b, double eps1)
{
    #if defined(DIVIDING_METHOD)

    // Метод деления отрезка пополам

    double c; // средняя точка с отрезка [a, b]
    iterations = 0;
    while ((b - a) > eps1)
    {
        c = (a + b) / 2;
        if ((f(a) - g(a)) * (f(c) - g(c)) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        iterations++;
    }
    return (a + b) / 2;

    #elif defined(TANGENT_METHOD)

    // Метод касательных

    double c; // Точка пересечения касательных с осью абцисс
    double ceps; // точка c +- эпсилон
    double d; // Точка, в которой проводится касательная к кривой F(x) = f(x) - g(x)
    iterations = 0;

    // F(a) < 0 - проверка возрастания
    int increasing = (f(a) - g(a)) < 0;
    // F((a+b)/2) > (F(a) + F(b)) / 2 - выше хорды или нет
    int above = (f((a + b) / 2) - g((a + b) / 2)) > (((f(a) - g(a)) + (f(b) - g(b))) / 2);

    int flag = 0;
    if ((increasing && !above) || (!increasing && above))
    {
        // первая и вторая производная имеют одинаковый знак
        d = b;
        flag = 1;
    }
    else
    {
        // первая и вторая производная имеют разный знак   
        d = a;
    }

    do
    {
        iterations++;

        c = d - ((f(d) - g(d)) / (fd(d) - gd(d)));

        if (flag)
        {
            ceps = c - eps1;
        }
        else
        {
            ceps = c + eps1;
        }    

        d = c;
        
    } while (((f(c) - g(c)) * (f(ceps) - g(ceps))) > 0); // сравнение знаков F(c) и F(ceps)
    return (c + ceps) / 2;

    #endif
}
