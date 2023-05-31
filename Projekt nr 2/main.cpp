#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

extern void strony(int wybor[], int dlugosc_strony);
extern void error(int nr, char* str);

int main()
{
	int wybor[3];
	
	//Co znajduje sie w naglowku
	for(int i=0; i<3; i++)
	{
		printf("Czy w naglowku ma sie znajdowac ");
		if (i == 0)
			printf("nazwa pliku? (1-tak/0-nie) ");
		if (i == 1)
			printf("numer strony? (1-tak/0-nie) ");
		if (i == 2)
			printf("data wydruku? (1-tak/0-nie) ");

		if (!(scanf("%d", &wybor[i]))||(wybor[i]!=0 && wybor[i]!=1))
		{
			error(1, "nalezy wpisywac 1 lub 0");
		}
	}
	if (wybor[0] == 0 && wybor[1] == 0 && wybor[2] == 0)
	{
		error(2, "naglowek powinien zawierac w sobie chociaz jedna informacje");
	}
	int dlugosc_strony;
	printf("Jak dluga ma byc strona (liczac ze naglowek jest pierwszym wierszem strony): ");
	if (!(scanf("%d", &dlugosc_strony)) || dlugosc_strony<4)
	{
		error(3, "dlugosc strony powinna byc liczba dodatnia wieksza od 3");
	}
	
	//stronicowanie
	strony(wybor, dlugosc_strony);

	return 0;
}
