#include <stddef.h>
#include "minimax.h"
#include "player.h"
#include "state.h"
#include "scores.h"
#include "nextstates.h"

int minimax(struct state *s, enum Player player) {
    if (calcscores == NULL) {
        calcscores = scoresalloc();
        calcscores->n = 0;
    }
    int cached = lookupscore(calcscores, s);
    if (cached != BIGNUM) {
        return cached;
    }
    int best = (player == Player1) ? -BIGNUM: BIGNUM;
    if (!gameover(s)) {
        struct nextstates *ns = allnext(s, player);
        int nextscore;
        for (int k = 0; k < ns->n; k++) {
            nextscore = minimax(&ns->states[k], other(player));
            if (player == Player1 && nextscore > best) best = nextscore;
            else if (player == Player2 && nextscore < best) best = nextscore;
        }
    } else {
        best = overscore(s);
    }
    add(calcscores, s, best);
    return best;
}

// learned state transition
struct state* transition(struct state *s, enum Player player) {
    struct nextstates *ns = allnext(s, player);
    int nextscore = (player == Player1) ? -BIGNUM: BIGNUM;
    int candidatescore;
    int candidate = 0;
    for (int i = 0; i < ns->n; i++) {
        candidatescore = lookupscore(calcscores, &ns->states[i]);
        if ((player == Player1 && candidatescore > nextscore) ||
            (player == Player2 && candidatescore < nextscore)) {
            nextscore = candidatescore;
            candidate = i;
        }
    }
    return &ns->states[candidate];
}
