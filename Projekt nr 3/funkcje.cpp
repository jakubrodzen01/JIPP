#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable: 4996)

extern error(int nr);

void rozkladLU(double** A, double** L, double** U, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < i)
                L[j][i] = 0;
            else
            {
                L[j][i] = A[j][i];
                for (int k = 0; k < i; k++)
                {
                    L[j][i] = L[j][i] - L[j][k] * U[k][i];
                }
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (j < i)
                U[i][j] = 0;
            else if (j == i)
                U[i][j] = 1;
            else
            {
                if (L[i][i] != 0)
                     U[i][j] = A[i][j] / L[i][i];
                for (int k = 0; k < i; k++)
                {
                    if(L[i][i]!=0)
                        U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                }
            }
        }
    }
}
void liczX(double** L, double** U, double *b, double *x, double *z, int n)
{
    for (int i = 0; i < n; i++)
        z[i] = b[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (i != j)
                z[i] = z[i] - L[i][j] * z[j];
        }
        if (L[i][i] != 0)
            z[i] = z[i] / L[i][i];
    }
    for (int i = 0; i < n; i++)
        x[i] = z[i];
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                x[i] = x[i] - U[i][j] * x[j];
        }
        if (U[i][i] != 0)
            x[i] = x[i] / U[i][i];
    }
}
void wypisz(double** A, double** L, double** U, double* b, double* x, double* z, int n)
{
    printf("Macierz A: \n");
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < n; j++)
        {
            k++;
            printf("%lf ", A[i][j]);
            if (k == n)
                printf("\n");
        }
    }
    printf("\nWektor b: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", b[i]);
    }
    printf("\n\nMacierz L: \n");
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < n; j++)
        {
            k++;
            printf("%lf ", L[i][j]);
            if (k == n)
                printf("\n");
        }
    }
    printf("\nMacierz U: \n");
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < n; j++)
        {
            k++;
            printf("%lf ", U[i][j]);
            if (k == n)
                printf("\n");
        }
    }
    printf("\nWektor z: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", z[i]);
    }
    printf("\n\nWektor x: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", x[i]);
    }
}
double WyzMac(double** A, int n) 
{
    if (n == 1) return A[0][0];
    if (n == 2) return (A[0][0] * A[1][1] - A[1][0] * A[0][1]);
    float wyznacznik = 0;
    int pom_r, pom_s;
    int i, r;
    for (i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            double** mac_dop;
            if (!(mac_dop = (double**)malloc((n - 1) * sizeof(double*)))) return -1;
            for (int i = 0; i < n - 1; i++) if (!(mac_dop[i] = (double*)malloc((n - 1) * sizeof(float)))) return -1;
            pom_r = pom_s = 0;
            for (r = 0; r < n - 1; r++) 
            {
                if (r == i) pom_r = 1;
                for (int s = 0; s < n - 1; s++) 
                {
                    if (j == s) pom_s = 1;
                    mac_dop[r][s] = A[r + pom_r][s + pom_s];
                }
                pom_s = 0;
            }
            wyznacznik += pow(-1, i + j) * A[i][j] * WyzMac(mac_dop, n - 1);
        }
    }
    return wyznacznik / n;
}