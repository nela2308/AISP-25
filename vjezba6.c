#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
	int element;
	Pozicija next;
};

int GeneriranjeBrojeva();
void PushStog(Pozicija, int);
void PopStog(Pozicija);
void EnqueueRed(Pozicija, int);
void DequeueRed(Pozicija);
void IspisListe(Pozicija);

int main() {

	Cvor stog, red;
	stog.next = NULL;
	red.next = NULL;

	int opcija = 1;

	srand((unsigned)time(NULL));

	while (opcija != 0) {
		printf("\nOdaberite opciju:\n");
		printf("0 - kraj programa\n");
		printf("1 - Push na stogu\n");
		printf("2 - Pop sa stoga\n");
		printf("3 - Enqueue (stavi) na red\n");
		printf("4 - Dequeue (makni) s reda\n");
		scanf(" %d", &opcija);

		switch (opcija) {

		case 0:
			printf("Program zavrsen.\n");
			opcija = 0;
			break;

		case 1:
			PushStog(&stog, GeneriranjeBrojeva());
			IspisListe(stog.next);
			break;

		case 2:
			PopStog(&stog);
			IspisListe(stog.next);
			break;

		case 3:
			EnqueueRed(&red, GeneriranjeBrojeva());
			IspisListe(red.next);
			break;

		case 4:
			DequeueRed(&red);
			IspisListe(red.next);
			break;

		default:
			printf("Opcija %d ne postoji. Pokusajte ponovno.\n", opcija);

		}

	}

	return 0;
}

int GeneriranjeBrojeva() {

	int broj = 0;
	broj = (rand() % (100 - 10) + 10);
	return broj;

}

void IspisListe(Pozicija P) {

	printf("\nIspis liste:\n");

	while (P) {
		printf(" %d", P->element);
		P = P->next;
	}

}

void PushStog(Pozicija P, int broj) {

	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(struct Cvor));
	if (temp == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return;
	}

	if (temp) {
		temp->element = broj;
		temp->next = P->next;
		P->next = temp;
	}

}

void PopStog(Pozicija P) {

	if (P->next == NULL) {
		printf("Stog je trenutno prazan.\n");
		return;
	}

	Pozicija temp;

	if (P->next != NULL) {

		temp = P->next;
		P->next = temp->next;

		free(temp);
	}

}

void EnqueueRed(Pozicija P, int broj) {

	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));
	if (temp == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return;
	}

	temp->element = broj;
	temp->next = NULL;

	if (P->next == NULL) {
		P->next = temp;
	}
	else {
		Pozicija zadnji = P->next;
		while (zadnji->next != NULL)
			zadnji = zadnji->next;
		zadnji->next = temp;
	}

}

void DequeueRed(Pozicija P) {

	if (P->next == NULL) {
		printf("\nRed je trenutno prazan.\n");
		return;
	}

	Pozicija temp = P->next;
	P->next = temp->next;

	free(temp);
}