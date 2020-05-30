#include "player.h"
#include "state.h"

#ifndef TICTACTOE_MINIMAX_H
#define TICTACTOE_MINIMAX_H

int minimax(struct state *, enum Player);
struct state* transition(struct state *, enum Player);



#endif //TICTACTOE_MINIMAX_H
