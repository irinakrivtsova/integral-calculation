#include "main.h"

extern int iterations;
static const double epsIntegral = 0.001;
static const double epsRoot = 0.001;

// [-1.9, -1], [0, 1], [-1, 0] - отрезки для поиска точек пересечения 
// Для функций 1 и 3
static const double a13 = -1.9;
static const double b13 = -1;
// Для функций 1 и 2
static const double a12 = 0;
static const double b12 = 1;
// Для функций 2 и 3
static const double a23 = -1;
static const double b23 = 0;


// Функции для тестирования

double f1(double x) { return pow(2, x) + 1; }

double f2(double x) { return pow(x, 5); }

double f3(double x) { return (1 - x) / 3; }

double d1(double x) { return pow(2, x) * log(2); }

double d2(double x) { return 5 * pow(x, 4); }

double d3(double x) { return -1 / 3; }

pfunc_t testFuncs[] = {f1, f2, f3};
pfunc_t testders[] = {d1, d2, d3};

int main(int argc, char *argv[])
{
    if (argc > 1 && (strcmp(argv[1], "--test-root") == 0 || strcmp(argv[1], "-R") == 0))
    {
        if (argc < 3) {
            printf("Usage: %s --test-root f1:f2:a:b:eps:ans\n", argv[0]);
            return 1;
        }

        int numFunc1, numFunc2;
        double a, b, eps, ans;
        double res, absEr, relEr;

        sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &numFunc1, &numFunc2, &a, &b, &eps, &ans);

        res = root(testFuncs[numFunc1 - 1], testFuncs[numFunc2 - 1], testders[numFunc1 - 1], testders[numFunc2 - 1], a, b, eps);
        absEr = fabs(res - ans);
        relEr = fabs(absEr / ans);

        printf("%lf %lf %lf\n", res, absEr, relEr);        
    }
    else if (argc > 1 && (strcmp(argv[1], "--test-integral") == 0 || strcmp(argv[1], "-I") == 0))
    {
        if (argc < 3) {
            printf("Usage: %s --test-integral f:a:b:eps:ans\n", argv[0]);
            return 1;
        }
        
        int numFunc;
        double a, b, eps, ans;
        double res, absEr, relEr;

        sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &numFunc, &a, &b, &eps, &ans);
        res = integral(testFuncs[numFunc - 1], a, b, eps);
        absEr = fabs(res - ans);
        relEr = fabs(absEr / ans);

        printf("%lf %lf %lf\n", res, absEr, relEr);
    }
    else if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
    {
        printf("Options:\n  --help, -h\t\tOutput of command line keys\n");
        printf("  --root, -r\t\tPrinting the abscissas of the intersection points of the curves\n");
        printf("  --iterations, -i\tPrinting the number of iterations required to solve the equations\n");
        printf("  --test-root, -R\tTesting the root function\n");
        printf("  --test-integral, -I\tTesting the integral function\n");
    }
    else if (argc == 1)
    {   
        double x1 = root(func1, func3, der1, der3, a13, b13, epsRoot);
        double x2 = root(func1, func2, der1, der2, a12, b12, epsRoot);
        double x3 = root(func2, func3, der2, der3, a23, b23, epsRoot);
        double res = integral(func1, x1, x2, epsIntegral)
                   - integral(func2, x3, x2, epsIntegral)
                   - integral(func3, x1, x3, epsIntegral);

        printf("%lf\n", res);
    }
    else if (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-r") == 0)
    {

        double x1 = root(func1, func3, der1, der3, a13, b13, epsRoot);
        double x2 = root(func1, func2, der1, der2, a12, b12, epsRoot);
        double x3 = root(func2, func3, der2, der3, a23, b23, epsRoot);

        printf("Абсциссы точек пересечения кривых:\n");
        printf("%lf %lf %lf\n", x1, x3, x2);
    }
    else if (strcmp(argv[1], "--iterations") == 0 || strcmp(argv[1], "-i") == 0)
    {

        double x1 = root(func1, func3, der1, der3, a13, b13, epsRoot);
        int iters1 = iterations;

        double x2 = root(func1, func2, der1, der2, a12, b12, epsRoot);
        int iters2 = iterations;

        double x3 = root(func2, func3, der2, der3, a23, b23, epsRoot);
        int iters3 = iterations;

        printf("Число итераций для поиска точек пересечения:\n");
        printf("Число итераций для поиска x1: %d\n", iters1);
        printf("Число итераций для поиска x2: %d\n", iters2);
        printf("Число итераций для поиска x3: %d\n", iters3);
    }
    return 0;
}
