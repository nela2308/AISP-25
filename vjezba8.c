#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct Cvor;
typedef struct Cvor* Position;

struct Cvor
{
	int El;
	Position Next;
};

int Push(Position, int);
int Pop(Position);
int Calculate(int, char, int);

int main()
{
	struct Cvor head;
	FILE* dat;
	char ime_dat[1024] = { 0 };

	head.Next = NULL;

	printf("\r\nUnesite ime datoteke za citanje : ");
	scanf(" %s", ime_dat);
	printf("\r\n\r\nIzraz :\t");

	dat = fopen(ime_dat, "r");
	if (dat == NULL)
	{
		printf("\r\nGreska u citanju datoteke!");
		return -1;
	}
	else
	{
		while (!feof(dat))
		{
			char data[32] = { 0 };
			int x;

			fscanf(dat, " %s", data);
			printf(" %s", data);

			x = atoi(data);
			if (x == 0 && data[0] != '0')
			{
				int x, y, n;

				y = Pop(&head);
				x = Pop(&head);
				n = Calculate(x, data[0], y);
				Push(&head, n);
			}
			else
				Push(&head, x);
		}
		fclose(dat);
	}

	printf("\r\n\r\nRezultat: %d\n", head.Next->El);
	free(head.Next);
}

int Push(Position P, int n)
{
	Position q;

	q = (Position)malloc(sizeof(Cvor));
	if (q)
	{
		q->El = n;
		q->Next = P->Next;
		P->Next = q;
	}
	return 0;
}

int Pop(Position P)
{
	Position q;
	int n = 0;

	if (P->Next != NULL)
	{
		q = P->Next;
		P->Next = q->Next;
		n = q->El;
		free(q);
	}
	return n;
}

int Calculate(int x, char c, int y)
{
	int n = 0;
	switch (c)
	{
	case '+':
		n = x + y;
		break;
	case '-':
		n = x - y;
		break;
	case '*':
		n = x * y;
		break;
	case '/':
		if (y != 0)
			n = x / y;
		else
			printf("\r\nNe moze se dijeliti s 0.\r\n");
		break;
	case '%':
		n = x % y;
		break;
	default:
		break;
	}
	return n;
}