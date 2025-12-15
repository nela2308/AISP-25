#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>                 
#include <time.h>

struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
    int element;
    int prioritet;
    Pozicija next;
};

int GeneriranjeBroja(int, int);
void PushStog(Pozicija, int, int*);
void PopStog(Pozicija, int*);
void EnqueueRed(Pozicija, int);
void DequeueRed(Pozicija);
void IspisListe(Pozicija);

int main() {
    Cvor stog, red;
    stog.next = NULL;
    red.next = NULL;

    int maxS = 0, _stog = 0;
    srand((unsigned)time(NULL));

    while (maxS < 5 || _stog > 20) {
        printf("Unesite max velicinu stoga (5-20): ");
        scanf("%d", &maxS);
    }

    int opcija = -1;
    while (opcija != 0) {
        printf("\nIzaberi opciju:\n");
        printf("0 - zavrsetak programa\n");
        printf("1 - push na stog\n");
        printf("2 - pop sa stoga\n");
        printf("3 - enqueue na red\n");
        printf("4 - dequeue s reda\n");
        scanf("%d", &opcija);

        switch (opcija) {

        case 0:
            printf("Program zavrsen.\n");
            break;

        case 1:
            if (_stog < maxS)
                PushStog(&stog, GeneriranjeBroja(10, 100), &_stog);
            else
                printf("Stog je pun!\n");
            IspisListe(stog.next);
            break;

        case 2:
            PopStog(&stog, &_stog);
            IspisListe(stog.next);
            break;

        case 3:
            EnqueueRed(&red, GeneriranjeBroja(10, 100));
            IspisListe(red.next);
            break;

        case 4:
            DequeueRed(&red);
            IspisListe(red.next);
            break;

        default:
            printf("Neispravan izbor!\n");
        }
    }

    return 0;
}

int GeneriranjeBroja(int min, int max) {

    int broj = 0;
    broj = (rand() % (max - min + 1) + min);
    return broj;

}

void PushStog(Pozicija P, int broj, int* _stog) {

    Pozicija q = (Pozicija)malloc(sizeof(struct Cvor));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    q->element = broj;
    q->next = P->next;
    P->next = q;
    (*_stog)++;

}

void PopStog(Pozicija P, int* _stog) {

    if (P->next == NULL) {
        printf("Stog je prazan.\n");
        return;
    }

    Pozicija temp;
    temp = P->next;
    P->next = temp->next;

    free(temp);
    (*_stog)--;
}

void EnqueueRed(Pozicija P, int broj) {

    Pozicija q = (Pozicija)malloc(sizeof(struct Cvor));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    q->element = broj;
    q->prioritet = GeneriranjeBroja(1, 5);

    Pozicija temp = P;
    while ((temp->next != NULL) && (temp->next->prioritet >= q->prioritet))
        temp = temp->next;

    q->next = temp->next;
    temp->next = q;

}

void DequeueRed(Pozicija P) {

    if (P->next == NULL) {
        printf("Red je prazan.\n");
        return;
    }

    Pozicija temp = P->next;
    P->next = temp->next;

    free(temp);
}

void IspisListe(Pozicija P) {

    printf("\nLista:\n");
    while (P) {
        if (P->prioritet)
            printf("%d(%d) ", P->element, P->prioritet);
        else
            printf("%d ", P->element);
        P = P->next;
    }
    printf("\n");
}