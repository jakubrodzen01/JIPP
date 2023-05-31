#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M 20                                //liczba calkowita dodatnia

#pragma warning(disable: 4996)

double sz(double x, double delta, int* ptr1, int* ptr2, int* ls)
{
    double d = 1, s = 1;
    int n = 3;
    do
    {
        if (*ls == M)
        {
            *ptr1 = 1;
            break;
        }

        if (n == 3)
        {
            d *= (n - 2) * x / n;
            s -= d;
            n = n + 3;
            *ls += 1;
        }
        else
        {
            d *= (n - 4) * x / n;
            s -= d;
            n = n + 3;
            *ls += 1;
        }
    } while (fabs(d) >= delta);

    if (*ls == M)
        *ptr1 = 1;
    if (fabs(d) < delta)
        *ptr2 = 1;

    return s;
}

int main()
{
    double a, b, n, dx, delta, x, y, z;
    printf("Podaj przedzial [a,b], ilosc przedzialow n, dokladnosc delta: ");
    if (scanf("%lf %lf %lf %lf", &a, &b, &n, &delta) != 4 || a > b || a < -1 || b > 1 || n <= 0 || delta < 0)
    {
        printf("Bledne dane\n");
        system("pause");
        exit(1);
    }
    dx = (b - a) / n;

    for (x = a; x <= b + 0.5 * dx; x += dx)
    {
        int k1 = 0, k2=0, d = 0;
        int* ptr1 = &k1;
        int* ptr2 = &k2;
        int* ls = &d;
        
        if(x < 1 - 0.5*dx)
        {
            y = sz(x, delta, ptr1, ptr2, ls);
            z = pow(1 - x, 1 / 3.);
        }
        else 
        {
            y = 0;
            z = 0;
        }
        printf("\t%10.2lf\t\t%15.4le\t\t%15.4le\t\t%d\t\t", x, y, z, d);

        if (k1 == 1 && k2 == 1)
            printf("Oba warunki\n");
        else if (k1 == 1)
            printf("Osiagnieto M\n");
        else if (k2 == 1)
            printf("Osiagnieto dokladnosc\n");

        if (y == 0 && z == 0)
            printf("Szczegolny przypadek\n");
    }
    return 0;
}
