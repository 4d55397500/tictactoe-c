#include "constants.h"
#include "player.h"

#ifndef TICTACTOE_STATE_H
#define TICTACTOE_STATE_H

struct state {
    char arr[SIZE][SIZE];;
};

struct state* nextalloc(struct state *, enum Player, int, int);
struct state* statealloc();
int iswin(struct state *, enum Player);
int stalemate(struct state *);
int allfilled(struct state *);
int gameover(struct state *);
int overscore(struct state *);
void printstate(struct state *);
void printkey(char *);
char* staterepr(struct state *);


#endif //TICTACTOE_STATE_H
