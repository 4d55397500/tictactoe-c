#include "constants.h"
#include "state.h"
#include "player.h"

#ifndef TICTACTOE_NEXTSTATES_H
#define TICTACTOE_NEXTSTATES_H


struct nextstates {
    struct state states[SIZE*SIZE];
    int n; // number of next states
};

struct nextstates* nextstatesalloc();
struct nextstates* allnext(struct state *, enum Player);


#endif //TICTACTOE_NEXTSTATES_H
