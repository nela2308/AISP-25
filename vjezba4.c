#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct cvor {
    int broj;
    int eks;
    struct cvor* next;
};

void UcitajPolinome(char* imedatoteke1, char* imedatoteke2, struct cvor* P1, struct cvor* P2) {
    FILE* f1, * f2;
    int broj, eks;
    struct cvor* q, * zadnji = NULL;

    f1 = fopen(imedatoteke1, "r");
    if (!f1) { printf("Neuspjesno otvaranje datoteke.\n"); return; }
    zadnji = P1;
    while (fscanf(f1, "%d %d", &broj, &eks) == 2) {
        q = (struct cvor*)malloc(sizeof(struct cvor));
        q->broj = broj;
        q->eks = eks;
        q->next = NULL;
        zadnji->next = q;
        zadnji = q;
    }
    fclose(f1);

    f2 = fopen(imedatoteke2, "r");
    if (!f2) { printf("Neuspjesno otvaranje datoteke.\n"); return; }
    zadnji = P2;
    while (fscanf(f2, "%d %d", &broj, &eks) == 2) {
        q = (struct cvor*)malloc(sizeof(struct cvor));
        q->broj = broj;
        q->eks = eks;
        q->next = NULL;
        zadnji->next = q;
        zadnji = q;
    }
    fclose(f2);
}

void IspisiPolinom(struct cvor* p) {
    p = p->next;
    if (!p) { printf("Polinom je prazan.\n"); return; }
    int prvi = 1;
    while (p) {
        if (!prvi) printf("%s", (p->broj >= 0) ? " + " : " - ");
        else if (p->broj < 0) printf("-");
        prvi = 0;
        int absBroj = (p->broj < 0) ? -p->broj : p->broj;
        if (absBroj != 1 || p->eks == 0) printf("%d", absBroj);
        if (p->eks != 0) { printf("x"); if (p->eks != 1) printf("^%d", p->eks); }
        p = p->next;
    }
    printf("\n");
}

void ZbrojiPolinome(struct cvor* P1, struct cvor* P2, struct cvor* z) {
    struct cvor* zadnji = z;
    while (zadnji->next) zadnji = zadnji->next;
    struct cvor* t1 = P1->next;
    while (t1) {
        struct cvor* t2 = P2->next;
        while (t2 && t2->eks != t1->eks) t2 = t2->next;
        if (t2) {
            struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
            q->broj = t1->broj + t2->broj;
            q->eks = t1->eks;
            q->next = NULL;
            zadnji->next = q;
            zadnji = q;
        }
        t1 = t1->next;
    }
}

void MnozenjePolinoma(struct cvor* P1, struct cvor* P2, struct cvor* p) {
    struct cvor* zadnji = p;
    while (zadnji->next) zadnji = zadnji->next;
    struct cvor* t1 = P1->next;
    while (t1) {
        struct cvor* t2 = P2->next;
        while (t2) {
            struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
            q->broj = t1->broj * t2->broj;
            q->eks = t1->eks + t2->eks;
            q->next = NULL;
            zadnji->next = q;
            zadnji = q;
            t2 = t2->next;
        }
        t1 = t1->next;
    }
}

int main() {
    struct cvor Head1 = { 0,0,NULL }, Head2 = { 0,0,NULL };
    struct cvor ZbrojRez = { 0,0,NULL }, ProduktRez = { 0,0,NULL };

    char imedatoteke1[50], imedatoteke2[50];
    printf("Unesi ime prve datoteke: "); scanf("%s", imedatoteke1);
    printf("Unesi ime druge datoteke: "); scanf("%s", imedatoteke2);

    UcitajPolinome(imedatoteke1, imedatoteke2, &Head1, &Head2);

    printf("Polinom P1:\n"); IspisiPolinom(&Head1);
    printf("Polinom P2:\n"); IspisiPolinom(&Head2);

    ZbrojiPolinome(&Head1, &Head2, &ZbrojRez);
    printf("Zbroj polinoma:\n"); IspisiPolinom(&ZbrojRez);

    MnozenjePolinoma(&Head1, &Head2, &ProduktRez);
    printf("Produkt polinoma:\n"); IspisiPolinom(&ProduktRez);

    return 0;
}