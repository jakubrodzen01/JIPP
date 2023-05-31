#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma warning(disable:4996)
#define MAX_BUFOR 2000

struct DANE
{
	char* imie;
	char* nazwisko;
	size_t rok;
	DANE* n;
};
DANE* H, * B;

enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_PRINT,
	INTERF_COUNT,
	INTERF_FIND_LASTNAME,
	INTERF_STOP,
	INTERF_TOT
};

enum FIND_WHAT
{
	IMIE,
	NAZWISKO,
	ROK,
	FINISH
};

char strtab[7][20] =
{
	"0 - push",
	"1 - pop",
	"2 - clear",
	"3 - print",
	"4 - count",
	"5 - find",
	"6 - finish"
};

char findtab[4][20] =
{
	"0 - name",
	"1 - lastname",
	"2 - year",
	"3 - back"
};

void menu()
{
	size_t it;
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", strtab[it]);
	}
}

void display()
{
	DANE* w;
	w = H;
	if (H == (DANE*)NULL)
	{
		printf("Kolejka pusta\n");
		return;
	}

	for (w = H; w != (DANE*)NULL; w = w->n)
	{
		printf("\t%s %s %4d\n", w->imie, w->nazwisko, w->rok);
	}
}

void free_dane(DANE* w)
{
	free(w->imie);
	free(w->nazwisko);
	free(w);
}

void count()
{
	int ile = 0;
	B = H;
	while (B != (DANE*)NULL)
	{
		ile++;
		B = B->n;
	}
	B = H;
	printf("Ilosc elementow w kolejce: %d\n", ile);
}

void push()
{
	char bufor[MAX_BUFOR];
	unsigned len;
	DANE* nowy;
	nowy = (DANE*)malloc(sizeof(DANE));
	printf("podaj imie, nazwisko, rok:");
	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	nowy->imie = (char*)malloc(len);
	strcpy(nowy->imie, bufor);

	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	nowy->nazwisko = (char*)malloc(len);
	strcpy(nowy->nazwisko, bufor);

	fgets(bufor, MAX_BUFOR, stdin);
	nowy->rok = atoi(bufor);

	nowy->n = (DANE*)NULL;

	if (H == (DANE*)NULL)
	{
		H = nowy;
		B = H;
	}
	else
	{
		B->n = nowy;
		B = nowy;
	}
	display();
}

void pop()
{
	B = H;
	if (H == (DANE*)NULL)
	{
		printf("Kolejka pusta\n");
		return;
	}
	H = B->n;
	free_dane(B);
	B = H;
	display();
}

void clear()
{
	DANE* N = (DANE*)NULL;
	if (H == (DANE*)NULL)
		return;
	while (H != (DANE*)NULL)
	{
		N = H->n;
		free_dane(H);
		H = N;
	}
}

void find()
{
	if (H == (DANE*)NULL)
		return;
	size_t wybor = 0;
	while (wybor >= IMIE && wybor < FINISH)
	{
		for (int i = 0; i <= FINISH; i++)
		{
			printf("%s\n", findtab[i]);
		}
		if (scanf("%d", &wybor) != 1)	exit(1); getchar();
		switch (wybor)
		{
		case IMIE:
			char name[512];
			printf("Podaj imie: ");
			scanf("%s", &name);
			B = H;
			while (B != (DANE*)NULL)
			{
				if (!strcmp(B->imie, name))
				{
					printf("\t%s %s %4d\n", B->imie, B->nazwisko, B->rok);
				}
				B = B->n;
			}
			B = H;
			break;
		case NAZWISKO:
			char lastname[512];
			printf("Podaj nazwisko: ");
			scanf("%s", &lastname);
			B = H;
			while (B != (DANE*)NULL)
			{
				if (!strcmp(B->nazwisko, lastname))
				{
					printf("\t%s %s %4d\n", B->imie, B->nazwisko, B->rok);
				}
				B = B->n;
			}
			B = H;
			break;
		case ROK:
			int rok;
			printf("Podaj rok: ");
			scanf("%d", &rok);
			B = H;
			while (B != (DANE*)NULL)
			{
				if (rok == B->rok)
				{
					printf("\t%s %s %4d\n", B->imie, B->nazwisko, B->rok);
				}
				B = B->n;
			}
			B = H;
			break;
		case FINISH:
			break;
		default:
			printf("\nNieuznawany kod operacji\n");
		}
	}
}

int main()
{
	//FIFO
	H = (DANE*)NULL;
	B = (DANE*)NULL;
	size_t op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
		if (scanf("%d", &op) != 1)	exit(1); getchar();
		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_PRINT: display();
			break;
		case INTERF_COUNT: count();
			break;
		case INTERF_FIND_LASTNAME: find();
			break;
		case INTERF_STOP: clear();
			return 0;
		default:
			printf("\nNieuznawany kod operacji\n");
		}
	}

	return 0;
}