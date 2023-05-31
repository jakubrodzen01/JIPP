#include<stdio.h>
#define MAX_ERR 5
static char* p[] = { ""," zle dane", "zly naglowek", "zle podana dlugosc strony", " otwarcie pliku", " nieznany ",};
void error(int nr, char* str)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	printf("Blad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}