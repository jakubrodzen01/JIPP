#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

extern void error(int nr);
extern void rozkladLU(double** A, double** L, double** U, int n);
extern void liczX(double** L, double** U, double* b, double* x, double* z, int n);
extern void wypisz(double**A, double** L, double** U, double* b, double* x, double* z, int n);
extern double WyzMac(double** A, int n);

int main()
{
	FILE* fp = NULL;
	if (!(fp = fopen("dane.txt", "r")))
		error(1);
	int n;
	double** A, **L, **U, *b, *x, *z;
	if (fscanf(fp, "%d", &n) != 1)
		error(2);
	if (n < 2)
		error(3);
	
	//alokacja dla wszystkich tablic
	A = (double**)malloc((unsigned)n * sizeof(double*));
	for (int i = 0; i < n; i++)
		A[i] = (double*)malloc((unsigned)n * sizeof(double));
	L = (double**)malloc((unsigned)n * sizeof(double*));
	for (int i = 0; i < n; i++)
		L[i] = (double*)malloc((unsigned)n * sizeof(double));
	U = (double**)malloc((unsigned)n * sizeof(double*));
	for (int i = 0; i < n; i++)
		U[i] = (double*)malloc((unsigned)n * sizeof(double));
	b = (double*)malloc((unsigned)n * sizeof(double));
	x = (double*)malloc((unsigned)n * sizeof(double));
	z = (double*)malloc((unsigned)n * sizeof(double));
	
	//wczytanie macierzy A
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (fscanf(fp, "%lf", &A[i][j]) != 1)
				error(2);
	//wczytanie wektora b
	for (int i = 0; i < n; i++)
		if (fscanf(fp, "%lf", &b[i]) != 1)
			error(2);

	if (WyzMac(A, n) == 0)
		error(4);

	rozkladLU(A, L, U, n);
	liczX(L, U, b, x, z, n);
	wypisz(A, L, U, b, x, z, n);

	//zwalnianie
	for (int i = 0; i < n; i++)
	{
		if (A[i])
		{
			free(A[i]);
		}
		if (L[i])
		{
			free(L[i]);
		}
		if (U[i])
		{
			free(U[i]);
		}
	}
	free(A);
	free(L);
	free(U);
	A = NULL;
	L = NULL;
	U = NULL;


	return 0;
}