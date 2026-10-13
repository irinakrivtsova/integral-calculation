// Вычисление интеграла с помощью функции Симпсона
// In = h / 3 * (F_0 + 4F_1 + 2F_2 + 4F_3 + ... + 4F_n-3 + 2F_n-2 + 4F_n-1 +F_n)
// F_i = F(a + i * h), где F(x) = f(x) - g(x), h = (b - a) / n

#include "integral.h"

// По правилу Рунге |I - I_n| ~ p * |I_n - I_2n|, p = 1/15 для формулы Симпсона
static const double P = 1.0 / 15.0;

double integral(pfunc_t f, double a, double b, double eps2)
{
    double In = 0;
    int n = 10;
    double h = (b - a) / n;

    double F0 = f(a);
    double Fn = f(a + n * h);
    double s2 = 0;
    double s4 = 0;
    for (int i = 1; i < n; i++)
    {
        double Fi = f(a + i * h);
        if (i % 2 == 1)
        {
            s4 += Fi;
        }
        else
        {
            s2 += Fi;
        }
    }
    // Формула Симпсона
    In = (h / 3) * (F0 + 4 * s4 + 2 * s2 + Fn);
    
    // Реализовано использование значений из Fn для F2n
    double newS4;
    double prevIn;
    do
    {
        prevIn = In;
        n *= 2;
        h /= 2;
        newS4 = 0;
        
        for (int i = 1; i < n; i += 2)
        {
            newS4 += f(a + i * h);
        }

        s2 = s4 + s2;
        s4 = newS4;
        In = (h / 3) * (F0 + 4 * s4 + 2 * s2 + Fn);
    }
    while ((P * fabs(In - prevIn)) >= eps2); // проверка по правилу Рунге
    return In;
}