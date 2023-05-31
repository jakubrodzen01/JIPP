#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma warning(disable:4996)
#define MAX_BUFOR 2000
#define N 10

struct DANE
{
	char* imie;
	char* nazwisko;
	size_t rok;
};

DANE tab[N];
int size = 0;

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

void menu()
{
	size_t it;
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", strtab[it]);
	}
}

char findtab[4][20] =
{
	"0 - name",
	"1 - lastname",
	"2 - year",
	"3 - back"
};

void display()
{
	if (size == 0)
	{
		printf("Stos pusty\n");
		return;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		printf("\t%s %s %4d\n", tab[i].imie, tab[i].nazwisko, tab[i].rok);
	}
}

void free_dane(int i)
{
	free(tab[i].imie);
	free(tab[i].nazwisko);
}

void count()
{
	printf("Ilosc elementow na stosie: %d\n", size);
}

void push()
{
	char bufor[MAX_BUFOR];
	unsigned len;
	if (size >= N)
	{
		printf("Stos pelny\n");
		return;
	}
	DANE* nowy;
	nowy = (DANE*)malloc(sizeof(DANE));
	printf("podaj imie, nazwisko, rok:");
	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	tab[size].imie = (char*)malloc(len);
	strcpy(tab[size].imie, bufor);

	fgets(bufor, MAX_BUFOR, stdin);
	len = (unsigned)strlen(bufor);
	bufor[len - 1] = '\0';
	tab[size].nazwisko = (char*)malloc(len);
	strcpy(tab[size].nazwisko, bufor);

	fgets(bufor, MAX_BUFOR, stdin);
	tab[size].rok = atoi(bufor);

	size++;

	display();
}

void pop()
{
	if (size == 0)
	{
		printf("Stos pusty\n");
		return;
	}
	free_dane(size - 1);
	size--;
	display();
}

void clear()
{
	if (size == 0)
		return;
	while (size != 0)
	{
		free_dane(size-1);
		size--;
	}
}

void find()
{
	if (size == 0)
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
			for (int i = 0; i < size; i++)
			{
				if (!strcmp(tab[i].imie, name))
				{
					printf("\t%s %s %4d\n", tab[i].imie, tab[i].nazwisko, tab[i].rok);
				}
			}
			break;
		case NAZWISKO:
			char lastname[512];
			printf("Podaj nazwisko: ");
			scanf("%s", &lastname);
			for (int i = 0; i < size; i++)
			{
				if (!strcmp(tab[i].nazwisko, lastname))
				{
					printf("\t%s %s %4d\n", tab[i].imie, tab[i].nazwisko, tab[i].rok);
				}
			}
			break;
		case ROK:
			int rok;
			printf("Podaj rok: ");
			scanf("%d", &rok);
			for (int i = 0; i < size; i++)
			{
				if (rok == tab[i].rok)
				{
					printf("\t%s %s %4d\n", tab[i].imie, tab[i].nazwisko, tab[i].rok);
				}
			}
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
	//LIFO_tab
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