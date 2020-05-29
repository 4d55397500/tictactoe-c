
#include "nextstates.h"


struct nextstates* nextstatesalloc() {
    return (struct nextstates *) malloc(sizeof(nextstates));
}

struct nextstates* allnext(struct state *s, Player player) {
    struct nextstates* ns = nextstatesalloc();
    ns->n = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s->arr[i][j] == EMPTY) {
                ns->states[ns->n] = *nextalloc(s, player, i, j);
                ns->n++;
            }
        }
    }
    return ns;
}