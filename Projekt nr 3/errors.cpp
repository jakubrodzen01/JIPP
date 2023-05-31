#include <stdio.h>
#include <stdlib.h>
#define MAX_ERR 5
static char* p[] = {" ",
"Blad otwarcia pliku dane.txt",
"Bledne dane",
"Macierz musi byc stopnia co najmniej 2",
"Macierz nie jest macierza oznaczona (wyznacznik glowny = 0)",
"Nieznany blad"
};
void error(int nr)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	printf("Blad(%d) - %s",nr, p[k]);
	exit(nr);
}