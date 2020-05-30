#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "state.h"
#include "scores.h"



// tbd
void sortscores(struct scores *sc) {}

int lookupscore(struct scores *sc, struct state *s) {
    char *r = staterepr(s);
    for (int i = 0; i < sc->n; i++) {
        if (strcmp(r, sc->reprs[i]) == 0) {
            return sc->scores[i];
        }
    }
    return BIGNUM;
}

void printscores(struct scores *sc) {
    for (int i = 0; i < sc->n; i++) {
        printf("score: %d state:\n", sc->scores[i]);
        printkey(sc->reprs[i]);
    }
}

struct scores* add(struct scores *sc, struct state *s, int score) {
    sc->reprs[sc->n] = staterepr(s);
    sc->scores[sc->n] = score;
    sc->n++;
    return sc;
}

struct scores* scoresalloc() {
    return (struct scores *) malloc(sizeof(struct scores));
}
