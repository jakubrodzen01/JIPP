#include <stdio.h>
#include <windows.h>

#pragma warning(disable: 4996)

extern void error(int nr, char* str);

void strony(int wybor[], int dlugosc_strony)
{
	FILE* fw = NULL;
	FILE* fp = NULL;
	fw = fopen("final_text.txt", "w");
	fp = fopen("text.txt", "r");
	if (fw == NULL || fp == NULL)
	{
		error(4, "blad otwarcia pliku text.txt lub final_text.txt");
	}
	int enter = 3, nr_strony=1;
	char z;

	SYSTEMTIME st;

	GetLocalTime(&st);

	//Pierwszy naglowek
	if (wybor[0] == 1)
		fprintf(fw, "nazwa pliku: %s", "final_text.txt ");
	if (wybor[1] == 1)
		fprintf(fw, "strona numer: %d ", nr_strony);
	if (wybor[2] == 1)
		fprintf(fw, "data stronicowania: %d.%d.%dr.", st.wDay, st.wMonth, st.wYear);
	fprintf(fw, "%s", "\n\n\n");

	//Nastepne naglowki
	while ((z = fgetc(fp)) != EOF)
	{
		if (z == '\n')
		{
			enter++;
			
			if (enter == dlugosc_strony)
			{
				nr_strony++;
				if (wybor[0] == 1)
					fprintf(fw, "\nnazwa pliku: %s", "final_text.txt ");
				if (wybor[1] == 1)
					fprintf(fw, "strona numer: %d ", nr_strony);
				if (wybor[2] == 1)
					fprintf(fw, "data stronicowania: %d.%d.%dr.", st.wDay, st.wMonth, st.wYear);
				fprintf(fw, "%s", "\n\n");

				enter = 3;
			}
		}
		fputc(z, fw);

	}

	fclose(fw);
	fclose(fp);
	fw = NULL;
	fp = NULL;
}