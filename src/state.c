#include <stdio.h>
#include "state.h"



struct state* nextalloc(struct state *s, Player player, int i, int j) {
    struct state *next = statealloc();
    for (int q = 0; q < SIZE; q++) {
        for (int v = 0; v < SIZE; v++) {
            next ->arr[q][v] = s->arr[q][v];
        }
    }
    next->arr[i][j] = player;
    return next;
}

struct state* statealloc() {
    struct state *s = (struct state*) malloc(sizeof(struct state));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            s->arr[i][j] = EMPTY;
        }
    }
    return s;
}

bool stalemate(struct state *s) {
    return !iswin(s, Player1) && !iswin(s, Player2) && allfilled(s);
}


bool allfilled(struct state *s) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s->arr[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}


bool iswin(struct state *s, Player player) {
    bool row1 = s->arr[0][0] == player && s->arr[0][1] == player && s->arr[0][2] == player;
    bool row2 = s->arr[1][0] == player && s->arr[1][1] == player && s->arr[1][2] == player;
    bool row3 = s->arr[2][0] == player && s->arr[2][1] == player && s->arr[2][2] == player;
    bool col1 = s->arr[0][0] == player && s->arr[1][0] == player && s->arr[2][0] == player;
    bool col2 = s->arr[0][1] == player && s->arr[1][1] == player && s->arr[2][1] == player;
    bool col3 = s->arr[0][2] == player && s->arr[1][2] == player && s->arr[2][2] == player;
    bool diag1 = s->arr[0][0] == player && s->arr[1][1] == player && s->arr[2][2] == player;
    bool diag2 = s->arr[0][2] == player && s->arr[1][1] == player && s->arr[2][0] == player;
    return row1 || row2 || row3 || col1 || col2 || col3 ||diag1 || diag2;
}



bool gameover(struct state *s) {
    return iswin(s, Player1) || iswin(s, Player2) || allfilled(s);
}

int overscore(struct state *s) {
    if (iswin(s, Player1)) return 1;
    else if (iswin(s, Player2)) return -1;
    else return 0;
}

void printstate(struct state* s) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", s->arr[i][j]);
            if ((j + 1) % SIZE == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
}

void printkey(char *repr) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", repr[i * SIZE + j]);
            if ((j+1) % SIZE == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
}

// a string representation of the state, for
// efficient ordering and lookup
char* staterepr(struct state *s) {
    char *r = (char *) malloc(sizeof(char) * SIZE * SIZE);
    for (int i = 0; i < SIZE * SIZE; i++) {
        r[i] = s->arr[i / SIZE][i % SIZE];
    }
    return r;
}
