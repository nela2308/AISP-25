#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Osoba {
	char ime[50];
	char prezime[50];
	int gr;
	struct Osoba* next;
};
// dinamièki dodaje novi element na poèetak liste
int UnosP(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.");
		return -1;
	}
	else {
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;
	}

	return 1;
}
// ispisuje listu
void Ispisi(struct Osoba* o) {
	if (o == NULL) {
		printf("Lista je prazna.\n");
	}
	else {
		while (o != NULL) {
			printf("%s %s %d\n", o->ime, o->prezime, o->gr);
			o = o->next;
		}
	}
}

// dinamièki dodaje novi element na kraj liste
int UnosK(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.\n");
		return -1;
	}
	else {
		while (o->next != NULL) {
			o = o->next;
		}
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;
	}
	return 1;
}

// pronalazi element u listi (po prezimenu)
struct Osoba* PronadjiPoPrezimenu(struct Osoba* o, char* prezime) {
	while (o->next != NULL && strcmp(o->prezime, prezime) != 0) {
		o = o->next;
	}

	return o;
}
// briše odreðeni element iz liste (npr po prezimenu)
struct Osoba* Brisi(struct Osoba* o, char* prezime) {
	struct Osoba* temp;


	while (o->next != NULL && strcmp(o->prezime, prezime) != 0) {
		o = o->next;
	}

	if (o->next == NULL) {     // ** OVO SPREÈAVA NULL DEREFERENCE **
		printf("Osoba nije pronadjena.\n");
		return NULL;
	}
	temp = o->next;
	o->next = temp->next;
	free(temp);

}
int main() {
	struct Osoba Head;
	Head.next = NULL;

	struct Osoba* TraziP = NULL;
	char odabir;
	int gr, status;
	char ime[30], prezime[30];

	while (1) {
		printf("\nOdaberite:\n");
		printf("1 - Unos na pocetak\n");
		printf("2 - Ispisi listu\n");
		printf("3 - Unos na kraj\n");
		printf("4 - Pronadji po prezimenu\n");
		printf("5 - Brisi po prezimenu\n");
		printf("K - Kraj\n");

		scanf(" %c", &odabir);

		switch (odabir) {

		case '1':
			printf("Unesi ime, prezime i godinu rodjenja:\n");
			scanf("%s %s %d", ime, prezime, &gr);

			status = UnosP(&Head, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu na pocetak!\n");
			else
				printf("Uspjesno dodano na pocetak.\n");

			break;

		case '2':
			Ispisi(Head.next);
			break;

		case '3':
			printf("Unesi ime, prezime i godinu rodjenja:\n");
			scanf("%s %s %d", ime, prezime, &gr);

			status = UnosK(&Head, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu na kraj!\n");
			else
				printf("Uspjesno dodano na kraj.\n");

			break;

		case '4':
			printf("Unesite prezime:\n");
			scanf("%s", prezime);

			TraziP = PronadjiPoPrezimenu(Head.next, prezime);
			if (TraziP != NULL)
				printf("%s %s %d\n", TraziP->ime, TraziP->prezime, TraziP->gr);
			else
				printf("Nije pronadjeno.\n");

			break;

		case '5':
			printf("Unesite prezime:\n");
			scanf("%s", prezime);

			if (Brisi(&Head, prezime) == NULL)
				printf("Brisanje nije uspjelo.\n");
			else
				printf("Uspjesno obrisano.\n");

			break;

		case 'K':
		case 'k':
			printf("Kraj programa.\n");
			return 0;

		default:
			printf("Pogresan odabir.\n");
		}
	}
}