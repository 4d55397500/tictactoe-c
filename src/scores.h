#include "constants.h"
#ifndef TICTACTOE_SCORES_H
#define TICTACTOE_SCORES_H

struct scores {
    char *reprs[MAXNUMSTATES];
    int scores[MAXNUMSTATES];
    int n; // number of states scored so far
};

static struct scores *calcscores;
void sortscores(struct scores *);
int lookupscore(struct scores *, struct state *);
void printscores(struct scores *);
struct scores* add(struct scores *, struct state *,
        int);
struct scores* scoresalloc();

#endif //TICTACTOE_SCORES_H
